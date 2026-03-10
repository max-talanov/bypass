/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#define _pval pval
// clang-format off
#include "md1redef.h"
#include "section_fwd.hpp"
#include "nrniv_mf.h"
#include "md2redef.h"
#include "nrnconf.h"
// clang-format on
#include "neuron/cache/mechanism_range.hpp"
static constexpr auto number_of_datum_variables = 4;
static constexpr auto number_of_floating_point_variables = 22;
namespace {
template <typename T>
using _nrn_mechanism_std_vector = std::vector<T>;
using _nrn_model_sorted_token = neuron::model_sorted_token;
using _nrn_mechanism_cache_range = neuron::cache::MechanismRange<number_of_floating_point_variables, number_of_datum_variables>;
using _nrn_mechanism_cache_instance = neuron::cache::MechanismInstance<number_of_floating_point_variables, number_of_datum_variables>;
using _nrn_non_owning_id_without_container = neuron::container::non_owning_identifier_without_container;
template <typename T>
using _nrn_mechanism_field = neuron::mechanism::field<T>;
template <typename... Args>
void _nrn_mechanism_register_data_fields(Args&&... args) {
  neuron::mechanism::register_data_fields(std::forward<Args>(args)...);
}
}
 
#if !NRNGPU
#undef exp
#define exp hoc_Exp
#if NRN_ENABLE_ARCH_INDEP_EXP_POW
#undef pow
#define pow hoc_pow
#endif
#endif
 
#define nrn_init _nrn_init__fHill
#define _nrn_initial _nrn_initial__fHill
#define nrn_cur _nrn_cur__fHill
#define _nrn_current _nrn_current__fHill
#define nrn_jacob _nrn_jacob__fHill
#define nrn_state _nrn_state__fHill
#define _net_receive _net_receive__fHill 
#define state_hill state_hill__fHill 
 
#define _threadargscomma_ _ml, _iml, _ppvar, _thread, _globals, _nt,
#define _threadargsprotocomma_ Memb_list* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt,
#define _internalthreadargsprotocomma_ _nrn_mechanism_cache_range* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt,
#define _threadargs_ _ml, _iml, _ppvar, _thread, _globals, _nt
#define _threadargsproto_ Memb_list* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt
#define _internalthreadargsproto_ _nrn_mechanism_cache_range* _ml, size_t _iml, Datum* _ppvar, Datum* _thread, double* _globals, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *hoc_getarg(int);
 
#define t _nt->_t
#define dt _nt->_dt
#define a0 _ml->template fpfield<0>(_iml)
#define a0_columnindex 0
#define b0 _ml->template fpfield<1>(_iml)
#define b0_columnindex 1
#define c0 _ml->template fpfield<2>(_iml)
#define c0_columnindex 2
#define d0 _ml->template fpfield<3>(_iml)
#define d0_columnindex 3
#define p0 _ml->template fpfield<4>(_iml)
#define p0_columnindex 4
#define g1 _ml->template fpfield<5>(_iml)
#define g1_columnindex 5
#define g2 _ml->template fpfield<6>(_iml)
#define g2_columnindex 6
#define xm_init _ml->template fpfield<7>(_iml)
#define xm_init_columnindex 7
#define xce_init _ml->template fpfield<8>(_iml)
#define xce_init_columnindex 8
#define Kse _ml->template fpfield<9>(_iml)
#define Kse_columnindex 9
#define F _ml->template fpfield<10>(_iml)
#define F_columnindex 10
#define Fc _ml->template fpfield<11>(_iml)
#define Fc_columnindex 11
#define A _ml->template fpfield<12>(_iml)
#define A_columnindex 12
#define xce _ml->template fpfield<13>(_iml)
#define xce_columnindex 13
#define xm _ml->template fpfield<14>(_iml)
#define xm_columnindex 14
#define DA _ml->template fpfield<15>(_iml)
#define DA_columnindex 15
#define Dxce _ml->template fpfield<16>(_iml)
#define Dxce_columnindex 16
#define Dxm _ml->template fpfield<17>(_iml)
#define Dxm_columnindex 17
#define mgi _ml->template fpfield<18>(_iml)
#define mgi_columnindex 18
#define cli _ml->template fpfield<19>(_iml)
#define cli_columnindex 19
#define v _ml->template fpfield<20>(_iml)
#define v_columnindex 20
#define _g _ml->template fpfield<21>(_iml)
#define _g_columnindex 21
#define _ion_mgi *(_ml->dptr_field<0>(_iml))
#define _p_ion_mgi static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_mgo *(_ml->dptr_field<1>(_iml))
#define _p_ion_mgo static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_cli *(_ml->dptr_field<2>(_iml))
#define _p_ion_cli static_cast<neuron::container::data_handle<double>>(_ppvar[2])
#define _ion_clo *(_ml->dptr_field<3>(_iml))
#define _p_ion_clo static_cast<neuron::container::data_handle<double>>(_ppvar[3])
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_dxdt(void);
 static void _hoc_g(void);
 static void _hoc_xse(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mechtype);
#endif
 static void _hoc_setdata();
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 {"setdata_fHill", _hoc_setdata},
 {"dxdt_fHill", _hoc_dxdt},
 {"g_fHill", _hoc_g},
 {"xse_fHill", _hoc_xse},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_dxdt(Prop*);
 static double _npy_g(Prop*);
 static double _npy_xse(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"dxdt", _npy_dxdt},
 {"g", _npy_g},
 {"xse", _npy_xse},
 {0, 0}
};
#define dxdt dxdt_fHill
#define g g_fHill
#define xse xse_fHill
 extern double dxdt( _internalthreadargsprotocomma_ double , double );
 extern double g( _internalthreadargsprotocomma_ double );
 extern double xse( _internalthreadargsprotocomma_ double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {0, 0}
};
 static double A0 = 0;
 static double delta_t = 0.01;
 static double xm0 = 0;
 static double xce0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {0, 0}
};
 static DoubVec hoc_vdoub[] = {
 {0, 0, 0}
};
 static double _sav_indep;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 _prop_id = _nrn_get_prop_id(_prop);
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 static void nrn_alloc(Prop*);
static void nrn_init(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_state(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void nrn_cur(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_jacob(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(Prop*, int, neuron::container::data_handle<double>*, neuron::container::data_handle<double>*, double*, int);
static void _ode_spec(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void _ode_matsol(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 
#define _cvode_ieq _ppvar[4].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
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
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     2.35, /* a0 */
     24.35, /* b0 */
     -7.4, /* c0 */
     30.3, /* d0 */
     23, /* p0 */
     -8, /* g1 */
     10, /* g2 */
     -8, /* xm_init */
     -8, /* xce_init */
     0.4, /* Kse */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
   _ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 22);
 	/*initialize range parameters*/
 	a0 = _parm_default[0]; /* 2.35 */
 	b0 = _parm_default[1]; /* 24.35 */
 	c0 = _parm_default[2]; /* -7.4 */
 	d0 = _parm_default[3]; /* 30.3 */
 	p0 = _parm_default[4]; /* 23 */
 	g1 = _parm_default[5]; /* -8 */
 	g2 = _parm_default[6]; /* 10 */
 	xm_init = _parm_default[7]; /* -8 */
 	xce_init = _parm_default[8]; /* -8 */
 	Kse = _parm_default[9]; /* 0.4 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 22);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_mg_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* mgi */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* mgo */
 prop_ion = need_memb(_cl_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* cli */
 	_ppvar[3] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* clo */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 {0, 0}
};
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _hill_eq_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("mg", 2.0);
 	ion_reg("cl", -1.0);
 	_mg_sym = hoc_lookup("mg_ion");
 	_cl_sym = hoc_lookup("cl_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"a0"} /* 0 */,
                                       _nrn_mechanism_field<double>{"b0"} /* 1 */,
                                       _nrn_mechanism_field<double>{"c0"} /* 2 */,
                                       _nrn_mechanism_field<double>{"d0"} /* 3 */,
                                       _nrn_mechanism_field<double>{"p0"} /* 4 */,
                                       _nrn_mechanism_field<double>{"g1"} /* 5 */,
                                       _nrn_mechanism_field<double>{"g2"} /* 6 */,
                                       _nrn_mechanism_field<double>{"xm_init"} /* 7 */,
                                       _nrn_mechanism_field<double>{"xce_init"} /* 8 */,
                                       _nrn_mechanism_field<double>{"Kse"} /* 9 */,
                                       _nrn_mechanism_field<double>{"F"} /* 10 */,
                                       _nrn_mechanism_field<double>{"Fc"} /* 11 */,
                                       _nrn_mechanism_field<double>{"A"} /* 12 */,
                                       _nrn_mechanism_field<double>{"xce"} /* 13 */,
                                       _nrn_mechanism_field<double>{"xm"} /* 14 */,
                                       _nrn_mechanism_field<double>{"DA"} /* 15 */,
                                       _nrn_mechanism_field<double>{"Dxce"} /* 16 */,
                                       _nrn_mechanism_field<double>{"Dxm"} /* 17 */,
                                       _nrn_mechanism_field<double>{"mgi"} /* 18 */,
                                       _nrn_mechanism_field<double>{"cli"} /* 19 */,
                                       _nrn_mechanism_field<double>{"v"} /* 20 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 21 */,
                                       _nrn_mechanism_field<double*>{"_ion_mgi", "mg_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_mgo", "mg_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_cli", "cl_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_clo", "cl_ion"} /* 3 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 4 */);
  hoc_register_prop_size(_mechtype, 22, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "mg_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "mg_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 fHill /Users/ann/memCPG/CPG_STDP/py/mod_files/hill_eq.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "Modified Hill-Mashima muscle model";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[1], _dlist1[1];
 static int state_hill(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (_internalthreadargsproto_) {int _reset = 0; {
   Fc = p0 * g ( _threadargscomma_ xm ) * A ;
   Dxce = dxdt ( _threadargscomma_ F , Fc ) ;
   }
 return _reset;
}
 static int _ode_matsol1 (_internalthreadargsproto_) {
 Fc = p0 * g ( _threadargscomma_ xm ) * A ;
 Dxce = Dxce  / (1. - dt*( 0.0 )) ;
  return 0;
}
 /*END CVODE*/
 static int state_hill (_internalthreadargsproto_) { {
   Fc = p0 * g ( _threadargscomma_ xm ) * A ;
    xce = xce - dt*(- ( dxdt ( _threadargscomma_ F , Fc ) ) ) ;
   }
  return 0;
}
 
double xse ( _internalthreadargsprotocomma_ double _lx , double _ly ) {
   double _lxse;
 double _ld_xm , _ld_xce , _ld_se ;
 _ld_se = ( _lx - xm_init ) - ( _ly - xce_init ) ;
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
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for xse_fHill. Requires prior call to setdata_fHill and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  xse ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_xse(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  xse ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
double g ( _internalthreadargsprotocomma_ double _lx ) {
   double _lg;
 _lg = exp ( - pow( ( ( _lx - g1 ) / g2 ) , 2.0 ) ) ;
   
return _lg;
 }
 
static void _hoc_g(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for g_fHill. Requires prior call to setdata_fHill and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  g ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_g(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  g ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double dxdt ( _internalthreadargsprotocomma_ double _lx , double _lxc ) {
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
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for dxdt_fHill. Requires prior call to setdata_fHill and that the specified mechanism instance still be in existence.", NULL);
  }
  Prop* _local_prop = _extcall_prop;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  dxdt ( _threadargscomma_ *getarg(1) , *getarg(2) );
 hoc_retpushx(_r);
}
 
static double _npy_dxdt(Prop* _prop) {
    double _r{0.0};
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 _nrn_mechanism_cache_instance _ml_real{_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _nrn_mechanism_access_dparam(_prop);
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  dxdt ( _threadargscomma_ *getarg(1) , *getarg(2) );
 return(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
   Datum* _ppvar;
   size_t _iml;   _nrn_mechanism_cache_range* _ml;   Node* _nd{};
  double _v{};
  int _cntml;
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
  _ml = &_lmr;
  _cntml = _ml_arg->_nodecount;
  Datum *_thread{_ml_arg->_thread};
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _ppvar = _ml_arg->_pdata[_iml];
    _nd = _ml_arg->_nodelist[_iml];
    v = NODEV(_nd);
  mgi = _ion_mgi;
  cli = _ion_cli;
     _ode_spec1 (_threadargs_);
 }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 1; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _ode_matsol1 (_threadargs_);
 }
 
static void _ode_matsol(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
   Datum* _ppvar;
   size_t _iml;   _nrn_mechanism_cache_range* _ml;   Node* _nd{};
  double _v{};
  int _cntml;
  _nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
  _ml = &_lmr;
  _cntml = _ml_arg->_nodecount;
  Datum *_thread{_ml_arg->_thread};
  double* _globals = nullptr;
  if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _ppvar = _ml_arg->_pdata[_iml];
    _nd = _ml_arg->_nodelist[_iml];
    v = NODEV(_nd);
  mgi = _ion_mgi;
  cli = _ion_cli;
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(_internalthreadargsproto_) {
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

static void nrn_init(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
 v = _v;
  mgi = _ion_mgi;
  cli = _ion_cli;
 initmodel(_threadargs_);
}
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{
} return _current;
}

static void nrn_cur(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_rhs = _nt->node_rhs_storage();
auto const _vec_sav_rhs = _nt->node_sav_rhs_storage();
auto const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
   _v = _vec_v[_ni[_iml]];
 
}
 
}

static void nrn_jacob(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto const _vec_d = _nt->node_d_storage();
auto const _vec_sav_d = _nt->node_sav_d_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (_iml = 0; _iml < _cntml; ++_iml) {
  _vec_d[_ni[_iml]] += _g;
 
}
 
}

static void nrn_state(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type) {
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
auto* const _ml = &_lmr;
Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni;
_ni = _ml_arg->_nodeindices;
size_t _cntml = _ml_arg->_nodecount;
_thread = _ml_arg->_thread;
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
for (size_t _iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
 _nd = _ml_arg->_nodelist[_iml];
   _v = _vec_v[_ni[_iml]];
 v=_v;
{
  mgi = _ion_mgi;
  cli = _ion_cli;
 {   state_hill(_threadargs_);
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
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {xce_columnindex, 0};  _dlist1[0] = {Dxce_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/hill_eq.mod";
    const char* nmodl_file_text = 
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
  "	g2 = 10 : 21.4		:[mm]\n"
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
  "	d_se = (x - xm_init) - (y - xce_init)\n"
  "    if (d_se <= 0) {\n"
  "        xse = 0\n"
  "    } else {\n"
  "        xse = d_se\n"
  "    }\n"
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
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
