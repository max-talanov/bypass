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
static constexpr auto number_of_datum_variables = 3;
static constexpr auto number_of_floating_point_variables = 31;
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
 
#define nrn_init _nrn_init__na14a
#define _nrn_initial _nrn_initial__na14a
#define nrn_cur _nrn_cur__na14a
#define _nrn_current _nrn_current__na14a
#define nrn_jacob _nrn_jacob__na14a
#define nrn_state _nrn_state__na14a
#define _net_receive _net_receive__na14a 
#define kin kin__na14a 
#define rates rates__na14a 
 
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
#define gbar _ml->template fpfield<0>(_iml)
#define gbar_columnindex 0
#define ina _ml->template fpfield<1>(_iml)
#define ina_columnindex 1
#define g _ml->template fpfield<2>(_iml)
#define g_columnindex 2
#define C1 _ml->template fpfield<3>(_iml)
#define C1_columnindex 3
#define C2 _ml->template fpfield<4>(_iml)
#define C2_columnindex 4
#define O1 _ml->template fpfield<5>(_iml)
#define O1_columnindex 5
#define O2 _ml->template fpfield<6>(_iml)
#define O2_columnindex 6
#define I1 _ml->template fpfield<7>(_iml)
#define I1_columnindex 7
#define I2 _ml->template fpfield<8>(_iml)
#define I2_columnindex 8
#define ena _ml->template fpfield<9>(_iml)
#define ena_columnindex 9
#define C1C2_a _ml->template fpfield<10>(_iml)
#define C1C2_a_columnindex 10
#define C2C1_a _ml->template fpfield<11>(_iml)
#define C2C1_a_columnindex 11
#define C2O1_a _ml->template fpfield<12>(_iml)
#define C2O1_a_columnindex 12
#define O1C2_a _ml->template fpfield<13>(_iml)
#define O1C2_a_columnindex 13
#define C2O2_a _ml->template fpfield<14>(_iml)
#define C2O2_a_columnindex 14
#define O2C2_a _ml->template fpfield<15>(_iml)
#define O2C2_a_columnindex 15
#define O1I1_a _ml->template fpfield<16>(_iml)
#define O1I1_a_columnindex 16
#define I1O1_a _ml->template fpfield<17>(_iml)
#define I1O1_a_columnindex 17
#define I1I2_a _ml->template fpfield<18>(_iml)
#define I1I2_a_columnindex 18
#define I2I1_a _ml->template fpfield<19>(_iml)
#define I2I1_a_columnindex 19
#define I1C1_a _ml->template fpfield<20>(_iml)
#define I1C1_a_columnindex 20
#define C1I1_a _ml->template fpfield<21>(_iml)
#define C1I1_a_columnindex 21
#define Q10 _ml->template fpfield<22>(_iml)
#define Q10_columnindex 22
#define DC1 _ml->template fpfield<23>(_iml)
#define DC1_columnindex 23
#define DC2 _ml->template fpfield<24>(_iml)
#define DC2_columnindex 24
#define DO1 _ml->template fpfield<25>(_iml)
#define DO1_columnindex 25
#define DO2 _ml->template fpfield<26>(_iml)
#define DO2_columnindex 26
#define DI1 _ml->template fpfield<27>(_iml)
#define DI1_columnindex 27
#define DI2 _ml->template fpfield<28>(_iml)
#define DI2_columnindex 28
#define v _ml->template fpfield<29>(_iml)
#define v_columnindex 29
#define _g _ml->template fpfield<30>(_iml)
#define _g_columnindex 30
#define _ion_ena *(_ml->dptr_field<0>(_iml))
#define _p_ion_ena static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_ina *(_ml->dptr_field<1>(_iml))
#define _p_ion_ina static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_dinadv *(_ml->dptr_field<2>(_iml))
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_rates2(void);
 static void _hoc_rates(void);
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
 {"setdata_na14a", _hoc_setdata},
 {"rates2_na14a", _hoc_rates2},
 {"rates_na14a", _hoc_rates},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_rates2(Prop*);
 static double _npy_rates(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"rates2", _npy_rates2},
 {"rates", _npy_rates},
 {0, 0}
};
#define rates2 rates2_na14a
 extern double rates2( _internalthreadargsprotocomma_ double , double , double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define C1I1k2 C1I1k2_na14a
 double C1I1k2 = -7;
#define C1I1v2 C1I1v2_na14a
 double C1I1v2 = -70;
#define C1I1b2 C1I1b2_na14a
 double C1I1b2 = 0.8;
#define C2O2k2 C2O2k2_na14a
 double C2O2k2 = -8;
#define C2O2v2 C2O2v2_na14a
 double C2O2v2 = -20;
#define C2O2b2 C2O2b2_na14a
 double C2O2b2 = 0.03;
#define C2O1k2 C2O1k2_na14a
 double C2O1k2 = -9;
#define C2O1v2 C2O1v2_na14a
 double C2O1v2 = -8;
#define C2O1b2 C2O1b2_na14a
 double C2O1b2 = 16;
#define C2C1k2 C2C1k2_na14a
 double C2C1k2 = -9;
#define C2C1v2 C2C1v2_na14a
 double C2C1v2 = -3;
#define C2C1b2 C2C1b2_na14a
 double C2C1b2 = 16;
#define C2C1k1 C2C1k1_na14a
 double C2C1k1 = 9;
#define C2C1v1 C2C1v1_na14a
 double C2C1v1 = -33;
#define C2C1b1 C2C1b1_na14a
 double C2C1b1 = 3;
#define C1C2k2 C1C2k2_na14a
 double C1C2k2 = -9;
#define C1C2v2 C1C2v2_na14a
 double C1C2v2 = -3;
#define C1C2b2 C1C2b2_na14a
 double C1C2b2 = 16;
#define I2I1k1 I2I1k1_na14a
 double I2I1k1 = 12;
#define I2I1v1 I2I1v1_na14a
 double I2I1v1 = -70;
#define I2I1b1 I2I1b1_na14a
 double I2I1b1 = 0.007;
#define I1I2k2 I1I2k2_na14a
 double I1I2k2 = -12;
#define I1I2v2 I1I2v2_na14a
 double I1I2v2 = -70;
#define I1I2b2 I1I2b2_na14a
 double I1I2b2 = 0.0015;
#define I1C1k1 I1C1k1_na14a
 double I1C1k1 = 10;
#define I1C1v1 I1C1v1_na14a
 double I1C1v1 = -70;
#define I1C1b1 I1C1b1_na14a
 double I1C1b1 = 0.35;
#define I1O1k1 I1O1k1_na14a
 double I1O1k1 = 10;
#define I1O1v1 I1O1v1_na14a
 double I1O1v1 = -10;
#define I1O1b1 I1O1b1_na14a
 double I1O1b1 = 1e-05;
#define O1I1k2 O1I1k2_na14a
 double O1I1k2 = -10;
#define O1I1v2 O1I1v2_na14a
 double O1I1v2 = -10;
#define O1I1b2 O1I1b2_na14a
 double O1I1b2 = 16;
#define O1I1k1 O1I1k1_na14a
 double O1I1k1 = 10;
#define O1I1v1 O1I1v1_na14a
 double O1I1v1 = -10;
#define O1I1b1 O1I1b1_na14a
 double O1I1b1 = 0;
#define O2C2k2 O2C2k2_na14a
 double O2C2k2 = -8;
#define O2C2v2 O2C2v2_na14a
 double O2C2v2 = -20;
#define O2C2b2 O2C2b2_na14a
 double O2C2b2 = 0.1;
#define O2C2k1 O2C2k1_na14a
 double O2C2k1 = 8;
#define O2C2v1 O2C2v1_na14a
 double O2C2v1 = -50;
#define O2C2b1 O2C2b1_na14a
 double O2C2b1 = 3;
#define O1C2k2 O1C2k2_na14a
 double O1C2k2 = -9;
#define O1C2v2 O1C2v2_na14a
 double O1C2v2 = -8;
#define O1C2b2 O1C2b2_na14a
 double O1C2b2 = 16;
#define O1C2k1 O1C2k1_na14a
 double O1C2k1 = 9;
#define O1C2v1 O1C2v1_na14a
 double O1C2v1 = -38;
#define O1C2b1 O1C2b1_na14a
 double O1C2b1 = 1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"gbar_na14a", "mho/cm2"},
 {"ina_na14a", "mA/cm2"},
 {"g_na14a", "mho/cm2"},
 {0, 0}
};
 static double C20 = 0;
 static double C10 = 0;
 static double I20 = 0;
 static double I10 = 0;
 static double O20 = 0;
 static double O10 = 0;
 static double delta_t = 0.01;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"C1C2b2_na14a", &C1C2b2_na14a},
 {"C1C2v2_na14a", &C1C2v2_na14a},
 {"C1C2k2_na14a", &C1C2k2_na14a},
 {"C2C1b1_na14a", &C2C1b1_na14a},
 {"C2C1v1_na14a", &C2C1v1_na14a},
 {"C2C1k1_na14a", &C2C1k1_na14a},
 {"C2C1b2_na14a", &C2C1b2_na14a},
 {"C2C1v2_na14a", &C2C1v2_na14a},
 {"C2C1k2_na14a", &C2C1k2_na14a},
 {"C2O1b2_na14a", &C2O1b2_na14a},
 {"C2O1v2_na14a", &C2O1v2_na14a},
 {"C2O1k2_na14a", &C2O1k2_na14a},
 {"O1C2b1_na14a", &O1C2b1_na14a},
 {"O1C2v1_na14a", &O1C2v1_na14a},
 {"O1C2k1_na14a", &O1C2k1_na14a},
 {"O1C2b2_na14a", &O1C2b2_na14a},
 {"O1C2v2_na14a", &O1C2v2_na14a},
 {"O1C2k2_na14a", &O1C2k2_na14a},
 {"C2O2b2_na14a", &C2O2b2_na14a},
 {"C2O2v2_na14a", &C2O2v2_na14a},
 {"C2O2k2_na14a", &C2O2k2_na14a},
 {"O2C2b1_na14a", &O2C2b1_na14a},
 {"O2C2v1_na14a", &O2C2v1_na14a},
 {"O2C2k1_na14a", &O2C2k1_na14a},
 {"O2C2b2_na14a", &O2C2b2_na14a},
 {"O2C2v2_na14a", &O2C2v2_na14a},
 {"O2C2k2_na14a", &O2C2k2_na14a},
 {"O1I1b1_na14a", &O1I1b1_na14a},
 {"O1I1v1_na14a", &O1I1v1_na14a},
 {"O1I1k1_na14a", &O1I1k1_na14a},
 {"O1I1b2_na14a", &O1I1b2_na14a},
 {"O1I1v2_na14a", &O1I1v2_na14a},
 {"O1I1k2_na14a", &O1I1k2_na14a},
 {"I1O1b1_na14a", &I1O1b1_na14a},
 {"I1O1v1_na14a", &I1O1v1_na14a},
 {"I1O1k1_na14a", &I1O1k1_na14a},
 {"I1C1b1_na14a", &I1C1b1_na14a},
 {"I1C1v1_na14a", &I1C1v1_na14a},
 {"I1C1k1_na14a", &I1C1k1_na14a},
 {"C1I1b2_na14a", &C1I1b2_na14a},
 {"C1I1v2_na14a", &C1I1v2_na14a},
 {"C1I1k2_na14a", &C1I1k2_na14a},
 {"I1I2b2_na14a", &I1I2b2_na14a},
 {"I1I2v2_na14a", &I1I2v2_na14a},
 {"I1I2k2_na14a", &I1I2k2_na14a},
 {"I2I1b1_na14a", &I2I1b1_na14a},
 {"I2I1v1_na14a", &I2I1v1_na14a},
 {"I2I1k1_na14a", &I2I1k1_na14a},
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
 
#define _cvode_ieq _ppvar[3].literal_value<int>()
 static void _ode_matsol_instance1(_internalthreadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"na14a",
 "gbar_na14a",
 0,
 "ina_na14a",
 "g_na14a",
 0,
 "C1_na14a",
 "C2_na14a",
 "O1_na14a",
 "O2_na14a",
 "I1_na14a",
 "I2_na14a",
 0,
 0};
 static Symbol* _na_sym;
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0.1, /* gbar */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
   _ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 31);
 	/*initialize range parameters*/
 	gbar = _parm_default[0]; /* 0.1 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 31);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 0); /* ena */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* ina */
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dinadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 {0, 0}
};
 static void _thread_cleanup(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _nav14_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 3);
  _extcall_thread.resize(2);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
         hoc_register_npy_direct(_mechtype, npy_direct_func_proc);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"gbar"} /* 0 */,
                                       _nrn_mechanism_field<double>{"ina"} /* 1 */,
                                       _nrn_mechanism_field<double>{"g"} /* 2 */,
                                       _nrn_mechanism_field<double>{"C1"} /* 3 */,
                                       _nrn_mechanism_field<double>{"C2"} /* 4 */,
                                       _nrn_mechanism_field<double>{"O1"} /* 5 */,
                                       _nrn_mechanism_field<double>{"O2"} /* 6 */,
                                       _nrn_mechanism_field<double>{"I1"} /* 7 */,
                                       _nrn_mechanism_field<double>{"I2"} /* 8 */,
                                       _nrn_mechanism_field<double>{"ena"} /* 9 */,
                                       _nrn_mechanism_field<double>{"C1C2_a"} /* 10 */,
                                       _nrn_mechanism_field<double>{"C2C1_a"} /* 11 */,
                                       _nrn_mechanism_field<double>{"C2O1_a"} /* 12 */,
                                       _nrn_mechanism_field<double>{"O1C2_a"} /* 13 */,
                                       _nrn_mechanism_field<double>{"C2O2_a"} /* 14 */,
                                       _nrn_mechanism_field<double>{"O2C2_a"} /* 15 */,
                                       _nrn_mechanism_field<double>{"O1I1_a"} /* 16 */,
                                       _nrn_mechanism_field<double>{"I1O1_a"} /* 17 */,
                                       _nrn_mechanism_field<double>{"I1I2_a"} /* 18 */,
                                       _nrn_mechanism_field<double>{"I2I1_a"} /* 19 */,
                                       _nrn_mechanism_field<double>{"I1C1_a"} /* 20 */,
                                       _nrn_mechanism_field<double>{"C1I1_a"} /* 21 */,
                                       _nrn_mechanism_field<double>{"Q10"} /* 22 */,
                                       _nrn_mechanism_field<double>{"DC1"} /* 23 */,
                                       _nrn_mechanism_field<double>{"DC2"} /* 24 */,
                                       _nrn_mechanism_field<double>{"DO1"} /* 25 */,
                                       _nrn_mechanism_field<double>{"DO2"} /* 26 */,
                                       _nrn_mechanism_field<double>{"DI1"} /* 27 */,
                                       _nrn_mechanism_field<double>{"DI2"} /* 28 */,
                                       _nrn_mechanism_field<double>{"v"} /* 29 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 30 */,
                                       _nrn_mechanism_field<double*>{"_ion_ena", "na_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_ina", "na_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_dinadv", "na_ion"} /* 2 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 3 */);
  hoc_register_prop_size(_mechtype, 31, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 na14a /Users/ann/memCPG/CPG_STDP/py/mod_files/nav14.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "Nav1.4 ionic voltage-gated channel with kinetic scheme";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_internalthreadargsprotocomma_ double);
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(static_cast<SparseObj*>(_so), _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
 static int _cvspth1 = 1;
 
static int _ode_spec1(_internalthreadargsproto_);
/*static int _ode_matsol1(_internalthreadargsproto_);*/
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(static_cast<SparseObj*>(_so), _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 0;
 static neuron::container::field_index _slist1[6], _dlist1[6]; static double *_temp1;
 static int kin (void* _so, double* _rhs, _internalthreadargsproto_);
 
static int kin (void* _so, double* _rhs, _internalthreadargsproto_)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<6;_i++){
  	_RHS1(_i) = -_dt1*(_ml->data(_iml, _slist1[_i]) - _ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
} }
 rates ( _threadargscomma_ v ) ;
   /* ~ C1 <-> C2 ( C1C2_a , C2C1_a )*/
 f_flux =  C1C2_a * C1 ;
 b_flux =  C2C1_a * C2 ;
 _RHS1( 2) -= (f_flux - b_flux);
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  C1C2_a ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  C2C1_a ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ C2 <-> O1 ( C2O1_a , O1C2_a )*/
 f_flux =  C2O1_a * C2 ;
 b_flux =  O1C2_a * O1 ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 5) += (f_flux - b_flux);
 
 _term =  C2O1_a ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 5 ,1)  -= _term;
 _term =  O1C2_a ;
 _MATELM1( 1 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ C2 <-> O2 ( C2O2_a , O2C2_a )*/
 f_flux =  C2O2_a * C2 ;
 b_flux =  O2C2_a * O2 ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 4) += (f_flux - b_flux);
 
 _term =  C2O2_a ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 4 ,1)  -= _term;
 _term =  O2C2_a ;
 _MATELM1( 1 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ O1 <-> I1 ( O1I1_a , I1O1_a )*/
 f_flux =  O1I1_a * O1 ;
 b_flux =  I1O1_a * I1 ;
 _RHS1( 5) -= (f_flux - b_flux);
 _RHS1( 3) += (f_flux - b_flux);
 
 _term =  O1I1_a ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 3 ,5)  -= _term;
 _term =  I1O1_a ;
 _MATELM1( 5 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ I1 <-> C1 ( I1C1_a , C1I1_a )*/
 f_flux =  I1C1_a * I1 ;
 b_flux =  C1I1_a * C1 ;
 _RHS1( 3) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  I1C1_a ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  C1I1_a ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ I1 <-> I2 ( I1I2_a , I2I1_a )*/
 f_flux =  I1I2_a * I1 ;
 b_flux =  I2I1_a * I2 ;
 _RHS1( 3) -= (f_flux - b_flux);
 
 _term =  I1I2_a ;
 _MATELM1( 3 ,3)  += _term;
 _term =  I2I1_a ;
 _MATELM1( 3 ,0)  -= _term;
 /*REACTION*/
   /* O1 + O2 + C1 + C2 + I1 + I2 = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= I2 ;
 _MATELM1(0, 3) = 1;
 _RHS1(0) -= I1 ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= C2 ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= C1 ;
 _MATELM1(0, 4) = 1;
 _RHS1(0) -= O2 ;
 _MATELM1(0, 5) = 1;
 _RHS1(0) -= O1 ;
 /*CONSERVATION*/
   } return _reset;
 }
 
double rates2 ( _internalthreadargsprotocomma_ double _lv , double _lb , double _lvv , double _lk ) {
   double _lrates2;
 _lrates2 = ( _lb / ( 1.0 + exp ( ( _lv - _lvv ) / _lk ) ) ) ;
   
return _lrates2;
 }
 
static void _hoc_rates2(void) {
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
 _r =  rates2 ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 hoc_retpushx(_r);
}
 
static double _npy_rates2(Prop* _prop) {
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
 _r =  rates2 ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) );
 return(_r);
}
 
static int  rates ( _internalthreadargsprotocomma_ double _lv ) {
    C1C2_a = Q10 * ( rates2 ( _threadargscomma_ _lv , C1C2b2 , C1C2v2 , C1C2k2 ) ) ;
   C2C1_a = Q10 * ( rates2 ( _threadargscomma_ _lv , C2C1b1 , C2C1v1 , C2C1k1 ) + rates2 ( _threadargscomma_ _lv , C2C1b2 , C2C1v2 , C2C1k2 ) ) ;
   C2O1_a = Q10 * ( rates2 ( _threadargscomma_ _lv , C2O1b2 , C2O1v2 , C2O1k2 ) ) ;
   O1C2_a = Q10 * ( rates2 ( _threadargscomma_ _lv , O1C2b1 , O1C2v1 , O1C2k1 ) + rates2 ( _threadargscomma_ _lv , O1C2b2 , O1C2v2 , O1C2k2 ) ) ;
   C2O2_a = Q10 * ( rates2 ( _threadargscomma_ _lv , C2O2b2 , C2O2v2 , C2O2k2 ) ) ;
   O2C2_a = Q10 * ( rates2 ( _threadargscomma_ _lv , O2C2b1 , O2C2v1 , O2C2k1 ) + rates2 ( _threadargscomma_ _lv , O2C2b2 , O2C2v2 , O2C2k2 ) ) ;
   O1I1_a = Q10 * ( rates2 ( _threadargscomma_ _lv , O1I1b1 , O1I1v1 , O1I1k1 ) + rates2 ( _threadargscomma_ _lv , O1I1b2 , O1I1v2 , O1I1k2 ) ) ;
   I1O1_a = Q10 * ( rates2 ( _threadargscomma_ _lv , I1O1b1 , I1O1v1 , I1O1k1 ) ) ;
   I1C1_a = Q10 * ( rates2 ( _threadargscomma_ _lv , I1C1b1 , I1C1v1 , I1C1k1 ) ) ;
   C1I1_a = Q10 * ( rates2 ( _threadargscomma_ _lv , C1I1b2 , C1I1v2 , C1I1k2 ) ) ;
   I1I2_a = Q10 * ( rates2 ( _threadargscomma_ _lv , I1I2b2 , I1I2v2 , I1I2k2 ) ) ;
   I2I1_a = Q10 * ( rates2 ( _threadargscomma_ _lv , I2I1b1 , I2I1v1 , I2I1k1 ) ) ;
     return 0; }
 
static void _hoc_rates(void) {
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
 _r = 1.;
 rates ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_rates(Prop* _prop) {
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
 rates ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1(_internalthreadargsproto_) {
  int _reset=0;
  {
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<6;_i++) _ml->data(_iml, _dlist1[_i]) = 0.0;}
 rates ( _threadargscomma_ v ) ;
 /* ~ C1 <-> C2 ( C1C2_a , C2C1_a )*/
 f_flux =  C1C2_a * C1 ;
 b_flux =  C2C1_a * C2 ;
 DC1 -= (f_flux - b_flux);
 DC2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C2 <-> O1 ( C2O1_a , O1C2_a )*/
 f_flux =  C2O1_a * C2 ;
 b_flux =  O1C2_a * O1 ;
 DC2 -= (f_flux - b_flux);
 DO1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ C2 <-> O2 ( C2O2_a , O2C2_a )*/
 f_flux =  C2O2_a * C2 ;
 b_flux =  O2C2_a * O2 ;
 DC2 -= (f_flux - b_flux);
 DO2 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ O1 <-> I1 ( O1I1_a , I1O1_a )*/
 f_flux =  O1I1_a * O1 ;
 b_flux =  I1O1_a * I1 ;
 DO1 -= (f_flux - b_flux);
 DI1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ I1 <-> C1 ( I1C1_a , C1I1_a )*/
 f_flux =  I1C1_a * I1 ;
 b_flux =  C1I1_a * C1 ;
 DI1 -= (f_flux - b_flux);
 DC1 += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ I1 <-> I2 ( I1I2_a , I2I1_a )*/
 f_flux =  I1I2_a * I1 ;
 b_flux =  I2I1_a * I2 ;
 DI1 -= (f_flux - b_flux);
 DI2 += (f_flux - b_flux);
 
 /*REACTION*/
   /* O1 + O2 + C1 + C2 + I1 + I2 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, _internalthreadargsproto_) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<6;_i++){
  	_RHS1(_i) = _dt1*(_ml->data(_iml, _dlist1[_i]));
	_MATELM1(_i, _i) = _dt1;
      
} }
 rates ( _threadargscomma_ v ) ;
 /* ~ C1 <-> C2 ( C1C2_a , C2C1_a )*/
 _term =  C1C2_a ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 1 ,2)  -= _term;
 _term =  C2C1_a ;
 _MATELM1( 2 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
  /* ~ C2 <-> O1 ( C2O1_a , O1C2_a )*/
 _term =  C2O1_a ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 5 ,1)  -= _term;
 _term =  O1C2_a ;
 _MATELM1( 1 ,5)  -= _term;
 _MATELM1( 5 ,5)  += _term;
 /*REACTION*/
  /* ~ C2 <-> O2 ( C2O2_a , O2C2_a )*/
 _term =  C2O2_a ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 4 ,1)  -= _term;
 _term =  O2C2_a ;
 _MATELM1( 1 ,4)  -= _term;
 _MATELM1( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ O1 <-> I1 ( O1I1_a , I1O1_a )*/
 _term =  O1I1_a ;
 _MATELM1( 5 ,5)  += _term;
 _MATELM1( 3 ,5)  -= _term;
 _term =  I1O1_a ;
 _MATELM1( 5 ,3)  -= _term;
 _MATELM1( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ I1 <-> C1 ( I1C1_a , C1I1_a )*/
 _term =  I1C1_a ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 2 ,3)  -= _term;
 _term =  C1I1_a ;
 _MATELM1( 3 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ I1 <-> I2 ( I1I2_a , I2I1_a )*/
 _term =  I1I2_a ;
 _MATELM1( 3 ,3)  += _term;
 _MATELM1( 0 ,3)  -= _term;
 _term =  I2I1_a ;
 _MATELM1( 3 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
   /* O1 + O2 + C1 + C2 + I1 + I2 = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ return 6;}
 
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
  ena = _ion_ena;
     _ode_spec1 (_threadargs_);
  }}
 
static void _ode_map(Prop* _prop, int _ieq, neuron::container::data_handle<double>* _pv, neuron::container::data_handle<double>* _pvdot, double* _atol, int _type) { 
  Datum* _ppvar;
  _ppvar = _nrn_mechanism_access_dparam(_prop);
  _cvode_ieq = _ieq;
  for (int _i=0; _i < 6; ++_i) {
    _pv[_i] = _nrn_mechanism_get_param_handle(_prop, _slist1[_i]);
    _pvdot[_i] = _nrn_mechanism_get_param_handle(_prop, _dlist1[_i]);
    _cvode_abstol(_atollist, _atol, _i);
  }
 }
 
static void _ode_matsol_instance1(_internalthreadargsproto_) {
 _cvode_sparse_thread(&(_thread[_cvspth1].literal_value<void*>()), 6, _dlist1, neuron::scopmath::row_view{_ml, _iml}, _ode_matsol1, _threadargs_);
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
  ena = _ion_ena;
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_spth1].get<void*>()));
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_cvspth1].get<void*>()));
 }

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  C2 = C20;
  C1 = C10;
  I2 = I20;
  I1 = I10;
  O2 = O20;
  O1 = O10;
 {
   Q10 = pow( 3.0 , ( ( celsius - 20.0 ) / 10.0 ) ) ;
    _ss_sparse_thread(&(_thread[_spth1].literal_value<void*>()), 6, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, kin, _linmat1, _threadargs_);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 6; ++_i) {
      _ml->data(_iml, _slist1[_i]) += dt*_ml->data(_iml, _dlist1[_i]);
    }}
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
  ena = _ion_ena;
 initmodel(_threadargs_);
 }
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   g = gbar * ( O1 + O2 ) ;
   ina = g * ( v - ena ) ;
   }
 _current += ina;

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
  ena = _ion_ena;
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_threadargscomma_ _v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g_local - _rhs)/.001;
  _ion_ina += ina ;
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
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
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
  ena = _ion_ena;
 {  sparse_thread(&(_thread[_spth1].literal_value<void*>()), 6, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, kin, _linmat1, _threadargs_);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 6; ++_i) {
      _ml->data(_iml, _slist1[_i]) += dt*_ml->data(_iml, _dlist1[_i]);
    }}
 } }}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = {I2_columnindex, 0};  _dlist1[0] = {DI2_columnindex, 0};
 _slist1[1] = {C2_columnindex, 0};  _dlist1[1] = {DC2_columnindex, 0};
 _slist1[2] = {C1_columnindex, 0};  _dlist1[2] = {DC1_columnindex, 0};
 _slist1[3] = {I1_columnindex, 0};  _dlist1[3] = {DI1_columnindex, 0};
 _slist1[4] = {O2_columnindex, 0};  _dlist1[4] = {DO2_columnindex, 0};
 _slist1[5] = {O1_columnindex, 0};  _dlist1[5] = {DO1_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/nav14.mod";
    const char* nmodl_file_text = 
  "TITLE Nav1.4 ionic voltage-gated channel with kinetic scheme\n"
  "\n"
  "COMMENT\n"
  "A six-state markovian kinetic model of ionic channel.\n"
  "Part of a study on kinetic models.\n"
  "Author: Piero Balbi, July 2016\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX na14a\n"
  "	USEION na READ ena WRITE ina\n"
  "	RANGE gbar, ina, g\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	v (mV)\n"
  "	ena (mV)\n"
  "	celsius = 37 (degC)\n"
  "	gbar  = 0.1	 (mho/cm2)\n"
  "\n"
  "	C1C2b2	  = 16\n"
  "	C1C2v2    = -3\n"
  "	C1C2k2	  = -9\n"
  "\n"
  "	C2C1b1	  = 3\n"
  "	C2C1v1    = -33\n"
  "	C2C1k1	  = 9\n"
  "	C2C1b2	  = 16\n"
  "	C2C1v2    = -3\n"
  "	C2C1k2	  = -9\n"
  "\n"
  "	C2O1b2	  = 16\n"
  "	C2O1v2    = -8\n"
  "	C2O1k2	  = -9\n"
  "\n"
  "	O1C2b1	  = 1\n"
  "	O1C2v1    = -38\n"
  "	O1C2k1	  = 9\n"
  "	O1C2b2	  = 16\n"
  "	O1C2v2    = -8\n"
  "	O1C2k2	  = -9\n"
  "\n"
  "	C2O2b2	  = 0.03\n"
  "	C2O2v2	  = -20\n"
  "	C2O2k2	  = -8\n"
  "\n"
  "	O2C2b1	  = 3\n"
  "	O2C2v1	  = -50\n"
  "	O2C2k1	  = 8\n"
  "	O2C2b2	  = 0.1\n"
  "	O2C2v2	  = -20\n"
  "	O2C2k2	  = -8\n"
  "\n"
  "	O1I1b1	  = 0\n"
  "	O1I1v1	  = -10\n"
  "	O1I1k1	  = 10\n"
  "	O1I1b2	  = 16\n"
  "	O1I1v2	  = -10\n"
  "	O1I1k2	  = -10\n"
  "\n"
  "	I1O1b1	  = 0.00001\n"
  "	I1O1v1	  = -10\n"
  "	I1O1k1	  = 10\n"
  "\n"
  "	I1C1b1	  = 0.35\n"
  "	I1C1v1	  = -70\n"
  "	I1C1k1	  = 10\n"
  "\n"
  "	C1I1b2	  = 0.8\n"
  "	C1I1v2	  = -70\n"
  "	C1I1k2	  = -7\n"
  "\n"
  "	I1I2b2	  = 0.0015\n"
  "	I1I2v2	  = -70\n"
  "	I1I2k2	  = -12\n"
  "\n"
  "	I2I1b1	  = 0.007\n"
  "	I2I1v1	  = -70\n"
  "	I2I1k1	  = 12\n"
  "\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	ina  (mA/cm2)\n"
  "	g   (mho/cm2)\n"
  "\n"
  "	C1C2_a (/ms)\n"
  "	C2C1_a (/ms)\n"
  "	C2O1_a (/ms)\n"
  "	O1C2_a (/ms)\n"
  "	C2O2_a (/ms)\n"
  "	O2C2_a (/ms)\n"
  "	O1I1_a (/ms)\n"
  "	I1O1_a (/ms)\n"
  "	I1I2_a (/ms)\n"
  "	I2I1_a (/ms)\n"
  "	I1C1_a (/ms)\n"
  "	C1I1_a (/ms)\n"
  "\n"
  "	Q10 (1)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	C1\n"
  "	C2\n"
  "	O1\n"
  "	O2\n"
  "	I1\n"
  "	I2\n"
  "}\n"
  "\n"
  "\n"
  "INITIAL {\n"
  "	Q10 = 3^((celsius-20(degC))/10 (degC))\n"
  "	SOLVE kin\n"
  "	STEADYSTATE sparse\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE kin METHOD sparse\n"
  "	g = gbar * (O1 + O2)	: (mho/cm2)\n"
  "	ina = g * (v - ena)   	: (mA/cm2)\n"
  "}\n"
  "\n"
  "KINETIC kin {\n"
  "	rates(v)\n"
  "\n"
  "	~ C1 <->  C2 (C1C2_a, C2C1_a)\n"
  "	~ C2 <->  O1 (C2O1_a, O1C2_a)\n"
  "	~ C2 <->  O2 (C2O2_a, O2C2_a)\n"
  "	~ O1 <->  I1 (O1I1_a, I1O1_a)\n"
  "	~ I1 <->  C1 (I1C1_a, C1I1_a)\n"
  "	~ I1 <->  I2 (I1I2_a, I2I1_a)\n"
  "\n"
  "	CONSERVE O1 + O2 + C1 + C2 + I1 + I2 = 1\n"
  "}\n"
  "\n"
  "FUNCTION rates2(v, b, vv, k) {\n"
  "	rates2 = (b/(1+exp((v-vv)/k)))\n"
  "}\n"
  "\n"
  "PROCEDURE rates(v(mV)) {\n"
  "UNITSOFF\n"
  "	C1C2_a = Q10*(rates2(v, C1C2b2, C1C2v2, C1C2k2))\n"
  "	C2C1_a = Q10*(rates2(v, C2C1b1, C2C1v1, C2C1k1) + rates2(v, C2C1b2, C2C1v2, C2C1k2))\n"
  "	C2O1_a = Q10*(rates2(v, C2O1b2, C2O1v2, C2O1k2))\n"
  "	O1C2_a = Q10*(rates2(v, O1C2b1, O1C2v1, O1C2k1) + rates2(v, O1C2b2, O1C2v2, O1C2k2))\n"
  "	C2O2_a = Q10*(rates2(v, C2O2b2, C2O2v2, C2O2k2))\n"
  "	O2C2_a = Q10*(rates2(v, O2C2b1, O2C2v1, O2C2k1) + rates2(v, O2C2b2, O2C2v2, O2C2k2))\n"
  "	O1I1_a = Q10*(rates2(v, O1I1b1, O1I1v1, O1I1k1) + rates2(v, O1I1b2, O1I1v2, O1I1k2))\n"
  "	I1O1_a = Q10*(rates2(v, I1O1b1, I1O1v1, I1O1k1))\n"
  "	I1C1_a = Q10*(rates2(v, I1C1b1, I1C1v1, I1C1k1))\n"
  "	C1I1_a = Q10*(rates2(v, C1I1b2, C1I1v2, C1I1k2))\n"
  "	I1I2_a = Q10*(rates2(v, I1I2b2, I1I2v2, I1I2k2))\n"
  "	I2I1_a = Q10*(rates2(v, I2I1b1, I2I1v1, I2I1k1))\n"
  "UNITSON\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
