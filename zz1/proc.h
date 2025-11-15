#pragma once

#include "dataTypes.h"
#include "box.h"
#include "shcall.h"
#include "hwcommon.h"
struct var_item_t;
struct c_tree_t;

struct params_ctx_t {
	params_ctx_t(box_mp_t  &mp) : mp_(mp), params_(NULL){};
	var_item_t *addParam(const wchar_t *pname, dataTypes type);
	var_item_t *getParam(const wchar_t *pname);
	int getSize() const // size in bytes on stack
	{
		return (abs(cnt_) * STACK_MEM_DATA_WIDTH) >>3 ;
	};

	box_mp_t  &mp_;
	box_set_t params_;
	int cnt_ = 0;
};

struct var_ctx_t {
	var_ctx_t(box_mp_t  &mp) : mp_(mp){};
	var_item_t *addVar(const wchar_t *pname, dataTypes type);
	var_item_t *getVar(const wchar_t *pname);
	int getSize() const // size in bytes on stack
	{
		return (abs(cnt_) * STACK_MEM_DATA_WIDTH) >> 3;
	};
	// difference with the begining of frame pointer
	void setBase(int base)
	{
		base_ = base;
	}

	std::unordered_map<std::wstring, var_item_t *> ht_locals_;
	box_mp_t  &mp_;
	int cnt_ = 0;
	int base_ = 0;
};

struct inst_t;
struct proc_def_t : public call_t {
	proc_def_t(ccode_t &cc, c_tree_t *exp);
	const wchar_t *metrica();

	virtual const wchar_t *get_name() const override { return name_; };
	virtual int get_nargs() const override;
	virtual int get_nrealargs() const override;
	virtual dataTypes get_arg_type(int idx) const override;
	virtual dataTypes get_ret_type() const override;
	virtual const wchar_t *get_arg_name(int idx) const override;
	virtual void gencode(ccode_t &cc, box_set_t *proccode) const override;

	ccode_t &cc_;
	const wchar_t *name_;
	params_ctx_t args_;
	var_ctx_t vars_;
	dataTypes ret_type_;
	inst_t  **entry_;
};
