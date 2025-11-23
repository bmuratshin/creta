#pragma once

enum c_tree_type {
	STMT_CALL = 1,
	STMT_STMT,
	STMT_RETURN,
	STMT_IDENTIFIER,
	STMT_LITERAL,
	STMT_PROC_DEF,
	STMT_PROC_HEAD,
	STMT_DCL,
	STMT_LIST,
	STMT_ASSIGN,
	STMT_IF,
	STMT_WHILE,
	STMT_SC_VARDEF,
	STMT_STRUCT_DEF,
	STMT_TYPE_DEF,
	STMT_PARAM_DEF,

	STMT_STOR_CLASS,
	STMT_TYPE_QUAL,
	STMT_FUNC_SPEC,
	STMT_ALIGN_SPEC,
	STMT_TYPE_SPEC,

	STMT_BOP_EQ,
	STMT_BOP_NEQ,
	STMT_BOP_GT,
	STMT_BOP_LT,
	STMT_BOP_GTE,
	STMT_BOP_LTE,
	STMT_BOP_PLUS,
	STMT_BOP_LSHIFT,
	STMT_BOP_RSHIFT,
	STMT_BOP_MINUS,
	STMT_BOP_DIV,
	STMT_BOP_TIMES,
	STMT_BOP_MODULO,
	STMT_BOP_AND,
	STMT_BOP_OR,
	STMT_SOP_NOT,
	STMT_BOP_BAND,
	STMT_BOP_BOR,
	STMT_BOP_BXOR,

	STMT_SOP_NEGATE,
	STMT_SOP_PREINC,
	STMT_SOP_PREDEC,
	STMT_SOP_POSTINC,
	STMT_SOP_POSTDEC,
};

#define TT		c_tree_t
struct c_tree_t {
	c_tree_type type_;
	uint32_t    line_;// Achtung! LittleEndian required! (c_driver_t::mk_node)
	union
	{
		struct
		{
			TT	    *name;
			TT **    params;
			intptr_t needpop;
		} call_;
		struct
		{
			const wchar_t	*name;
		} identifier_;
		struct
		{
			char    *box;
		} literal_;
		struct
		{
			TT	   **ret;
			TT	    *head;
			TT      *elems;
		} proc_def_;
		struct
		{
			TT	    *name;
			TT     **params;
			TT     **ret_type;
		} proc_head_;
		struct
		{
			TT     **elems;
		} list_;
		struct
		{
			TT     **lvalue;
			TT    	*rvalue;
			intptr_t op;
		} assign_;
		struct
		{
			TT    	*value;
		} return_;
		struct
		{
			TT      *name;
			TT     **type;
			TT      *value;
		} vardef_;
		struct
		{
			TT    	*expr;
			TT    	*then_code;
			TT    	*else_code;
		} if_;
		struct
		{
			TT    	*expr;
			TT    	*body;
		} while_;
		struct
		{
			TT	    *left;
			TT	    *right;
		} bop_;
		struct
		{
			TT	   **vars;
			TT	   **type;
		} dcl_;
		struct
		{
			TT	    *name;
			intptr_t type;
			TT	   **members;
		} struct_;
		struct
		{
			TT	   *exp;
		} unaryop_;
		struct
		{
			intptr_t prim;
			TT	    *type;
		} type_or_smth_spec_;
	} _;
};


