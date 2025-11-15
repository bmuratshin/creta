#include "stdafx.h"
#include "box.h"
#include "Datum.h"
#include "ccode.h"
#include "c_tree.h"
//#include "qproc.h"
#include "shcall.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif


#if 0
Datum
__interrupt(qproc_t &qp, const Datum *)
{
	qp.state_ = qpInterrupted;
	Datum ret;
	ret.Zero();
	return ret;
}

Datum
print_int_proc(qproc_t & /*qp*/, const Datum *args)
{
	Datum ret;
	ret.Zero();
	printf("%d ", args[0].ival);
	return ret;
}
const int print_int_proc_nargs = 1;
const wchar_t *print_int_proc_names[print_int_proc_nargs] = { L"val" };
dataTypes print_int_proc_types[print_int_proc_nargs] = { ftInteger32 };

Datum
print_long_proc(qproc_t & /*qp*/, const Datum *args)
{
	Datum ret;
	ret.Zero();
	printf("%I64d ", args[0].lval);
	return ret;
}
const int print_long_proc_nargs = 1;
const wchar_t *print_long_proc_names[print_long_proc_nargs] = { L"val" };
dataTypes print_long_proc_types[print_long_proc_nargs] = { ftInteger64 };

Datum
print_double_proc(qproc_t & /*qp*/, const Datum *args)
{
	Datum ret;
	ret.Zero();
	printf("%lg ", args[0].dval);
	return ret;
}
const int print_double_proc_nargs = 1;
const wchar_t *print_double_proc_names[print_double_proc_nargs] = { L"val" };
dataTypes print_double_proc_types[print_double_proc_nargs] = { ftDouble };
#endif

struct shcalls_guard_t {
	std::unordered_map<std::wstring, shcall_t *> ht_shcalls_;

	shcalls_guard_t()
	{
		//add_shcall(L"print_int", stRegularProc, ftInteger32, print_int_proc_nargs, print_int_proc_names, print_int_proc_types, print_int_proc);
		//add_shcall(L"print_long", stRegularProc, ftInteger32, print_long_proc_nargs, print_long_proc_names, print_long_proc_types, print_long_proc);
		//add_shcall(L"print_double", stRegularProc, ftInteger32, print_double_proc_nargs, print_double_proc_names, print_double_proc_types, print_double_proc);
		//add_shcall(L"__interrupt", stRegularProc, ftInteger32, 0, NULL, NULL, __interrupt);
	}
	~shcalls_guard_t()
	{
		for (auto it : ht_shcalls_)
		{
			shcall_t *pcall = it.second;
			DEL_SMTH(shcall_t, pcall);
		}
	}
};

shcalls_guard_t shcalls_guard;

shcall_t::shcall_t(const wchar_t *name, shcallTypes type, dataTypes ret, int nargs, const wchar_t **names, dataTypes *types, shar_proc_t proc)
{
	type_ = type;
	ret_ = ret;
	name_ = wcsdup_smth(name);
	proc_ = proc;
	nargs_ = nargs;
	nrealargs_ = nargs;
	for (int i = 0; i < nargs; i++)
		if (ftUnknown == types[i])
			nrealargs_++;
	if (nargs > 0)
	{
		names_ = (wchar_t **)new_smth(sizeof(void*) * nargs);
		types_ = (dataTypes *)new_smth(sizeof(dataTypes) * nargs);
		for (int i = 0; i < nargs; i++)
		{
			names_[i] = wcsdup_smth(names[i]);
			types_[i] = types[i];
		}
	}
	else
	{
		names_ = NULL;
		types_ = NULL;
	}
}

shcall_t::~shcall_t()
{
	for (int i = 0; i < nargs_; i++)
		free_smth(names_[i]);
	free_smth(types_);
	free_smth(names_);
	free_smth(name_);
}

void shcall_t::gencode(ccode_t &cc, box_set_t *code) const
{
	cc.new_inst(get_asm_instr(-1, 0), code);
	inst_t *pinst = cc.new_inst(NULL, code);
	pinst->ptr_ = this;

	cc.tpush(get_ret_type());
}

const shcall_t *
get_shcall(const wchar_t *pname)
{
	auto it = shcalls_guard.ht_shcalls_.find(pname);
	if (it == shcalls_guard.ht_shcalls_.end())
		return NULL;
	return it->second;
}

void
add_shcall(const wchar_t *name, shcallTypes type, dataTypes ret, int nargs, const wchar_t **names, dataTypes *types, shar_proc_t proc)
{
	assert(NULL == get_shcall(name));
	shcall_t *pcall = NEW_SMTH_P(shcall_t, (name, type, ret, nargs, names, types, proc));
	const wchar_t *pname = pcall->get_name();
	shcalls_guard.ht_shcalls_[pname] = pcall;
}

