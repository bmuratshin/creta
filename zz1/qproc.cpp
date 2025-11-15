#include "stdafx.h"
#include <math.h>
//#include "qproc.h"
#include "ccode.h"
#include "Datum.h"
#include "shcall.h"
#include "proc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

inline int __eq_doubles ( const double &val1, const double &val2 )
{
  int e1;
  double m1 = frexp (val1, &e1);
  int e2;
  double m2 = frexp (val2, &e2);
  if (e1 != e2)
    return 0;
  return (fabs (m1 - m2) < 1e-7)? 1 : 0;
}

inline int __gt_doubles ( const double &val1, const double &val2 )
{
  return (val1 > val2 && !__eq_doubles (val1, val2))?1:0;
}

inline int __ge_doubles ( const double &val1, const double &val2 )
{
  return (val1 > val2 || __eq_doubles (val1, val2))?1:0;
}

inline int __lt_doubles ( const double &val1, const double &val2 )
{
  return (val1 < val2 && !__eq_doubles (val1, val2))?1:0;
}

inline int __le_doubles ( const double &val1, const double &val2 )
{
  return (val1 < val2 || __eq_doubles (val1, val2))?1:0;
}


qproc_t::qproc_t (ccode_t &code) : code_ (code)
{
  stack_ = (Datum *)new_smth (sizeof (Datum) * max_stack_);
  stackp_ = stack_;

  frames_ = (frame_t *)new_smth(sizeof(frame_t) * max_frames_);
  fp_ = frames_;

  ip_ = NULL;
  //coltypes_ = NULL;
  state_ = qpUnknown;
}

qproc_t::~qproc_t ()
{
  free_smth (frames_);
  free_smth (stack_);

  //DEL_SMTH (memses_t, sess_);
  //free_smth (coltypes_);
  //DEL_ARR_SMTH (ugd_variant_t, cols_);
}


void 
qproc_t::inst_nop (qproc_t & /*qp*/)
{
}

void 
qproc_t::inst_pop (qproc_t &qp)
{
#ifdef _DEBUG
  if (qp.stackp_ == qp.stack_)
    throw_ ("stack underflow");
#endif
  --qp.stackp_;
}

void
qproc_t::inst_iconstpush(qproc_t &qp)
{
	inst_constpush(qp);
}

void
qproc_t::inst_lconstpush(qproc_t &qp)
{
	inst_constpush(qp);
}

void
qproc_t::inst_dconstpush(qproc_t &qp)
{
	inst_constpush(qp);
}

void
qproc_t::inst_constpush(qproc_t &qp)
{
  qp.ip_++;
  Datum &d = *qp.ip_->data_;
  qp.push(d);

}

void 
qproc_t::inst_imdpush (qproc_t &qp)
{
  qp.ip_++;
  Datum d;
  d.lval = qp.ip_->ival_;
  qp.push(d);
}

void 
qproc_t::inst_constpush_typed (qproc_t &qp)
{
  qp.ip_++;
  Datum d;
  d = *qp.ip_->data_;
  qp.push(d);

  qp.ip_++;
  dataTypes type = (dataTypes)qp.ip_->ival_;
  //switch (type) {
    //case ftString:
    //	(qp.stackp_ - 1)->Sval = NEW_SMTH_P (decore::str_t, (*(qp.stackp_ - 1)->Sval));
    //  break;
    //default:
      assert (0);
      //break;
  //};
}

void 
qproc_t::inst_preand (qproc_t &qp)
{
  qp.ip_++;
  Datum &d2 = qp.s2 ();
  if (!d2.ival)
    qp.ip_ += qp.ip_->ival_ - 1;
}

void 
qproc_t::inst_and (qproc_t &qp)
{
  Datum &d2 = qp.s2 ();
  Datum &d1 = qp.s1 ();
  d1.ival = ((0 != d1.ival) && (0 != d2.ival));
  qp.pop_m ();
}

void 
qproc_t::inst_preor (qproc_t &qp)
{
  qp.ip_++;
  Datum &d2 = qp.s2 ();
  if (d2.ival)
    qp.ip_ += qp.ip_->ival_ - 1;
}

void 
qproc_t::inst_or (qproc_t &qp)
{
  Datum &d2 = qp.s2 ();
  Datum &d1 = qp.s1 ();
  d1.ival = ((0 != d1.ival) || (0 != d2.ival));
  qp.pop_m ();
}

void 
qproc_t::inst_xor (qproc_t &qp)
{
  Datum &d2 = qp.s2 ();
  Datum &d1 = qp.s1 ();
  d1.ival = (((0 != d1.ival)?1:0) ^ ((0 != d2.ival)?1:0));
  qp.pop_m ();
}

void 
qproc_t::inst_not (qproc_t &qp)
{
  Datum &d = qp.s2 ();
  d.ival = (d.ival == 0);
}

void 
qproc_t::inst_i2l1 (qproc_t &qp)
{
  (qp.stackp_- 2)->lval = (qp.stackp_ - 2)->ival;
}

void 
qproc_t::inst_i2d1 (qproc_t &qp)
{
  (qp.stackp_- 2)->dval = (qp.stackp_ - 2)->ival;				
}

//void 
//qproc_t::inst_i2s1 (qproc_t &qp)
//{
//	wchar_t str[128];
//	swprintf(str, 128, L"%d",(qp.stackp_ - 2)->ival);
//	(qp.stackp_ - 2)->Sval = NEW_SMTH_P (decore::str_t, (str));
//}

void 
qproc_t::inst_l2i1 (qproc_t &qp)
{
  (qp.stackp_- 2)->ival = int ((qp.stackp_ - 2)->lval);
}

void 
qproc_t::inst_l2d1 (qproc_t &qp)
{
  (qp.stackp_- 2)->dval = double((qp.stackp_ - 2)->lval);
}

//void 
//qproc_t::inst_l2s1 (qproc_t &qp)
//{
//	wchar_t str[128];
//	swprintf(str, 128, L"%I64d",(qp.stackp_ - 2)->lval);
//	(qp.stackp_ - 2)->Sval = NEW_SMTH_P (decore::str_t, (str));
//}

void 
qproc_t::inst_d2i1 (qproc_t &qp)
{
  (qp.stackp_- 2)->ival = int ((qp.stackp_-2)->dval);
}

void 
qproc_t::inst_d2l1 (qproc_t &qp)
{
  (qp.stackp_- 2)->lval = int64_t ((qp.stackp_ - 2)->dval);
}

//void 
//qproc_t::inst_d2s1 (qproc_t &qp)
//{
//	wchar_t str[128];
//	swprintf (str, L"%.15g",(qp.stackp_ - 2)->dval);
//	(qp.stackp_ - 2)->Sval = NEW_SMTH_P (decore::str_t, (str));
//}

//void 
//qproc_t::inst_s2i1 (qproc_t &qp)
//{
//  decore::str_t *s = (qp.stackp_ - 2)->Sval;
//  (qp.stackp_ - 2)->ival = _wtoi (s->cwstr ());
//  DEL_SMTH (decore::str_t, s);
//}

//void 
//qproc_t::inst_s2l1 (qproc_t &qp)
//{
//  decore::str_t *s=(qp.stackp_ - 2)->Sval;
//  (qp.stackp_ - 2)->lval = _wtoi64 (s->cwstr ());
//  DEL_SMTH (decore::str_t, s);
//}

//void 
//qproc_t::inst_s2d1 (qproc_t &qp)
//{
//  decore::str_t *s = (qp.stackp_ - 2)->Sval;
//  (qp.stackp_ - 2)->dval = __wtof (s->cwstr ());
//  DEL_SMTH (decore::str_t, s);
//}

void 
qproc_t::inst_i2l2 (qproc_t &qp)
{
  (qp.stackp_- 1)->lval = (qp.stackp_ - 1)->ival;
}

void 
qproc_t::inst_i2d2 (qproc_t &qp)
{
  (qp.stackp_- 1)->dval = (qp.stackp_ - 1)->ival;				
}

//void 
//qproc_t::inst_i2s2 (qproc_t &qp)
//{
//	wchar_t str[128];
//	swprintf(str,128, L"%d",(qp.stackp_ - 1)->ival);
//	(qp.stackp_ - 1)->Sval = NEW_SMTH_P (decore::str_t, (str));
//}

void 
qproc_t::inst_l2i2 (qproc_t &qp)
{
  (qp.stackp_- 1)->ival = int ((qp.stackp_ - 1)->lval);
}

void 
qproc_t::inst_l2d2 (qproc_t &qp)
{
  (qp.stackp_- 1)->dval = double((qp.stackp_ - 1)->lval);
}

//void 
//qproc_t::inst_l2s2 (qproc_t &qp)
//{
//	wchar_t str[128];
//	swprintf(str, 128, L"%I64d",(qp.stackp_ - 1)->lval);
//	(qp.stackp_ - 1)->Sval = NEW_SMTH_P (decore::str_t, (str));
//}

void 
qproc_t::inst_d2i2 (qproc_t &qp)
{
  (qp.stackp_ - 1)->ival = int ((qp.stackp_ - 1)->dval);
}

void 
qproc_t::inst_d2l2 (qproc_t &qp)
{
  (qp.stackp_ - 1)->lval = int64_t ((qp.stackp_ - 1)->dval);
}

//void 
//qproc_t::inst_d2s2 (qproc_t &qp)
//{
//	wchar_t str[128];
//	swprintf(str, L"%.15g",(qp.stackp_ - 1)->dval);
//	(qp.stackp_ - 1)->Sval = NEW_SMTH_P (decore::str_t, (str));
//}

//void 
//qproc_t::inst_s2i2 (qproc_t &qp)
//{
//  decore::str_t *s = (qp.stackp_ - 1)->Sval;
//  (qp.stackp_ - 1)->ival = _wtoi (s->cwstr ());
//  DEL_SMTH (decore::str_t, s);
//}

//void 
//qproc_t::inst_s2l2 (qproc_t &qp)
//{
//  decore::str_t *s=(qp.stackp_ - 1)->Sval;
//  (qp.stackp_ - 1)->lval = _wtoi64 (s->cwstr ());
//  DEL_SMTH (decore::str_t, s);
//}

//void 
//qproc_t::inst_s2d2 (qproc_t &qp)
//{
//  decore::str_t *s = (qp.stackp_ - 1)->Sval;
//  (qp.stackp_ - 1)->dval = __wtof (s->cwstr ());
//  DEL_SMTH (decore::str_t, s);
//}

//void 
//qproc_t::inst_str_ctor1 (qproc_t &qp)
//{
//	(qp.stackp_ - 2)->Sval = NEW_SMTH (decore::str_t);
//}

//void 
//qproc_t::inst_str_ctor2 (qproc_t &qp)
//{
//	(qp.stackp_ - 1)->Sval = NEW_SMTH (decore::str_t);
//}

//void 
//qproc_t::inst_str_dtor (qproc_t &qp)
//{
//  if (NULL != (qp.stackp_ - 1)->Sval)
//  {
//    DEL_SMTH (decore::str_t, (qp.stackp_ - 1)->Sval);
//	  (qp.stackp_ - 1)->Sval = NULL;
//  }
//}

void 
qproc_t::inst_iassign (qproc_t &qp)
{
  Datum &d2 = qp.s2 ();
  Datum &d1 = qp.s1 ();
  *d2.Dval = d1;
  //std::swap(d1, d2);

  qp.pop_m ();
}

void 
qproc_t::inst_lassign (qproc_t &qp)
{
  Datum &d2 = qp.s2 ();
  Datum &d1 = qp.s1 ();
  *d2.Dval = d1;
  //std::swap(d1, d2);

  qp.pop_m();
}

void 
qproc_t::inst_dassign (qproc_t &qp)
{
  Datum &d2 = qp.s2 ();
  Datum &d1 = qp.s1 ();
  *d2.Dval = d1;
  //std::swap(d1, d2);

  qp.pop_m ();
}

//void 
//qproc_t::inst_sassign (qproc_t &qp)
//{
//  Datum &d2 = qp.s2 ();
//  Datum &d1 = qp.s1 ();
//  *d1.Dval->Sval = *d2.Sval;
//  std::swap(d1, d2);
//  qp.pop_m ();
//}

void 
qproc_t::inst_ivarpush(qproc_t &qp)
{
  inst_varpush(qp);
}

void
qproc_t::inst_lvarpush(qproc_t &qp)
{
	inst_varpush(qp);
}

void
qproc_t::inst_dvarpush(qproc_t &qp)
{
	inst_varpush(qp);
}

void
qproc_t::inst_varpush(qproc_t &qp)
{
	qp.ip_++;
	Datum d;
	size_t idx = qp.ip_->ival_;
	d.Dval = &qp.fp_[-1].savsp_[idx];
	qp.push(d);
}

//void 
//qproc_t::inst_svarpushd (qproc_t &qp)
//{
//  qp.ip_++;
//  Datum d;
//  d.Sval = NEW_SMTH_P (decore::str_t, (*qp.ip_->data_->Sval));
//  qp.push(d);
//}

void
qproc_t::inst_lvarpushd(qproc_t &qp)
{
	inst_varpushd(qp);
}

void
qproc_t::inst_ivarpushd(qproc_t &qp)
{
	inst_varpushd(qp);
}

void
qproc_t::inst_dvarpushd(qproc_t &qp)
{
	inst_varpushd(qp);
}


void 
qproc_t::inst_varpushd(qproc_t &qp)
{
  qp.ip_++;

  size_t idx = qp.ip_->ival_;
  Datum &d = qp.fp_[-1].savsp_[idx];
  qp.push(d);
}

void
qproc_t::inst_goto(qproc_t &qp)
{
	const inst_t *ip = qp.ip_;
	const size_t shift = (ip + 1)->ival_;
	qp.ip_ += 1 + shift;
}

void 
qproc_t::inst_ifcode (qproc_t &qp)
{
  Datum &d2 = qp.s2 ();
  bool bret = (d2.ival != 0);
  qp.pop_m (true);

  if (!bret)
  {
	  qproc_t::inst_goto(qp);
  }
  else
  {
	  qp.ip_++;
  }
}

void 
qproc_t::inst_whilecode (qproc_t &qp)
{
  qprocState state = qp.state_;
  const inst_t *ip = qp.ip_;

  const inst_t *exprcode = (ip + 1)->inst_;
  qp.exec_raw (exprcode);
  Datum &d2 = qp.s2 ();
  bool bret = (d2.ival != 0);
  qp.pop_m (true);
  if (!bret)
    {
      qp.state_ = state;
      qp.ip_ = ip + 2; // exprcode & bodycode
    }
  else
    {
      const inst_t *bodycode = (ip+2)->inst_;
      qp.ip_ = ip;
      qp.exec_call (bodycode);
    }
}


void 
qproc_t::inst_iadd (qproc_t &qp)
{
	qp.s1 ().ival += qp.s2 ().ival;
	qp.pop_m ();
}

void 
qproc_t::inst_ladd (qproc_t &qp)
{
	qp.s1().lval += qp.s2().lval;
	qp.pop_m ();
}

void 
qproc_t::inst_dadd (qproc_t &qp)
{
	qp.s1().dval += qp.s2().dval;
	qp.pop_m ();
}

//void 
//qproc_t::inst_sadd (qproc_t &qp)
//{
//  (*qp.s1 ().Sval) += *qp.s2 ().Sval;
//  inst_str_dtor (qp);
//  qp.pop_m ();
//}

void 
qproc_t::inst_ineg (qproc_t &qp)
{
  Datum &d = qp.s2 ();
  d.ival = -d.ival;
}

void 
qproc_t::inst_lneg (qproc_t &qp)
{
  Datum &d = qp.s2 ();
  d.lval = -d.lval;
}

void 
qproc_t::inst_dneg (qproc_t &qp)
{
  Datum &d = qp.s2 ();
  d.dval = -d.dval;
}

void 
qproc_t::inst_isub (qproc_t &qp)
{
	qp.s1().ival -= qp.s2().ival;
	qp.pop_m ();
}

void 
qproc_t::inst_lsub (qproc_t &qp)
{
	qp.s1().lval -= qp.s2().lval;
	qp.pop_m ();
}

void 
qproc_t::inst_dsub (qproc_t &qp)
{
	qp.s1().dval -= qp.s2().dval;
	qp.pop_m ();
}

void 
qproc_t::inst_imul (qproc_t &qp)
{
  qp.s1 ().ival *= qp.s2 ().ival;
  qp.pop_m ();
}

void 
qproc_t::inst_lmul (qproc_t &qp)
{
  qp.s1 ().lval *= qp.s2 ().lval;
  qp.pop_m ();
}

void 
qproc_t::inst_dmul (qproc_t &qp)
{
  qp.s1 ().dval *= qp.s2 ().dval;
  qp.pop_m ();
}

void 
qproc_t::inst_idiv (qproc_t &qp)
{
  if (0 == qp.s2 ().ival)
    throw_ ("integer zero divide");
  else
    qp.s1 ().ival /= qp.s2 ().ival;
  qp.pop_m ();
}

void 
qproc_t::inst_ldiv (qproc_t &qp)
{
  if (0 == qp.s2 ().lval)
    throw_ ("long zero divide");
  else
    qp.s1 ().lval /= qp.s2 ().lval;
  qp.pop_m ();
}

void 
qproc_t::inst_ddiv (qproc_t &qp)
{
  if (0 == qp.s2 ().dval)
    throw_ ("double zero divide");
  else
    qp.s1 ().dval /= qp.s2 ().dval;
  qp.pop_m ();
}

// EQ -------------------------------------------------------------------------------------------------
void 
qproc_t::inst_ieq (qproc_t &qp)
{
	Datum &ds1 = qp.s1();
	Datum &ds2 = qp.s2();
	ds1.ival = (ds1.ival == ds2.ival)?1:0;
	qp.pop_m ();
}

void 
qproc_t::inst_leq (qproc_t &qp)
{
	Datum &ds1 = qp.s1();
	Datum &ds2 = qp.s2();
	ds1.ival = (ds1.lval == ds2.lval)?1:0;
	qp.pop_m ();
}

void 
qproc_t::inst_deq (qproc_t &qp)
{
	Datum &ds1 = qp.s1();
	Datum &ds2 = qp.s2();
	ds1.ival = __eq_doubles (ds1.dval, ds2.dval);
	qp.pop_m ();
}

//void 
//qproc_t::inst_seq (qproc_t &qp)
//{
//  Datum &ds1 = qp.s1();
//  Datum &ds2 = qp.s2();
//  int ival = (*ds1.Sval == *ds2.Sval)?1:0;
//  DEL_SMTH (decore::str_t, ds1.Sval);
//  DEL_SMTH (decore::str_t, ds2.Sval);
//  ds1.ival = ival;
//  qp.pop_m ();
//}

// NE -------------------------------------------------------------------------------------------------
void 
qproc_t::inst_ine (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.ival != ds2.ival)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_lne (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.lval != ds2.lval)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_dne (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = __eq_doubles (ds1.dval, ds2.dval)?0:1;
  qp.pop_m ();
}

//void 
//qproc_t::inst_sne (qproc_t &qp)
//{
//  Datum &ds1 = qp.s1();
//  Datum &ds2 = qp.s2();
//  int ival = (*ds1.Sval != *ds2.Sval)?1:0;
//  DEL_SMTH (decore::str_t, ds1.Sval);
//  DEL_SMTH (decore::str_t, ds2.Sval);
//  ds1.ival = ival;
//  qp.pop_m ();
//}

// GT -------------------------------------------------------------------------------------------------
void 
qproc_t::inst_igt (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.ival > ds2.ival)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_lgt (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.lval > ds2.lval)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_dgt (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = __gt_doubles (ds1.dval, ds2.dval);
  qp.pop_m ();
}

//void 
//qproc_t::inst_sgt (qproc_t &qp)
//{
//  Datum &ds1 = qp.s1();
//  Datum &ds2 = qp.s2();
//  int ival = (*ds1.Sval > *ds2.Sval)?1:0;
//  DEL_SMTH (decore::str_t, ds1.Sval);
//  DEL_SMTH (decore::str_t, ds2.Sval);
//  ds1.ival = ival;
//  qp.pop_m ();
//}

// GE -------------------------------------------------------------------------------------------------
void 
qproc_t::inst_ige (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.ival >= ds2.ival)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_lge (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.lval >= ds2.lval)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_dge (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = __ge_doubles (ds1.dval, ds2.dval);
  qp.pop_m ();
}

//void 
//qproc_t::inst_sge (qproc_t &qp)
//{
//  Datum &ds1 = qp.s1();
//  Datum &ds2 = qp.s2();
//  int ival = (*ds1.Sval >= *ds2.Sval)?1:0;
//  DEL_SMTH (decore::str_t, ds1.Sval);
//  DEL_SMTH (decore::str_t, ds2.Sval);
//  ds1.ival = ival;
//  qp.pop_m ();
//}

// LT -------------------------------------------------------------------------------------------------
void 
qproc_t::inst_ilt (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.ival < ds2.ival)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_llt (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.lval < ds2.lval)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_dlt (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = __lt_doubles (ds1.dval, ds2.dval);
  qp.pop_m ();
}

//void 
//qproc_t::inst_slt (qproc_t &qp)
//{
//  Datum &ds1 = qp.s1();
//  Datum &ds2 = qp.s2();
//  int ival = (*ds1.Sval < *ds2.Sval)?1:0;
//  DEL_SMTH (decore::str_t, ds1.Sval);
//  DEL_SMTH (decore::str_t, ds2.Sval);
//  ds1.ival = ival;
//  qp.pop_m ();
//}

// LE -------------------------------------------------------------------------------------------------
void 
qproc_t::inst_ile (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.ival <= ds2.ival)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_lle (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = (ds1.lval <= ds2.lval)?1:0;
  qp.pop_m ();
}

void 
qproc_t::inst_dle (qproc_t &qp)
{
  Datum &ds1 = qp.s1();
  Datum &ds2 = qp.s2();
  ds1.ival = __le_doubles (ds1.dval, ds2.dval);
  qp.pop_m ();
}

//void 
//qproc_t::inst_sle (qproc_t &qp)
//{
//  Datum &ds1 = qp.s1();
//  Datum &ds2 = qp.s2();
//  int ival = (*ds1.Sval <= *ds2.Sval)?1:0;
//  DEL_SMTH (decore::str_t, ds2.Sval);
//  DEL_SMTH (decore::str_t, ds1.Sval);
//  ds1.ival = ival;
//  qp.pop_m ();
//}

//-------------------------------------------------------------------
void
qproc_t::inst_call(qproc_t &qp)
{
	qp.ip_++;
	proc_def_t *proc = (proc_def_t *)qp.ip_->ptr_;

	//Datum *savsp = qp.stackp_;
	qp.enter_call(proc);
	qp.ip_ = proc->entry_ - 1;


	/*
	qp.exec(proc->entry_);
	Datum d = qp.pop_m();
	assert(qp.stackp_ == savsp);
	int n = proc->get_nargs();
	for (int i = n - 1; i >= 0; i--)
	{
		dataTypes type = proc->get_arg_type(i);
	again:
		qp.stackp_--;
		switch (type) {
		case ftUnknown:
			type = dataTypes(qp.stackp_->ival);
			goto again;
			break;
			//case ftString:
			//  DEL_SMTH (decore::str_t, qp.stackp_->Sval);
			//  break;
		};
	}
	qp.push(d);
	*/
}

void 
qproc_t::inst_shcall (qproc_t &qp)
{

	qp.ip_++;
	shcall_t *proc = (shcall_t *)qp.ip_->ptr_;
	
	Datum *savsp = qp.stackp_;
	Datum d = proc->proc_ (qp, qp.stackp_ - proc->get_nrealargs ());
	assert (qp.stackp_ == savsp);
	int n = proc->get_nargs ();
	for (int i = n - 1; i >= 0; i--)
	{
		dataTypes type = proc->get_arg_type (i);
	again:
		qp.pop_m(true);
		//qp.stackp_--;
		switch (type) {
		case ftUnknown:
			type = dataTypes (qp.stackp_->ival);
			goto again;
			break;
		//case ftString:
		//  DEL_SMTH (decore::str_t, qp.stackp_->Sval);
		//  break;
		};
	}
	qp.push(d);
}


void 
qproc_t::inst_param_getval (qproc_t &qp)
{
  qp.ip_++;
  var_item_t *par = (var_item_t *)qp.ip_->ptr_;
  qp.push (par->data_);
  //if (ftString == par->type_)
   // {
    //  (qp.stackp_ - 1)->Sval = NEW_SMTH_P (decore::str_t, (*(qp.stackp_ - 1)->Sval));      
    //}
}

void 
qproc_t::inst_return(qproc_t &qp)
{
	qp.leave_call();
	//qp.state_ = qpStopped;
}


void 
qproc_t::inst_ipreinc(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	d2.Dval->ival++;
	d2 = *d2.Dval;
}

void 
qproc_t::inst_lpreinc(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	d2.Dval->lval++;
	d2 = *d2.Dval;
}

void
qproc_t::inst_dpreinc(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	d2.Dval->dval++;
	d2 = *d2.Dval;
}

void 
qproc_t::inst_ipredec(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	d2.Dval->ival--;
	d2 = *d2.Dval;
}

void
qproc_t::inst_lpredec(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	d2.Dval->lval--;
	d2 = *d2.Dval;
}

void
qproc_t::inst_dpredec(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	d2.Dval->dval--;
	d2 = *d2.Dval;
}

void 
qproc_t::inst_ipostinc(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	Datum &d0 = *d2.Dval;
	d2 = d0;
	d0.ival++;
}

void
qproc_t::inst_lpostinc(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	Datum &d0 = *d2.Dval;
	d2 = d0;
	d0.lval++;
}

void
qproc_t::inst_dpostinc(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	Datum &d0 = *d2.Dval;
	d2 = d0;
	d0.dval++;
}

void 
qproc_t::inst_ipostdec(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	Datum &d0 = *d2.Dval;
	d2 = d0;
	d0.ival--;
}

void
qproc_t::inst_lpostdec(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	Datum &d0 = *d2.Dval;
	d2 = d0;
	d0.lval--;
}

void
qproc_t::inst_dpostdec(qproc_t &qp)
{
	Datum &d2 = qp.s2();
	Datum &d0 = *d2.Dval;
	d2 = d0;
	d0.dval--;
}

//----------------------------------------------------------------------------------

qprocState 
qproc_t::interrupt ()
{
  qprocState st = state_;
  state_ = qpInterrupted;
  return st;
}

qprocState 
qproc_t::enter_call(const proc_def_t *proc)
{
	state_ = qpReady;
	size_t nvars = proc->vars_.ht_locals_.size();
	fp_->ret_ip_ = ip_;
	if (fp_ - frames_ >= max_frames_)
	{
		int rr = 0;
	}
	fp_->savsp_ = stackp_;
	stackp_ += nvars;
	fp_->proc_ = proc;
	fp_++;
	return state_;
}

qprocState
qproc_t::leave_call()
{
	if (fp_ == frames_)
		return state_ = qpStopped;
	fp_--;

	Datum d = pop_m();

	size_t nvars = fp_->proc_->vars_.ht_locals_.size();
	stackp_ -= nvars;

	assert(stackp_ == fp_->savsp_);
	int n = fp_->proc_->get_nargs();
	for (int i = n - 1; i >= 0; i--)
	{
		dataTypes type = fp_->proc_->get_arg_type(i);
	again:
		pop_m(true);
		switch (type) {
		case ftUnknown:
			type = dataTypes(stackp_->ival);
			goto again;
			break;
			//case ftString:
			//  DEL_SMTH (decore::str_t, qp.stackp_->Sval);
			//  break;
		};
	}

	push(d);
	ip_ = fp_->ret_ip_;
	return state_;
}

qprocState
qproc_t::exec_call (const inst_t *inst)
{
  if (NULL == inst)
    return qpStopped;
    
  state_ = qpReady;
  fp_->ret_ip_ = ip_;
  fp_++;
  
  ip_ = inst - 1;
  return state_;
}

qprocState
qproc_t::exec (const inst_t *inst)
{
  state_ = qpReady;
  ip_ = inst;
  if (NULL == ip_)
    return state_ = qpStopped;
  for (;state_ != qpStopped;)
    {
      if (NULL == ip_->proc_)
        {
			leave_call();
          //if (fp_ == frames_)
          //  return state_ = qpStopped;
          //fp_--;
          //ip_ = fp_->ip_;
          continue;
        }      
      if (qpInterrupted == state_)
        return state_;
      
      if (NULL == ip_->proc_)
        continue;
        
      ip_->proc_ (*this);
      ip_++;
    }
  if (NULL == ip_->proc_ && qpInterrupted != state_)
    state_ = qpStopped;
  return state_;
}

qprocState
qproc_t::exec_raw (const inst_t *inst)
{
  state_ = qpReady;
  ip_ = inst;
  if (NULL == ip_)
    return qpStopped;
  for (;state_ != qpStopped;)
    {
      if (NULL == ip_->proc_)
        return qpStopped;
      
      if (NULL == ip_->proc_)
        continue;
        
      ip_->proc_ (*this);
      ip_++;
    }
  return qpStopped;
}

qprocState
qproc_t::exec_safe (const inst_t *inst)
{
  if (NULL == inst)
    return qpStopped;
    
  const inst_t *ip = ip_;
  Datum *pd = stackp_;
  qprocState state = state_;
  qprocState ret = exec (inst);
  ip_ = ip;
  state_ = state;
  stackp_ = pd;
  return ret;
}

