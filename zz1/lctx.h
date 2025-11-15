#pragma once

#include "box.h"
#include "dataTypes.h"

  struct ccode_t;
  struct params_ctx_t;
  class lookup_ctx_t {
    public:
      lookup_ctx_t (ccode_t &cc) : ccode_(cc) {next_ = NULL;};
      virtual ~lookup_ctx_t () {};
	  virtual bool add_trivial_var (const wchar_t *name, dataTypes type) const = 0;
	  virtual bool find_col_and_gencode_(const wchar_t *name, bool lval, dataTypes &type, box_set_t *code) const = 0;
      bool find_col_and_gencode (const wchar_t *name, bool lval, dataTypes &type, box_set_t *code) const;
      
      lookup_ctx_t *next_;
      ccode_t      &ccode_;

    private:
      lookup_ctx_t ();
      lookup_ctx_t (const lookup_ctx_t &);
      lookup_ctx_t & operator =  (const lookup_ctx_t &);
  };

  class params_lookup_ctx_t : public lookup_ctx_t {
	public:
		params_lookup_ctx_t(ccode_t &cc, params_ctx_t &params);
		virtual bool add_trivial_var(const wchar_t *name, dataTypes type) const;
		virtual ~params_lookup_ctx_t();
		virtual bool find_col_and_gencode_(const wchar_t *name, bool lval, dataTypes &type, box_set_t *code) const;
      
		params_ctx_t &params_;
	private:
		params_lookup_ctx_t();
		params_lookup_ctx_t(const params_lookup_ctx_t &);
		params_lookup_ctx_t & operator =  (const params_lookup_ctx_t &);
  };

  class locals_lookup_ctx_t : public lookup_ctx_t {
  public:
	  locals_lookup_ctx_t(ccode_t &cc, var_ctx_t &vars);
	  virtual bool add_trivial_var(const wchar_t *name, dataTypes type) const;
	  virtual ~locals_lookup_ctx_t();
	  virtual bool find_col_and_gencode_(const wchar_t *name, bool lval, dataTypes &type, box_set_t *code) const;

	  var_ctx_t &vars_;
  private:
	  locals_lookup_ctx_t();
	  locals_lookup_ctx_t(const locals_lookup_ctx_t &);
	  locals_lookup_ctx_t & operator =  (const locals_lookup_ctx_t &);
  };
