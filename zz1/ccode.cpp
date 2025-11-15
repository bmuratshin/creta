#include "stdafx.h"
#include "dataTypes.h"
#include "box.h"
#include "ccode.h"
#include "c_tree.h"
//#include "qproc.h"
#include "lctx.h"
#include "shcall.h"
#include "c_driver.h"
#include "c_parser.h"
#include "proc.h"
#include "hwcommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

#ifndef DEBUG_NEW
#	define DEBUG_NEW new
#endif

const_impl_t::const_impl_t(int val)
{
	type_ = ftInteger32;
	val_.ival = val;
}
const_impl_t::const_impl_t(int64_t val)
{
	type_ = ftInteger64;
	val_.lval = val;
}
const_impl_t::const_impl_t(double val)
{
	type_ = ftDouble;
	val_.dval = val;
}
//const_impl_t::const_impl_t(const wchar_t *val)
//{
//	type_ = ftString;
//	val_.Sval = NEW_SMTH_P(decore::str_t, (val));
//}

var_item_t::var_item_t(const wchar_t *name, dataTypes type)
	: name_(name)
	, type_(type)
	, idx_(0)
{
	data_.lval = 0;
	switch (type_) {
	case ftInteger16:
	case ftInteger32:
	case ftInteger64:
	case ftDouble:
		break;
	//case ftString:
	//	data_.Sval = NEW_SMTH(decore::str_t);
	//	break;
	default:
		throw_("variable of invalid type");
	};
}

ccode_t::ccode_t()
{
	consts_ = NULL;
	tstackp_ = 0;
	stream_entry_ = NULL;
	// close_entries_ = NULL;

	stmt_text_ = NULL;

	lookup_ctx_ = NULL;
	cur_inst_ = 0;

	globs_ = (var_ctx_t*)mp_.alloc(sizeof(var_ctx_t));
	new (globs_)var_ctx_t(mp_);
	globals_ctx_ = (locals_lookup_ctx_t *)mp_.alloc(sizeof(locals_lookup_ctx_t));
	new (globals_ctx_)locals_lookup_ctx_t(*this, *globs_);
	lctx_push(globals_ctx_);
}

ccode_t::~ccode_t()
{
	for (auto it : procs_map_)
	{
		it.second->~proc_def_t();
	}
	/*
	DO_SET(const_impl_t *, cnst, &consts_)
	{
		if (ftString == cnst->type_)
		{
			DEL_SMTH(decore::str_t, cnst->val_.Sval);
		}
	}
	END_DO_SET();
	*/
}

const instr_def_t *ccode_t::cvrt_arr1_[max_intypes_][max_intypes_] = {
	{ get_asm_instr(ioCXnop, false), get_asm_instr(ioCXnop, false), NULL },                         // int32
	{ get_asm_instr(ioCXnop, false), get_asm_instr(ioCXnop, false), NULL },                         // int64
	{ NULL,                          NULL,                          get_asm_instr(ioCXnop, false)}, // double
};

const instr_def_t* ccode_t::cvrt_arr2_[max_intypes_][max_intypes_] = {
	{ get_asm_instr(ioCXnop, false), get_asm_instr(ioCXnop, false), NULL },                         // int32
	{ get_asm_instr(ioCXnop, false), get_asm_instr(ioCXnop, false), NULL },                         // int64
	{ NULL,                          NULL,                          get_asm_instr(ioCXnop, false)}, // double
};

const instr_def_t *ccode_t::a_assign_[max_intypes_] = {
	get_asm_instr(ioCXassign, false),
	get_asm_instr(ioCXassign, false),
	get_asm_instr(ioCXassign, false),
 };

const instr_def_t *ccode_t::a_varpushd_[max_intypes_] = {
	get_asm_instr(ioCXvarpushd, false),
	get_asm_instr(ioCXvarpushd, false),
	get_asm_instr(ioCXvarpushd, false),
};

const instr_def_t *ccode_t::a_varpush_[max_intypes_] = {
	get_asm_instr(ioCXvarpush, false),
	get_asm_instr(ioCXvarpush, false),
	get_asm_instr(ioCXvarpush, false),
};

const instr_def_t* ccode_t::a_locpushd_[max_intypes_] = {
	get_asm_instr(ioCXlocpushd, false),
	get_asm_instr(ioCXlocpushd, false),
	get_asm_instr(ioCXlocpushd, false),
};

const instr_def_t* ccode_t::a_locpush_[max_intypes_] = {
	get_asm_instr(ioCXlocpush, false),
	get_asm_instr(ioCXlocpush, false),
	get_asm_instr(ioCXlocpush, false),
};

const instr_def_t *ccode_t::a_add_[max_intypes_] = {
	get_asm_instr(ioCXadd, false),
	get_asm_instr(ioCXadd, false),
	NULL,
};

const instr_def_t *ccode_t::a_neg_[max_intypes_] = {
	get_asm_instr(ioCXneg, false),
	get_asm_instr(ioCXneg, false),
	NULL,
};

const instr_def_t *ccode_t::a_sub_[max_intypes_] = {
	get_asm_instr(ioCXsub, false),
	get_asm_instr(ioCXsub, false),
	NULL,
};

const instr_def_t *ccode_t::a_mul_[max_intypes_] = {
	get_asm_instr(ioCXmul, false),
	get_asm_instr(ioCXdiv, false),
	NULL,
};

const instr_def_t *ccode_t::a_div_[max_intypes_] = {
	get_asm_instr(ioCXdiv, false),
	get_asm_instr(ioCXdiv, false),
	NULL,
};

const instr_def_t *ccode_t::a_eq_[max_intypes_] = {
	get_asm_instr(ioCXeq, false),
	get_asm_instr(ioCXeq, false),
	NULL,
};

const instr_def_t *ccode_t::a_ne_[max_intypes_] = {
	get_asm_instr(ioCXne, false),
	get_asm_instr(ioCXne, false),
	NULL,
};

const instr_def_t *ccode_t::a_gt_[max_intypes_] = {
	get_asm_instr(ioCXgt, false),
	get_asm_instr(ioCXgt, false),
	NULL,
};

const instr_def_t *ccode_t::a_ge_[max_intypes_] = {
	get_asm_instr(ioCXge, false),
	get_asm_instr(ioCXge, false),
	NULL,
};

const instr_def_t *ccode_t::a_lt_[max_intypes_] = {
	get_asm_instr(ioCXlt, false),
	get_asm_instr(ioCXlt, false),
	NULL,
};

const instr_def_t *ccode_t::a_le_[max_intypes_] = {
	get_asm_instr(ioCXle, false),
	get_asm_instr(ioCXle, false),
	NULL,
};

const instr_def_t *ccode_t::a_predec_[max_intypes_] = {
	get_asm_instr(ioCXdec, false),
	get_asm_instr(ioCXdec, false),
	NULL,
};

const instr_def_t *ccode_t::a_preinc_[max_intypes_] = {
	get_asm_instr(ioCXinc, false),
	get_asm_instr(ioCXinc, false),
	NULL,
};


const instr_def_t *ccode_t::a_postdec_[max_intypes_] = {
	get_asm_instr(ioCXpostdec, false),
	get_asm_instr(ioCXpostdec, false),
	NULL,
};

const instr_def_t *ccode_t::a_postinc_[max_intypes_] = {
	get_asm_instr(ioCXpostinc, false),
	get_asm_instr(ioCXpostinc, false),
	NULL,
};

bool
ccode_t::has_ctor(dataTypes t)
{
	switch (t) {
	case ftInteger16:
	case ftInteger32:
	case ftInteger64:
	case ftFloat:
	case ftDouble:
		return false;
	//case ftString:
	//	return true;
	default:
		throw_("unsupported type conversion");
	};
	return false;
}

int
ccode_t::type2intidx(dataTypes type)
{
	switch (type) {
	case ftInteger16:
	case ftInteger32:
		return 0;
	case ftInteger64:
		return 1;
	case ftFloat:
	case ftDouble:
		return 2;
	//case ftString:
	//	return 3;

	default:
	case 	ftUnknown:
		throw_("unsupported type conversion");
	};
	assert(0);
	return -1;
}

dataTypes
ccode_t::t1(void)
{
	assert(tstackp_ > 1);
	return tstack_[tstackp_ - 2];
}

dataTypes
ccode_t::t2(void)
{
	assert(tstackp_ > 0);
	return tstack_[tstackp_ - 1];
}



void
ccode_t::tpush(dataTypes type)
{
	if (tstackp_ >= max_tstack_)
		throw_("tstack too deep");
	tstack_[tstackp_++] = type;
}

dataTypes
ccode_t::tpop(void)
{
	if (0 == tstackp_)
		throw_("tstack underflow");
	dataTypes ret = tstack_[--tstackp_];
	tstack_[tstackp_] = ftUnknown;
	return ret;
}

inst_t *
ccode_t::tcheck(const instr_def_t** procs, box_set_t *code)
{
	was_cons1_ = false;
	was_cons2_ = false;
	dataTypes i1, i2;
	int j1, j2, j3 = 0;
	const instr_def_t *proc;

	i1 = tpop();
	i2 = tpop();
	j1 = type2intidx(i1);
	j2 = type2intidx(i2);

	if (i1 != i2)
	{
		if (j1 > j2)
		{
			j3 = j1;
			tpush(i1);
			proc = cvrt_arr1_[j2][j3];
		}
		else
		{
			j3 = j2;
			tpush(i2);
			proc = cvrt_arr2_[j1][j3];
		}
		if (NULL != proc)
		{
			new_inst(proc, code);
			if (proc != get_asm_instr(ioCXnop, false))
			{
				was_cons2_ = true;
				conscode(2, code);
			}
			else
				was_cons2_ = false;
		}
		else
			throw_("unresolved type conversion N3");
	}
	else
	{
		tpush(i1);
		j3 = j1;
	}
	proc = procs[j3];
	if (0 == proc)
		throw_("type mismatch N1");
	return new_inst(proc, code);
}

inst_t *
ccode_t::tcheck1(const instr_def_t **procs, box_set_t *code)
{
	int i1;
	dataTypes i2;
	const instr_def_t *proc;

	i2 = t2();
	i1 = type2intidx(i2);
	proc = procs[i1];

	if (0 == proc)
		throw_("type mismatch N2");
	return new_inst(proc, code);
}

void
ccode_t::cvrt1(dataTypes t, box_set_t *code)
{
	int j1, j2;
	dataTypes i1, i2;
	const instr_def_t *proc;

	i1 = tpop();
	i2 = tpop();
	j1 = type2intidx(i1);
	j2 = type2intidx(t);

	if (i2 != t)
		throw_("mtypes mismatch");

	tpush(t);

	if (i1 == i2)
		return;

	if ((proc = cvrt_arr1_[j1][j2]) != 0)
	{
		new_inst(proc, code);
		if (proc != get_asm_instr(ioCXnop, false))
		{
			was_cons1_ = true;
			conscode(1, code);
		}
		else
			was_cons2_ = false;
		return;
	}
	else
		throw_("unresolved type conversion N1");
}

void
ccode_t::cvrt2(dataTypes t, box_set_t *code)
{
	dataTypes i2;
	int j1, j2;
	const instr_def_t *proc;

	if (ftUnknown == t)
		return;

	i2 = tpop();
	j1 = type2intidx(i2);
	j2 = type2intidx(t);
	tpush(t);

	if (t == i2)
		return;

	if ((proc = cvrt_arr2_[j1][j2]) != 0)
	{
		new_inst(proc, code);
		if (get_asm_instr(ioCXnop, false) != proc)
		{
			was_cons2_ = true;
			conscode(2, code);
		}
		else
			was_cons2_ = false;
	}
	else
		throw_("unresolved type conversion N2");
}

int
ccode_t::conscode(int n, box_set_t *code)
{
	dataTypes ht;
	switch (n) {
	case 1:
		if (was_cons1_)
			return 0;
		ht = t1();
		break;
	case 2:
		if (was_cons2_)
			return 0;
		ht = t2();
		break;
	default:
		assert(0);
		return -1;
	};
	if (!has_ctor(ht))
		return 0;
//	switch (n) {
//	case 1:
//		new_inst(qproc_t::inst_str_ctor1, code);
//		break;
//	case 2:
//		new_inst(qproc_t::inst_str_ctor2, code);
//		break;
//	};
	return 0;
}

int
ccode_t::descode(box_set_t *code)
{
	dataTypes ht = t2();
	if (!has_ctor(ht))
		return 0;
	//switch (ht) {
	//case ftString:
	//	new_inst(qproc_t::inst_str_dtor, code);
	//	break;
	//default:
		assert(0);
	//};
	return 0;
}


void
ccode_t::c_exp_trace(TT * exp)
{
	box_set_t code = NULL;
	box_set_t *pcode = &code;

	c_exp_trace(exp, pcode);

	new_inst(NULL, pcode);
	set_entry(code);
}

void
ccode_t::c_exp_trace(c_tree_t *exp, box_set_t *pcode)
{
	tag_t tag = BT_TYPE_OF(exp);
	switch (tag) {
	case BT_LIST_OF_POINTER:
	case BT_ARRAY_OF_POINTER:
	{
		switch (exp->type_)
		{
		case STMT_CALL:
		{
			assert(0 == tstackp_);
			tstackp_ = 0;
			/*const shcall_t *sh =*/ c_call_exp(exp, pcode);

			assert(1 == exp->_.call_.needpop);
			break;
		}
		case STMT_RETURN:
		{
			scalar_exp_generate(exp->_.return_.value, pcode);
			new_inst(get_asm_instr(ioCSret, true), pcode);
			tpop();
			break;
		}
		case STMT_TYPE_DEF:
		{
			break;
		}
		case STMT_STRUCT_DEF:
		{
			break;
		}
		case STMT_LIST:
		{
			int inx = 0;
			DO_BOX(TT *, elem, inx, exp->_.list_.elems)
			{
				c_exp_trace(elem, pcode);
			}
			END_DO_BOX;
			break;
		}
		default:
			c_exp_trace_(exp, pcode);
			//assert (0);
		}
		break;
	}
	default:
		assert(0);
	};
}

void
ccode_t::c_exp_trace_(TT * exp, box_set_t *pcode)
{
	tag_t tag = BT_TYPE_OF(exp);
	switch (tag) {
	case BT_LIST_OF_POINTER:
	case BT_ARRAY_OF_POINTER:
	{
		switch (exp->type_)
		{
		case STMT_WHILE:
		{
			///*inst_t *pinst =*/ new_inst(qproc_t::inst_whilecode, pcode);
			/*inst_t *pinst =*/ new_inst(NULL, pcode);
			inst_t *pinst1 = new_inst(NULL, pcode);
			inst_t *pinst2 = new_inst(NULL, pcode);

			box_set_t testcode = NULL;
			box_set_t *ptestcode = &testcode;
			scalar_exp_generate(exp->_.while_.expr, ptestcode);
			new_inst(NULL, ptestcode);
			pinst1->ptr_ = mp_.revlist_to_array(testcode);

			box_set_t bodycode = NULL;
			box_set_t *pbodycode = &bodycode;
			c_exp_trace_(exp->_.while_.body, pbodycode);
			new_inst(NULL, pbodycode);
			pinst2->ptr_ = mp_.revlist_to_array(bodycode);

			break;
		}
		case STMT_STMT:
		{
			c_exp_trace_(exp->_.unaryop_.exp, pcode);
			break;
		}
		case STMT_IF:
		{
			char buf[64];
			ifcnt_++;

			scalar_exp_generate(exp->_.if_.expr, pcode);
			cvrt2(ftInteger32, pcode);
			tpop();

			/*inst_t *pinst =*/ new_inst(get_asm_instr(ioCSif, true), pcode);
			inst_t *pinst1 = new_inst(NULL, pcode);

			box_set_t thencode = NULL;
			box_set_t *pthencode = &thencode;
			sprintf(buf, "@thencode_%d", ifcnt_);
			add_bookmark(pthencode, mp_.box_string(buf));
			c_exp_trace_(exp->_.if_.then_code, pthencode);

			box_set_t elsecode = NULL;
			box_set_t *pelsecode = &elsecode;
			if (NULL != exp->_.if_.else_code)
			{
				sprintf(buf, "@elsecode_%d", ifcnt_);
				add_bookmark(pelsecode, mp_.box_string(buf));
				c_exp_trace_(exp->_.if_.else_code, pelsecode);
			}

			size_t then_len = box_mp_t::box_set_length(thencode);
			size_t else_len = box_mp_t::box_set_length(elsecode);

			sprintf(buf, "@endif_%d", ifcnt_);
			const wchar_t* endif = mp_.box_string(buf);

			if (else_len)
			{
				new_inst(get_asm_instr(ioCSgoto, true), pthencode);
				inst_t *gotocode = new_inst(NULL, pthencode);
				gotocode->ptr_ = endif;
			}
			else
			{
				pinst1->ptr_ = endif;
			}
			*pcode = mp_.box_set_conc(thencode, *pcode);
			*pcode = mp_.box_set_conc(elsecode, *pcode);
			add_bookmark(pcode, endif);
			break;
		}
		case STMT_CALL:
		{
			c_call_exp(exp, pcode);
			break;
		}
		case STMT_RETURN:
		{
			scalar_exp_generate(exp->_.return_.value, pcode);
			new_inst(get_asm_instr(ioCSret, true), pcode);
			tpop();
			break;
		}
		case STMT_PROC_HEAD:
		{
			break;
		}
		case STMT_PROC_DEF:
		{
			proc_def_t *proc = (proc_def_t *)mp_.alloc(sizeof(proc_def_t));
			new (proc) proc_def_t(*this, exp);
			assert(procs_map_.find(proc->metrica()) != procs_map_.end());
			break;
		}
		case STMT_SC_VARDEF:
		{
			const wchar_t *name = exp->_.vardef_.name->_.identifier_.name;
			dataTypes type = ftUnknown;
			tag_t dtp2 = BT_TYPE_OF(exp->_.vardef_.type);
			if (BT_INT == dtp2)
			{
				type = dataTypes(mp_.unbox_int(exp->_.vardef_.type));
			}
			lookup_ctx_->add_trivial_var(name, type);
			break;
		}
		case STMT_LIST:
		{
			int inx = 0;
			DO_BOX(TT *, elem, inx, exp->_.list_.elems)
			{
				c_exp_trace_(elem, pcode);
				if (tstackp_)
				{
					new_inst(get_asm_instr(ioCXpop, false), pcode);
					tpop();
				}
				//printf("<%d>", tstackp_);
			}
			END_DO_BOX;
			break;
		}
		case STMT_ASSIGN:
		{
			TT *lvalue = *exp->_.assign_.lvalue;
			assert(NULL != lvalue);
			const wchar_t *name = lvalue->_.identifier_.name;

			box_set_t varcode = NULL;
			box_set_t *pvarcode = &varcode;

			dataTypes dt;
			bool bf = lookup_ctx_->find_col_and_gencode(name, true, dt, pvarcode);
			if (!bf)
				throw_("unresolved symbol");

			scalar_exp_generate(exp->_.assign_.rvalue, pcode);
			cvrt2(dt, pcode);

			*pcode = mp_.box_set_conc(varcode, *pcode);

			tcheck(a_assign_, pcode);
			descode(pcode);
			new_inst(get_asm_instr(ioCXpop, false), pcode);
			tpop();

			break;
		}
		case STMT_DCL:
		{
			dataTypes partype = ftUnknown;
			intptr_t attr = 0;
			c_exp_type(exp->_.dcl_.type, partype, attr);

			if (ftUnknown != partype)
			{
				int inx = 0;
				DO_BOX(TT *, elem, inx, exp->_.dcl_.vars)
				{
					if (STMT_IDENTIFIER == elem->type_)
					{
						const wchar_t *name = elem->_.identifier_.name;
						lookup_ctx_->add_trivial_var(name, partype);
					}
				}
				END_DO_BOX;
			}
			break;
		}
		case STMT_SOP_PREINC:
		{
			break;
		}
		case STMT_SOP_PREDEC:
		{
			break;
		}
		case STMT_SOP_POSTINC:
		{
			scalar_exp_generate(exp->_.unaryop_.exp, pcode);
			tcheck1(a_postinc_, pcode);
			break;
		}
		case STMT_SOP_POSTDEC:
		{
			break;
		}
		default:
			c_exp_trace(exp, pcode);
			//assert (0);
		}
		break;
	}
	};
}

const call_t *ccode_t::get_smth_callable(const wchar_t *name) const
{
	const call_t *pcall = reinterpret_cast<const call_t *>(get_shcall(name));
	if (NULL == pcall)
	{
		auto it = procs_map_.find(name);
		if (it != procs_map_.end())
			return it->second;
	}
	return pcall;
}

const call_t *
ccode_t::c_call_exp(c_tree_t *tree, box_set_t *code)
{
	assert(STMT_CALL == tree->type_);
	char buf[64];
	const wchar_t *name = tree->_.call_.name->_.identifier_.name;
	const call_t *pcall = get_smth_callable(name);
	if (NULL == pcall)
	{
		sprintf(buf, "Unresolved symbol:'%.30ls'", name);
		throw_(buf);
	}

	TT **act_params = tree->_.call_.params;
	int n_params = act_params ? BOX_ELEMENTS(act_params) : 0;
	int inx = 0;
	if (n_params != pcall->get_nargs())
	{
		sprintf(buf, "'%.30ls' requires %d args but not %d", name, pcall->get_nargs(), n_params);
		throw_(buf);
	}

	DO_BOX(TT *, par, inx, act_params)
	{
		scalar_exp_generate(par, code);
		dataTypes dt = pcall->get_arg_type(inx);
		cvrt2(dt, code);
		if (ftUnknown == dt)
		{
			new_inst(get_asm_instr(ioCXimdpush, false), code);
			inst_t *pinst = new_inst(NULL, code);
			pinst->ival_ = t2();
		}
		tpop();
	}
	END_DO_BOX;

	pcall->gencode(*this, code);
	//new_inst(qproc_t::inst_shcall, code);
	//inst_t *pinst = new_inst(NULL, code);
	//pinst->ptr_ = pcall;

	//tpush(pcall->get_ret_type());

	if (0 != tree->_.call_.needpop)
	{
		descode(code);
		new_inst(get_asm_instr(ioCXpop, false), code);
		tpop();
	}
	return pcall;
}



void
ccode_t::scalar_exp_generate(c_tree_t * exp, box_set_t *code)
{
	TT *tree = exp;
	tag_t tag = BT_TYPE_OF(exp);
	switch (tag) {
	case BT_LONG_INT:
	case BT_INT:
	{
		const_impl_t *cnst = (const_impl_t *)mp_.alloc(sizeof(const_impl_t));
		new (cnst)const_impl_t((int64_t)box_mp_t::unbox_int(tree));
		mp_.set_push(&consts_, cnst);
		new_inst(/*(BT_INT == tag) ?*/ get_asm_instr(ioCXimdpush, false), code);
		inst_t *pinst = new_inst(NULL, code);
		pinst->ival_ = cnst->val_.lval;
		tpush((BT_INT == tag) ? ftInteger32 : ftInteger64);
		break;
	}
	case BT_STRING:
	{
//		const_impl_t *cnst = (const_impl_t *)mp_.alloc(sizeof(const_impl_t));
//		new (cnst)const_impl_t(box_mp_t::unbox_string(tree));
//		mp_.set_push(&consts_, cnst);
//		new_inst(qproc_t::inst_constpush_typed, code);
//		inst_t *pinst = new_inst(NULL, code);
//		pinst->data_ = &cnst->val_;
//		pinst = new_inst(NULL, code);
//		pinst->ival_ = ftString;
//		tpush(ftString);
		break;
	}
	case BT_DOUBLE:
	{
		const_impl_t *cnst = (const_impl_t *)mp_.alloc(sizeof(const_impl_t));
		new (cnst)const_impl_t(box_mp_t::unbox_double(tree));
		mp_.set_push(&consts_, cnst);
		new_inst(get_asm_instr(ioCXvarpushd, false), code);
		inst_t *pinst = new_inst(NULL, code);
		pinst->data_ = &cnst->val_;
		tpush(ftDouble);
		break;
	}
	case BT_LIST_OF_POINTER:
	case BT_ARRAY_OF_POINTER:
	{
		switch (exp->type_) {
		case STMT_CALL:
		{
			c_call_exp(exp, code);
			break;
		}
		case STMT_RETURN:
		{
			scalar_exp_generate(exp->_.return_.value, code);
			new_inst(get_asm_instr(ioCSret, true), code);
			tpop();
			break;
		}
		//case STMT_PARAMETER:
		case STMT_IDENTIFIER:
		{
			const wchar_t *name = exp->_.identifier_.name;
			dataTypes type = ftUnknown;
			bool bfound = lookup_ctx_->find_col_and_gencode(name, false, type, code);
			if (!bfound)
				throw_("unresolved symbol");
			break;
		}
		case STMT_BOP_EQ:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_eq_, code);
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_BOP_NEQ:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_ne_, code);
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_BOP_GT:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_gt_, code);
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_BOP_LT:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_lt_, code);
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_BOP_GTE:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_ge_, code);
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_BOP_LTE:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_le_, code);
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_BOP_PLUS:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_add_, code);
			break;
		}
		case STMT_BOP_MINUS:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_sub_, code);
			break;
		}
		case STMT_BOP_DIV:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_div_, code);
			break;
		}
		case STMT_BOP_TIMES:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			tcheck(a_mul_, code);
			break;
		}
		case STMT_BOP_AND:
		{
			scalar_exp_generate(exp->_.bop_.left, code);

			int ci = cur_inst_;
			new_inst(get_asm_instr(ioCXpreand, false), code);
			inst_t *pinst = new_inst(NULL, code);

			scalar_exp_generate(exp->_.bop_.right, code);
			new_inst(get_asm_instr(ioCXand, false), code);

			pinst->ival_ = cur_inst_ - ci - 1;

			tpop();
			tpop();
			tpush(ftInteger32);

			break;
		}
		case STMT_BOP_OR:
		{
			scalar_exp_generate(exp->_.bop_.left, code);

			int ci = cur_inst_;
			new_inst(get_asm_instr(ioCXpreor, false), code);
			inst_t *pinst = new_inst(NULL, code);

			scalar_exp_generate(exp->_.bop_.right, code);
			new_inst(get_asm_instr(ioCXor, false), code);

			pinst->ival_ = cur_inst_ - ci - 1;

			tpop();
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_BOP_BXOR:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			scalar_exp_generate(exp->_.bop_.right, code);
			new_inst(get_asm_instr(ioCXxor, false), code);
			tpop();
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_SOP_NOT:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			new_inst(get_asm_instr(ioCXnot, false), code);
			tpop();
			tpush(ftInteger32);
			break;
		}
		case STMT_SOP_NEGATE:
		{
			scalar_exp_generate(exp->_.bop_.left, code);
			tcheck1(a_neg_, code);
			break;
		}
		};
		break;
	}
	};
}

void ccode_t::c_exp_type(c_tree_t **exp, dataTypes &dt, intptr_t &attr)
{
	tag_t tag = BT_TYPE_OF(exp);
	assert(BT_ARRAY_OF_POINTER == tag);

	int inx2 = 0;
	dt = ftUnknown;
	attr = 0;
	DO_BOX(TT *, decl, inx2, exp)
	{
		if (NULL == decl->_.type_or_smth_spec_.type)
		{
			size_t type = decl->_.type_or_smth_spec_.prim;
			switch (type) {
			case VOID:
				break;
			case BOOL:
			case CHAR:
			case SHORT:
			case INT:
			case SIGNED:
			case UNSIGNED:
				dt = ftInteger32;
				break;
			case LONG:
				dt = ftInteger64;
				break;
			case FLOAT:
				dt = ftFloat;
				break;
			case DOUBLE:
				dt = ftDouble;
				break;
			case COMPLEX:
			case IMAGINARY:
				break;
			default:
				assert(0);
				break;
			};
		}
	}
	END_DO_BOX;
}

inst_t *
ccode_t::new_inst(const instr_def_t* instr, box_set_t *code)
{
	//if (instr && ioCXnop == instr->opcode_)
	//	return NULL;
	cur_inst_++;
	inst_t* ptr = (inst_t*)mp_.alloc(sizeof(inst_t));
	ptr->instr_ = instr;
	mp_.set_push(code, (void*)ptr);
	assert(((*code)->data) == ptr);
	return (inst_t *)((*code)->data);
}

void 
ccode_t::add_bookmark(box_set_t* code, const wchar_t* name)
{
	inst_t* pit = new_inst(get_asm_instr(ioCSnop, 1), code);
	pit->bookmark_ = name;
}

void
ccode_t::set_entry(box_set_t code)
{
	stream_entry_ = (inst_t*)mp_.revlist_to_array(code);
}

int ccode_t::outcode(FILE* fl)
{
	for (const auto& it : procs_map_)
	{
		proc_outcode(fl, it.second);
	}
	return 0;
}

int ccode_t::proc_outcode(FILE* fl, const proc_def_t* proc)
{
	fprintf(fl, "// Proc: %ls\n", proc->get_name());
	stream_outcode(fl, proc->entry_);
	return 0;
}

int ccode_t::stream_outcode(FILE* fl, inst_t** pip, bool starts_from_cf)
{
	char buf[1024];
	std::string ccode("\nCCODE {\n");
	std::string xcode("\nXCODE {\n");

	bool in_cf = starts_from_cf;
	//if (in_cf)
		//fprintf(fl, "CCODE {\n");
	//else 
		//fprintf(fl, "XCODE {\n");

	for (; (*pip)->ptr_; pip++)
	{
		inst_t* ip = *pip;
		if (ip->instr_ && ip->bookmark_)
		{
			//fprintf(fl, "%ls:\n", ip->bookmark_);

			sprintf(buf, "%ls:\n", ip->bookmark_);
			if (ip->instr_->cf_)
				ccode += buf;
			else
				xcode += buf;
		}
		if (ip->instr_ && ip->instr_->opcode_ != ioCSnop)
		{
			if (in_cf && !ip->instr_->cf_)
			{
				char buf0[64];
				sprintf(buf0, "@blk_%d", ++blkcnt_);

				sprintf(buf, "    exec %s ;\n", buf0);
				ccode += buf;

				//sprintf(buf, "}\n");
				//sprintf(buf, "XCODE {\n");
				sprintf(buf, "%s:\n", buf0);
				xcode += buf;
			}
			else if (!in_cf && ip->instr_->cf_)
			{
				//fprintf(fl, "}\n");
				//fprintf(fl, "CCODE {\n");
			}
			in_cf = ip->instr_->cf_;

			int n = ip->instr_->nargs_;
			const instr_def_t* instr = ip->instr_;
			//fprintf(fl, "    %s\n", instr->name_);

			sprintf(buf, "    %s ", instr->name_);
			if (in_cf)
				ccode += buf;
			else
				xcode += buf;

			for (int i = 0; i < n; i++)
			{
				ip = *++pip;
				switch (instr->arg_types_[i]) {
				case 	iatInt:
				case 	iatLong:
					sprintf(buf, "%lld ", ip->ival_);
					break;
				case 	iatCAddr:
					sprintf(buf, "%ls ", ip->str_);
					break;

				}
				if (in_cf)
					ccode += buf;
				else
					xcode += buf;
			}
			if (in_cf)
				ccode += ";\n";
			else
				xcode += ";\n";
		}
	}
	ccode += "}\n\n";
	xcode += "}\n\n";
	fprintf(fl, "%s", ccode.c_str());
	fprintf(fl, "%s", xcode.c_str());

	return 0;
}

void
ccode_t::lctx_push(lookup_ctx_t *ctx)
{
	ctx->next_ = lookup_ctx_;
	lookup_ctx_ = ctx;
}

lookup_ctx_t *
ccode_t::lctx_pop()
{
	assert(NULL != lookup_ctx_);
	lookup_ctx_t *ret = lookup_ctx_;
	lookup_ctx_ = lookup_ctx_->next_;
	return ret;
}

#if 0
stmt_t::stmt_t() :
code_()
{
	proc_ = NULL;
}

stmt_t::~stmt_t()
{
	if (NULL != proc_)
	{
		//proc_->exec_safe(code_.finit_entry_);
		//DO_SET(inst_t *, code, &code_.close_entries_)
		//{
		//	proc_->exec_safe(code);
		//}
		//END_DO_SET();
		DEL_SMTH(qproc_t, proc_);
	}
}

int
stmt_t::exec()
{
	qprocState state = proc_->exec(code_.stream_entry_);
	proc_->ip_ = code_.get_entry();
	return (state == qpInterrupted) ? 1 : 0;
}


var_item_t *
stmt_t::find_param(const wchar_t *name)
{
	//DO_SET(var_item_t *, elt, &code_.params_)
	//{
	//	if (0 == wcscmp(elt->name_, name))
	//		return elt;
	//}
	//END_DO_SET();
	return NULL;
}

int
stmt_t::nparams()
{
	int cnt = 0;
	//DO_SET(var_item_t *, elt, &code_.params_)
	//{
	//	cnt++;
	//}
	//END_DO_SET();
	return cnt;
}

#endif