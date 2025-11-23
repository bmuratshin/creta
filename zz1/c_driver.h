#pragma once

#include <string>

#include "box.h"
#include "c_tree.h"
#include "ccode.h"

typedef void* yyscan_t;
struct stmt_t;
struct c_tree_t;
struct yy_buffer_state;
struct c_driver_t;

#include "c_parser.h"
#include "c_scanner.h"

struct c_driver_t {
	c_driver_t(const char *fname);
	~c_driver_t();

	int parse();
	int gencode();
	int outcode();
	char **mk_node(long n, ...);
	//	int run();

	FILE               *fl_;
	box_mp_t            mp_;
	yyscan_t            scanner_;
	c_tree_t           *parse_tree_;
	box_set_t           parse_list_;

	ccode_t				code_;

	std::string         cur_file_;
	std::string         error_;
	std::string         error_tmp_;
};