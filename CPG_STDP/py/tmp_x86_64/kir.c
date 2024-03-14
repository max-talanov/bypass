/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
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
 
#define nrn_init _nrn_init__kir
#define _nrn_initial _nrn_initial__kir
#define nrn_cur _nrn_cur__kir
#define _nrn_current _nrn_current__kir
#define nrn_jacob _nrn_jacob__kir
#define nrn_state _nrn_state__kir
#define _net_receive _net_receive__kir 
#define rate rate__kir 
#define states states__kir 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define gkbar _p[0]
#define gkbar_columnindex 0
#define vhalfl _p[1]
#define vhalfl_columnindex 1
#define kl _p[2]
#define kl_columnindex 2
#define vhalft _p[3]
#define vhalft_columnindex 3
#define at _p[4]
#define at_columnindex 4
#define bt _p[5]
#define bt_columnindex 5
#define q10 _p[6]
#define q10_columnindex 6
#define ik _p[7]
#define ik_columnindex 7
#define l _p[8]
#define l_columnindex 8
#define Dl _p[9]
#define Dl_columnindex 9
#define gk _p[10]
#define gk_columnindex 10
#define ek _p[11]
#define ek_columnindex 11
#define _g _p[12]
#define _g_columnindex 12
#define _ion_ek	*_ppvar[0]._pval
#define _ion_ik	*_ppvar[1]._pval
#define _ion_dikdv	*_ppvar[2]._pval
 
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
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_rate(void);
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
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_kir", _hoc_setdata,
 "rate_kir", _hoc_rate,
 0, 0
};
 /* declare global and static user variables */
#define linf linf_kir
 double linf = 0;
#define taul taul_kir
 double taul = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gkbar_kir", "S/cm2",
 "vhalfl_kir", "mV",
 "kl_kir", "mV",
 "vhalft_kir", "mV",
 "at_kir", "/ms",
 "bt_kir", "/ms",
 "ik_kir", "mA/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double l0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "linf_kir", &linf_kir,
 "taul_kir", &taul_kir,
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
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"kir",
 "gkbar_kir",
 "vhalfl_kir",
 "kl_kir",
 "vhalft_kir",
 "at_kir",
 "bt_kir",
 "q10_kir",
 0,
 "ik_kir",
 0,
 "l_kir",
 0,
 0};
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 13, _prop);
 	/*initialize range parameters*/
 	gkbar = 1.44e-05;
 	vhalfl = -98.92;
 	kl = 10.89;
 	vhalft = 67.0828;
 	at = 0.00610779;
 	bt = 0.0817741;
 	q10 = 1;
 	_prop->param = _p;
 	_prop->param_size = 13;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
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

 void _kir_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 0);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 13, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 kir /home/yulia/bypass/CPG_STDP/py/mod_files/kir.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "inward rectifier potassium (Kir) channel";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rate(double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rate ( _threadargscomma_ v ) ;
   Dl = ( linf - l ) / taul ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 rate ( _threadargscomma_ v ) ;
 Dl = Dl  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taul )) ;
  return 0;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rate ( _threadargscomma_ v ) ;
    l = l + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / taul)))*(- ( ( ( linf ) ) / taul ) / ( ( ( ( - 1.0 ) ) ) / taul ) - l) ;
   }
  return 0;
}
 
static int  rate (  double _lv ) {
   double _lqt ;
 _lqt = pow( q10 , ( ( celsius - 33.0 ) / 10.0 ) ) ;
   linf = 1.0 / ( 1.0 + exp ( ( _lv - vhalfl ) / kl ) ) ;
   taul = 1.0 / ( _lqt * ( at * exp ( - _lv / vhalft ) + bt * exp ( _lv / vhalft ) ) ) ;
    return 0; }
 
static void _hoc_rate(void) {
  double _r;
   _r = 1.;
 rate (  *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
     _ode_spec1 ();
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ek = _ion_ek;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_k_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 4);
 }

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  l = l0;
 {
   rate ( _threadargscomma_ v ) ;
   l = linf ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
  ek = _ion_ek;
 initmodel();
 }}

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   gk = gkbar * l ;
   ik = gk * ( v - ek ) ;
   }
 _current += ik;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
  ek = _ion_ek;
 _g = _nrn_current(_v + .001);
 	{ double _dik;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ik += ik ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
 
}}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
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
  ek = _ion_ek;
 { error =  states();
 if(error){fprintf(stderr,"at line 80 in file kir.mod:\n	SOLVE states METHOD cnexp	: solve differential equations in states with method 'cnexp'\n"); nrn_complain(_p); abort_run(error);}
 } }}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = l_columnindex;  _dlist1[0] = Dl_columnindex;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/home/yulia/bypass/CPG_STDP/py/mod_files/kir.mod";
static const char* nmodl_file_text = 
  "TITLE inward rectifier potassium (Kir) channel\n"
  "\n"
  "COMMENT\n"
  "\n"
  "Mod File by A. Hanuschkin <AH, 2011> for:\n"
  "Yim MY, Hanuschkin A, Wolfart J (2015) Hippocampus 25:297-308.\n"
  "http://onlinelibrary.wiley.com/doi/10.1002/hipo.22373/abstract\n"
  "\n"
  "Channel description and parameters from:\n"
  "Stegen M, Kirchheim F, Hanuschkin A, Staszewski O, Veh R, and Wolfart J. Cerebral Cortex, 22:9, 2087-2101, 2012.\n"
  "\n"
  "Mod File history:\n"
  "- tau(V), linf(V) fitted to experimental values of human dentate gyrus granual cells\n"
  "- ModelDB file adapted from\n"
  "  Wolf JA, Moyer JT, Lazarewicz MT, Contreras D, Benoit-Marand M, O'Donnell P, Finkel LH (2005) J Neurosci 25:9080-95\n"
  "  https://senselab.med.yale.edu/ModelDB/ShowModel.cshtml?model=112834&file=/nacb_msp/kir.mod\n"
  "- file modified to uses nomoclature of\n"
  "  Li X, Ascoli GA (2006) J of Comput Neurosci 21(2):191-209\n"
  "  Li X, Ascoli GA (2008) Neural Comput 20:1717-31\n"
  "\n"
  "A. Hanuschkin(c) 2011,2012\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "        (S)  = (siemens)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	v 		(mV)\n"
  "	gkbar  = 1.44e-05	(S/cm2) 	: to be fitted\n"
  "\n"
  "	: Boltzman steady state curve\n"
  "        vhalfl = -98.92  (mV)    		: fitted to patch data, Stegen et al. 2012\n"
  "        kl = 10.89       (mV)    		: Stegen et al. 2012\n"
  "\n"
  "	: tau_infty\n"
  "        vhalft=67.0828	 (mV)    		: fitted #100 \\muM sens curr 350a,  Stegen et al. 2012\n"
  "        at=0.00610779	 (/ms)   		: Stegen et al. 2012\n"
  "	bt=0.0817741	 (/ms)	 		: Note: typo in Stegen et al. 2012\n"
  "\n"
  "	: Temperature dependence\n"
  "        celsius         (degC)  		: unused if q10 == 1.\n"
  "        q10 = 1.                              	: temperature scaling\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX kir\n"
  "	USEION k READ ek WRITE ik\n"
  "        RANGE  ik, gkbar, vhalfl, kl, vhalft, at, bt, q10\n"
  "        GLOBAL linf,taul\n"
  "}\n"
  "\n"
  "\n"
  "STATE {\n"
  "        l\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "        ik                              (mA/cm2)\n"
  "        gk                              (S/cm2)\n"
  "        ek                              (mV)\n"
  "        linf\n"
  "        taul\n"
  "}\n"
  "\n"
  "\n"
  "INITIAL {\n"
  "	rate(v)\n"
  "	l=linf\n"
  "}\n"
  "\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp	: solve differential equations in states with method 'cnexp'\n"
  "	gk = gkbar*l			: use state l to calulate gk\n"
  "        ik = gk * ( v - ek )		: calculate ik\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "DERIVATIVE states {\n"
  "        rate(v)\n"
  "        l' =  (linf - l)/taul		: differential equation\n"
  "}\n"
  "\n"
  "PROCEDURE rate(v (mV)) { :callable from hoc\n"
  "        LOCAL qt\n"
  "	qt=q10^((celsius-33)/10)\n"
  "        linf = 1/(1 + exp((v-vhalfl)/kl))			: l_steadystate\n"
  " 	taul = 1/(qt *(at*exp(-v/vhalft) + bt*exp(v/vhalft) ))\n"
  "}\n"
  ;
#endif
