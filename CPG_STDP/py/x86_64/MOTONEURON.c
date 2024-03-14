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
 
#define nrn_init _nrn_init__motoneuron
#define _nrn_initial _nrn_initial__motoneuron
#define nrn_cur _nrn_cur__motoneuron
#define _nrn_current _nrn_current__motoneuron
#define nrn_jacob _nrn_jacob__motoneuron
#define nrn_state _nrn_state__motoneuron
#define _net_receive _net_receive__motoneuron 
#define evaluate_fct evaluate_fct__motoneuron 
#define states states__motoneuron 
 
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
#define gnabar _p[0]
#define gnabar_columnindex 0
#define gl _p[1]
#define gl_columnindex 1
#define gkrect _p[2]
#define gkrect_columnindex 2
#define gcaN _p[3]
#define gcaN_columnindex 3
#define gcaL _p[4]
#define gcaL_columnindex 4
#define gcak _p[5]
#define gcak_columnindex 5
#define ena _p[6]
#define ena_columnindex 6
#define ek _p[7]
#define ek_columnindex 7
#define el _p[8]
#define el_columnindex 8
#define il _p[9]
#define il_columnindex 9
#define m_inf _p[10]
#define m_inf_columnindex 10
#define mc_inf _p[11]
#define mc_inf_columnindex 11
#define h_inf _p[12]
#define h_inf_columnindex 12
#define hc_inf _p[13]
#define hc_inf_columnindex 13
#define n_inf _p[14]
#define n_inf_columnindex 14
#define p_inf _p[15]
#define p_inf_columnindex 15
#define tau_m _p[16]
#define tau_m_columnindex 16
#define tau_h _p[17]
#define tau_h_columnindex 17
#define tau_p _p[18]
#define tau_p_columnindex 18
#define tau_n _p[19]
#define tau_n_columnindex 19
#define tau_mc _p[20]
#define tau_mc_columnindex 20
#define tau_hc _p[21]
#define tau_hc_columnindex 21
#define p _p[22]
#define p_columnindex 22
#define m _p[23]
#define m_columnindex 23
#define h _p[24]
#define h_columnindex 24
#define n _p[25]
#define n_columnindex 25
#define cai _p[26]
#define cai_columnindex 26
#define mc _p[27]
#define mc_columnindex 27
#define hc _p[28]
#define hc_columnindex 28
#define Dp _p[29]
#define Dp_columnindex 29
#define Dm _p[30]
#define Dm_columnindex 30
#define Dh _p[31]
#define Dh_columnindex 31
#define Dn _p[32]
#define Dn_columnindex 32
#define Dcai _p[33]
#define Dcai_columnindex 33
#define Dmc _p[34]
#define Dmc_columnindex 34
#define Dhc _p[35]
#define Dhc_columnindex 35
#define ina _p[36]
#define ina_columnindex 36
#define ica _p[37]
#define ica_columnindex 37
#define ik _p[38]
#define ik_columnindex 38
#define Eca _p[39]
#define Eca_columnindex 39
#define cao _p[40]
#define cao_columnindex 40
#define v _p[41]
#define v_columnindex 41
#define _g _p[42]
#define _g_columnindex 42
#define _ion_ina	*_ppvar[0]._pval
#define _ion_dinadv	*_ppvar[1]._pval
#define _ion_ik	*_ppvar[2]._pval
#define _ion_dikdv	*_ppvar[3]._pval
#define _ion_cao	*_ppvar[4]._pval
#define _ion_ica	*_ppvar[5]._pval
#define _ion_dicadv	*_ppvar[6]._pval
 
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
 static void _hoc_Exp(void);
 static void _hoc_alpham(void);
 static void _hoc_betam(void);
 static void _hoc_evaluate_fct(void);
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
 "setdata_motoneuron", _hoc_setdata,
 "Exp_motoneuron", _hoc_Exp,
 "alpham_motoneuron", _hoc_alpham,
 "betam_motoneuron", _hoc_betam,
 "evaluate_fct_motoneuron", _hoc_evaluate_fct,
 0, 0
};
#define Exp Exp_motoneuron
#define alpham alpham_motoneuron
#define betam betam_motoneuron
 extern double Exp( _threadargsprotocomma_ double );
 extern double alpham( _threadargsprotocomma_ double );
 extern double betam( _threadargsprotocomma_ double );
 /* declare global and static user variables */
#define F F_motoneuron
 double F = 96485.3;
#define R R_motoneuron
 double R = 8.31447;
#define amC amC_motoneuron
 double amC = 5;
#define amB amB_motoneuron
 double amB = 66;
#define amA amA_motoneuron
 double amA = 0.4;
#define bmC bmC_motoneuron
 double bmC = 5;
#define bmB bmB_motoneuron
 double bmB = 32;
#define bmA bmA_motoneuron
 double bmA = 0.4;
#define ca0 ca0_motoneuron
 double ca0 = 2;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gnabar_motoneuron", "mho/cm2",
 "gl_motoneuron", "mho/cm2",
 "gkrect_motoneuron", "mho/cm2",
 "gcaN_motoneuron", "mho/cm2",
 "gcaL_motoneuron", "mho/cm2",
 "gcak_motoneuron", "mho/cm2",
 "ena_motoneuron", "mV",
 "ek_motoneuron", "mV",
 "el_motoneuron", "mV",
 "il_motoneuron", "mA/cm2",
 0,0
};
 static double cai0 = 0;
 static double delta_t = 1;
 static double hc0 = 0;
 static double h0 = 0;
 static double mc0 = 0;
 static double m0 = 0;
 static double n0 = 0;
 static double p0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ca0_motoneuron", &ca0_motoneuron,
 "amA_motoneuron", &amA_motoneuron,
 "amB_motoneuron", &amB_motoneuron,
 "amC_motoneuron", &amC_motoneuron,
 "bmA_motoneuron", &bmA_motoneuron,
 "bmB_motoneuron", &bmB_motoneuron,
 "bmC_motoneuron", &bmC_motoneuron,
 "R_motoneuron", &R_motoneuron,
 "F_motoneuron", &F_motoneuron,
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
 
#define _cvode_ieq _ppvar[7]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"motoneuron",
 "gnabar_motoneuron",
 "gl_motoneuron",
 "gkrect_motoneuron",
 "gcaN_motoneuron",
 "gcaL_motoneuron",
 "gcak_motoneuron",
 "ena_motoneuron",
 "ek_motoneuron",
 "el_motoneuron",
 0,
 "il_motoneuron",
 "m_inf_motoneuron",
 "mc_inf_motoneuron",
 "h_inf_motoneuron",
 "hc_inf_motoneuron",
 "n_inf_motoneuron",
 "p_inf_motoneuron",
 "tau_m_motoneuron",
 "tau_h_motoneuron",
 "tau_p_motoneuron",
 "tau_n_motoneuron",
 "tau_mc_motoneuron",
 "tau_hc_motoneuron",
 0,
 "p_motoneuron",
 "m_motoneuron",
 "h_motoneuron",
 "n_motoneuron",
 "cai_motoneuron",
 "mc_motoneuron",
 "hc_motoneuron",
 0,
 0};
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 43, _prop);
 	/*initialize range parameters*/
 	gnabar = 0.05;
 	gl = 0.002;
 	gkrect = 0.3;
 	gcaN = 0.05;
 	gcaL = 0.0001;
 	gcak = 0.3;
 	ena = 50;
 	ek = -80;
 	el = -70;
 	_prop->param = _p;
 	_prop->param_size = 43;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 8, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[1]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[4]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[5]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[6]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
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

 void _MOTONEURON_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	ion_reg("k", -10000.);
 	ion_reg("ca", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	_k_sym = hoc_lookup("k_ion");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 43, 8);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 6, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 7, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 motoneuron /home/yulia/bypass/CPG_STDP/py/mod_files/MOTONEURON.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Motor Axon Soma";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int evaluate_fct(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[7], _dlist1[7];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   evaluate_fct ( _threadargscomma_ v ) ;
   Dm = ( m_inf - m ) / tau_m ;
   Dh = ( h_inf - h ) / tau_h ;
   Dp = ( p_inf - p ) / tau_p ;
   Dn = ( n_inf - n ) / tau_n ;
   Dmc = ( mc_inf - mc ) / tau_mc ;
   Dhc = ( hc_inf - hc ) / tau_hc ;
   Dcai = 0.01 * ( - ( ica ) - 4.0 * cai ) ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 evaluate_fct ( _threadargscomma_ v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_m )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_h )) ;
 Dp = Dp  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_p )) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_n )) ;
 Dmc = Dmc  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_mc )) ;
 Dhc = Dhc  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_hc )) ;
 Dcai = Dcai  / (1. - dt*( ( 0.01 )*( ( ( - ( 4.0 )*( 1.0 ) ) ) ) )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   evaluate_fct ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_m)))*(- ( ( ( m_inf ) ) / tau_m ) / ( ( ( ( - 1.0 ) ) ) / tau_m ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h)))*(- ( ( ( h_inf ) ) / tau_h ) / ( ( ( ( - 1.0 ) ) ) / tau_h ) - h) ;
    p = p + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_p)))*(- ( ( ( p_inf ) ) / tau_p ) / ( ( ( ( - 1.0 ) ) ) / tau_p ) - p) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( n_inf ) ) / tau_n ) / ( ( ( ( - 1.0 ) ) ) / tau_n ) - n) ;
    mc = mc + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_mc)))*(- ( ( ( mc_inf ) ) / tau_mc ) / ( ( ( ( - 1.0 ) ) ) / tau_mc ) - mc) ;
    hc = hc + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_hc)))*(- ( ( ( hc_inf ) ) / tau_hc ) / ( ( ( ( - 1.0 ) ) ) / tau_hc ) - hc) ;
    cai = cai + (1. - exp(dt*(( 0.01 )*( ( ( - ( 4.0 )*( 1.0 ) ) ) ))))*(- ( ( 0.01 )*( ( - ( ica ) ) ) ) / ( ( 0.01 )*( ( ( - ( 4.0 )*( 1.0 ) ) ) ) ) - cai) ;
   }
  return 0;
}
 
static int  evaluate_fct ( _threadargsprotocomma_ double _lv ) {
   double _la , _lb , _lv2 ;
 _la = alpham ( _threadargscomma_ _lv ) ;
   _lb = betam ( _threadargscomma_ _lv ) ;
   tau_m = 1.0 / ( _la + _lb ) ;
   m_inf = _la / ( _la + _lb ) ;
   tau_h = 30.0 / ( Exp ( _threadargscomma_ ( _lv + 60.0 ) / 15.0 ) + Exp ( _threadargscomma_ - ( _lv + 60.0 ) / 16.0 ) ) ;
   h_inf = 1.0 / ( 1.0 + Exp ( _threadargscomma_ ( _lv + 65.0 ) / 7.0 ) ) ;
   tau_n = 5.0 / ( Exp ( _threadargscomma_ ( _lv + 50.0 ) / 40.0 ) + Exp ( _threadargscomma_ - ( _lv + 50.0 ) / 50.0 ) ) ;
   n_inf = 1.0 / ( 1.0 + Exp ( _threadargscomma_ - ( _lv + 38.0 ) / 15.0 ) ) ;
   tau_mc = 15.0 ;
   mc_inf = 1.0 / ( 1.0 + Exp ( _threadargscomma_ - ( _lv + 32.0 ) / 5.0 ) ) ;
   tau_hc = 50.0 ;
   hc_inf = 1.0 / ( 1.0 + Exp ( _threadargscomma_ ( _lv + 50.0 ) / 5.0 ) ) ;
   tau_p = 400.0 ;
   p_inf = 1.0 / ( 1.0 + Exp ( _threadargscomma_ - ( _lv + 55.8 ) / 3.7 ) ) ;
    return 0; }
 
static void _hoc_evaluate_fct(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 evaluate_fct ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double alpham ( _threadargsprotocomma_ double _lx ) {
   double _lalpham;
 if ( fabs ( ( _lx + amB ) / amC ) < 1e-6 ) {
     _lalpham = amA * amC ;
     }
   else {
     _lalpham = ( amA * ( _lx + amB ) ) / ( 1.0 - Exp ( _threadargscomma_ - ( _lx + amB ) / amC ) ) ;
     }
   
return _lalpham;
 }
 
static void _hoc_alpham(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  alpham ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double betam ( _threadargsprotocomma_ double _lx ) {
   double _lbetam;
 if ( fabs ( ( _lx + bmB ) / bmC ) < 1e-6 ) {
     _lbetam = - bmA * bmC ;
     }
   else {
     _lbetam = ( bmA * ( - ( _lx + bmB ) ) ) / ( 1.0 - Exp ( _threadargscomma_ ( _lx + bmB ) / bmC ) ) ;
     }
   
return _lbetam;
 }
 
static void _hoc_betam(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  betam ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double Exp ( _threadargsprotocomma_ double _lx ) {
   double _lExp;
 if ( _lx < - 100.0 ) {
     _lExp = 0.0 ;
     }
   else {
     _lExp = exp ( _lx ) ;
     }
   
return _lExp;
 }
 
static void _hoc_Exp(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  Exp ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 7;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cao = _ion_cao;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
    }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 7; ++_i) {
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
  cao = _ion_cao;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 3, 4);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 4, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 5, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 6, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  cai = cai0;
  hc = hc0;
  h = h0;
  mc = mc0;
  m = m0;
  n = n0;
  p = p0;
 {
   evaluate_fct ( _threadargscomma_ v ) ;
   m = m_inf ;
   h = h_inf ;
   p = p_inf ;
   n = n_inf ;
   mc = mc_inf ;
   hc = hc_inf ;
   cai = 0.0001 ;
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
  cao = _ion_cao;
 initmodel(_p, _ppvar, _thread, _nt);
   }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ina = gnabar * m * m * m * h * ( v - ena ) ;
   ik = gkrect * n * n * n * n * ( v - ek ) + gcak * ( cai * cai ) / ( cai * cai + 0.014 * 0.014 ) * ( v - ek ) ;
   il = gl * ( v - el ) ;
   Eca = ( ( 1000.0 * R * 309.15 ) / ( 2.0 * F ) ) * log ( ca0 / cai ) ;
   ica = gcaN * mc * mc * hc * ( v - Eca ) + gcaL * p * ( v - Eca ) ;
   }
 _current += ina;
 _current += ik;
 _current += ica;
 _current += il;

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
  cao = _ion_cao;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dica;
 double _dik;
 double _dina;
  _dina = ina;
  _dik = ik;
  _dica = ica;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
  _ion_ik += ik ;
  _ion_ica += ica ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
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
  cao = _ion_cao;
 {   states(_p, _ppvar, _thread, _nt);
  }   }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_columnindex;  _dlist1[0] = Dm_columnindex;
 _slist1[1] = h_columnindex;  _dlist1[1] = Dh_columnindex;
 _slist1[2] = p_columnindex;  _dlist1[2] = Dp_columnindex;
 _slist1[3] = n_columnindex;  _dlist1[3] = Dn_columnindex;
 _slist1[4] = mc_columnindex;  _dlist1[4] = Dmc_columnindex;
 _slist1[5] = hc_columnindex;  _dlist1[5] = Dhc_columnindex;
 _slist1[6] = cai_columnindex;  _dlist1[6] = Dcai_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/yulia/bypass/CPG_STDP/py/mod_files/MOTONEURON.mod";
static const char* nmodl_file_text = 
  ": SOMA\n"
  "\n"
  ": Marco Capogrosso & Emanuele Formento\n"
  ":\n"
  ":\n"
  ": This model has been adapted and is described in detail in:\n"
  ":\n"
  ": McIntyre CC and Grill WM. Extracellular Stimulation of Central Neurons:\n"
  ": Influence of Stimulus Waveform and Frequency on Neuronal Output\n"
  ": Journal of Neurophysiology 88:1592-1604, 2002.\n"
  "\n"
  "TITLE Motor Axon Soma\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX motoneuron\n"
  "\n"
  "	USEION na WRITE ina\n"
  "	USEION k WRITE ik\n"
  "	USEION ca READ cao WRITE ica\n"
  "	NONSPECIFIC_CURRENT il\n"
  "\n"
  "\n"
  "	RANGE  gnabar, gl, ena, ek, el, gkrect, gcaN, gcaL, gcak\n"
  "	RANGE p_inf, m_inf, h_inf, n_inf, mc_inf, hc_inf\n"
  "	RANGE tau_p, tau_m, tau_h, tau_n, tau_mc, tau_hc\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	:SOMA PARAMETERS\n"
  "	gnabar	= 0.05	(mho/cm2)\n"
  "	gl	= 0.002 (mho/cm2)\n"
  "	gkrect = 0.3  (mho/cm2)\n"
  "	gcaN = 0.05  (mho/cm2)\n"
  "	gcaL = 0.0001  (mho/cm2)\n"
  "	gcak = 0.3  (mho/cm2)\n"
  "	ca0 = 2\n"
  "	ena = 50.0  (mV)\n"
  "	ek = -80.0 (mV)\n"
  "	el = -70.0 (mV)\n"
  "	dt              (ms)\n"
  "	v               (mV)\n"
  "	amA = 0.4\n"
  "	amB = 66\n"
  "	amC = 5\n"
  "	bmA = 0.4\n"
  "	bmB = 32\n"
  "	bmC = 5\n"
  "	R = 8.314472\n"
  "	F = 96485.34\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	 p m h n cai mc hc\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ina	 (mA/cm2)\n"
  "	il      (mA/cm2)\n"
  "	ica  (mA/cm2)\n"
  "	ik  (mA/cm2)\n"
  "	Eca  (mV)\n"
  "	m_inf\n"
  "	mc_inf\n"
  "	h_inf\n"
  "	hc_inf\n"
  "	n_inf\n"
  "	p_inf\n"
  "	tau_m\n"
  "	tau_h\n"
  "	tau_p\n"
  "	tau_n\n"
  "	tau_mc\n"
  "	tau_hc\n"
  "	cao (mM)\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	ina = gnabar * m*m*m*h*(v - ena)\n"
  "	ik = gkrect *n*n*n*n*(v - ek) + gcak*(cai*cai)/(cai*cai+0.014*0.014)*(v-ek)  :stesso ek di sotto\n"
  "	il = gl * (v - el)\n"
  "	Eca = ((1000*R*309.15)/(2*F))*log(ca0/cai)\n"
  "	ica = gcaN*mc*mc*hc*(v-Eca) + gcaL*p*(v-Eca)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "	 : exact Hodgkin-Huxley equations\n"
  "        evaluate_fct(v)\n"
  "	m' = (m_inf - m) / tau_m\n"
  "	h' = (h_inf - h) / tau_h\n"
  "	p' = (p_inf - p) / tau_p\n"
  "	n' = (n_inf - n) / tau_n\n"
  "	mc' = (mc_inf - mc) / tau_mc\n"
  "	hc' = (hc_inf - hc) / tau_hc\n"
  "	cai'= 0.01*(-(ica) - 4*cai)\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "\n"
  "INITIAL {\n"
  "	evaluate_fct(v)\n"
  "	m = m_inf\n"
  "	h = h_inf\n"
  "	p = p_inf\n"
  "	n = n_inf\n"
  "	mc = mc_inf\n"
  "	hc = hc_inf\n"
  "	cai = 0.0001\n"
  "}\n"
  "\n"
  "PROCEDURE evaluate_fct(v(mV)) { LOCAL a,b,v2\n"
  "\n"
  "	:FAST SODIUM\n"
  "	:m\n"
  "	a = alpham(v)\n"
  "	b = betam(v)\n"
  "	tau_m = 1 / (a + b)\n"
  "	m_inf = a / (a + b)\n"
  "	:h\n"
  "	tau_h = 30 / (Exp((v+60)/15) + Exp(-(v+60)/16))\n"
  "	h_inf = 1 / (1 + Exp((v+65)/7))\n"
  "\n"
  "	:DELAYED RECTIFIER POTASSIUM\n"
  "	tau_n = 5 / (Exp((v+50)/40) + Exp(-(v+50)/50))\n"
  "	n_inf = 1 / (1 + Exp(-(v+38)/15))\n"
  "\n"
  "	:CALCIUM DYNAMICS\n"
  "    :N-type\n"
  "	tau_mc = 15\n"
  "	mc_inf = 1/(1+Exp(-(v+32)/5))\n"
  "	tau_hc = 50\n"
  "	hc_inf =  1/(1+Exp((v+50)/5))\n"
  "\n"
  "	:L-type\n"
  "	tau_p = 400\n"
  "	p_inf = 1/(1+Exp(-(v+55.8)/3.7))\n"
  "\n"
  "}\n"
  "\n"
  "FUNCTION alpham(x) {\n"
  "	if (fabs((x+amB)/amC) < 1e-6) {\n"
  "		alpham = amA*amC\n"
  "	}else{\n"
  "		alpham = (amA*(x+amB)) / (1 - Exp(-(x+amB)/amC))\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION betam(x) {\n"
  "	if (fabs((x+bmB)/bmC) < 1e-6) {\n"
  "		betam = -bmA*bmC\n"
  "	}else{\n"
  "		betam = (bmA*(-(x+bmB))) / (1 - Exp((x+bmB)/bmC))\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION Exp(x) {\n"
  "	if (x < -100) {\n"
  "		Exp = 0\n"
  "	}else{\n"
  "		Exp = exp(x)\n"
  "	}\n"
  "}\n"
  "\n"
  "UNITSON\n"
  ;
#endif
