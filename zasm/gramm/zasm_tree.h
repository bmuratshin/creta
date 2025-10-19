#pragma once

#include "box.h"
#include "../../common/instr.h"

enum zasm_tree_type {
	STMT_LIST=1,
	ZASM_DATAITEM,
	ZASM_INSTR_ARG,
};

#define TT		zasm_tree_t
struct  zasm_tree_t {
	zasm_tree_type type_;
	uint32_t    line_;// Achtung! LittleEndian required! (c_driver_t::list)
	union
	{
		struct
		{
			intptr_t len;
			char    *data;
		} dataitem_;
		struct
		{
			instrArgTypes type;
			char* val;
		} instr_arg_;
	} _;
};


