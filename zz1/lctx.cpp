#include "stdafx.h"
#include "dataTypes.h"
#include "hwcommon.h"
#include "Datum.h"
#include "box.h"
#include "ccode.h"
#include "c_tree.h"
//#include "qproc.h"
#include "proc.h"
#include "lctx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

bool 
lookup_ctx_t::find_col_and_gencode(const wchar_t *name, bool lval, dataTypes &type, box_set_t *code) const
{
  bool bret = false;
  const lookup_ctx_t *ptr = this;
  while (NULL != ptr)
    {  
      bret = ptr->find_col_and_gencode_ (name, lval, type, code);
      if (bret)
        return true;
      ptr = ptr->next_;
    }
  return false;
}

// ------------- PARAMS ------------------------------------------

params_lookup_ctx_t::params_lookup_ctx_t(ccode_t &cc, params_ctx_t &params)
	: lookup_ctx_t(cc)
	, params_(params)
{
}

bool params_lookup_ctx_t::add_trivial_var(const wchar_t *name, dataTypes type) const
{
	params_.addParam(name, type);
	return true;
}

params_lookup_ctx_t::~params_lookup_ctx_t()
{

}

bool params_lookup_ctx_t::find_col_and_gencode_(const wchar_t *name, bool lval, dataTypes &type, box_set_t *code) const
{
	var_item_t *pit = params_.getParam(name);
	if (NULL == pit)
		return false;

	type = pit->type_;
	ccode_.tpush(pit->type_);
	inst_t *pinst = lval ?
		ccode_.tcheck1(ccode_t::a_locpush_, code) :
		ccode_.tcheck1(ccode_t::a_locpushd_, code);
	pinst = ccode_.new_inst(NULL, code);
	// position in bytes from frame pointer
	pinst->ival_ = (abs(pit->idx_) * STACK_MEM_DATA_WIDTH) >> 3;
//	pinst->data_ = &pit->data_;
	return true;
}


// ------------- LOCALS ------------------------------------------

locals_lookup_ctx_t::locals_lookup_ctx_t(ccode_t &cc, var_ctx_t &vars) 
	:	lookup_ctx_t (cc)
	,	vars_(vars)
{
}

locals_lookup_ctx_t::~locals_lookup_ctx_t ()
{
}

bool 
locals_lookup_ctx_t::find_col_and_gencode_(const wchar_t *name, bool lval, dataTypes &type, box_set_t *code) const
{
	var_item_t *pit = vars_.getVar(name);
	if (NULL == pit)
		return false;

	type = pit->type_;
	ccode_.tpush (pit->type_);

	inst_t *pinst = lval ?
		ccode_.tcheck1(ccode_t::a_locpush_, code) :
		ccode_.tcheck1(ccode_t::a_locpushd_, code);
	pinst = ccode_.new_inst (NULL, code);
	pinst->ival_ = vars_.base_ + ((pit->idx_ * STACK_MEM_DATA_WIDTH) >> 3);
	return true;
}

bool 
locals_lookup_ctx_t::add_trivial_var(const wchar_t *name, dataTypes type) const
{
	vars_.addVar(name, type);
	return true;
}



