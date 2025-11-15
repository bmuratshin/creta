#include "stdafx.h"
#include "c_driver.h"
#include "ccode.h"
#include "QProc.h"
#include "shcall.h"

extern int yyparse(yyscan_t yyscanner, c_driver_t *ptr);


c_driver_t::c_driver_t(const char *fname)
	: parse_list_(NULL)
	, parse_tree_(NULL)
{
	cur_file_ = fname;

	fl_ = fopen(fname, "rt");
	if (NULL == fl_)
		throw "can't open input file";
	yylex_init(&scanner_);
	yyset_in(fl_, scanner_);
}

c_driver_t::~c_driver_t()
{
	yylex_destroy(scanner_);
	scanner_ = NULL;
	fclose(fl_);
	fl_ = NULL;
}

int c_driver_t::parse()
{
	int ret = 0;
	try {
		int ret = yyparse(scanner_, this);
		if (0 == ret)
		{
			parse_tree_ = (TT*)mp_.list_to_array(parse_list_);
			return gencode();
		}
	}
	catch (const char* err)
	{
		ret = -1;
		error_ = err;
	}
	return ret;
}

char **
c_driver_t::list(long n, ...)
{
	char **box;
	va_list ap;
	va_start(ap, n);

	box = mp_.list(n, ap);
	c_tree_t* ptr = (c_tree_t*)box;
	ptr->line_ = yyget_lineno(scanner_) + 1;

	va_end(ap);
	return ((char**)box);
}

int c_driver_t::gencode()
{
	//stmt_ = NEW_SMTH(stmt_t);
	parse_tree_ = (TT*)mp_.list(2, STMT_LIST, mp_.list_to_array(parse_list_));
	code_.c_exp_trace(parse_tree_);
	//stmt_->proc_ = NEW_SMTH_P(qproc_t, (stmt_->code_));
	return 0;
}

int c_driver_t::outcode()
{
	const call_t* pcall = code_.get_smth_callable(L"main");
	if (NULL == pcall)
		return -1;

	const char* tmp = strrchr(cur_file_.c_str(), '.');
	size_t pos = tmp ? tmp - cur_file_.c_str() : cur_file_.length();

	std::string fname = std::string(cur_file_.c_str(), pos);
	fname += ".asm";
	FILE* fl = fopen(fname.c_str(), "w");
	if (NULL == fl)
		throw_("can't create output file");

	code_.outcode(fl);
	fclose(fl);
	return 0;
}

#if 0
int c_driver_t::run()
{
	if (stmt_)
	{
		const call_t *pcall = stmt_->code_.get_smth_callable(L"main");
		if (NULL == pcall)
			return -1;

		box_set_t code = NULL;
		box_set_t *pcode = &code;
		pcall->gencode(stmt_->code_, pcode);
		stmt_->code_.new_inst(NULL, pcode);
		stmt_->code_.set_entry(code);
		stmt_->exec();
	}
	return 0;
}
#endif