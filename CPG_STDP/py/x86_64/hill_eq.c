/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__fHill
#define _nrn_initial _nrn_initial__fHill
#define nrn_cur _nrn_cur__fHill
#define _nrn_current _nrn_current__fHill
#define nrn_jacob _nrn_jacob__fHill
#define nrn_state _nrn_state__fHill
#define _net_receive _net_receive__fHill 
#define state_hill state_hill__fHill 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define a0 _p[0]
#define a0_columnindex 0
#define b0 _p[1]
#define b0_columnindex 1
#define c0 _p[2]
#define c0_columnindex 2
#define d0 _p[3]
#define d0_columnindex 3
#define p0 _p[4]
#define p0_columnindex 4
#define g1 _p[5]
#define g1_columnindex 5
#define g2 _p[6]
#define g2_columnindex 6
#define xm_init _p[7]
#define xm_init_columnindex 7
#define xce_init _p[8]
#define xce_init_columnindex 8
#define Kse _p[9]
#define Kse_columnindex 9
#define F _p[10]
#define F_columnindex 10
#define Fc _p[11]
#define Fc_columnindex 11
#define A _p[12]
#define A_columnindex 12
#define xce _p[13]
#define xce_columnindex 13
#define xm _p[14]
#define xm_columnindex 14
#define DA _p[15]
#define DA_columnindex 15
#define Dxce _p[16]
#define Dxce_columnindex 16
#define Dxm _p[17]
#define Dxm_columnindex 17
#define mgi _p[18]
#define mgi_columnindex 18
#define cli _p[19]
#define cli_columnindex 19
#define v _p[20]
#define v_columnindex 20
#define _g _p[21]
#define _g_columnindex 21
#define _ion_mgi	*_ppvar[0]._pval
#define _ion_cli	*_ppvar[1]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_dxdt(void);
 static void _hoc_g(void);
 static void _hoc_xse(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_fHill", _hoc_setdata,
 "dxdt_fHill", _hoc_dxdt,
 "g_fHill", _hoc_g,
 "xse_fHill", _hoc_xse,
 0, 0
};
#define dxdt dxdt_fHill
#define g g_fHill
#define xse xse_fHill
 extern double dxdt( _threadargsprotocomma_ double , double );
 extern double g( _threadargsprotocomma_ double );
 extern double xse( _threadargsprotocomma_ double , double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 0,0
};
 static double A0 = 0;
 static double delta_t = 0.01;
 static double xm0 = 0;
 static double xce0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[2]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"fHill",
 "a0_fHill",
 "b0_fHill",
 "c0_fHill",
 "d0_fHill",
 "p0_fHill",
 "g1_fHill",
 "g2_fHill",
 "xm_init_fHill",
 "xce_init_fHill",
 "Kse_fHill",
 0,
 "F_fHill",
 "Fc_fHill",
 0,
 "A_fHill",
 "xce_fHill",
 "xm_fHill",
 0,
 0};
 static Symbol* _mg_sym;
 static Symbol* _cl_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 22, _prop);
 	/*initialize range parameters*/
 	a0 = 2.35;
 	b0 = 24.35;
 	c0 = -7.4;
 	d0 = 30.3;
 	p0 = 23;
 	g1 = -8;
 	g2 = 21.4;
 	xm_init = -8;
 	xce_init = -8;
 	Kse = 0.4;
 	_prop->param = _p;
 	_prop->param_size = 22;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_mg_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* mgi */
 prop_ion = need_memb(_cl_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[1]._pval = &prop_ion->param[1]; /* cli */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _hill_eq_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("mg", 2.0);
 	ion_reg("cl", -1.0);
 	_mg_sym = hoc_lookup("mg_ion");
 	_cl_sym = hoc_lookup("cl_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 22, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "mg_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 fHill /home/yulia/bypass/CPG_STDP/py/mod_files/hill_eq.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Modified Hill-Mashima muscle model";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int state_hill(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   Fc = p0 * g ( _threadargscomma_ xm ) * A ;
   Dxce = dxdt ( _threadargscomma_ F , Fc ) ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 Fc = p0 * g ( _threadargscomma_ xm ) * A ;
 Dxce = Dxce  / (1. - dt*( 0.0 )) ;
  return 0;
}
 /*END CVODE*/
 static int state_hill (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   Fc = p0 * g ( _threadargscomma_ xm ) * A ;
    xce = xce - dt*(- ( dxdt ( _threadargscomma_ F , Fc ) ) ) ;
   }
  return 0;
}
 
double xse ( _threadargsprotocomma_ double _lx , double _ly ) {
   double _lxse;
 double _ld_xm , _ld_xce , _ld_se ;
 _ld_xm = xm - xm_init ;
   _ld_xce = xce - xce_init ;
   _ld_se = _ld_xm - _ld_xce ;
   if ( _ld_se <= 0.0 ) {
     _lxse = 0.0 ;
     }
   else {
     _lxse = _ld_se ;
     }
   
return _lxse;
 }
 
static void _hoc_xse(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  xse ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double g ( _threadargsprotocomma_ double _lx ) {
   double _lg;
 _lg = exp ( - pow( ( ( _lx - g1 ) / g2 ) , 2.0 ) ) ;
   
return _lg;
 }
 
static void _hoc_g(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  g ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double dxdt ( _threadargsprotocomma_ double _lx , double _lxc ) {
   double _ldxdt;
 double _lgain_length ;
 if ( _lx <= _lxc ) {
     _ldxdt = ( pow( 10.0 , - 3.0 ) ) * ( - b0 * ( _lxc - _lx ) ) / ( _lx + a0 * _lxc / p0 ) ;
     }
   else {
     _lgain_length = ( - d0 * ( _lxc - _lx ) ) / ( 2.0 * _lxc - _lx + c0 * _lxc / p0 ) ;
     if ( _lgain_length <= 0.0 ) {
       _ldxdt = ( pow( 10.0 , - 3.0 ) ) * 1e5 ;
       }
     else {
       _ldxdt = ( pow( 10.0 , - 3.0 ) ) * _lgain_length ;
       }
     }
   
return _ldxdt;
 }
 
static void _hoc_dxdt(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  dxdt ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  mgi = _ion_mgi;
  cli = _ion_cli;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  mgi = _ion_mgi;
  cli = _ion_cli;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_mg_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 1, 1);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  A = A0;
  xce = xce0;
  xm = xm0;
 {
   A = 0.0 ;
   xm = xm_init ;
   xce = xce_init ;
   F = 1e-5 ;
   }
 
}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  mgi = _ion_mgi;
  cli = _ion_cli;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  mgi = _ion_mgi;
  cli = _ion_cli;
 {   state_hill(_p, _ppvar, _thread, _nt);
  } {
   double _ld_xm , _ld_xce , _ld_se ;
 A = mgi ;
   xm = cli ;
   F = p0 * Kse * xse ( _threadargscomma_ xm , xce ) ;
   }
}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = xce_columnindex;  _dlist1[0] = Dxce_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/yulia/bypass/CPG_STDP/py/mod_files/hill_eq.mod";
static const char* nmodl_file_text = 
  "TITLE Modified Hill-Mashima muscle model\n"
  "\n"
  "UNITS {}\n"
  "\n"
  "NEURON {\n"
  "    SUFFIX fHill\n"
  "    RANGE a0, b0, c0, d0\n"
  "	RANGE p0, g1, g2, g3\n"
  "	RANGE Kse, A, Fc, F\n"
  "	RANGE xm_init, xm, xce_init, xce\n"
  "	USEION mg READ mgi VALENCE 2\n"
  "	USEION cl READ cli VALENCE -1\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	a0 = 2.35		:[N]\n"
  "	b0 = 24.35		:[mm*s-1]\n"
  "	c0 = -7.4		:[N]\n"
  "	d0 = 30.3		:[mm*s-1]\n"
  "	p0 = 23			:[N]\n"
  "	g1 = -8			:[mm]\n"
  "	g2 = 21.4		:[mm]\n"
  "	xm_init = -8	:[mm]\n"
  "	xce_init = -8	:[mm]\n"
  "	Kse = 0.4		:[mm-1]\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	A\n"
  "	xce\n"
  "	xm\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	F\n"
  "	Fc\n"
  "	mgi\n"
  "	cli\n"
  "}\n"
  "\n"
  "BREAKPOINT { LOCAL d_xm, d_xce, d_se\n"
  "	A = mgi\n"
  "	xm = cli\n"
  "\n"
  "	SOLVE state_hill METHOD cnexp\n"
  "\n"
  "	F = p0*Kse*xse(xm, xce)\n"
  "}\n"
  "\n"
  "DERIVATIVE state_hill {\n"
  "	Fc = p0*g(xm)*A\n"
  "	xce' = dxdt (F, Fc)\n"
  "}\n"
  "\n"
  "FUNCTION xse (x, y) { LOCAL d_xm, d_xce, d_se\n"
  "	d_xm = xm - xm_init\n"
  "	d_xce = xce - xce_init\n"
  "	d_se = d_xm - d_xce\n"
  "\n"
  "	if (d_se <= 0) {xse = 0}\n"
  "	else {xse = d_se}\n"
  "}\n"
  "\n"
  "FUNCTION g (x) {\n"
  "	g = exp(-((x-g1)/g2)^2)\n"
  "}\n"
  "\n"
  "FUNCTION dxdt (x, xc) {LOCAL gain_length\n"
  "	if (x <= xc) {\n"
  "		dxdt = (10^-3)*(-b0*(xc-x))/(x+a0*xc/p0)\n"
  "	} else {\n"
  "		gain_length = (-d0*(xc-x))/(2*xc-x+c0*xc/p0)\n"
  "		if (gain_length <= 0) {dxdt = (10^-3)*1e5}\n"
  "		else {dxdt = (10^-3)*gain_length}\n"
  "	}\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	A = 0\n"
  "	xm = xm_init\n"
  "	xce = xce_init\n"
  "	F=1e-5\n"
  "}\n"
  ;
#endif
