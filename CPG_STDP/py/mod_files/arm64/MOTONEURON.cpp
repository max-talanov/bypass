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
static constexpr auto number_of_datum_variables = 8;
static constexpr auto number_of_floating_point_variables = 43;
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
 
#define nrn_init _nrn_init__motoneuron
#define _nrn_initial _nrn_initial__motoneuron
#define nrn_cur _nrn_cur__motoneuron
#define _nrn_current _nrn_current__motoneuron
#define nrn_jacob _nrn_jacob__motoneuron
#define nrn_state _nrn_state__motoneuron
#define _net_receive _net_receive__motoneuron 
#define evaluate_fct evaluate_fct__motoneuron 
#define states states__motoneuron 
 
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
#define il _ml->template fpfield<9>(_iml)
#define il_columnindex 9
#define m_inf _ml->template fpfield<10>(_iml)
#define m_inf_columnindex 10
#define mc_inf _ml->template fpfield<11>(_iml)
#define mc_inf_columnindex 11
#define h_inf _ml->template fpfield<12>(_iml)
#define h_inf_columnindex 12
#define hc_inf _ml->template fpfield<13>(_iml)
#define hc_inf_columnindex 13
#define n_inf _ml->template fpfield<14>(_iml)
#define n_inf_columnindex 14
#define p_inf _ml->template fpfield<15>(_iml)
#define p_inf_columnindex 15
#define tau_m _ml->template fpfield<16>(_iml)
#define tau_m_columnindex 16
#define tau_h _ml->template fpfield<17>(_iml)
#define tau_h_columnindex 17
#define tau_p _ml->template fpfield<18>(_iml)
#define tau_p_columnindex 18
#define tau_n _ml->template fpfield<19>(_iml)
#define tau_n_columnindex 19
#define tau_mc _ml->template fpfield<20>(_iml)
#define tau_mc_columnindex 20
#define tau_hc _ml->template fpfield<21>(_iml)
#define tau_hc_columnindex 21
#define p _ml->template fpfield<22>(_iml)
#define p_columnindex 22
#define m _ml->template fpfield<23>(_iml)
#define m_columnindex 23
#define h _ml->template fpfield<24>(_iml)
#define h_columnindex 24
#define n _ml->template fpfield<25>(_iml)
#define n_columnindex 25
#define cai _ml->template fpfield<26>(_iml)
#define cai_columnindex 26
#define mc _ml->template fpfield<27>(_iml)
#define mc_columnindex 27
#define hc _ml->template fpfield<28>(_iml)
#define hc_columnindex 28
#define Dp _ml->template fpfield<29>(_iml)
#define Dp_columnindex 29
#define Dm _ml->template fpfield<30>(_iml)
#define Dm_columnindex 30
#define Dh _ml->template fpfield<31>(_iml)
#define Dh_columnindex 31
#define Dn _ml->template fpfield<32>(_iml)
#define Dn_columnindex 32
#define Dcai _ml->template fpfield<33>(_iml)
#define Dcai_columnindex 33
#define Dmc _ml->template fpfield<34>(_iml)
#define Dmc_columnindex 34
#define Dhc _ml->template fpfield<35>(_iml)
#define Dhc_columnindex 35
#define ina _ml->template fpfield<36>(_iml)
#define ina_columnindex 36
#define ica _ml->template fpfield<37>(_iml)
#define ica_columnindex 37
#define ik _ml->template fpfield<38>(_iml)
#define ik_columnindex 38
#define Eca _ml->template fpfield<39>(_iml)
#define Eca_columnindex 39
#define cao _ml->template fpfield<40>(_iml)
#define cao_columnindex 40
#define v _ml->template fpfield<41>(_iml)
#define v_columnindex 41
#define _g _ml->template fpfield<42>(_iml)
#define _g_columnindex 42
#define _ion_ina *(_ml->dptr_field<0>(_iml))
#define _p_ion_ina static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_dinadv *(_ml->dptr_field<1>(_iml))
#define _ion_ik *(_ml->dptr_field<2>(_iml))
#define _p_ion_ik static_cast<neuron::container::data_handle<double>>(_ppvar[2])
#define _ion_dikdv *(_ml->dptr_field<3>(_iml))
#define _ion_cao *(_ml->dptr_field<4>(_iml))
#define _p_ion_cao static_cast<neuron::container::data_handle<double>>(_ppvar[4])
#define _ion_cai *(_ml->dptr_field<5>(_iml))
#define _p_ion_cai static_cast<neuron::container::data_handle<double>>(_ppvar[5])
#define _ion_ica *(_ml->dptr_field<6>(_iml))
#define _p_ion_ica static_cast<neuron::container::data_handle<double>>(_ppvar[6])
#define _ion_dicadv *(_ml->dptr_field<7>(_iml))
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
 {"setdata_motoneuron", _hoc_setdata},
 {"Exp_motoneuron", _hoc_Exp},
 {"alpham_motoneuron", _hoc_alpham},
 {"betam_motoneuron", _hoc_betam},
 {"evaluate_fct_motoneuron", _hoc_evaluate_fct},
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
#define Exp Exp_motoneuron
#define alpham alpham_motoneuron
#define betam betam_motoneuron
 extern double Exp( _internalthreadargsprotocomma_ double );
 extern double alpham( _internalthreadargsprotocomma_ double );
 extern double betam( _internalthreadargsprotocomma_ double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
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
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gnabar_motoneuron", "mho/cm2"},
 {"gl_motoneuron", "mho/cm2"},
 {"gkrect_motoneuron", "mho/cm2"},
 {"gcaN_motoneuron", "mho/cm2"},
 {"gcaL_motoneuron", "mho/cm2"},
 {"gcak_motoneuron", "mho/cm2"},
 {"ena_motoneuron", "mV"},
 {"ek_motoneuron", "mV"},
 {"el_motoneuron", "mV"},
 {"il_motoneuron", "mA/cm2"},
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
 {"ca0_motoneuron", &ca0_motoneuron},
 {"amA_motoneuron", &amA_motoneuron},
 {"amB_motoneuron", &amB_motoneuron},
 {"amC_motoneuron", &amC_motoneuron},
 {"bmA_motoneuron", &bmA_motoneuron},
 {"bmB_motoneuron", &bmB_motoneuron},
 {"bmC_motoneuron", &bmC_motoneuron},
 {"R_motoneuron", &R_motoneuron},
 {"F_motoneuron", &F_motoneuron},
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
 
#define _cvode_ieq _ppvar[8].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
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
   _ppvar = nrn_prop_datum_alloc(_mechtype, 9, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 43);
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
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 43);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ina */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ik */
 	_ppvar[3] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dikdv */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[4] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* cao */
 	_ppvar[5] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* cai */
 	_ppvar[6] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ica */
 	_ppvar[7] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dicadv */
 
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

 extern "C" void _MOTONEURON_reg() {
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
                                       _nrn_mechanism_field<double>{"il"} /* 9 */,
                                       _nrn_mechanism_field<double>{"m_inf"} /* 10 */,
                                       _nrn_mechanism_field<double>{"mc_inf"} /* 11 */,
                                       _nrn_mechanism_field<double>{"h_inf"} /* 12 */,
                                       _nrn_mechanism_field<double>{"hc_inf"} /* 13 */,
                                       _nrn_mechanism_field<double>{"n_inf"} /* 14 */,
                                       _nrn_mechanism_field<double>{"p_inf"} /* 15 */,
                                       _nrn_mechanism_field<double>{"tau_m"} /* 16 */,
                                       _nrn_mechanism_field<double>{"tau_h"} /* 17 */,
                                       _nrn_mechanism_field<double>{"tau_p"} /* 18 */,
                                       _nrn_mechanism_field<double>{"tau_n"} /* 19 */,
                                       _nrn_mechanism_field<double>{"tau_mc"} /* 20 */,
                                       _nrn_mechanism_field<double>{"tau_hc"} /* 21 */,
                                       _nrn_mechanism_field<double>{"p"} /* 22 */,
                                       _nrn_mechanism_field<double>{"m"} /* 23 */,
                                       _nrn_mechanism_field<double>{"h"} /* 24 */,
                                       _nrn_mechanism_field<double>{"n"} /* 25 */,
                                       _nrn_mechanism_field<double>{"cai"} /* 26 */,
                                       _nrn_mechanism_field<double>{"mc"} /* 27 */,
                                       _nrn_mechanism_field<double>{"hc"} /* 28 */,
                                       _nrn_mechanism_field<double>{"Dp"} /* 29 */,
                                       _nrn_mechanism_field<double>{"Dm"} /* 30 */,
                                       _nrn_mechanism_field<double>{"Dh"} /* 31 */,
                                       _nrn_mechanism_field<double>{"Dn"} /* 32 */,
                                       _nrn_mechanism_field<double>{"Dcai"} /* 33 */,
                                       _nrn_mechanism_field<double>{"Dmc"} /* 34 */,
                                       _nrn_mechanism_field<double>{"Dhc"} /* 35 */,
                                       _nrn_mechanism_field<double>{"ina"} /* 36 */,
                                       _nrn_mechanism_field<double>{"ica"} /* 37 */,
                                       _nrn_mechanism_field<double>{"ik"} /* 38 */,
                                       _nrn_mechanism_field<double>{"Eca"} /* 39 */,
                                       _nrn_mechanism_field<double>{"cao"} /* 40 */,
                                       _nrn_mechanism_field<double>{"v"} /* 41 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 42 */,
                                       _nrn_mechanism_field<double*>{"_ion_ina", "na_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_dinadv", "na_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_ik", "k_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_dikdv", "k_ion"} /* 3 */,
                                       _nrn_mechanism_field<double*>{"_ion_cao", "ca_ion"} /* 4 */,
                                       _nrn_mechanism_field<double*>{"_ion_cai", "ca_ion"} /* 5 */,
                                       _nrn_mechanism_field<double*>{"_ion_ica", "ca_ion"} /* 6 */,
                                       _nrn_mechanism_field<double*>{"_ion_dicadv", "ca_ion"} /* 7 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 8 */);
  hoc_register_prop_size(_mechtype, 43, 9);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 6, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 7, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 8, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 motoneuron /Users/ann/memCPG/CPG_STDP/py/mod_files/MOTONEURON.mod\n");
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
   Dcai = 0.01 * ( - ( ica ) - 4.0 * cai ) ;
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
    cai = cai + (1. - exp(dt*(( 0.01 )*( ( ( - ( 4.0 )*( 1.0 ) ) ) ))))*(- ( ( 0.01 )*( ( - ( ica ) ) ) ) / ( ( 0.01 )*( ( ( - ( 4.0 )*( 1.0 ) ) ) ) ) - cai) ;
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
    hoc_execerror("No data for evaluate_fct_motoneuron. Requires prior call to setdata_motoneuron and that the specified mechanism instance still be in existence.", NULL);
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
  cao = _ion_cao;
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
  cao = _ion_cao;
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
  cao = _ion_cao;
 initmodel(_threadargs_);
   }
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
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
  cao = _ion_cao;
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ double _dica;
 double _dik;
 double _dina;
  _dina = ina;
  _dik = ik;
  _dica = ica;
 _rhs = _nrn_current(_threadargscomma_ _v);
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g_local - _rhs)/.001;
  _ion_ina += ina ;
  _ion_ik += ik ;
  _ion_ica += ica ;
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
  cao = _ion_cao;
 {   states(_threadargs_);
  }   }}

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
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/MOTONEURON.mod";
    const char* nmodl_file_text = 
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
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
