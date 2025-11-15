#pragma once

#include "box.h"
#include "Datum.h"

  //class qproc_t;
  //typedef Datum (*shar_proc_t)(qproc_t &qp, const Datum *);
  typedef Datum(*shar_proc_t)(void *qp, const Datum*);
  enum shcallTypes {
    stUnknown = 0,
    stRegularProc,
  };

  struct ccode_t;
  class call_t {
  public:
	  virtual const wchar_t *get_name() const = 0;
	  virtual int get_nargs() const = 0;
	  virtual int get_nrealargs() const = 0;
	  virtual dataTypes get_arg_type(int idx) const = 0;
	  virtual const wchar_t *get_arg_name(int idx) const = 0;
	  virtual dataTypes get_ret_type() const  = 0;
	  virtual void gencode(ccode_t &cc, box_set_t *proccode) const = 0;
  };

  class shcall_t : public call_t {
    public:
      shcall_t (const wchar_t *name, shcallTypes type, dataTypes ret, int nargs, const wchar_t **names, dataTypes *types, shar_proc_t proc);
      ~shcall_t ();

	  virtual const wchar_t *get_name() const override { return name_; };
	  virtual int get_nargs() const override { return nargs_; };
	  virtual int get_nrealargs() const override { return nrealargs_; };
	  virtual dataTypes get_arg_type(int idx) const override { return types_[idx]; };
	  virtual dataTypes get_ret_type() const override { return ret_; };
	  virtual const wchar_t *get_arg_name(int idx) const override { return names_[idx]; };
	  virtual void gencode(ccode_t &cc, box_set_t *proccode) const override;

      shar_proc_t     proc_;
      dataTypes       ret_;
      shcallTypes     type_;

    protected:
      wchar_t        *name_;
      int             nargs_;
      int             nrealargs_;
      wchar_t       **names_;
      dataTypes      *types_;

    private:
      shcall_t ();
      shcall_t (const shcall_t &);
      shcall_t & operator= (const shcall_t &);
  };

  const shcall_t * get_shcall (const wchar_t *pname);
  void add_shcall (const wchar_t *pname, shcallTypes type, dataTypes ret, int nargs, const wchar_t **names, dataTypes *types, shar_proc_t proc);

