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
static constexpr auto number_of_floating_point_variables = 44;
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
 
#define nrn_init _nrn_init__motoneuron_5ht
#define _nrn_initial _nrn_initial__motoneuron_5ht
#define nrn_cur _nrn_cur__motoneuron_5ht
#define _nrn_current _nrn_current__motoneuron_5ht
#define nrn_jacob _nrn_jacob__motoneuron_5ht
#define nrn_state _nrn_state__motoneuron_5ht
#define _net_receive _net_receive__motoneuron_5ht 
#define evaluate_fct evaluate_fct__motoneuron_5ht 
#define states states__motoneuron_5ht 
 
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
#define gnabar _ml->template fpfield<0>(_iml)
#define gnabar_columnindex 0
#define gl _ml->template fpfield<1>(_iml)
#define gl_columnindex 1
#define gkrect _ml->template fpfield<2>(_iml)
#define gkrect_columnindex 2
#define gcaN _ml->template fpfield<3>(_iml)
#define gcaN_columnindex 3
#define gcaL _ml->template fpfield<4>(_iml)
#define gcaL_columnindex 4
#define gcak _ml->template fpfield<5>(_iml)
#define gcak_columnindex 5
#define ena _ml->template fpfield<6>(_iml)
#define ena_columnindex 6
#define ek _ml->template fpfield<7>(_iml)
#define ek_columnindex 7
#define el _ml->template fpfield<8>(_iml)
#define el_columnindex 8
#define ina _ml->template fpfield<9>(_iml)
#define ina_columnindex 9
#define il _ml->template fpfield<10>(_iml)
#define il_columnindex 10
#define ikrect _ml->template fpfield<11>(_iml)
#define ikrect_columnindex 11
#define icaN _ml->template fpfield<12>(_iml)
#define icaN_columnindex 12
#define icaL _ml->template fpfield<13>(_iml)
#define icaL_columnindex 13
#define ikca _ml->template fpfield<14>(_iml)
#define ikca_columnindex 14
#define m_inf _ml->template fpfield<15>(_iml)
#define m_inf_columnindex 15
#define mc_inf _ml->template fpfield<16>(_iml)
#define mc_inf_columnindex 16
#define h_inf _ml->template fpfield<17>(_iml)
#define h_inf_columnindex 17
#define hc_inf _ml->template fpfield<18>(_iml)
#define hc_inf_columnindex 18
#define n_inf _ml->template fpfield<19>(_iml)
#define n_inf_columnindex 19
#define p_inf _ml->template fpfield<20>(_iml)
#define p_inf_columnindex 20
#define tau_m _ml->template fpfield<21>(_iml)
#define tau_m_columnindex 21
#define tau_h _ml->template fpfield<22>(_iml)
#define tau_h_columnindex 22
#define tau_p _ml->template fpfield<23>(_iml)
#define tau_p_columnindex 23
#define tau_n _ml->template fpfield<24>(_iml)
#define tau_n_columnindex 24
#define tau_mc _ml->template fpfield<25>(_iml)
#define tau_mc_columnindex 25
#define tau_hc _ml->template fpfield<26>(_iml)
#define tau_hc_columnindex 26
#define p _ml->template fpfield<27>(_iml)
#define p_columnindex 27
#define m _ml->template fpfield<28>(_iml)
#define m_columnindex 28
#define h _ml->template fpfield<29>(_iml)
#define h_columnindex 29
#define n _ml->template fpfield<30>(_iml)
#define n_columnindex 30
#define cai _ml->template fpfield<31>(_iml)
#define cai_columnindex 31
#define mc _ml->template fpfield<32>(_iml)
#define mc_columnindex 32
#define hc _ml->template fpfield<33>(_iml)
#define hc_columnindex 33
#define Dp _ml->template fpfield<34>(_iml)
#define Dp_columnindex 34
#define Dm _ml->template fpfield<35>(_iml)
#define Dm_columnindex 35
#define Dh _ml->template fpfield<36>(_iml)
#define Dh_columnindex 36
#define Dn _ml->template fpfield<37>(_iml)
#define Dn_columnindex 37
#define Dcai _ml->template fpfield<38>(_iml)
#define Dcai_columnindex 38
#define Dmc _ml->template fpfield<39>(_iml)
#define Dmc_columnindex 39
#define Dhc _ml->template fpfield<40>(_iml)
#define Dhc_columnindex 40
#define Eca _ml->template fpfield<41>(_iml)
#define Eca_columnindex 41
#define v _ml->template fpfield<42>(_iml)
#define v_columnindex 42
#define _g _ml->template fpfield<43>(_iml)
#define _g_columnindex 43
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_Exp(void);
 static void _hoc_alpham(void);
 static void _hoc_betam(void);
 static void _hoc_evaluate_fct(void);
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
 {"setdata_motoneuron_5ht", _hoc_setdata},
 {"Exp_motoneuron_5ht", _hoc_Exp},
 {"alpham_motoneuron_5ht", _hoc_alpham},
 {"betam_motoneuron_5ht", _hoc_betam},
 {"evaluate_fct_motoneuron_5ht", _hoc_evaluate_fct},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_Exp(Prop*);
 static double _npy_alpham(Prop*);
 static double _npy_betam(Prop*);
 static double _npy_evaluate_fct(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"Exp", _npy_Exp},
 {"alpham", _npy_alpham},
 {"betam", _npy_betam},
 {"evaluate_fct", _npy_evaluate_fct},
 {0, 0}
};
#define Exp Exp_motoneuron_5ht
#define alpham alpham_motoneuron_5ht
#define betam betam_motoneuron_5ht
 extern double Exp( _internalthreadargsprotocomma_ double );
 extern double alpham( _internalthreadargsprotocomma_ double );
 extern double betam( _internalthreadargsprotocomma_ double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define F F_motoneuron_5ht
 double F = 96485.3;
#define R R_motoneuron_5ht
 double R = 8.31447;
#define amC amC_motoneuron_5ht
 double amC = 5;
#define amB amB_motoneuron_5ht
 double amB = 66;
#define amA amA_motoneuron_5ht
 double amA = 0.4;
#define bmC bmC_motoneuron_5ht
 double bmC = 5;
#define bmB bmB_motoneuron_5ht
 double bmB = 32;
#define bmA bmA_motoneuron_5ht
 double bmA = 0.4;
#define ca0 ca0_motoneuron_5ht
 double ca0 = 2;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gnabar_motoneuron_5ht", "mho/cm2"},
 {"gl_motoneuron_5ht", "mho/cm2"},
 {"gkrect_motoneuron_5ht", "mho/cm2"},
 {"gcaN_motoneuron_5ht", "mho/cm2"},
 {"gcaL_motoneuron_5ht", "mho/cm2"},
 {"gcak_motoneuron_5ht", "mho/cm2"},
 {"ena_motoneuron_5ht", "mV"},
 {"ek_motoneuron_5ht", "mV"},
 {"el_motoneuron_5ht", "mV"},
 {"ina_motoneuron_5ht", "mA/cm2"},
 {"il_motoneuron_5ht", "mA/cm2"},
 {"ikrect_motoneuron_5ht", "mA/cm2"},
 {"icaN_motoneuron_5ht", "mA/cm2"},
 {"icaL_motoneuron_5ht", "mA/cm2"},
 {"ikca_motoneuron_5ht", "mA/cm2"},
 {0, 0}
};
 static double cai0 = 0;
 static double delta_t = 0.01;
 static double hc0 = 0;
 static double h0 = 0;
 static double mc0 = 0;
 static double m0 = 0;
 static double n0 = 0;
 static double p0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"ca0_motoneuron_5ht", &ca0_motoneuron_5ht},
 {"amA_motoneuron_5ht", &amA_motoneuron_5ht},
 {"amB_motoneuron_5ht", &amB_motoneuron_5ht},
 {"amC_motoneuron_5ht", &amC_motoneuron_5ht},
 {"bmA_motoneuron_5ht", &bmA_motoneuron_5ht},
 {"bmB_motoneuron_5ht", &bmB_motoneuron_5ht},
 {"bmC_motoneuron_5ht", &bmC_motoneuron_5ht},
 {"R_motoneuron_5ht", &R_motoneuron_5ht},
 {"F_motoneuron_5ht", &F_motoneuron_5ht},
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
"motoneuron_5ht",
 "gnabar_motoneuron_5ht",
 "gl_motoneuron_5ht",
 "gkrect_motoneuron_5ht",
 "gcaN_motoneuron_5ht",
 "gcaL_motoneuron_5ht",
 "gcak_motoneuron_5ht",
 "ena_motoneuron_5ht",
 "ek_motoneuron_5ht",
 "el_motoneuron_5ht",
 0,
 "ina_motoneuron_5ht",
 "il_motoneuron_5ht",
 "ikrect_motoneuron_5ht",
 "icaN_motoneuron_5ht",
 "icaL_motoneuron_5ht",
 "ikca_motoneuron_5ht",
 "m_inf_motoneuron_5ht",
 "mc_inf_motoneuron_5ht",
 "h_inf_motoneuron_5ht",
 "hc_inf_motoneuron_5ht",
 "n_inf_motoneuron_5ht",
 "p_inf_motoneuron_5ht",
 "tau_m_motoneuron_5ht",
 "tau_h_motoneuron_5ht",
 "tau_p_motoneuron_5ht",
 "tau_n_motoneuron_5ht",
 "tau_mc_motoneuron_5ht",
 "tau_hc_motoneuron_5ht",
 0,
 "p_motoneuron_5ht",
 "m_motoneuron_5ht",
 "h_motoneuron_5ht",
 "n_motoneuron_5ht",
 "cai_motoneuron_5ht",
 "mc_motoneuron_5ht",
 "hc_motoneuron_5ht",
 0,
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0.05, /* gnabar */
     0.002, /* gl */
     0.3, /* gkrect */
     0.05, /* gcaN */
     0.0001, /* gcaL */
     0.3, /* gcak */
     50, /* ena */
     -80, /* ek */
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
    assert(_nrn_mechanism_get_num_vars(_prop) == 44);
 	/*initialize range parameters*/
 	gnabar = _parm_default[0]; /* 0.05 */
 	gl = _parm_default[1]; /* 0.002 */
 	gkrect = _parm_default[2]; /* 0.3 */
 	gcaN = _parm_default[3]; /* 0.05 */
 	gcaL = _parm_default[4]; /* 0.0001 */
 	gcak = _parm_default[5]; /* 0.3 */
 	ena = _parm_default[6]; /* 50 */
 	ek = _parm_default[7]; /* -80 */
 	el = _parm_default[8]; /* -70 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 44);
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

 extern "C" void _MOTONEURON_5HT_reg() {
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
                                       _nrn_mechanism_field<double>{"gnabar"} /* 0 */,
                                       _nrn_mechanism_field<double>{"gl"} /* 1 */,
                                       _nrn_mechanism_field<double>{"gkrect"} /* 2 */,
                                       _nrn_mechanism_field<double>{"gcaN"} /* 3 */,
                                       _nrn_mechanism_field<double>{"gcaL"} /* 4 */,
                                       _nrn_mechanism_field<double>{"gcak"} /* 5 */,
                                       _nrn_mechanism_field<double>{"ena"} /* 6 */,
                                       _nrn_mechanism_field<double>{"ek"} /* 7 */,
                                       _nrn_mechanism_field<double>{"el"} /* 8 */,
                                       _nrn_mechanism_field<double>{"ina"} /* 9 */,
                                       _nrn_mechanism_field<double>{"il"} /* 10 */,
                                       _nrn_mechanism_field<double>{"ikrect"} /* 11 */,
                                       _nrn_mechanism_field<double>{"icaN"} /* 12 */,
                                       _nrn_mechanism_field<double>{"icaL"} /* 13 */,
                                       _nrn_mechanism_field<double>{"ikca"} /* 14 */,
                                       _nrn_mechanism_field<double>{"m_inf"} /* 15 */,
                                       _nrn_mechanism_field<double>{"mc_inf"} /* 16 */,
                                       _nrn_mechanism_field<double>{"h_inf"} /* 17 */,
                                       _nrn_mechanism_field<double>{"hc_inf"} /* 18 */,
                                       _nrn_mechanism_field<double>{"n_inf"} /* 19 */,
                                       _nrn_mechanism_field<double>{"p_inf"} /* 20 */,
                                       _nrn_mechanism_field<double>{"tau_m"} /* 21 */,
                                       _nrn_mechanism_field<double>{"tau_h"} /* 22 */,
                                       _nrn_mechanism_field<double>{"tau_p"} /* 23 */,
                                       _nrn_mechanism_field<double>{"tau_n"} /* 24 */,
                                       _nrn_mechanism_field<double>{"tau_mc"} /* 25 */,
                                       _nrn_mechanism_field<double>{"tau_hc"} /* 26 */,
                                       _nrn_mechanism_field<double>{"p"} /* 27 */,
                                       _nrn_mechanism_field<double>{"m"} /* 28 */,
                                       _nrn_mechanism_field<double>{"h"} /* 29 */,
                                       _nrn_mechanism_field<double>{"n"} /* 30 */,
                                       _nrn_mechanism_field<double>{"cai"} /* 31 */,
                                       _nrn_mechanism_field<double>{"mc"} /* 32 */,
                                       _nrn_mechanism_field<double>{"hc"} /* 33 */,
                                       _nrn_mechanism_field<double>{"Dp"} /* 34 */,
                                       _nrn_mechanism_field<double>{"Dm"} /* 35 */,
                                       _nrn_mechanism_field<double>{"Dh"} /* 36 */,
                                       _nrn_mechanism_field<double>{"Dn"} /* 37 */,
                                       _nrn_mechanism_field<double>{"Dcai"} /* 38 */,
                                       _nrn_mechanism_field<double>{"Dmc"} /* 39 */,
                                       _nrn_mechanism_field<double>{"Dhc"} /* 40 */,
                                       _nrn_mechanism_field<double>{"Eca"} /* 41 */,
                                       _nrn_mechanism_field<double>{"v"} /* 42 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 43 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 0 */);
  hoc_register_prop_size(_mechtype, 44, 1);
  hoc_register_dparam_semantics(_mechtype, 0, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 motoneuron_5ht /Users/ann/memCPG/CPG_STDP/py/mod_files/MOTONEURON_5HT.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "Motor Axon Soma";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int evaluate_fct(_internalthreadargsprotocomma_ double);
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 static neuron::container::field_index _slist1[7], _dlist1[7];
 static int states(_internalthreadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (_internalthreadargsproto_) {int _reset = 0; {
   evaluate_fct ( _threadargscomma_ v ) ;
   Dm = ( m_inf - m ) / tau_m ;
   Dh = ( h_inf - h ) / tau_h ;
   Dp = ( p_inf - p ) / tau_p ;
   Dn = ( n_inf - n ) / tau_n ;
   Dmc = ( mc_inf - mc ) / tau_mc ;
   Dhc = ( hc_inf - hc ) / tau_hc ;
   Dcai = 0.01 * ( - ( icaN + icaL ) - 4.0 * cai ) ;
   }
 return _reset;
}
 static int _ode_matsol1 (_internalthreadargsproto_) {
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
 static int states (_internalthreadargsproto_) { {
   evaluate_fct ( _threadargscomma_ v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_m)))*(- ( ( ( m_inf ) ) / tau_m ) / ( ( ( ( - 1.0 ) ) ) / tau_m ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_h)))*(- ( ( ( h_inf ) ) / tau_h ) / ( ( ( ( - 1.0 ) ) ) / tau_h ) - h) ;
    p = p + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_p)))*(- ( ( ( p_inf ) ) / tau_p ) / ( ( ( ( - 1.0 ) ) ) / tau_p ) - p) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_n)))*(- ( ( ( n_inf ) ) / tau_n ) / ( ( ( ( - 1.0 ) ) ) / tau_n ) - n) ;
    mc = mc + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_mc)))*(- ( ( ( mc_inf ) ) / tau_mc ) / ( ( ( ( - 1.0 ) ) ) / tau_mc ) - mc) ;
    hc = hc + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_hc)))*(- ( ( ( hc_inf ) ) / tau_hc ) / ( ( ( ( - 1.0 ) ) ) / tau_hc ) - hc) ;
    cai = cai + (1. - exp(dt*(( 0.01 )*( ( ( - ( 4.0 )*( 1.0 ) ) ) ))))*(- ( ( 0.01 )*( ( - ( icaN + icaL ) ) ) ) / ( ( 0.01 )*( ( ( - ( 4.0 )*( 1.0 ) ) ) ) ) - cai) ;
   }
  return 0;
}
 
static int  evaluate_fct ( _internalthreadargsprotocomma_ double _lv ) {
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
 Datum* _ppvar; Datum* _thread; NrnThread* _nt;
 
  if(!_prop_id) {
    hoc_execerror("No data for evaluate_fct_motoneuron_5ht. Requires prior call to setdata_motoneuron_5ht and that the specified mechanism instance still be in existence.", NULL);
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
 
double alpham ( _internalthreadargsprotocomma_ double _lx ) {
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
 _r =  alpham ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_alpham(Prop* _prop) {
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
 _r =  alpham ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double betam ( _internalthreadargsprotocomma_ double _lx ) {
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
 _r =  betam ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_betam(Prop* _prop) {
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
 _r =  betam ( _threadargscomma_ *getarg(1) );
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
 
static int _ode_count(int _type){ return 7;}
 
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
  for (int _i=0; _i < 7; ++_i) {
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
   ina = gnabar * m * m * m * h * ( v - ena ) ;
   ikrect = gkrect * n * n * n * n * ( v - ek ) ;
   il = gl * ( v - el ) ;
   Eca = ( ( 1000.0 * R * 309.15 ) / ( 2.0 * F ) ) * log ( ca0 / cai ) ;
   icaN = gcaN * mc * mc * hc * ( v - Eca ) ;
   icaL = gcaL * p * ( v - Eca ) ;
   ikca = 0.6 * gcak * ( cai * cai ) / ( cai * cai + 0.014 * 0.014 ) * ( v - ek ) ;
   }
 _current += ina;
 _current += ikrect;
 _current += ikca;
 _current += il;
 _current += icaN;
 _current += icaL;

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
 _slist1[0] = {m_columnindex, 0};  _dlist1[0] = {Dm_columnindex, 0};
 _slist1[1] = {h_columnindex, 0};  _dlist1[1] = {Dh_columnindex, 0};
 _slist1[2] = {p_columnindex, 0};  _dlist1[2] = {Dp_columnindex, 0};
 _slist1[3] = {n_columnindex, 0};  _dlist1[3] = {Dn_columnindex, 0};
 _slist1[4] = {mc_columnindex, 0};  _dlist1[4] = {Dmc_columnindex, 0};
 _slist1[5] = {hc_columnindex, 0};  _dlist1[5] = {Dhc_columnindex, 0};
 _slist1[6] = {cai_columnindex, 0};  _dlist1[6] = {Dcai_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/MOTONEURON_5HT.mod";
    const char* nmodl_file_text = 
  ":SOMA\n"
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
  "	SUFFIX motoneuron_5ht\n"
  "	NONSPECIFIC_CURRENT ina\n"
  "	NONSPECIFIC_CURRENT ikrect\n"
  "	NONSPECIFIC_CURRENT ikca\n"
  "	NONSPECIFIC_CURRENT il\n"
  "	NONSPECIFIC_CURRENT icaN\n"
  "	NONSPECIFIC_CURRENT icaL\n"
  "	RANGE  gnabar, gl, ena, ek, el, gkrect, gcaN, gcaL, gcak\n"
  "	RANGE p_inf, m_inf, h_inf, n_inf, mc_inf, hc_inf\n"
  "	RANGE tau_p, tau_m, tau_h, tau_n, tau_mc, tau_hc\n"
  "}\n"
  "\n"
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
  "	ca0 = 2  \n"
  "	ena     = 50.0  (mV)\n"
  "	ek      = -80.0 (mV)\n"
  "	el	= -70.0 (mV)\n"
  "	dt              (ms)\n"
  "	v               (mV)\n"
  "	amA = 0.4\n"
  "	amB = 66\n"
  "	amC = 5\n"
  "	bmA = 0.4\n"
  "	bmB = 32\n"
  "	bmC = 5\n"
  "	R=8.314472\n"
  "	F=96485.34\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	 p m h n cai mc hc\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ina	 (mA/cm2)\n"
  "	il      (mA/cm2)\n"
  "	ikrect    (mA/cm2)\n"
  "	icaN  (mA/cm2)\n"
  "	icaL  (mA/cm2)\n"
  "	ikca  (mA/cm2)\n"
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
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	ina = gnabar * m*m*m*h*(v - ena)\n"
  "	ikrect   = gkrect *n*n*n*n*(v - ek)   :stesso ek di sotto\n"
  "	il   = gl * (v - el)\n"
  "	Eca = ((1000*R*309.15)/(2*F))*log(ca0/cai)\n"
  "	icaN = gcaN*mc*mc*hc*(v-Eca)\n"
  "	icaL = gcaL*p*(v-Eca)\n"
  "	ikca = 0.6*gcak*(cai*cai)/(cai*cai+0.014*0.014)*(v-ek)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {  \n"
  "	 : exact Hodgkin-Huxley equations\n"
  "        evaluate_fct(v)\n"
  "	m' = (m_inf - m) / tau_m\n"
  "	h' = (h_inf - h) / tau_h\n"
  "	p' = (p_inf - p) / tau_p\n"
  "	n' = (n_inf - n) / tau_n\n"
  "	mc' = (mc_inf - mc) / tau_mc\n"
  "	hc' = (hc_inf - hc) / tau_hc\n"
  "	cai'= 0.01*(-(icaN+icaL) - 4*cai)\n"
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
  "	mc=mc_inf\n"
  "	hc=hc_inf\n"
  "	cai = 0.0001\n"
  "}\n"
  "\n"
  "PROCEDURE evaluate_fct(v(mV)) { LOCAL a,b,v2\n"
  "	  \n"
  "	 \n"
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
  "	\n"
  "	:DELAYED RECTIFIER POTASSIUM \n"
  "	tau_n = 5 / (Exp((v+50)/40) + Exp(-(v+50)/50))\n"
  "	n_inf = 1 / (1 + Exp(-(v+38)/15))\n"
  "\n"
  "	:CALCIUM DYNAMICS\n"
  "        :N-type\n"
  "	tau_mc = 15\n"
  "	mc_inf = 1/(1+Exp(-(v+32)/5))\n"
  "	tau_hc = 50\n"
  "	hc_inf =  1/(1+Exp((v+50)/5))\n"
  "	\n"
  "	:L-type\n"
  "	tau_p=400\n"
  "	p_inf=1/(1+Exp(-(v+55.8)/3.7))\n"
  "\n"
  "}\n"
  "\n"
  "\n"
  "FUNCTION alpham(x) {\n"
  "	if (fabs((x+amB)/amC) < 1e-6) {\n"
  "		alpham = amA*amC\n"
  "	}else{\n"
  "		alpham = (amA*(x+amB)) / (1 - Exp(-(x+amB)/amC))\n"
  "	}\n"
  "}\n"
  "\n"
  "\n"
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
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
