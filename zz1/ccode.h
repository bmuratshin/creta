#pragma once

#include <stdio.h>
#include "box.h"
#include "Datum.h"
#include "dataTypes.h"
#include "c_tree.h"
#include "instr.h"
//#include "proc.h"

  struct c_tree_t;
  struct proc_def_t;

  //class qproc_t;
  //typedef void (*inst_proc_t) (qproc_t &);
  struct inst_t {
      union {
          const instr_def_t* instr_;
          const Datum* cdata_;
          Datum* data_;
          const void* ptr_;
          const wchar_t* str_;
          inst_t* inst_;
          int64_t          ival_;
      };
      const wchar_t* bookmark_;
  };
  
  struct frame_t {
	const proc_def_t *proc_;
	const inst_t *ret_ip_;
	Datum *savsp_;
  };

  class const_impl_t {
    public:
      const_impl_t (int);
      const_impl_t (int64_t);
      const_impl_t (double);
      //const_impl_t (const wchar_t *);
      ~const_impl_t ();

      dataTypes type_;
      Datum     val_;
      
    private:
      const_impl_t ();
      const_impl_t (const const_impl_t &);
      const_impl_t & operator= (const const_impl_t &);
  };

  struct var_item_t {
    var_item_t (const wchar_t *name, dataTypes type); // mempool::alloc name first!!!
  
    const wchar_t	*name_;  
    dataTypes		type_;
    Datum			data_;
	// index מע םאקאכא פנוילא
	int				idx_;
  };

  struct var_ctx_t;
  class shcall_t;
  class call_t;
  class lookup_ctx_t;
  class locals_lookup_ctx_t;
  struct proc_def_t;
  struct ccode_t {
    public:
      ccode_t ();
     ~ccode_t ();

      inst_t *new_inst (const instr_def_t *, box_set_t *code);
      void add_bookmark(box_set_t* code, const wchar_t *name);
      
	  void c_exp_trace(c_tree_t *exp);
	  void c_exp_trace(c_tree_t *exp, box_set_t *code);
	  void c_exp_trace_(c_tree_t *exp, box_set_t *code);
      const call_t *
           c_call_exp (c_tree_t *exp, box_set_t *code);
	  void c_exp_type(c_tree_t **exp, dataTypes &dt, intptr_t &attr);

      void scalar_exp_generate (c_tree_t * exp, box_set_t *code);

      static int  type2intidx (dataTypes type);
      void tpush (dataTypes type);
      dataTypes tpop( void );
      void set_entry (box_set_t);

      int outcode(FILE *fl);
      int proc_outcode(FILE* fl, const proc_def_t* proc);
      int stream_outcode(FILE* fl, inst_t **entry, bool starts_from_cf = true);

	  const call_t *get_smth_callable(const wchar_t *name) const;


      bool has_ctor (dataTypes t);
      dataTypes t1 ( void );
      dataTypes t2 ( void );
      inst_t *tcheck (const instr_def_t **proc, box_set_t *code);
      inst_t *tcheck1 (const instr_def_t **proc, box_set_t *code);
      void cvrt1 (dataTypes t, box_set_t *code);
      void cvrt2 (dataTypes t, box_set_t *code);
      int conscode (int n, box_set_t *code);
      int descode (box_set_t *code);
      
      box_mp_t &get_mp () {return mp_;};
      const inst_t *get_entry () const {return stream_entry_;};
      
      void lctx_push (lookup_ctx_t *);
      lookup_ctx_t *lctx_pop ();
      
      char          *stmt_text_ = NULL;
      box_mp_t       mp_;
      box_set_t      consts_;
      inst_t        *stream_entry_ = NULL;

	  var_ctx_t     *globs_ = NULL;
	  typedef std::unordered_map<std::wstring, proc_def_t *> procs_map_t;
	  procs_map_t procs_map_;

      lookup_ctx_t        *lookup_ctx_ = NULL;
      locals_lookup_ctx_t *globals_ctx_ = NULL;
      
      static const int max_tstack_ = 256;
      dataTypes        tstack_[max_tstack_];
      int              tstackp_ = 0;
      bool             was_cons1_ = false;
      bool             was_cons2_ = false;
      
      int              cur_inst_ = 0;

      // for if bookmarks generation;
      int              ifcnt_ = 0;
      int              blkcnt_ = 0;

      static const int max_intypes_ = 3;
      static const instr_def_t *cvrt_arr1_[max_intypes_][max_intypes_];
      static const instr_def_t *cvrt_arr2_[max_intypes_][max_intypes_];

      static const instr_def_t *a_assign_[max_intypes_];
      static const instr_def_t *a_varpushd_[max_intypes_];
	  static const instr_def_t* a_varpush_[max_intypes_];
      static const instr_def_t* a_locpushd_[max_intypes_];
      static const instr_def_t* a_locpush_[max_intypes_];
      static const instr_def_t* a_add_[max_intypes_];
      static const instr_def_t* a_neg_[max_intypes_];
      static const instr_def_t* a_sub_[max_intypes_];
      static const instr_def_t* a_mul_[max_intypes_];
      static const instr_def_t* a_div_[max_intypes_];
      static const instr_def_t* a_eq_[max_intypes_];
      static const instr_def_t* a_ne_[max_intypes_];
      static const instr_def_t* a_gt_[max_intypes_];
      static const instr_def_t* a_ge_[max_intypes_];
      static const instr_def_t* a_lt_[max_intypes_];
      static const instr_def_t* a_le_[max_intypes_];
	  static const instr_def_t* a_predec_[max_intypes_];
	  static const instr_def_t* a_preinc_[max_intypes_];
	  static const instr_def_t* a_postdec_[max_intypes_];
	  static const instr_def_t* a_postinc_[max_intypes_];

    private:
      ccode_t (const ccode_t &);
      ccode_t &operator=(const ccode_t &);
  };
#if 0
  struct stmt_t {
    stmt_t ();
    virtual ~stmt_t ();
    
    //qproc_t    *proc_;
    ccode_t     code_;

    int exec_intl ();
    int nparams ();
    var_item_t *find_param (const wchar_t *name);

    virtual int exec ();
  };
#endif

