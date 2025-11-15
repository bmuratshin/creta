#include "stdafx.h"
#include "ccode.h"
#include "c_driver.h"
#include "c_parser.h"
#include "c_tree.h"
//#include "qproc.h"
#include "lctx.h"
#include "shcall.h"
#include "proc.h"

var_item_t *
params_ctx_t::getParam(const wchar_t *pname)
{
	DO_SET(var_item_t *, elt, &params_)
	{
		if (0 == wcscmp(elt->name_, pname))
			return elt;
	}
	END_DO_SET();
	return NULL;
}

var_item_t *
params_ctx_t::addParam(const wchar_t *pname, dataTypes type)
{
	DO_SET(var_item_t *, elt, &params_)
	{
		if (0 == wcscmp(elt->name_, pname))
			return elt;
	}
	END_DO_SET();

	var_item_t *it = (var_item_t *)mp_.alloc(sizeof(var_item_t));
	it->type_ = type;
	it->name_ = mp_.box_string(pname);
	params_ = mp_.box_set_conc(params_, mp_.cons_set(it, NULL));
	it->idx_ = cnt_--;
	return it;
}

var_item_t *
var_ctx_t::addVar(const wchar_t *pname, dataTypes type)
{
	var_item_t *it = (var_item_t *)mp_.alloc(sizeof(var_item_t));
	new (it)var_item_t(mp_.box_string(pname), type);
	it->idx_ = cnt_++;
	assert(ht_locals_.find(pname) == ht_locals_.end());
	ht_locals_[pname] = it;
	return it;
}

var_item_t *
var_ctx_t::getVar(const wchar_t *pname)
{
	auto it = ht_locals_.find(pname);
	if (it == ht_locals_.end())
		return NULL;
	return it->second;
}


proc_def_t::proc_def_t(ccode_t &cc, c_tree_t *exp) 
	: cc_(cc)
	, args_(cc.mp_)
	, vars_(cc.mp_)
{
	box_set_t proccode = NULL;
	box_set_t *pproccode = &proccode;

	{
		ret_type_ = ftInteger32;
		int inx = 0;
		//  parameters
		DO_BOX(TT *, par, inx, exp->_.proc_def_.ret)
		{
			if (STMT_TYPE_SPEC == par->type_)
			{
				switch (par->_.type_or_smth_spec_.prim)
				{
				case VOID:
					ret_type_ = ftUnknown;
					break;
				case CHAR:
				case SHORT:
				case INT:
					ret_type_ = ftInteger32;
					break;
				case LONG:
					ret_type_ = ftInteger64;
					break;
				case FLOAT:
				case DOUBLE:
					ret_type_ = ftDouble;
					break;
				case SIGNED:
				case UNSIGNED:
				case BOOL:
				case COMPLEX:
				case IMAGINARY:
				default:
					assert(0);
				};
			}
		}
		END_DO_BOX;
	}

	TT *head = exp->_.proc_def_.head;
	if (STMT_PROC_HEAD == head->type_)
	{
		name_ = cc_.mp_.box_string(head->_.proc_head_.name->_.identifier_.name);

		int inx = 0;
		//  parameters
		DO_BOX(TT *, par, inx, head->_.proc_head_.params)
		{
			assert(STMT_PARAM_DEF == par->type_);
			assert(STMT_IDENTIFIER == par->_.vardef_.name->type_);
			const wchar_t *par_name = par->_.vardef_.name->_.identifier_.name;

			dataTypes partype = ftUnknown;
			intptr_t attr = 0;
			cc.c_exp_type(par->_.vardef_.type, partype, attr);

			args_.addParam(par_name, partype);
		}
		END_DO_BOX;
	}
	else if (STMT_IDENTIFIER == head->type_)
	{
		name_ = cc_.mp_.box_string(head->_.identifier_.name);
	}
	if (cc.procs_map_.find(metrica()) != cc.procs_map_.end())
	{
		char buf[64];
		sprintf(buf, "Proc:'%.30ls' is already defined", metrica());
		throw_(buf);
	}
	cc.procs_map_[metrica()] = this;

	params_lookup_ctx_t pctx(cc_, args_);
	cc_.lctx_push(&pctx);
	locals_lookup_ctx_t lctx(cc_, vars_);
	cc_.lctx_push(&lctx);
	vars_.setBase(args_.getSize());

	cc_.add_bookmark(pproccode, metrica());

	cc_.c_exp_trace_(exp->_.proc_def_.elems, pproccode);
	cc_.new_inst(NULL, pproccode);
	entry_ = (inst_t**)cc.mp_.revlist_to_array(proccode);

	cc_.lctx_pop();
	cc_.lctx_pop();

}


const wchar_t *
proc_def_t::metrica()
{
	return name_;
}

int 
proc_def_t::get_nargs() const
{
	return box_mp_t::box_set_length(args_.params_);// box_length_inline args_.cnt_;
}

int 
proc_def_t::get_nrealargs() const
{
	return box_mp_t::box_set_length(args_.params_);// box_length_inline args_.cnt_;
//	return args_.cnt_;
}

dataTypes 
proc_def_t::get_arg_type(int idx) const
{
	int ix = 0;
	DO_SET(var_item_t *, elt, &args_.params_)
	{
		if (idx == ix++)
			return elt->type_;
	}
	END_DO_SET();
	return ftUnknown;
}

dataTypes 
proc_def_t::get_ret_type() const
{
	return ret_type_;
}

const wchar_t *
proc_def_t::get_arg_name(int idx) const
{
	int ix = 0;
	DO_SET(var_item_t *, elt, &args_.params_)
	{
		if (idx == ix++)
			return elt->name_;
	}
	END_DO_SET();
	return L"";
}


void proc_def_t::gencode(ccode_t &cc, box_set_t *code) const
{
	cc.new_inst(get_asm_instr(ioCScall, 1), code);
	inst_t *pinst = cc.new_inst(NULL, code);
	pinst->ptr_ = cc.mp_.box_string(get_name());
	inst_t* pinst2 = cc.new_inst(NULL, code);
	pinst2->ival_ = args_.getSize();
	inst_t* pinst3 = cc.new_inst(NULL, code);
	pinst3->ival_ = vars_.getSize();

	cc.tpush(get_ret_type());
}

