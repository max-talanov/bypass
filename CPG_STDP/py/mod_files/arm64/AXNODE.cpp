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
static constexpr auto number_of_datum_variables = 0;
static constexpr auto number_of_floating_point_variables = 32;
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
 
#define nrn_init _nrn_init__axnode
#define _nrn_initial _nrn_initial__axnode
#define nrn_cur _nrn_cur__axnode
#define _nrn_current _nrn_current__axnode
#define nrn_jacob _nrn_jacob__axnode
#define nrn_state _nrn_state__axnode
#define _net_receive _net_receive__axnode 
#define evaluate_fct evaluate_fct__axnode 
#define states states__axnode 
 
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
#define gnapbar _ml->template fpfield<0>(_iml)
#define gnapbar_columnindex 0
#define gnabar _ml->template fpfield<1>(_iml)
#define gnabar_columnindex 1
#define gkbar _ml->template fpfield<2>(_iml)
#define gkbar_columnindex 2
#define gl _ml->template fpfield<3>(_iml)
#define gl_columnindex 3
#define ena _ml->template fpfield<4>(_iml)
#define ena_columnindex 4
#define ek _ml->template fpfield<5>(_iml)
#define ek_columnindex 5
#define el _ml->template fpfield<6>(_iml)
#define el_columnindex 6
#define inap _ml->template fpfield<7>(_iml)
#define inap_columnindex 7
#define ina _ml->template fpfield<8>(_iml)
#define ina_columnindex 8
#define ik _ml->template fpfield<9>(_iml)
#define ik_columnindex 9
#define il _ml->template fpfield<10>(_iml)
#define il_columnindex 10
#define mp_inf _ml->template fpfield<11>(_iml)
#define mp_inf_columnindex 11
#define m_inf _ml->template fpfield<12>(_iml)
#define m_inf_columnindex 12
#define h_inf _ml->template fpfield<13>(_iml)
#define h_inf_columnindex 13
#define s_inf _ml->template fpfield<14>(_iml)
#define s_inf_columnindex 14
#define tau_mp _ml->template fpfield<15>(_iml)
#define tau_mp_columnindex 15
#define tau_m _ml->template fpfield<16>(_iml)
#define tau_m_columnindex 16
#define tau_h _ml->template fpfield<17>(_iml)
#define tau_h_columnindex 17
#define tau_s _ml->template fpfield<18>(_iml)
#define tau_s_columnindex 18
#define mp _ml->template fpfield<19>(_iml)
#define mp_columnindex 19
#define m _ml->template fpfield<20>(_iml)
#define m_columnindex 20
#define h _ml->template fpfield<21>(_iml)
#define h_columnindex 21
#define s _ml->template fpfield<22>(_iml)
#define s_columnindex 22
#define Dmp _ml->template fpfield<23>(_iml)
#define Dmp_columnindex 23
#define Dm _ml->template fpfield<24>(_iml)
#define Dm_columnindex 24
#define Dh _ml->template fpfield<25>(_iml)
#define Dh_columnindex 25
#define Ds _ml->template fpfield<26>(_iml)
#define Ds_columnindex 26
#define q10_1 _ml->template fpfield<27>(_iml)
#define q10_1_columnindex 27
#define q10_2 _ml->template fpfield<28>(_iml)
#define q10_2_columnindex 28
#define q10_3 _ml->template fpfield<29>(_iml)
#define q10_3_columnindex 29
#define v _ml->template fpfield<30>(_iml)
#define v_columnindex 30
#define _g _ml->template fpfield<31>(_iml)
#define _g_columnindex 31
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_Exp(void);
 static void _hoc_evaluate_fct(void);
 static void _hoc_vtrap(void);
 static void _hoc_vtrap8(void);
 static void _hoc_vtrap7(void);
 static void _hoc_vtrap6(void);
 static void _hoc_vtrap2(void);
 static void _hoc_vtrap1(void);
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
 {"setdata_axnode", _hoc_setdata},
 {"Exp_axnode", _hoc_Exp},
 {"evaluate_fct_axnode", _hoc_evaluate_fct},
 {"vtrap_axnode", _hoc_vtrap},
 {"vtrap8_axnode", _hoc_vtrap8},
 {"vtrap7_axnode", _hoc_vtrap7},
 {"vtrap6_axnode", _hoc_vtrap6},
 {"vtrap2_axnode", _hoc_vtrap2},
 {"vtrap1_axnode", _hoc_vtrap1},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_Exp(Prop*);
 static double _npy_evaluate_fct(Prop*);
 static double _npy_vtrap(Prop*);
 static double _npy_vtrap8(Prop*);
 static double _npy_vtrap7(Prop*);
 static double _npy_vtrap6(Prop*);
 static double _npy_vtrap2(Prop*);
 static double _npy_vtrap1(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"Exp", _npy_Exp},
 {"evaluate_fct", _npy_evaluate_fct},
 {"vtrap", _npy_vtrap},
 {"vtrap8", _npy_vtrap8},
 {"vtrap7", _npy_vtrap7},
 {"vtrap6", _npy_vtrap6},
 {"vtrap2", _npy_vtrap2},
 {"vtrap1", _npy_vtrap1},
 {0, 0}
};
#define Exp Exp_axnode
#define vtrap vtrap_axnode
#define vtrap8 vtrap8_axnode
#define vtrap7 vtrap7_axnode
#define vtrap6 vtrap6_axnode
#define vtrap2 vtrap2_axnode
#define vtrap1 vtrap1_axnode
 extern double Exp( _internalthreadargsprotocomma_ double );
 extern double vtrap( _internalthreadargsprotocomma_ double );
 extern double vtrap8( _internalthreadargsprotocomma_ double );
 extern double vtrap7( _internalthreadargsprotocomma_ double );
 extern double vtrap6( _internalthreadargsprotocomma_ double );
 extern double vtrap2( _internalthreadargsprotocomma_ double );
 extern double vtrap1( _internalthreadargsprotocomma_ double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define asC asC_axnode
 double asC = -5;
#define asB asB_axnode
 double asB = -27;
#define asA asA_axnode
 double asA = 0.3;
#define ahC ahC_axnode
 double ahC = 11;
#define ahB ahB_axnode
 double ahB = 114;
#define ahA ahA_axnode
 double ahA = 0.062;
#define amC amC_axnode
 double amC = 10.3;
#define amB amB_axnode
 double amB = 21.4;
#define amA amA_axnode
 double amA = 1.86;
#define ampC ampC_axnode
 double ampC = 10.2;
#define ampB ampB_axnode
 double ampB = 27;
#define ampA ampA_axnode
 double ampA = 0.01;
#define bsC bsC_axnode
 double bsC = -1;
#define bsB bsB_axnode
 double bsB = 10;
#define bsA bsA_axnode
 double bsA = 0.03;
#define bhC bhC_axnode
 double bhC = 13.4;
#define bhB bhB_axnode
 double bhB = 31.8;
#define bhA bhA_axnode
 double bhA = 2.3;
#define bmC bmC_axnode
 double bmC = 9.16;
#define bmB bmB_axnode
 double bmB = 25.7;
#define bmA bmA_axnode
 double bmA = 0.086;
#define bmpC bmpC_axnode
 double bmpC = 10;
#define bmpB bmpB_axnode
 double bmpB = 34;
#define bmpA bmpA_axnode
 double bmpA = 0.00025;
#define vtraub vtraub_axnode
 double vtraub = -80;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gnapbar_axnode", "mho/cm2"},
 {"gnabar_axnode", "mho/cm2"},
 {"gkbar_axnode", "mho/cm2"},
 {"gl_axnode", "mho/cm2"},
 {"ena_axnode", "mV"},
 {"ek_axnode", "mV"},
 {"el_axnode", "mV"},
 {"inap_axnode", "mA/cm2"},
 {"ina_axnode", "mA/cm2"},
 {"ik_axnode", "mA/cm2"},
 {"il_axnode", "mA/cm2"},
 {0, 0}
};
 static double delta_t = 0.01;
 static double h0 = 0;
 static double m0 = 0;
 static double mp0 = 0;
 static double s0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"vtraub_axnode", &vtraub_axnode},
 {"ampA_axnode", &ampA_axnode},
 {"ampB_axnode", &ampB_axnode},
 {"ampC_axnode", &ampC_axnode},
 {"bmpA_axnode", &bmpA_axnode},
 {"bmpB_axnode", &bmpB_axnode},
 {"bmpC_axnode", &bmpC_axnode},
 {"amA_axnode", &amA_axnode},
 {"amB_axnode", &amB_axnode},
 {"amC_axnode", &amC_axnode},
 {"bmA_axnode", &bmA_axnode},
 {"bmB_axnode", &bmB_axnode},
 {"bmC_axnode", &bmC_axnode},
 {"ahA_axnode", &ahA_axnode},
 {"ahB_axnode", &ahB_axnode},
 {"ahC_axnode", &ahC_axnode},
 {"bhA_axnode", &bhA_axnode},
 {"bhB_axnode", &bhB_axnode},
 {"bhC_axnode", &bhC_axnode},
 {"asA_axnode", &asA_axnode},
 {"asB_axnode", &asB_axnode},
 {"asC_axnode", &asC_axnode},
 {"bsA_axnode", &bsA_axnode},
 {"bsB_axnode", &bsB_axnode},
 {"bsC_axnode", &bsC_axnode},
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
 
#define _cvode_ieq _ppvar[0].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"axnode",
 "gnapbar_axnode",
 "gnabar_axnode",
 "gkbar_axnode",
 "gl_axnode",
 "ena_axnode",
 "ek_axnode",
 "el_axnode",
 0,
 "inap_axnode",
 "ina_axnode",
 "ik_axnode",
 "il_axnode",
 "mp_inf_axnode",
 "m_inf_axnode",
 "h_inf_axnode",
 "s_inf_axnode",
 "tau_mp_axnode",
 "tau_m_axnode",
 "tau_h_axnode",
 "tau_s_axnode",
 0,
 "mp_axnode",
 "m_axnode",
 "h_axnode",
 "s_axnode",
 0,
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0.01, /* gnapbar */
     7.4, /* gnabar */
     0.13, /* gkbar */
     0.007, /* gl */
     50, /* ena */
     -90, /* ek */
     -70, /* el */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
   _ppvar = nrn_prop_datum_alloc(_mechtype, 1, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 32);
 	/*initialize range parameters*/
 	gnapbar = _parm_default[0]; /* 0.01 */
 	gnabar = _parm_default[1]; /* 7.4 */
 	gkbar = _parm_default[2]; /* 0.13 */
 	gl = _parm_default[3]; /* 0.007 */
 	ena = _parm_default[4]; /* 50 */
 	ek = _parm_default[5]; /* -90 */
 	el = _parm_default[6]; /* -70 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 32);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 
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

 extern "C" void _AXNODE_reg() {
	int _vectorized = 1;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"gnapbar"} /* 0 */,
                                       _nrn_mechanism_field<double>{"gnabar"} /* 1 */,
                                       _nrn_mechanism_field<double>{"gkbar"} /* 2 */,
                                       _nrn_mechanism_field<double>{"gl"} /* 3 */,
                                       _nrn_mechanism_field<double>{"ena"} /* 4 */,
                                       _nrn_mechanism_field<double>{"ek"} /* 5 */,
                                       _nrn_mechanism_field<double>{"el"} /* 6 */,
                                       _nrn_mechanism_field<double>{"inap"} /* 7 */,
                                       _nrn_mechanism_field<double>{"ina"} /* 8 */,
                                       _nrn_mechanism_field<double>{"ik"} /* 9 */,
                                       _nrn_mechanism_field<double>{"il"} /* 10 */,
                                       _nrn_mechanism_field<double>{"mp_inf"} /* 11 */,
                                       _nrn_mechanism_field<double>{"m_inf"} /* 12 */,
                                       _nrn_mechanism_field<double>{"h_inf"} /* 13 */,
                                       _nrn_mechanism_field<double>{"s_inf"} /* 14 */,
                                       _nrn_mechanism_field<double>{"tau_mp"} /* 15 */,
                                       _nrn_mechanism_field<double>{"tau_m"} /* 16 */,
                                       _nrn_mechanism_field<double>{"tau_h"} /* 17 */,
                                       _nrn_mechanism_field<double>{"tau_s"} /* 18 */,
                                       _nrn_mechanism_field<double>{"mp"} /* 19 */,
                                       _nrn_mechanism_field<double>{"m"} /* 20 */,
                                       _nrn_mechanism_field<double>{"h"} /* 21 */,
                                       _nrn_mechanism_field<double>{"s"} /* 22 */,
                                       _nrn_mechanism_field<double>{"Dmp"} /* 23 */,
                                       _nrn_mechanism_field<double>{"Dm"} /* 24 */,
                                       _nrn_mechanism_field<double>{"Dh"} /* 25 */,
                                       _nrn_mechanism_field<double>{"Ds"} /* 26 */,
                                       _nrn_mechanism_field<double>{"q10_1"} /* 27 */,
                                       _nrn_mechanism_field<double>{"q10_2"} /* 28 */,
                                       _nrn_mechanism_field<double>{"q10_3"} /* 29 */,
                                       _nrn_mechanism_field<double>{"v"} /* 30 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 31 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 0 */);
  hoc_register_prop_size(_mechtype, 32, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 axnode /Users/ann/memCPG/CPG_STDP/py/mod_files/AXNODE.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "Motor Axon Node channels";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int evaluate_fct(_internalthreadargsprotocomma_ double);
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[4], _dlist1[4];
 static int states(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (_internalthreadargsproto_) {int _reset = 0; {
   evaluate_fct ( _threadargscomma_ v ) ;
   Dmp = ( mp_inf - mp ) / tau_mp ;
   Dm = ( m_inf - m ) / tau_m ;
   Dh = ( h_inf - h ) / tau_h ;
   Ds = ( s_inf - s ) / tau_s ;
   }
 return _reset;
}
 static int _ode_matsol1 (_internalthreadargsproto_) {
 evaluate_fct ( _threadargscomma_ v ) ;
 Dmp = Dmp  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_mp )) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_m )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_h )) ;
 Ds = Ds  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_s )) ;
  return 0;
}
 /*END CVODE*/
 static int states (_internalthreadargsproto_) { {
   evaluate_fct ( _threadargscomma_ v ) ;
    mp = mp + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_mp)))*(- ( ( ( mp_inf ) ) / tau_mp ) / ( ( ( ( - 1.0 ) ) ) / tau_mp ) - mp) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_m)))*(- ( ( ( m_inf ) ) / tau_m ) / ( ( ( ( - 1.0 ) ) ) / tau_m ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h)))*(- ( ( ( h_inf ) ) / tau_h ) / ( ( ( ( - 1.0 ) ) ) / tau_h ) - h) ;
    s = s + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_s)))*(- ( ( ( s_inf ) ) / tau_s ) / ( ( ( ( - 1.0 ) ) ) / tau_s ) - s) ;
   }
  return 0;
}
 
static int  evaluate_fct ( _internalthreadargsprotocomma_ double _lv ) {
   double _la , _lb , _lv2 ;
 _la = q10_1 * vtrap1 ( _threadargscomma_ _lv ) ;
   _lb = q10_1 * vtrap2 ( _threadargscomma_ _lv ) ;
   tau_mp = 1.0 / ( _la + _lb ) ;
   mp_inf = _la / ( _la + _lb ) ;
   _la = q10_1 * vtrap6 ( _threadargscomma_ _lv ) ;
   _lb = q10_1 * vtrap7 ( _threadargscomma_ _lv ) ;
   tau_m = 1.0 / ( _la + _lb ) ;
   m_inf = _la / ( _la + _lb ) ;
   _la = q10_2 * vtrap8 ( _threadargscomma_ _lv ) ;
   _lb = q10_2 * bhA / ( 1.0 + Exp ( _threadargscomma_ - ( _lv + bhB ) / bhC ) ) ;
   tau_h = 1.0 / ( _la + _lb ) ;
   h_inf = _la / ( _la + _lb ) ;
   _lv2 = _lv - vtraub ;
   _la = q10_3 * asA / ( Exp ( _threadargscomma_ ( _lv2 + asB ) / asC ) + 1.0 ) ;
   _lb = q10_3 * bsA / ( Exp ( _threadargscomma_ ( _lv2 + bsB ) / bsC ) + 1.0 ) ;
   tau_s = 1.0 / ( _la + _lb ) ;
   s_inf = _la / ( _la + _lb ) ;
    return 0; }
 
static void _hoc_evaluate_fct(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for evaluate_fct_axnode. Requires prior call to setdata_axnode and that the specified mechanism instance still be in existence.", NULL);
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
 _r = 1.;
 evaluate_fct ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_evaluate_fct(Prop* _prop) {
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
 _r = 1.;
 evaluate_fct ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double vtrap ( _internalthreadargsprotocomma_ double _lx ) {
   double _lvtrap;
 if ( _lx < - 50.0 ) {
     _lvtrap = 0.0 ;
     }
   else {
     _lvtrap = bsA / ( Exp ( _threadargscomma_ ( _lx + bsB ) / bsC ) + 1.0 ) ;
     }
   
return _lvtrap;
 }
 
static void _hoc_vtrap(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  vtrap ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_vtrap(Prop* _prop) {
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
 _r =  vtrap ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double vtrap1 ( _internalthreadargsprotocomma_ double _lx ) {
   double _lvtrap1;
 if ( fabs ( ( _lx + ampB ) / ampC ) < 1e-6 ) {
     _lvtrap1 = ampA * ampC ;
     }
   else {
     _lvtrap1 = ( ampA * ( _lx + ampB ) ) / ( 1.0 - Exp ( _threadargscomma_ - ( _lx + ampB ) / ampC ) ) ;
     }
   
return _lvtrap1;
 }
 
static void _hoc_vtrap1(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  vtrap1 ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_vtrap1(Prop* _prop) {
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
 _r =  vtrap1 ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double vtrap2 ( _internalthreadargsprotocomma_ double _lx ) {
   double _lvtrap2;
 if ( fabs ( ( _lx + bmpB ) / bmpC ) < 1e-6 ) {
     _lvtrap2 = bmpA * bmpC ;
     }
   else {
     _lvtrap2 = ( bmpA * ( - ( _lx + bmpB ) ) ) / ( 1.0 - Exp ( _threadargscomma_ ( _lx + bmpB ) / bmpC ) ) ;
     }
   
return _lvtrap2;
 }
 
static void _hoc_vtrap2(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  vtrap2 ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_vtrap2(Prop* _prop) {
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
 _r =  vtrap2 ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double vtrap6 ( _internalthreadargsprotocomma_ double _lx ) {
   double _lvtrap6;
 if ( fabs ( ( _lx + amB ) / amC ) < 1e-6 ) {
     _lvtrap6 = amA * amC ;
     }
   else {
     _lvtrap6 = ( amA * ( _lx + amB ) ) / ( 1.0 - Exp ( _threadargscomma_ - ( _lx + amB ) / amC ) ) ;
     }
   
return _lvtrap6;
 }
 
static void _hoc_vtrap6(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  vtrap6 ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_vtrap6(Prop* _prop) {
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
 _r =  vtrap6 ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double vtrap7 ( _internalthreadargsprotocomma_ double _lx ) {
   double _lvtrap7;
 if ( fabs ( ( _lx + bmB ) / bmC ) < 1e-6 ) {
     _lvtrap7 = bmA * bmC ;
     }
   else {
     _lvtrap7 = ( bmA * ( - ( _lx + bmB ) ) ) / ( 1.0 - Exp ( _threadargscomma_ ( _lx + bmB ) / bmC ) ) ;
     }
   
return _lvtrap7;
 }
 
static void _hoc_vtrap7(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  vtrap7 ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_vtrap7(Prop* _prop) {
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
 _r =  vtrap7 ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double vtrap8 ( _internalthreadargsprotocomma_ double _lx ) {
   double _lvtrap8;
 if ( fabs ( ( _lx + ahB ) / ahC ) < 1e-6 ) {
     _lvtrap8 = ahA * ahC ;
     }
   else {
     _lvtrap8 = ( ahA * ( - ( _lx + ahB ) ) ) / ( 1.0 - Exp ( _threadargscomma_ ( _lx + ahB ) / ahC ) ) ;
     }
   
return _lvtrap8;
 }
 
static void _hoc_vtrap8(void) {
  double _r;
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  vtrap8 ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_vtrap8(Prop* _prop) {
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
 _r =  vtrap8 ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double Exp ( _internalthreadargsprotocomma_ double _lx ) {
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
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  Prop* _local_prop = _prop_id ? _extcall_prop : nullptr;
  _nrn_mechanism_cache_instance _ml_real{_local_prop};
auto* const _ml = &_ml_real;
size_t const _iml{};
_ppvar = _local_prop ? _nrn_mechanism_access_dparam(_local_prop) : nullptr;
_thread = _extcall_thread.data();
double* _globals = nullptr;
if (gind != 0 && _thread != nullptr) { _globals = _thread[_gth].get<double*>(); }
_nt = nrn_threads;
 _r =  Exp ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_Exp(Prop* _prop) {
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
 _r =  Exp ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
static int _ode_count(int _type){ return 4;}
 
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
     _ode_spec1 (_threadargs_);
 }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 4; ++_i) {
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
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  h = h0;
  m = m0;
  mp = mp0;
  s = s0;
 {
   q10_1 = pow( 2.2 , ( ( celsius - 20.0 ) / 10.0 ) ) ;
   q10_2 = pow( 2.9 , ( ( celsius - 20.0 ) / 10.0 ) ) ;
   q10_3 = pow( 3.0 , ( ( celsius - 36.0 ) / 10.0 ) ) ;
   evaluate_fct ( _threadargscomma_ v ) ;
   mp = mp_inf ;
   m = m_inf ;
   h = h_inf ;
   s = s_inf ;
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
 initmodel(_threadargs_);
}
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   inap = gnapbar * mp * mp * mp * ( v - ena ) ;
   ina = gnabar * m * m * m * h * ( v - ena ) ;
   ik = gkbar * s * ( v - ek ) ;
   il = gl * ( v - el ) ;
   }
 _current += ina;
 _current += inap;
 _current += ik;
 _current += il;

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
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ _rhs = _nrn_current(_threadargscomma_ _v);
 	}
 _g = (_g_local - _rhs)/.001;
	 _vec_rhs[_ni[_iml]] -= _rhs;
 
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
 {   states(_threadargs_);
  }}}

}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {mp_columnindex, 0};  _dlist1[0] = {Dmp_columnindex, 0};
 _slist1[1] = {m_columnindex, 0};  _dlist1[1] = {Dm_columnindex, 0};
 _slist1[2] = {h_columnindex, 0};  _dlist1[2] = {Dh_columnindex, 0};
 _slist1[3] = {s_columnindex, 0};  _dlist1[3] = {Ds_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/AXNODE.mod";
    const char* nmodl_file_text = 
  "TITLE Motor Axon Node channels\n"
  "\n"
  ": 2/02\n"
  ": Cameron C. McIntyre\n"
  ":\n"
  ": Fast Na+, Persistant Na+, Slow K+, and Leakage currents \n"
  ": responsible for nodal action potential\n"
  ": Iterative equations H-H notation rest = -80 mV\n"
  ":\n"
  ": This model is described in detail in:\n"
  ":\n"
  ": McIntyre CC, Richardson AG, and Grill WM. Modeling the excitability of\n"
  ": mammalian nerve fibers: influence of afterpotentials on the recovery\n"
  ": cycle. Journal of Neurophysiology 87:995-1006, 2002.\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX axnode\n"
  "	NONSPECIFIC_CURRENT ina\n"
  "	NONSPECIFIC_CURRENT inap\n"
  "	NONSPECIFIC_CURRENT ik\n"
  "	NONSPECIFIC_CURRENT il\n"
  "	RANGE gnapbar, gnabar, gkbar, gl, ena, ek, el\n"
  "	RANGE mp_inf, m_inf, h_inf, s_inf\n"
  "	RANGE tau_mp, tau_m, tau_h, tau_s\n"
  "}\n"
  "\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "\n"
  "	gnapbar = 0.01	(mho/cm2)\n"
  "	gnabar	= 7.4	(mho/cm2)\n"
  "	gkbar   = 0.13 	(mho/cm2)\n"
  "	gl	= 0.007 (mho/cm2)\n"
  "	ena     = 50.0  (mV)\n"
  "	ek      = -90.0 (mV)\n"
  "	el	= -70.0 (mV)\n"
  "	celsius		(degC)\n"
  "	dt              (ms)\n"
  "	v               (mV)\n"
  "	vtraub=-80\n"
  "	ampA = 0.01\n"
  "	ampB = 27\n"
  "	ampC = 10.2\n"
  "	bmpA = 0.00025\n"
  "	bmpB = 34\n"
  "	bmpC = 10\n"
  "	amA = 1.86\n"
  "	amB = 21.4\n"
  "	amC = 10.3\n"
  "	bmA = 0.086\n"
  "	bmB = 25.7\n"
  "	bmC = 9.16\n"
  "	ahA = 0.062\n"
  "	ahB = 114.0\n"
  "	ahC = 11.0\n"
  "	bhA = 2.3\n"
  "	bhB = 31.8\n"
  "	bhC = 13.4\n"
  "	asA = 0.3\n"
  "	asB = -27\n"
  "	asC = -5\n"
  "	bsA = 0.03\n"
  "	bsB = 10\n"
  "	bsC = -1\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	mp m h s\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	inap    (mA/cm2)\n"
  "	ina	(mA/cm2)\n"
  "	ik      (mA/cm2)\n"
  "	il      (mA/cm2)\n"
  "	mp_inf\n"
  "	m_inf\n"
  "	h_inf\n"
  "	s_inf\n"
  "	tau_mp\n"
  "	tau_m\n"
  "	tau_h\n"
  "	tau_s\n"
  "	q10_1\n"
  "	q10_2\n"
  "	q10_3\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	inap = gnapbar * mp*mp*mp * (v - ena)\n"
  "	ina = gnabar * m*m*m*h * (v - ena)\n"
  "	ik   = gkbar * s * (v - ek)\n"
  "	il   = gl * (v - el)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {   : exact Hodgkin-Huxley equations\n"
  "       evaluate_fct(v)\n"
  "	mp'= (mp_inf - mp) / tau_mp\n"
  "	m' = (m_inf - m) / tau_m\n"
  "	h' = (h_inf - h) / tau_h\n"
  "	s' = (s_inf - s) / tau_s\n"
  "}\n"
  "\n"
  "UNITSOFF\n"
  "\n"
  "INITIAL {\n"
  ":\n"
  ":	Q10 adjustment\n"
  ":\n"
  "\n"
  "	q10_1 = 2.2 ^ ((celsius-20)/ 10 )\n"
  "	q10_2 = 2.9 ^ ((celsius-20)/ 10 )\n"
  "	q10_3 = 3.0 ^ ((celsius-36)/ 10 )\n"
  "\n"
  "	evaluate_fct(v)\n"
  "	mp = mp_inf\n"
  "	m = m_inf\n"
  "	h = h_inf\n"
  "	s = s_inf\n"
  "}\n"
  "\n"
  "PROCEDURE evaluate_fct(v(mV)) { LOCAL a,b,v2\n"
  "\n"
  "	a = q10_1*vtrap1(v)\n"
  "	b = q10_1*vtrap2(v)\n"
  "	tau_mp = 1 / (a + b)\n"
  "	mp_inf = a / (a + b)\n"
  "\n"
  "	a = q10_1*vtrap6(v)\n"
  "	b = q10_1*vtrap7(v)\n"
  "	tau_m = 1 / (a + b)\n"
  "	m_inf = a / (a + b)\n"
  "\n"
  "	a = q10_2*vtrap8(v)\n"
  "	b = q10_2*bhA / (1 + Exp(-(v+bhB)/bhC))\n"
  "	tau_h = 1 / (a + b)\n"
  "	h_inf = a / (a + b)\n"
  "\n"
  "	v2 = v - vtraub : convert to traub convention\n"
  "\n"
  "	a = q10_3*asA / (Exp((v2+asB)/asC) + 1) \n"
  "	b = q10_3*bsA / (Exp((v2+bsB)/bsC) + 1)\n"
  "	tau_s = 1 / (a + b)\n"
  "	s_inf = a / (a + b)\n"
  "}\n"
  "\n"
  "FUNCTION vtrap(x) {\n"
  "	if (x < -50) {\n"
  "		vtrap = 0\n"
  "	}else{\n"
  "		vtrap = bsA / (Exp((x+bsB)/bsC) + 1)\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION vtrap1(x) {\n"
  "	if (fabs((x+ampB)/ampC) < 1e-6) {\n"
  "		vtrap1 = ampA*ampC\n"
  "	}else{\n"
  "		vtrap1 = (ampA*(x+ampB)) / (1 - Exp(-(x+ampB)/ampC))\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION vtrap2(x) {\n"
  "	if (fabs((x+bmpB)/bmpC) < 1e-6) {\n"
  "		vtrap2 = bmpA*bmpC : Ted Carnevale minus sign bug fix\n"
  "	}else{\n"
  "		vtrap2 = (bmpA*(-(x+bmpB))) / (1 - Exp((x+bmpB)/bmpC))\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION vtrap6(x) {\n"
  "	if (fabs((x+amB)/amC) < 1e-6) {\n"
  "		vtrap6 = amA*amC\n"
  "	}else{\n"
  "		vtrap6 = (amA*(x+amB)) / (1 - Exp(-(x+amB)/amC))\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION vtrap7(x) {\n"
  "	if (fabs((x+bmB)/bmC) < 1e-6) {\n"
  "		vtrap7 = bmA*bmC : Ted Carnevale minus sign bug fix\n"
  "	}else{\n"
  "		vtrap7 = (bmA*(-(x+bmB))) / (1 - Exp((x+bmB)/bmC))\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION vtrap8(x) {\n"
  "	if (fabs((x+ahB)/ahC) < 1e-6) {\n"
  "		vtrap8 = ahA*ahC : Ted Carnevale minus sign bug fix\n"
  "	}else{\n"
  "		vtrap8 = (ahA*(-(x+ahB))) / (1 - Exp((x+ahB)/ahC)) \n"
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
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
