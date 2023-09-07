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
 
#define nrn_init _nrn_init__cac1
#define _nrn_initial _nrn_initial__cac1
#define nrn_cur _nrn_cur__cac1
#define _nrn_current _nrn_current__cac1
#define nrn_jacob _nrn_jacob__cac1
#define nrn_state _nrn_state__cac1
#define _net_receive _net_receive__cac1 
#define kstates kstates__cac1 
 
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
#define gmax _p[0]
#define gmax_columnindex 0
#define Ev _p[1]
#define Ev_columnindex 1
#define Cs _p[2]
#define Cs_columnindex 2
#define C1 _p[3]
#define C1_columnindex 3
#define C2 _p[4]
#define C2_columnindex 4
#define O1 _p[5]
#define O1_columnindex 5
#define O2 _p[6]
#define O2_columnindex 6
#define C0 _p[7]
#define C0_columnindex 7
#define icl _p[8]
#define icl_columnindex 8
#define g _p[9]
#define g_columnindex 9
#define a1 _p[10]
#define a1_columnindex 10
#define b1 _p[11]
#define b1_columnindex 11
#define l1 _p[12]
#define l1_columnindex 12
#define u1 _p[13]
#define u1_columnindex 13
#define cli _p[14]
#define cli_columnindex 14
#define clo _p[15]
#define clo_columnindex 15
#define DCs _p[16]
#define DCs_columnindex 16
#define DC1 _p[17]
#define DC1_columnindex 17
#define DC2 _p[18]
#define DC2_columnindex 18
#define DO1 _p[19]
#define DO1_columnindex 19
#define DO2 _p[20]
#define DO2_columnindex 20
#define DC0 _p[21]
#define DC0_columnindex 21
#define v _p[22]
#define v_columnindex 22
#define _g _p[23]
#define _g_columnindex 23
#define _ion_cli	*_ppvar[0]._pval
#define _ion_clo	*_ppvar[1]._pval
#define _ion_icl	*_ppvar[2]._pval
#define _ion_dicldv	*_ppvar[3]._pval
 
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
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_KTF(void);
 static void _hoc_efun(void);
 static void _hoc_ghk(void);
 static void _hoc_update_state(void);
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
 "setdata_cac1", _hoc_setdata,
 "KTF_cac1", _hoc_KTF,
 "efun_cac1", _hoc_efun,
 "ghk_cac1", _hoc_ghk,
 "update_state_cac1", _hoc_update_state,
 0, 0
};
#define KTF KTF_cac1
#define efun efun_cac1
#define ghk ghk_cac1
#define update_state update_state_cac1
 extern double KTF( _threadargsprotocomma_ double );
 extern double efun( _threadargsprotocomma_ double );
 extern double ghk( _threadargsprotocomma_ double , double , double );
 extern double update_state( _threadargsprotocomma_ double , double , double );
 /* declare global and static user variables */
#define az az_cac1
 double az = -0.5;
#define a0 a0_cac1
 double a0 = 0.34;
#define bz bz_cac1
 double bz = 0.2;
#define b0 b0_cac1
 double b0 = 0.22;
#define lz lz_cac1
 double lz = -0.3;
#define l0 l0_cac1
 double l0 = 0.13;
#define uz uz_cac1
 double uz = 0.2;
#define u0 u0_cac1
 double u0 = 0.6;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "a0_cac1", "/s",
 "b0_cac1", "/s",
 "l0_cac1", "/s",
 "u0_cac1", "/s",
 "gmax_cac1", "mho/cm2",
 "Ev_cac1", "mV",
 0,0
};
 static double C00 = 0;
 static double C20 = 0;
 static double C10 = 0;
 static double Cs0 = 0;
 static double O20 = 0;
 static double O10 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "a0_cac1", &a0_cac1,
 "b0_cac1", &b0_cac1,
 "l0_cac1", &l0_cac1,
 "u0_cac1", &u0_cac1,
 "az_cac1", &az_cac1,
 "bz_cac1", &bz_cac1,
 "lz_cac1", &lz_cac1,
 "uz_cac1", &uz_cac1,
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
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"cac1",
 "gmax_cac1",
 "Ev_cac1",
 0,
 0,
 "Cs_cac1",
 "C1_cac1",
 "C2_cac1",
 "O1_cac1",
 "O2_cac1",
 "C0_cac1",
 0,
 0};
 static Symbol* _cl_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 24, _prop);
 	/*initialize range parameters*/
 	gmax = 0.1;
 	Ev = -60;
 	_prop->param = _p;
 	_prop->param_size = 24;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_cl_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cli */
 	_ppvar[1]._pval = &prop_ion->param[2]; /* clo */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* icl */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicldv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _cac1_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("cl", -1.0);
 	_cl_sym = hoc_lookup("cl_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 3);
  _extcall_thread = (Datum*)ecalloc(2, sizeof(Datum));
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 24, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cac1 /home/max/PROJECTS/memristive-spinal-cord/memristive-spinal-cord/NEURON/second_layer/neuron+python/mod_files/cac1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 
#define FARADAY _nrnunit_FARADAY[_nrnunit_use_legacy_]
static double _nrnunit_FARADAY[2] = {0x1.81f0fae775425p+6, 96.4853}; /* 96.4853321233100161 */
 
#define R _nrnunit_R[_nrnunit_use_legacy_]
static double _nrnunit_R[2] = {0x1.0a1013e8990bep+3, 8.3145}; /* 8.3144626181532395 */
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  static int _cvspth1 = 1;
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 extern double *_nrn_thread_getelm(SparseObj*, int, int);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 0;
 static int _slist1[6], _dlist1[6]; static double *_temp1;
 static int kstates();
 
static int kstates (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<6;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 a1 = update_state ( _threadargscomma_ v , a0 , az ) ;
   b1 = update_state ( _threadargscomma_ v , b0 , bz ) ;
   l1 = update_state ( _threadargscomma_ v , l0 , lz ) ;
   u1 = update_state ( _threadargscomma_ v , u0 , uz ) ;
   /* ~ Cs <-> O1 ( 2.0 * a1 , b1 )*/
 f_flux =  2.0 * a1 * Cs ;
 b_flux =  b1 * O1 ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  2.0 * a1 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 5 ,4)  -= _term;
 _term =  b1 ;
 _MATELM1( 4 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ O1 <-> O2 ( a1 , 2.0 * b1 )*/
 f_flux =  a1 * O1 ;
 b_flux =  2.0 * b1 * O2 ;
 _RHS1( 5) -= (f_flux - b_flux);
 
 _term =  a1 ;
 _MATELM1( 5 ,5)  += _term;
 _term =  2.0 * b1 ;
 _MATELM1( 5 ,0)  -= _term;
 /*REACTION*/
  /* ~ C0 <-> C1 ( 2.0 * a1 , b1 )*/
 f_flux =  2.0 * a1 * C0 ;
 b_flux =  b1 * C1 ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  2.0 * a1 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 3 ,1)  -= _term;
 _term =  b1 ;
 _MATELM1( 1 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ C1 <-> C2 ( a1 , 2.0 * b1 )*/
 f_flux =  a1 * C1 ;
 b_flux =  2.0 * b1 * C2 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  a1 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  2.0 * b1 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ O2 <-> C2 ( u1 , l1 )*/
 f_flux =  u1 * O2 ;
 b_flux =  l1 * C2 ;
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  u1 ;
 _MATELM1( 2 ,0)  -= _term;
 _term =  l1 ;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ O1 <-> C1 ( u1 , l1 )*/
 f_flux =  u1 * O1 ;
 b_flux =  l1 * C1 ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  u1 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 3 ,5)  -= _term;
 _term =  l1 ;
 _MATELM1( 5 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ Cs <-> C0 ( u1 , l1 )*/
 f_flux =  u1 * Cs ;
 b_flux =  l1 * C0 ;
 _RHS1( 4) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  u1 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 1 ,4)  -= _term;
 _term =  l1 ;
 _MATELM1( 4 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* Cs + C0 + C1 + C2 + O1 + O2 = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= O2 ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= O1 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= C2 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= C1 ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= C0 ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= Cs ;
 /*CONSERVATION*/
   } return _reset;
 }
 
double update_state ( _threadargsprotocomma_ double _lv , double _lstate0 , double _lz0 ) {
   double _lupdate_state;
 _lupdate_state = _lstate0 * exp ( _lz0 * FARADAY * _lv / R / ( 273.15 + celsius ) ) ;
   
return _lupdate_state;
 }
 
static void _hoc_update_state(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  update_state ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
double ghk ( _threadargsprotocomma_ double _lv , double _lci , double _lco ) {
   double _lghk;
 double _lnu , _lf ;
 _lf = KTF ( _threadargscomma_ celsius ) / 2.0 ;
   _lnu = _lv / _lf ;
   _lghk = - _lf * ( 1. - ( _lci / _lco ) * exp ( _lnu ) ) * efun ( _threadargscomma_ _lnu ) ;
   
return _lghk;
 }
 
static void _hoc_ghk(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  ghk ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
double KTF ( _threadargsprotocomma_ double _lcelsius ) {
   double _lKTF;
 _lKTF = ( ( 25. / 293.15 ) * ( _lcelsius + 273.15 ) ) ;
   
return _lKTF;
 }
 
static void _hoc_KTF(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  KTF ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double efun ( _threadargsprotocomma_ double _lz ) {
   double _lefun;
 if ( fabs ( _lz ) < 1e-4 ) {
     _lefun = 1.0 - _lz / 2.0 ;
     }
   else {
     _lefun = _lz / ( exp ( _lz ) - 1.0 ) ;
     }
   
return _lefun;
 }
 
static void _hoc_efun(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  efun ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<6;_i++) _p[_dlist1[_i]] = 0.0;}
 a1 = update_state ( _threadargscomma_ v , a0 , az ) ;
 b1 = update_state ( _threadargscomma_ v , b0 , bz ) ;
 l1 = update_state ( _threadargscomma_ v , l0 , lz ) ;
 u1 = update_state ( _threadargscomma_ v , u0 , uz ) ;
 /* ~ Cs <-> O1 ( 2.0 * a1 , b1 )*/
 f_flux =  2.0 * a1 * Cs ;
 b_flux =  b1 * O1 ;
 DCs -= (f_flux - b_flux);
 DO1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ O1 <-> O2 ( a1 , 2.0 * b1 )*/
 f_flux =  a1 * O1 ;
 b_flux =  2.0 * b1 * O2 ;
 DO1 -= (f_flux - b_flux);
 DO2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C0 <-> C1 ( 2.0 * a1 , b1 )*/
 f_flux =  2.0 * a1 * C0 ;
 b_flux =  b1 * C1 ;
 DC0 -= (f_flux - b_flux);
 DC1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C1 <-> C2 ( a1 , 2.0 * b1 )*/
 f_flux =  a1 * C1 ;
 b_flux =  2.0 * b1 * C2 ;
 DC1 -= (f_flux - b_flux);
 DC2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ O2 <-> C2 ( u1 , l1 )*/
 f_flux =  u1 * O2 ;
 b_flux =  l1 * C2 ;
 DO2 -= (f_flux - b_flux);
 DC2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ O1 <-> C1 ( u1 , l1 )*/
 f_flux =  u1 * O1 ;
 b_flux =  l1 * C1 ;
 DO1 -= (f_flux - b_flux);
 DC1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ Cs <-> C0 ( u1 , l1 )*/
 f_flux =  u1 * Cs ;
 b_flux =  l1 * C0 ;
 DCs -= (f_flux - b_flux);
 DC0 += (f_flux - b_flux);
 
 /*REACTION*/
   /* Cs + C0 + C1 + C2 + O1 + O2 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<6;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
 a1 = update_state ( _threadargscomma_ v , a0 , az ) ;
 b1 = update_state ( _threadargscomma_ v , b0 , bz ) ;
 l1 = update_state ( _threadargscomma_ v , l0 , lz ) ;
 u1 = update_state ( _threadargscomma_ v , u0 , uz ) ;
 /* ~ Cs <-> O1 ( 2.0 * a1 , b1 )*/
 _term =  2.0 * a1 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 5 ,4)  -= _term;
 _term =  b1 ;
 _MATELM1( 4 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ O1 <-> O2 ( a1 , 2.0 * b1 )*/
 _term =  a1 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 0 ,5)  -= _term;
 _term =  2.0 * b1 ;
 _MATELM1( 5 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ C0 <-> C1 ( 2.0 * a1 , b1 )*/
 _term =  2.0 * a1 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 3 ,1)  -= _term;
 _term =  b1 ;
 _MATELM1( 1 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ C1 <-> C2 ( a1 , 2.0 * b1 )*/
 _term =  a1 ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  2.0 * b1 ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ O2 <-> C2 ( u1 , l1 )*/
 _term =  u1 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 2 ,0)  -= _term;
 _term =  l1 ;
 _MATELM1( 0 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ O1 <-> C1 ( u1 , l1 )*/
 _term =  u1 ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 3 ,5)  -= _term;
 _term =  l1 ;
 _MATELM1( 5 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ Cs <-> C0 ( u1 , l1 )*/
 _term =  u1 ;
 _MATELM1( 4 ,4)  += _term;
 _MATELM1( 1 ,4)  -= _term;
 _term =  l1 ;
 _MATELM1( 4 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
   /* Cs + C0 + C1 + C2 + O1 + O2 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 6;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cli = _ion_cli;
  clo = _ion_clo;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 6; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _cvode_sparse_thread(&_thread[_cvspth1]._pvoid, 6, _dlist1, _p, _ode_matsol1, _ppvar, _thread, _nt);
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
  cli = _ion_cli;
  clo = _ion_clo;
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_spth1]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_cvspth1]._pvoid);
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_cl_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 1, 2);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 3, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  C0 = C00;
  C2 = C20;
  C1 = C10;
  Cs = Cs0;
  O2 = O20;
  O1 = O10;
 {
    sparse_thread(&_thread[_spth1]._pvoid, 6, _slist1, _dlist1, _p, &t, dt, kstates, _linmat1, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 6; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
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
  cli = _ion_cli;
  clo = _ion_clo;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   g = gmax * ( O1 + O2 ) ;
   icl = g * ghk ( _threadargscomma_ v , cli , clo ) ;
   }
 _current += icl;

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
  cli = _ion_cli;
  clo = _ion_clo;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dicl;
  _dicl = icl;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicldv += (_dicl - icl)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_icl += icl ;
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
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
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
  cli = _ion_cli;
  clo = _ion_clo;
 {  sparse_thread(&_thread[_spth1]._pvoid, 6, _slist1, _dlist1, _p, &t, dt, kstates, _linmat1, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 6; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 } }}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = O2_columnindex;  _dlist1[0] = DO2_columnindex;
 _slist1[1] = C0_columnindex;  _dlist1[1] = DC0_columnindex;
 _slist1[2] = C2_columnindex;  _dlist1[2] = DC2_columnindex;
 _slist1[3] = C1_columnindex;  _dlist1[3] = DC1_columnindex;
 _slist1[4] = Cs_columnindex;  _dlist1[4] = DCs_columnindex;
 _slist1[5] = O1_columnindex;  _dlist1[5] = DO1_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/max/PROJECTS/memristive-spinal-cord/memristive-spinal-cord/NEURON/second_layer/neuron+python/mod_files/cac1.mod";
static const char* nmodl_file_text = 
  "NEURON {\n"
  "	SUFFIX cac1\n"
  "	RANGE gmax, Ev\n"
  "  USEION cl READ cli, clo WRITE icl VALENCE -1\n"
  "}\n"
  "\n"
  "UNITS{\n"
  "	(pA) = (picoamp)\n"
  "	(molar) = (1/liter)\n"
  "	(uM) = (micromolar)\n"
  "	(mV) = (millivolt)\n"
  "	(pS) = (picosiemens)\n"
  "\n"
  "  FARADAY = (faraday)  (kilocoulombs)\n"
  "	R = (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "\n"
  "	a0 = 0.34 (/s)\n"
  "	b0 = 0.22 (/s)\n"
  "	l0 = 0.13 (/s)\n"
  "	u0 = 0.6 (/s)\n"
  "  celsius = 37	(degC)\n"
  "\n"
  "  az = -0.5\n"
  "	bz = 0.2\n"
  "	lz = -0.3\n"
  "	uz = 0.2\n"
  "\n"
  "	gmax = 0.1 (mho/cm2)	: conductivity\n"
  "	Ev = -60 (mV)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	v (mV)	: voltage\n"
  "	icl (mA/cm2)	: current\n"
  "	g  (mho/cm2)	: conductance\n"
  "  a1 (/s)\n"
  "  b1 (/s)\n"
  "  l1 (/s)\n"
  "  u1 (/s)\n"
  "  cli\n"
  "  clo\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	Cs\n"
  "	C1\n"
  "	C2\n"
  "	O1\n"
  "	O2\n"
  "  C0\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	SOLVE kstates METHOD sparse\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE kstates METHOD sparse\n"
  "	g = gmax*(O1+O2)\n"
  "	icl = g * ghk(v,cli,clo)\n"
  "}\n"
  "\n"
  "KINETIC kstates{\n"
  "\n"
  "  a1 = update_state(v, a0, az)\n"
  "	b1 = update_state(v, b0, bz)\n"
  "  l1 = update_state(v, l0, lz)\n"
  "  u1 = update_state(v, u0, uz)\n"
  "\n"
  "	~ Cs <-> O1 (2*a1, b1)\n"
  "	~ O1 <-> O2 (a1, 2*b1)\n"
  "	~ C0 <-> C1 (2*a1, b1)\n"
  "	~ C1 <-> C2 (a1, 2*b1)\n"
  "	~ O2 <-> C2 (u1, l1)\n"
  "	~ O1 <-> C1 (u1, l1)\n"
  "  ~ Cs <-> C0 (u1, l1)\n"
  "\n"
  "\n"
  "	CONSERVE 	Cs+C0+C1+C2+O1+O2=1\n"
  "}\n"
  "\n"
  "FUNCTION update_state(v(mV), state0, z0){\n"
  "	update_state = state0*exp(z0*FARADAY*v/R/(273.15 + celsius))\n"
  "}\n"
  "\n"
  "FUNCTION ghk(v(mV), ci(mM), co(mM)) (mV) {\n"
  "        LOCAL nu,f\n"
  "\n"
  "        f = KTF(celsius)/2\n"
  "        nu = v/f\n"
  "        ghk=-f*(1. - (ci/co)*exp(nu))*efun(nu)\n"
  "}\n"
  "\n"
  "FUNCTION KTF(celsius (DegC)) (mV) {\n"
  "        KTF = ((25./293.15)*(celsius + 273.15))\n"
  "}\n"
  "\n"
  "\n"
  "FUNCTION efun(z) {\n"
  "	if (fabs(z) < 1e-4) {\n"
  "		efun = 1 - z/2\n"
  "	}else{\n"
  "		efun = z/(exp(z) - 1)\n"
  "	}\n"
  "}\n"
  ;
#endif
