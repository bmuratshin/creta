#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include "../../common/box.h"
#include "../../common/hwcommon.h"

	typedef void* yyscan_t;
	struct stmt_t;
	struct zasm_tree_t;
	struct yy_buffer_state;
	struct instr_def_t;

	struct zasm_driver_t {
		zasm_driver_t(const char *fname);
		~zasm_driver_t();


		/******************************************************************************/

		int add_var(const wchar_t *name, box_set_t data);
		int add_instr(const instr_def_t *pinst, box_set_t args);
		int add_bookmark(const wchar_t* name);
		int gencode();

		/******************************************************************************/

		int set_stmt(const char* text);
		void set_in_cf() { in_cf = true; }
		void set_in_xf() { in_cf = false; }
		int parse(const char* text);
		wchar_t* strliteral(char* s);
		static wchar_t charliteral(char* s);

		// обёртка box_mp_t::list, добавляет line
		char** list(long n, ...);
		void outcode(const std::vector<unsigned char>& code, FILE* fl);
		void write64VLuint7(uint64_t val, std::vector<unsigned char>& code, uint64_t &cnt);
		void update64VLuint7(uint64_t val, std::vector<unsigned char>& code, uint64_t& pos);
		void test_stop();


		box_mp_t            mp_;
		std::string         cur_file_;
		int                 lineno_ = 0;
		yy_buffer_state    *buffer_ = NULL;
		std::string         error_;
		std::string         error_tmp_;

		yyscan_t            scanner_;

		struct zasm_tree_t *parse_tree_ = NULL;
		box_set_t           parse_list_ = NULL;

		stmt_t             *stmt_ = NULL;
		bool			    in_cf = true;

		//-- DATA ------------------------------------------------------------------------
		struct data_item_t {
			const wchar_t* name;
			size_t pos;
			size_t len;
		};
		std::vector<uint32_t> data_seg_;
		std::vector<data_item_t*> data_items_;
		std::map<std::wstring, uint64_t> vars_;	// name => addr

		//-- CCODE ------------------------------------------------------------------------
		struct instr_item_t {
			const instr_def_t* instr;
			uint64_t pos;
			char    *args[4];
		};
		std::vector<instr_item_t> ccode_instrs_;
		std::map<std::wstring, uint64_t> ccode_bookmarks_;	// name => pos in ccode_instrs_

		//-- XCODE ------------------------------------------------------------------------
		std::vector<instr_item_t> xcode_instrs_;
		std::map<std::wstring, uint64_t> xcode_bookmarks_;	// name => pos in ccode_instrs_
	};

