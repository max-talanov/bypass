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
 
#define nrn_init _nrn_init__CaSP
#define _nrn_initial _nrn_initial__CaSP
#define nrn_cur _nrn_cur__CaSP
#define _nrn_current _nrn_current__CaSP
#define nrn_jacob _nrn_jacob__CaSP
#define nrn_state _nrn_state__CaSP
#define _net_receive _net_receive__CaSP 
#define CaR CaR__CaSP 
#define SPK_DETECT SPK_DETECT__CaSP 
#define rate rate__CaSP 
#define state state__CaSP 
 
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
#define k1 _p[0]
#define k1_columnindex 0
#define k2 _p[1]
#define k2_columnindex 1
#define k3 _p[2]
#define k3_columnindex 2
#define k4 _p[3]
#define k4_columnindex 3
#define k5i _p[4]
#define k5i_columnindex 4
#define k6i _p[5]
#define k6i_columnindex 5
#define k _p[6]
#define k_columnindex 6
#define SF_AM _p[7]
#define SF_AM_columnindex 7
#define Rmax _p[8]
#define Rmax_columnindex 8
#define Umax _p[9]
#define Umax_columnindex 9
#define t1 _p[10]
#define t1_columnindex 10
#define t2 _p[11]
#define t2_columnindex 11
#define phi1 _p[12]
#define phi1_columnindex 12
#define phi2 _p[13]
#define phi2_columnindex 13
#define phi3 _p[14]
#define phi3_columnindex 14
#define phi4 _p[15]
#define phi4_columnindex 15
#define c1 _p[16]
#define c1_columnindex 16
#define c2 _p[17]
#define c2_columnindex 17
#define c3 _p[18]
#define c3_columnindex 18
#define c4 _p[19]
#define c4_columnindex 19
#define c5 _p[20]
#define c5_columnindex 20
#define alpha _p[21]
#define alpha_columnindex 21
#define alpha1 _p[22]
#define alpha1_columnindex 22
#define alpha2 _p[23]
#define alpha2_columnindex 23
#define alpha3 _p[24]
#define alpha3_columnindex 24
#define beta _p[25]
#define beta_columnindex 25
#define gamma _p[26]
#define gamma_columnindex 26
#define vth _p[27]
#define vth_columnindex 27
#define spk_index _p[28]
#define spk_index_columnindex 28
#define t_axon _p[29]
#define t_axon_columnindex 29
#define R _p[30]
#define R_columnindex 30
#define k5 _p[31]
#define k5_columnindex 31
#define k6 _p[32]
#define k6_columnindex 32
#define AMinf _p[33]
#define AMinf_columnindex 33
#define AMtau _p[34]
#define AMtau_columnindex 34
#define vm _p[35]
#define vm_columnindex 35
#define acm _p[36]
#define acm_columnindex 36
#define CaSR _p[37]
#define CaSR_columnindex 37
#define CaSRCS _p[38]
#define CaSRCS_columnindex 38
#define Ca _p[39]
#define Ca_columnindex 39
#define CaB _p[40]
#define CaB_columnindex 40
#define CaT _p[41]
#define CaT_columnindex 41
#define AM _p[42]
#define AM_columnindex 42
#define DCaSR _p[43]
#define DCaSR_columnindex 43
#define DCaSRCS _p[44]
#define DCaSRCS_columnindex 44
#define DCa _p[45]
#define DCa_columnindex 45
#define DCaB _p[46]
#define DCaB_columnindex 46
#define DCaT _p[47]
#define DCaT_columnindex 47
#define DAM _p[48]
#define DAM_columnindex 48
#define mgi _p[49]
#define mgi_columnindex 49
#define Dmgi _p[50]
#define Dmgi_columnindex 50
#define t_shift _p[51]
#define t_shift_columnindex 51
#define R_On _p[52]
#define R_On_columnindex 52
#define Spike_On _p[53]
#define Spike_On_columnindex 53
#define cli _p[54]
#define cli_columnindex 54
#define spk (_p + 55)
#define spk_columnindex 55
#define xm (_p + 10055)
#define xm_columnindex 10055
#define v _p[10057]
#define v_columnindex 10057
#define _g _p[10058]
#define _g_columnindex 10058
#define _ion_mgi	*_ppvar[0]._pval
#define _style_mg	*((int*)_ppvar[1]._pvoid)
#define _ion_cli	*_ppvar[2]._pval
 
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
 static void _hoc_CaR(void);
 static void _hoc_SPK_DETECT(void);
 static void _hoc_U(void);
 static void _hoc_phi(void);
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
 "setdata_CaSP", _hoc_setdata,
 "CaR_CaSP", _hoc_CaR,
 "SPK_DETECT_CaSP", _hoc_SPK_DETECT,
 "U_CaSP", _hoc_U,
 "phi_CaSP", _hoc_phi,
 "rate_CaSP", _hoc_rate,
 0, 0
};
#define U U_CaSP
#define phi phi_CaSP
 extern double U( _threadargsprotocomma_ double );
 extern double phi( _threadargsprotocomma_ double );
 /* declare global and static user variables */
#define B0 B0_CaSP
 double B0 = 0.00043;
#define CS0 CS0_CaSP
 double CS0 = 0.03;
#define T0 T0_CaSP
 double T0 = 7e-05;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 0,0
};
 static double AM0 = 0;
 static double CaT0 = 0;
 static double CaB0 = 0;
 static double Ca0 = 0;
 static double CaSRCS0 = 0;
 static double CaSR0 = 0;
 static double delta_t = 0.01;
 static double mgi0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "CS0_CaSP", &CS0_CaSP,
 "B0_CaSP", &B0_CaSP,
 "T0_CaSP", &T0_CaSP,
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
"CaSP",
 "k1_CaSP",
 "k2_CaSP",
 "k3_CaSP",
 "k4_CaSP",
 "k5i_CaSP",
 "k6i_CaSP",
 "k_CaSP",
 "SF_AM_CaSP",
 "Rmax_CaSP",
 "Umax_CaSP",
 "t1_CaSP",
 "t2_CaSP",
 "phi1_CaSP",
 "phi2_CaSP",
 "phi3_CaSP",
 "phi4_CaSP",
 "c1_CaSP",
 "c2_CaSP",
 "c3_CaSP",
 "c4_CaSP",
 "c5_CaSP",
 "alpha_CaSP",
 "alpha1_CaSP",
 "alpha2_CaSP",
 "alpha3_CaSP",
 "beta_CaSP",
 "gamma_CaSP",
 "vth_CaSP",
 "spk_index_CaSP",
 "t_axon_CaSP",
 0,
 "R_CaSP",
 "k5_CaSP",
 "k6_CaSP",
 "AMinf_CaSP",
 "AMtau_CaSP",
 "vm_CaSP",
 "acm_CaSP",
 0,
 "CaSR_CaSP",
 "CaSRCS_CaSP",
 "Ca_CaSP",
 "CaB_CaSP",
 "CaT_CaSP",
 "AM_CaSP",
 0,
 0};
 static Symbol* _mg_sym;
 static Symbol* _cl_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 10059, _prop);
 	/*initialize range parameters*/
 	k1 = 3000;
 	k2 = 3;
 	k3 = 400;
 	k4 = 1;
 	k5i = 400000;
 	k6i = 150;
 	k = 850;
 	SF_AM = 5;
 	Rmax = 10;
 	Umax = 2000;
 	t1 = 3;
 	t2 = 25;
 	phi1 = 0.03;
 	phi2 = 1.23;
 	phi3 = 0.01;
 	phi4 = 1.08;
 	c1 = 0.128;
 	c2 = 0.093;
 	c3 = 61.206;
 	c4 = -13.116;
 	c5 = 5.095;
 	alpha = 2;
 	alpha1 = 4.77;
 	alpha2 = 400;
 	alpha3 = 160;
 	beta = 0.47;
 	gamma = 0.001;
 	vth = -40;
 	spk_index = 0;
 	t_axon = 0.01;
 	_prop->param = _p;
 	_prop->param_size = 10059;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_mg_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* mgi */
 	_ppvar[1]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for mg */
 prop_ion = need_memb(_cl_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[2]._pval = &prop_ion->param[1]; /* cli */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _muscle_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("mg", 2.0);
 	ion_reg("cl", -1.0);
 	_mg_sym = hoc_lookup("mg_ion");
 	_cl_sym = hoc_lookup("cl_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 5);
  _extcall_thread = (Datum*)ecalloc(4, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 10059, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "mg_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "#mg_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 CaSP /home/max/PROJECTS/memristive-spinal-cord/memristive-spinal-cord/NEURON/second_layer/neuron+python/mod_files/muscle.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Calcium dynamics and cross-bridge formation";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int CaR(_threadargsprotocomma_ double, double);
static int SPK_DETECT(_threadargsprotocomma_ double, double);
static int rate(_threadargsprotocomma_ double, double, double, double);
 
#define _deriv1_advance _thread[0]._i
#define _dith1 1
#define _recurse _thread[2]._i
#define _newtonspace1 _thread[3]._pvoid
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist2[7];
  static int _slist1[7], _dlist1[7];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rate ( _threadargscomma_ cli , CaT , AM , t ) ;
   DCaSR = - k1 * CS0 * CaSR + ( k1 * CaSR + k2 ) * CaSRCS - R + U ( _threadargscomma_ Ca ) ;
   DCaSRCS = k1 * CS0 * CaSR - ( k1 * CaSR + k2 ) * CaSRCS ;
   DCa = - k5 * T0 * Ca + ( k5 * Ca + k6 ) * CaT - k3 * B0 * Ca + ( k3 * Ca + k4 ) * CaB + R - U ( _threadargscomma_ Ca ) ;
   DCaB = k3 * B0 * Ca - ( k3 * Ca + k4 ) * CaB ;
   DCaT = k5 * T0 * Ca - ( k5 * Ca + k6 ) * CaT ;
   DAM = ( AMinf - AM ) / AMtau ;
   Dmgi = 0.0 ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rate ( _threadargscomma_ cli , CaT , AM , t ) ;
 DCaSR = DCaSR  / (1. - dt*( ( - k1 * CS0 )*( 1.0 ) + ( ( ( k1 )*( 1.0 ) ) )*( CaSRCS ) )) ;
 DCaSRCS = DCaSRCS  / (1. - dt*( ( - ( ( k1 * CaSR + k2 ) )*( 1.0 ) ) )) ;
 DCa = DCa  / (1. - dt*( (( - k5 * T0 * ( Ca  + .001) + ( k5 * ( Ca  + .001) + k6 ) * CaT - k3 * B0 * ( Ca  + .001) + ( k3 * ( Ca  + .001) + k4 ) * CaB + R - U ( _threadargscomma_ ( Ca  + .001) ) ) - ( - k5 * T0 * Ca + ( k5 * Ca + k6 ) * CaT - k3 * B0 * Ca + ( k3 * Ca + k4 ) * CaB + R - U ( _threadargscomma_ Ca )  )) / .001 )) ;
 DCaB = DCaB  / (1. - dt*( ( - ( ( k3 * Ca + k4 ) )*( 1.0 ) ) )) ;
 DCaT = DCaT  / (1. - dt*( ( - ( ( k5 * Ca + k6 ) )*( 1.0 ) ) )) ;
 DAM = DAM  / (1. - dt*( ( ( ( - 1.0 ) ) ) / AMtau )) ;
 Dmgi = Dmgi  / (1. - dt*( 0.0 )) ;
  return 0;
}
 /*END CVODE*/
 
static int state (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset=0; int error = 0;
 { double* _savstate1 = _thread[_dith1]._pval;
 double* _dlist2 = _thread[_dith1]._pval + 7;
 int _counte = -1;
 if (!_recurse) {
 _recurse = 1;
 {int _id; for(_id=0; _id < 7; _id++) { _savstate1[_id] = _p[_slist1[_id]];}}
 error = nrn_newton_thread(_newtonspace1, 7,_slist2, _p, state, _dlist2, _ppvar, _thread, _nt);
 _recurse = 0; if(error) {abort_run(error);}}
 {
   rate ( _threadargscomma_ cli , CaT , AM , t ) ;
   DCaSR = - k1 * CS0 * CaSR + ( k1 * CaSR + k2 ) * CaSRCS - R + U ( _threadargscomma_ Ca ) ;
   DCaSRCS = k1 * CS0 * CaSR - ( k1 * CaSR + k2 ) * CaSRCS ;
   DCa = - k5 * T0 * Ca + ( k5 * Ca + k6 ) * CaT - k3 * B0 * Ca + ( k3 * Ca + k4 ) * CaB + R - U ( _threadargscomma_ Ca ) ;
   DCaB = k3 * B0 * Ca - ( k3 * Ca + k4 ) * CaB ;
   DCaT = k5 * T0 * Ca - ( k5 * Ca + k6 ) * CaT ;
   DAM = ( AMinf - AM ) / AMtau ;
   Dmgi = 0.0 ;
   {int _id; for(_id=0; _id < 7; _id++) {
if (_deriv1_advance) {
 _dlist2[++_counte] = _p[_dlist1[_id]] - (_p[_slist1[_id]] - _savstate1[_id])/dt;
 }else{
_dlist2[++_counte] = _p[_slist1[_id]] - _savstate1[_id];}}}
 } }
 return _reset;}
 
static int  SPK_DETECT ( _threadargsprotocomma_ double _lv , double _lt ) {
   if ( Spike_On  == 0.0  && _lv > vth ) {
     Spike_On = 1.0 ;
     spk [ ((int) spk_index ) ] = _lt + t_axon ;
     spk_index = spk_index + 1.0 ;
     R_On = 1.0 ;
     }
   else if ( _lv < vth ) {
     Spike_On = 0.0 ;
     }
    return 0; }
 
static void _hoc_SPK_DETECT(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 SPK_DETECT ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
double U ( _threadargsprotocomma_ double _lx ) {
   double _lU;
 if ( _lx >= 0.0 ) {
     _lU = Umax * pow( ( pow( _lx , 2.0 ) * pow( k , 2.0 ) / ( 1.0 + _lx * k + pow( _lx , 2.0 ) * pow( k , 2.0 ) ) ) , 2.0 ) ;
     }
   else {
     _lU = 0.0 ;
     }
   
return _lU;
 }
 
static void _hoc_U(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  U ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double phi ( _threadargsprotocomma_ double _lx ) {
   double _lphi;
 if ( _lx <= - 8.0 ) {
     _lphi = phi1 * _lx + phi2 ;
     }
   else {
     _lphi = phi3 * _lx + phi4 ;
     }
   
return _lphi;
 }
 
static void _hoc_phi(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  phi ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  CaR ( _threadargsprotocomma_ double _lCaSR , double _lt ) {
   double _li , _ltempR ;
 if ( R_On  == 1.0 ) {
     if ( spk_index > 0.0 ) {
       _ltempR = _ltempR + _lCaSR * Rmax * ( 1.0 - exp ( - ( _lt - spk [ ((int) spk_index ) - 1 ] ) / t1 ) ) * exp ( - ( _lt - spk [ ((int) spk_index ) - 1 ] ) / t2 ) ;
       }
     R = _ltempR ;
     _ltempR = 0.0 ;
     }
   else {
     R = 0.0 ;
     }
    return 0; }
 
static void _hoc_CaR(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 CaR ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static int  rate ( _threadargsprotocomma_ double _lcli , double _lCaT , double _lAM , double _lt ) {
   k5 = phi ( _threadargscomma_ _lcli ) * k5i ;
   k6 = k6i / ( 1.0 + SF_AM * _lAM ) ;
   AMinf = 0.5 * ( 1.0 + tanh ( ( ( _lCaT / T0 ) - c1 ) / c2 ) ) ;
   AMtau = c3 / ( cosh ( ( ( _lCaT / T0 ) - c4 ) / ( 2.0 * c5 ) ) ) ;
    return 0; }
 
static void _hoc_rate(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rate ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
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
  mgi = _ion_mgi;
  cli = _ion_cli;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  _ion_mgi = mgi;
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 7; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 	_pv[6] = &(_ion_mgi);
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
 
static void _thread_mem_init(Datum* _thread) {
   _thread[_dith1]._pval = (double*)ecalloc(14, sizeof(double));
   _newtonspace1 = nrn_cons_newtonspace(7);
 }
 
static void _thread_cleanup(Datum* _thread) {
   free((void*)(_thread[_dith1]._pval));
   nrn_destroy_newtonspace(_newtonspace1);
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_mg_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 2, 1);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  AM = AM0;
  CaT = CaT0;
  CaB = CaB0;
  Ca = Ca0;
  CaSRCS = CaSRCS0;
  CaSR = CaSR0;
 {
   double _li ;
 CaSR = 0.0025 ;
   CaSRCS = 0.0 ;
   Ca = 1e-10 ;
   CaB = 0.0 ;
   CaT = 0.0 ;
   AM = 0.0 ;
   mgi = 0.0 ;
   {int  _li ;for ( _li = 0 ; _li <= 9999 ; _li ++ ) {
     spk [ _li ] = 0.0 ;
     } }
   {int  _li ;for ( _li = 0 ; _li <= 1 ; _li ++ ) {
     xm [ _li ] = 0.0 ;
     } }
   spk_index = 0.0 ;
   R_On = 0.0 ;
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
  _ion_mgi = mgi;
  nrn_wrote_conc(_mg_sym, (&(_ion_mgi)) - 1, _style_mg);
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
  mgi = _ion_mgi;
  cli = _ion_cli;
 {  _deriv1_advance = 1;
 derivimplicit_thread(7, _slist1, _dlist1, _p, state, _ppvar, _thread, _nt);
_deriv1_advance = 0;
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 7; ++_i) {
      _p[_slist1[_i]] += dt*_p[_dlist1[_i]];
    }}
 } {
   double _li , _ltempR ;
 SPK_DETECT ( _threadargscomma_ v , t ) ;
   CaR ( _threadargscomma_ CaSR , t ) ;
   xm [ 0 ] = xm [ 1 ] ;
   xm [ 1 ] = cli ;
   vm = ( xm [ 1 ] - xm [ 0 ] ) / ( dt * pow( 10.0 , - 3.0 ) ) ;
   mgi = pow( AM , alpha ) ;
   }
  _ion_mgi = mgi;
}}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = CaSR_columnindex;  _dlist1[0] = DCaSR_columnindex;
 _slist1[1] = CaSRCS_columnindex;  _dlist1[1] = DCaSRCS_columnindex;
 _slist1[2] = Ca_columnindex;  _dlist1[2] = DCa_columnindex;
 _slist1[3] = CaB_columnindex;  _dlist1[3] = DCaB_columnindex;
 _slist1[4] = CaT_columnindex;  _dlist1[4] = DCaT_columnindex;
 _slist1[5] = AM_columnindex;  _dlist1[5] = DAM_columnindex;
 _slist1[6] = mgi_columnindex;  _dlist1[6] = Dmgi_columnindex;
 _slist2[0] = AM_columnindex;
 _slist2[1] = CaT_columnindex;
 _slist2[2] = CaB_columnindex;
 _slist2[3] = Ca_columnindex;
 _slist2[4] = CaSRCS_columnindex;
 _slist2[5] = CaSR_columnindex;
 _slist2[6] = mgi_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/max/PROJECTS/memristive-spinal-cord/memristive-spinal-cord/NEURON/second_layer/neuron+python/mod_files/muscle.mod";
static const char* nmodl_file_text = 
  "TITLE Calcium dynamics and cross-bridge formation\n"
  "\n"
  "UNITS { }\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX CaSP\n"
  "\n"
  "	::module 1::\n"
  "	RANGE k1, k2, k3, k4, k5, k6, k, k5i, k6i\n"
  "	RANGE Umax, Rmax, t1, t2, R, vth, U\n"
  "	RANGE phi0, phi1, phi2, phi3, phi4, phi\n"
  "\n"
  "	::module 2::\n"
  "	RANGE c1, c2, c3, c4, c5\n"
  "	RANGE AMinf, AMtau, SF_AM\n"
  "	RANGE acm, alpha, alpha1, alpha2, alpha3, beta, gamma\n"
  "\n"
  "	::simulation::\n"
  "	RANGE spk_index, t_axon, vm, R\n"
  "	USEION mg WRITE mgi VALENCE 2\n"
  "	USEION cl READ cli VALENCE -1\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	::module 1::\n"
  "	k1 = 3000		: M-1*ms-1\n"
  "	k2 = 3			: ms-1\n"
  "	k3 = 400		: M-1*ms-1\n"
  "	k4 = 1			: ms-1\n"
  "	k5i = 4e5		: M-1*ms-1\n"
  "	k6i = 150		: ms-1\n"
  "	k = 850			: M-1\n"
  "	SF_AM = 5\n"
  "	Rmax = 10		: ms-1\n"
  "	Umax = 2000		: M-1*ms-1\n"
  "	t1 = 3			: ms\n"
  "	t2 = 25			: ms\n"
  "	phi1 = 0.03\n"
  "	phi2 = 1.23\n"
  "	phi3 = 0.01\n"
  "	phi4 = 1.08\n"
  "	CS0 = 0.03     	:[M]\n"
  "	B0 = 0.00043	:[M]\n"
  "	T0 = 0.00007 	:[M]\n"
  "\n"
  "	::module 2::\n"
  "	c1 = 0.128\n"
  "	c2 = 0.093\n"
  "	c3 = 61.206\n"
  "	c4 = -13.116\n"
  "	c5 = 5.095\n"
  "	alpha = 2\n"
  "	alpha1 = 4.77\n"
  "	alpha2 = 400\n"
  "	alpha3 = 160\n"
  "	beta = 0.47\n"
  "	gamma = 0.001\n"
  "\n"
  "	::simulation::\n"
  "	vth = -40\n"
  "	spk_index = 0\n"
  "	t_axon = 0.01\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	CaSR\n"
  "	CaSRCS\n"
  "	Ca\n"
  "	CaB\n"
  "	CaT\n"
  "	AM\n"
  "	mgi\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	v 	(mV)\n"
  "	R\n"
  "	t_shift\n"
  "	R_On\n"
  "	Spike_On\n"
  "	k5\n"
  "	k6\n"
  "	AMinf\n"
  "	AMtau\n"
  "	cli\n"
  "	spk[10000]\n"
  "	xm[2]\n"
  "	vm\n"
  "	acm\n"
  "}\n"
  "\n"
  "BREAKPOINT { LOCAL i, tempR\n"
  "\n"
  "	SPK_DETECT (v, t)\n"
  "	CaR (CaSR, t)\n"
  "\n"
  "	SOLVE state METHOD cnexp\n"
  "\n"
  "	xm[0]=xm[1]\n"
  "	xm[1]=cli\n"
  "\n"
  "	vm = (xm[1]-xm[0])/(dt*10^-3)\n"
  "\n"
  "	::isometric and isokinetic condition::\n"
  "	mgi = AM^alpha\n"
  "}\n"
  "\n"
  "DERIVATIVE state {\n"
  "	rate (cli, CaT, AM, t)\n"
  "\n"
  "	CaSR' = -k1*CS0*CaSR + (k1*CaSR+k2)*CaSRCS - R + U(Ca)\n"
  "	CaSRCS' = k1*CS0*CaSR - (k1*CaSR+k2)*CaSRCS\n"
  "\n"
  "	Ca' = - k5*T0*Ca + (k5*Ca+k6)*CaT - k3*B0*Ca + (k3*Ca+k4)*CaB + R - U(Ca)\n"
  "	CaB' = k3*B0*Ca - (k3*Ca+k4)*CaB\n"
  "	CaT' = k5*T0*Ca - (k5*Ca+k6)*CaT\n"
  "\n"
  "	AM' = (AMinf -AM)/AMtau\n"
  "	mgi' = 0\n"
  "}\n"
  "\n"
  "PROCEDURE SPK_DETECT (v (mv), t (ms)) {\n"
  "	if (Spike_On == 0 && v > vth) {\n"
  "	Spike_On = 1\n"
  "	spk[spk_index] = t + t_axon\n"
  "	spk_index = spk_index + 1\n"
  "	R_On = 1\n"
  "	} else if (v < vth) {\n"
  "	Spike_On = 0\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION U (x) {\n"
  "	if (x >= 0) {U = Umax*(x^2*k^2/(1+x*k+x^2*k^2))^2}\n"
  "	else {U = 0}\n"
  "}\n"
  "\n"
  "FUNCTION phi (x) {\n"
  "	if (x <= -8) {phi = phi1*x + phi2}\n"
  "	else {phi = phi3*x + phi4}\n"
  "}\n"
  "\n"
  "PROCEDURE CaR (CaSR (M), t (ms)) { LOCAL i, tempR  ::Ca_Release::\n"
  "	if (R_On == 1) {\n"
  "    if (spk_index > 0){\n"
  "      tempR = tempR + CaSR*Rmax*(1-exp(-(t-spk[spk_index-1])/t1))*exp(-(t-spk[spk_index-1])/t2)\n"
  "    }\n"
  "    R = tempR\n"
  "    tempR = 0\n"
  "	}\n"
  "	else {R = 0}\n"
  "}\n"
  "\n"
  "PROCEDURE rate (cli (M), CaT (M), AM (M), t(ms)) {\n"
  "	k5 = phi(cli)*k5i\n"
  "	k6 = k6i/(1 + SF_AM*AM)\n"
  "	AMinf = 0.5*(1+tanh(((CaT/T0)-c1)/c2))\n"
  "	AMtau = c3/(cosh(((CaT/T0)-c4)/(2*c5)))\n"
  "}\n"
  "\n"
  "INITIAL {LOCAL i\n"
  "	CaSR = 0.0025  		:[M]\n"
  "	CaSRCS = 0			:[M]\n"
  "	Ca = 1e-10			:[M]\n"
  "	CaB = 0				:[M]\n"
  "	CaT = 0				:[M]\n"
  "	AM = 0				:[M]\n"
  "	mgi = 0\n"
  "\n"
  "	FROM i = 0 TO 9999 {\n"
  "	spk[i] = 0\n"
  "	}\n"
  "	FROM i = 0 TO 1 {\n"
  "	xm[i] = 0\n"
  "	}\n"
  "	spk_index = 0\n"
  "	R_On = 0\n"
  "}\n"
  ;
#endif
