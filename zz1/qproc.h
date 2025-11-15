#pragma once

#include "Datum.h"
#include "dataTypes.h"

  enum qprocState {
      qpUnknown = 0,
      qpReady,
      qpInterrupted,
      qpStopped,
  };

  struct ccode_t;
  struct inst_t;
  struct frame_t;
  struct proc_def_t;
  class qproc_t {
    public:
      qproc_t (ccode_t &code);
     ~qproc_t ();
     
      qprocState exec (const inst_t *);
      qprocState exec_raw (const inst_t *);
      qprocState exec_call (const inst_t *);
      qprocState exec_safe (const inst_t *);
      qprocState interrupt ();
	  qprocState enter_call(const proc_def_t *proc);
	  qprocState leave_call();

      inline void push (const Datum &d)
      {
       *stackp_++ = d;
      }
	  inline Datum &pop_m(bool free_reg = false)
      {
#ifdef _DEBUG
        if (stackp_== stack_)
          throw_ ("stack underflow");
#endif
		return *--stackp_;
      }
      inline Datum &s1( void )
      {
       return *(stackp_ - 2);
      }
      inline Datum &s2( void )
      {
       return *(stackp_ - 1);
      }
      
      static void inst_nop (qproc_t &);
      static void inst_pop (qproc_t &);
      static void inst_imdpush (qproc_t &);
	  static void inst_iconstpush(qproc_t &);
	  static void inst_lconstpush(qproc_t &);
	  static void inst_dconstpush(qproc_t &);
	  static void inst_constpush(qproc_t &id);
      static void inst_constpush_typed (qproc_t &);
      static void inst_ifcode (qproc_t &);
	  static void inst_goto(qproc_t &);
	  static void inst_whilecode(qproc_t &);
      static void inst_forcode (qproc_t &);
      
      static void inst_i2l1 (qproc_t &);
      static void inst_i2d1 (qproc_t &);
      //static void inst_i2s1 (qproc_t &);
      static void inst_l2i1 (qproc_t &);
      static void inst_l2d1 (qproc_t &);
      //static void inst_l2s1 (qproc_t &);
      static void inst_d2i1 (qproc_t &);
      static void inst_d2l1 (qproc_t &);
      //static void inst_d2s1 (qproc_t &);
      //static void inst_s2i1 (qproc_t &);
      //static void inst_s2l1 (qproc_t &);
      //static void inst_s2d1 (qproc_t &);
      //static void inst_s2blob1 (qproc_t &);
      //static void inst_blob2s1 (qproc_t &);

      static void inst_i2l2 (qproc_t &);
      static void inst_i2d2 (qproc_t &);
      //static void inst_i2s2 (qproc_t &);
      static void inst_l2i2 (qproc_t &);
      static void inst_l2d2 (qproc_t &);
      //static void inst_l2s2 (qproc_t &);
      static void inst_d2i2 (qproc_t &);
      static void inst_d2l2 (qproc_t &);
      //static void inst_d2s2 (qproc_t &);
      //static void inst_s2i2 (qproc_t &);
      //static void inst_s2l2 (qproc_t &);
      //static void inst_s2d2 (qproc_t &);
      //static void inst_s2blob2 (qproc_t &);
      //static void inst_blob2s2 (qproc_t &);

      //static void inst_str_ctor1 (qproc_t &);
      //static void inst_str_ctor2 (qproc_t &);
      //static void inst_str_dtor (qproc_t &);
      //static void inst_shape_dtor (qproc_t &);
      //static void inst_blob_dtor (qproc_t &);
      //static void inst_raster_dtor (qproc_t &);

      static void inst_iassign (qproc_t &);
      static void inst_lassign (qproc_t &);
      static void inst_dassign (qproc_t &);
      //static void inst_sassign (qproc_t &);
      //static void inst_shape_assign (qproc_t &);
      //static void inst_blob_assign (qproc_t &);
      //static void inst_raster_assign (qproc_t &);

	  static void inst_varpush(qproc_t &);
	  static void inst_ivarpush(qproc_t &);
	  static void inst_lvarpush(qproc_t &);
	  static void inst_dvarpush(qproc_t &);
	  static void inst_varpushd(qproc_t &);
	  static void inst_ivarpushd(qproc_t &);
	  static void inst_lvarpushd(qproc_t &);
	  static void inst_dvarpushd(qproc_t &);
	  //static void inst_svarpushd (qproc_t &);

      static void inst_iadd (qproc_t &);
      static void inst_ladd (qproc_t &);
      static void inst_dadd (qproc_t &);
      //static void inst_sadd (qproc_t &);
      static void inst_ineg (qproc_t &);
      static void inst_lneg (qproc_t &);
      static void inst_dneg (qproc_t &);
      static void inst_isub (qproc_t &);
      static void inst_lsub (qproc_t &);
      static void inst_dsub (qproc_t &);
      static void inst_imul (qproc_t &);
      static void inst_lmul (qproc_t &);
      static void inst_dmul (qproc_t &);
      static void inst_idiv (qproc_t &);
      static void inst_ldiv (qproc_t &);
      static void inst_ddiv (qproc_t &);

      static void inst_ieq (qproc_t &);
      static void inst_leq (qproc_t &);
      static void inst_deq (qproc_t &);
      //static void inst_seq (qproc_t &);

      static void inst_ine (qproc_t &);
      static void inst_lne (qproc_t &);
      static void inst_dne (qproc_t &);
      //static void inst_sne (qproc_t &);

      static void inst_igt (qproc_t &);
      static void inst_lgt (qproc_t &);
      static void inst_dgt (qproc_t &);
      //static void inst_sgt (qproc_t &);

      static void inst_ige (qproc_t &);
      static void inst_lge (qproc_t &);
      static void inst_dge (qproc_t &);
      //static void inst_sge (qproc_t &);

      static void inst_ilt (qproc_t &);
      static void inst_llt (qproc_t &);
      static void inst_dlt (qproc_t &);
      //static void inst_slt (qproc_t &);

      static void inst_ile (qproc_t &);
      static void inst_lle (qproc_t &);
      static void inst_dle (qproc_t &);
      //static void inst_sle (qproc_t &);
      
      static void inst_preand (qproc_t &);
      static void inst_and (qproc_t &);
      static void inst_preor (qproc_t &);
      static void inst_or (qproc_t &);
      static void inst_not (qproc_t &);
      static void inst_xor (qproc_t &);

	  static void inst_ipreinc(qproc_t &);
	  static void inst_lpreinc(qproc_t &);
	  static void inst_dpreinc(qproc_t &);

	  static void inst_ipredec(qproc_t &);
	  static void inst_lpredec(qproc_t &);
	  static void inst_dpredec(qproc_t &);

	  static void inst_ipostinc(qproc_t &);
	  static void inst_lpostinc(qproc_t &);
	  static void inst_dpostinc(qproc_t &);

	  static void inst_ipostdec(qproc_t &);
	  static void inst_lpostdec(qproc_t &);
	  static void inst_dpostdec(qproc_t &);

      static void inst_shcall (qproc_t &);
	  static void inst_call(qproc_t &);
	  static void inst_return(qproc_t &);

      static void inst_param_getval (qproc_t &);
      
    //protected:
      static const int max_stack_ = 8192 << 10;
	  static const int max_frames_ = 1024 << 10;

      const inst_t   *ip_;
      Datum          *stack_;
      Datum          *stackp_;
      
      frame_t        *frames_;
      frame_t        *fp_;
      
      qprocState      state_;
      ccode_t        &code_;

    private:
      qproc_t (const qproc_t &);
      qproc_t &operator=(const qproc_t &);
  };

