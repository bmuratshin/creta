#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "utils.h"
#include "box.h"
#include "multibyte.h"

#include "zasm_tree.h"
#include "zasm_driver.h"

#include "zasm_parser.h"
#include "zasm_scanner.h"

extern void zasmerror(yyscan_t yyscanner, zasm_driver_t* driver, const char* s);

	zasm_driver_t::zasm_driver_t(const char *fname)
		: parse_list_(NULL)
		, parse_tree_(NULL)
		, stmt_(NULL)
		, cur_file_(fname)
	{

		zasmlex_init(&scanner_);
	}

	zasm_driver_t::~zasm_driver_t()
	{
		zasmlex_destroy(scanner_);
		scanner_ = NULL;

	}

	int zasm_driver_t::set_stmt(const char *text)
	{
		zasmset_extra(this, scanner_);
		buffer_ = zasm_scan_string(text, scanner_);
		zasmset_lineno(0, scanner_);
		//yydebug = 1;
		return 0;
	}


	int zasm_driver_t::parse(const char *text)
	{
		data_seg_.clear();
		data_items_.clear();

		set_stmt(text);


		//yydebug = 1;
		int ret = 0;
		try {
			ret = zasmparse(scanner_, this);
			if (0 == ret) {
				//parse_tree_ = (TT*)mp_.list_to_array(parse_list_);
				return gencode();
			}
		}
		catch (const char *e)
		{
			ret = -1;
			error_ = e;
		}
		return ret;
	}


	char **
		zasm_driver_t::list(long n, ...)
	{
		char **box;
		va_list ap;
		va_start(ap, n);

		box = mp_.list(n, ap);
		zasm_tree_t* ptr = (zasm_tree_t*)box;
		ptr->line_ = zasmget_lineno(scanner_) + 1;

		va_end(ap);
		return ((char **)box);
	}

	int zasm_driver_t::add_var(const wchar_t* name, box_set_t data)
	{
		std::wstring wname(name);
		size_t len = 0;
		DO_SET(TT*, elem, &data)
		{
			len += ALIGN_4(elem->_.dataitem_.len);

			auto it = vars_.find(wname);
			if (it != vars_.end())
				fthrow_("var %ls already declared at line %d", name, lineno_);

			vars_[wname] = data_seg_.size() * sizeof(data_seg_[0]);
		}
		END_DO_SET();

		data_item_t* pv = (data_item_t*)mp_.alloc(sizeof(data_item_t)); data_items_;
		pv->name = name;
		pv->pos = data_seg_.size() * sizeof(data_seg_[0]);
		pv->len = len;
		data_items_.push_back(pv);

		len = 0;
		DO_SET(TT*, elem, &data)
		{
			len = ALIGN_4(elem->_.dataitem_.len);
			uint32_t* tmp = (uint32_t*)elem->_.dataitem_.data;
			for (size_t i = 0; i < len; i += sizeof(int32_t))
			{
				data_seg_.push_back(*tmp++);
			}
		}
		END_DO_SET();

		return 0;
	}

	void zasm_driver_t::test_stop()
	{
		if (in_cf)
		{
			size_t n = ccode_instrs_.size();
			if (n && ccode_instrs_[n - 1].instr->opcode_ != ioCSstop)
			{
				instr_item_t instr{ test_asm_name("stop", in_cf), 0, {0} };
				ccode_instrs_.push_back(instr);
			}
		}
		else {
			size_t n = xcode_instrs_.size();
			if (n && xcode_instrs_[n - 1].instr->opcode_ != ioCXstop)
			{
				instr_item_t instr{ test_asm_name("stop", in_cf), 0, {0} };
				xcode_instrs_.push_back(instr);
			}
		}

	}

	struct bookmark_t {
		const wchar_t* name;
		uint64_t       pos;
	};

	int zasm_driver_t::add_instr(const instr_def_t* pinst, box_set_t args)
	{
		instr_item_t instr;
		instr.instr = pinst;
		instr.pos = 0;

		//printf(" %s: ", pinst->name_);
		unsigned cnt = 0;
		if (args)
		{
			DO_SET(TT*, elem, &args)
			{
				if (cnt >= pinst->nargs_)
					fthrow_("too many args in instruction %s at line %d", pinst->name_, lineno_);

				switch (elem->_.instr_arg_.type) {
				case iatDouble:
					//printf(" %g ", mp_.unbox_double(elem->_.instr_arg_.val));
					break;
				case iatInt:
				case iatLong:
					//printf(" %ld ", (long)mp_.unbox_long(elem->_.instr_arg_.val));
					break;
				case iatString:
					//printf(" '%ls' ", (wchar_t*)elem->_.instr_arg_.val);
					break;
				case iatIdent:
					//printf(" %ls ", (wchar_t*)elem->_.instr_arg_.val);
					break;
				default:
					assert(0);
				};
				instr.args[cnt++] = elem->_.instr_arg_.val;
			}
			END_DO_SET();
		}
		//printf("\n");
		if (cnt < pinst->nargs_)
			fthrow_("too little args in instruction %s at line %d", pinst->name_, lineno_);

		if (in_cf)
			ccode_instrs_.push_back(instr);
		else
			xcode_instrs_.push_back(instr);

		return 0;
	}

	int zasm_driver_t::add_bookmark(const wchar_t* name)
	{
		if (in_cf)
			ccode_bookmarks_[name] = ccode_instrs_.size();
		else
			xcode_bookmarks_[name] = xcode_instrs_.size();
		return 0;
	}

	void zasm_driver_t::outcode(const std::vector<unsigned char>& code, FILE* fl)
	{
		for (int i = 0; i < code.size(); i++)
		{
			fprintf(fl, "%02x ", code[i]);
			if (7 == (i % 8))
				fprintf(fl, "\n");
		}
		fprintf(fl, "\n");
	}

	void zasm_driver_t::write64VLuint7(uint64_t val, std::vector<unsigned char>& code, uint64_t &cnt)
	{
		while (val >= 128) {
			code.push_back((uint8_t)(val & 255) | 0x80);
			cnt++;
			val >>= 7;
		}
		code.push_back((uint8_t)(val & 255));
		cnt++;
	}

	void zasm_driver_t::update64VLuint7(uint64_t val, std::vector<unsigned char>& code, uint64_t& pos)
	{
		while (val >= 128) {
			code[pos++] = (uint8_t)((val & 255) | 0x80);
			val >>= 7;
		}
		code[pos++] = (uint8_t)(val & 255);
	}


	int zasm_driver_t::gencode()
	{
		{
			FILE* fl = fopen("data_segment.mem", "w");
			if (NULL == fl)
				return -1;

			for (size_t i = 0; i < data_seg_.size(); i++)
			{
				uint32_t v = data_seg_[i];
				fprintf(fl, " %08x ", v);
				if ((i & 3) == 3)
					fprintf(fl, "\n");
			}
			fprintf(fl, "\n");
			fclose(fl);
		}
		std::vector<unsigned char> code;
		{
			uint64_t cnt = 0;
			for (size_t i = 0; i < xcode_instrs_.size(); i++)
			{
				instr_item_t& instr = xcode_instrs_[i];
				instr.pos = cnt;
				write64VLuint7(instr.instr->opcode_, code, cnt);
				for (size_t j = 0; j < instr.instr->nargs_; j++)
				{
					switch (instr.instr->arg_types_[j]) {
						break;
					case iatInt:
					case iatLong:
					{
						uint64_t val = (uint64_t)mp_.unbox_long(instr.args[j]);
						write64VLuint7(val, code, cnt);
						break;
					}
					case iatDAddr:
					{
						const wchar_t* name = (const wchar_t*)instr.args[j];
						auto it = vars_.find(name);
						if (it == vars_.end())
							fthrow_("undefined variable '%ls' at line %d", name, lineno_);
						write64VLuint7(it->second, code, cnt);
						break;
					}
					case iatString:
					case iatDouble:
					default:
						assert(0);
					};
				}
			}

			for (auto& it : xcode_bookmarks_)
			{
				uint64_t ix = it.second;
				instr_item_t& instr = xcode_instrs_[ix];
				it.second = instr.pos;
			}

			std::vector<bookmark_t> cs_bookmarks;
			for (size_t i = 0; i < ccode_instrs_.size(); i++)
			{
				instr_item_t& instr = ccode_instrs_[i];
				instr.pos = cnt;
				write64VLuint7(instr.instr->opcode_, code, cnt);
				for (size_t j = 0; j < instr.instr->nargs_; j++)
				{
					switch (instr.instr->arg_types_[j]) {
						break;
					case iatInt:
					case iatLong:
					{
						uint64_t val = (uint64_t)mp_.unbox_long(instr.args[j]);
						write64VLuint7(val, code, cnt);
						break;
					}
					case iatXAddr:
					{
						const wchar_t* name = (const wchar_t*)instr.args[j];
						auto it = xcode_bookmarks_.find(name);
						if (it == xcode_bookmarks_.end())
							fthrow_("undefined reference '%ls' at line %d", name, lineno_);
						uint64_t addr = it->second;
						write64VLuint7(addr, code, cnt);
						break;
					}
					case iatCAddr:
					{
						const wchar_t* name = (const wchar_t*)instr.args[j];
						auto it = ccode_bookmarks_.find(name);
						if (it == ccode_bookmarks_.end())
							fthrow_("undefined reference '%ls' at line %d", name, lineno_);

						bookmark_t bm {name, cnt};
						cs_bookmarks.push_back(bm);
						// dummy nops to substitute later by actual addr
						write64VLuint7(ioCSnop, code, cnt);
						write64VLuint7(ioCSnop, code, cnt);
						break;
					}
					case iatString:
					case iatDouble:
					default:
						assert(0);
					};
				}
			}

			for (auto& it : ccode_bookmarks_)
			{
				uint64_t ix = it.second;
				instr_item_t& instr = ccode_instrs_[ix];
				it.second = instr.pos;
			}

			for (const auto& it : cs_bookmarks)
			{
				auto bit = ccode_bookmarks_.find(it.name);
				assert(bit != ccode_bookmarks_.end());
				uint64_t bkaddr = bit->second;
				uint64_t pos = it.pos;
				//printf("bookmark %ls, %lx => %lx\n", it.name, (long)bkaddr, (long)pos);
				update64VLuint7(bkaddr, code, pos);
			}


			FILE* fl = fopen("rom_image.mem", "w");
			if (NULL == fl)
				return -1;

			outcode(code, fl);
			fclose(fl);
		}

		{
			std::string fname = cur_file_ + ".map";
			FILE* fl = fopen(fname.c_str(), "w");
			if (NULL == fl)
				return -1;

			fprintf(fl, "DATA:\n");
			for (const auto it: vars_)
			{
				fprintf(fl, "\t %ls: 0x%llx\n", it.first.c_str(), it.second);
			}

			fprintf(fl, "\n");
			fclose(fl);
		}

		{
			auto bit = ccode_bookmarks_.find(L"initial");
			if (bit != ccode_bookmarks_.end())
				printf("Initial code address: 0x%lx\n", (long)bit->second);

			printf("Stack start position: 0x%lx\n", (long)(data_seg_.size() * sizeof (data_seg_[0])));

		}

		return 0;
	}


	wchar_t zasm_driver_t::charliteral(char *s)
	{
		const unsigned maxlen = 6;
		wchar_t wstr[maxlen];
		unsigned char **src = (unsigned char **)&s;
		int64_t len = dest_mbsnrtowcs(wstr, src, strlen(s), maxlen) / sizeof(wchar_t);
		if (len < 0)
			throw ("error in utf-8 literal parse");
		if (len < maxlen)
			wstr[len] = L'\0';

		wchar_t *tmp = wstr;
		len = parse_string_literal(&tmp, NULL, L'\'');
		wchar_t buf[4];
		tmp = wstr;
		parse_string_literal((wchar_t **)&tmp, buf, L'\'');
		return buf[0];
	}


	wchar_t *
		zasm_driver_t::strliteral(char *s)
	{
		wchar_t *start = mp_.box_string(s);
		wchar_t *tmp = start;
		int64_t len = parse_string_literal(&start, NULL);

		wchar_t *box = (wchar_t *)mp_.alloc_box(int(sizeof(wchar_t) * (len + 1)), BT_STRING);
		parse_string_literal((wchar_t **)&tmp, box);
		box[len] = 0;
		return (wchar_t *)box;
	}



