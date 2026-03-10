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
static constexpr auto number_of_floating_point_variables = 24;
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
 
#define nrn_init _nrn_init__cac1
#define _nrn_initial _nrn_initial__cac1
#define nrn_cur _nrn_cur__cac1
#define _nrn_current _nrn_current__cac1
#define nrn_jacob _nrn_jacob__cac1
#define nrn_state _nrn_state__cac1
#define _net_receive _net_receive__cac1 
#define kstates kstates__cac1 
 
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
#define gmax _ml->template fpfield<0>(_iml)
#define gmax_columnindex 0
#define Ev _ml->template fpfield<1>(_iml)
#define Ev_columnindex 1
#define Cs _ml->template fpfield<2>(_iml)
#define Cs_columnindex 2
#define C1 _ml->template fpfield<3>(_iml)
#define C1_columnindex 3
#define C2 _ml->template fpfield<4>(_iml)
#define C2_columnindex 4
#define O1 _ml->template fpfield<5>(_iml)
#define O1_columnindex 5
#define O2 _ml->template fpfield<6>(_iml)
#define O2_columnindex 6
#define C0 _ml->template fpfield<7>(_iml)
#define C0_columnindex 7
#define icl _ml->template fpfield<8>(_iml)
#define icl_columnindex 8
#define g _ml->template fpfield<9>(_iml)
#define g_columnindex 9
#define a1 _ml->template fpfield<10>(_iml)
#define a1_columnindex 10
#define b1 _ml->template fpfield<11>(_iml)
#define b1_columnindex 11
#define l1 _ml->template fpfield<12>(_iml)
#define l1_columnindex 12
#define u1 _ml->template fpfield<13>(_iml)
#define u1_columnindex 13
#define cli _ml->template fpfield<14>(_iml)
#define cli_columnindex 14
#define clo _ml->template fpfield<15>(_iml)
#define clo_columnindex 15
#define DCs _ml->template fpfield<16>(_iml)
#define DCs_columnindex 16
#define DC1 _ml->template fpfield<17>(_iml)
#define DC1_columnindex 17
#define DC2 _ml->template fpfield<18>(_iml)
#define DC2_columnindex 18
#define DO1 _ml->template fpfield<19>(_iml)
#define DO1_columnindex 19
#define DO2 _ml->template fpfield<20>(_iml)
#define DO2_columnindex 20
#define DC0 _ml->template fpfield<21>(_iml)
#define DC0_columnindex 21
#define v _ml->template fpfield<22>(_iml)
#define v_columnindex 22
#define _g _ml->template fpfield<23>(_iml)
#define _g_columnindex 23
#define _ion_cli *(_ml->dptr_field<0>(_iml))
#define _p_ion_cli static_cast<neuron::container::data_handle<double>>(_ppvar[0])
#define _ion_clo *(_ml->dptr_field<1>(_iml))
#define _p_ion_clo static_cast<neuron::container::data_handle<double>>(_ppvar[1])
#define _ion_icl *(_ml->dptr_field<2>(_iml))
#define _p_ion_icl static_cast<neuron::container::data_handle<double>>(_ppvar[2])
#define _ion_dicldv *(_ml->dptr_field<3>(_iml))
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
 static Prop* _extcall_prop;
 /* _prop_id kind of shadows _extcall_prop to allow validity checking. */
 static _nrn_non_owning_id_without_container _prop_id{};
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_KTF(void);
 static void _hoc_efun(void);
 static void _hoc_ghk(void);
 static void _hoc_update_state(void);
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
 {"setdata_cac1", _hoc_setdata},
 {"KTF_cac1", _hoc_KTF},
 {"efun_cac1", _hoc_efun},
 {"ghk_cac1", _hoc_ghk},
 {"update_state_cac1", _hoc_update_state},
 {0, 0}
};
 
/* Direct Python call wrappers to density mechanism functions.*/
 static double _npy_KTF(Prop*);
 static double _npy_efun(Prop*);
 static double _npy_ghk(Prop*);
 static double _npy_update_state(Prop*);
 
static NPyDirectMechFunc npy_direct_func_proc[] = {
 {"KTF", _npy_KTF},
 {"efun", _npy_efun},
 {"ghk", _npy_ghk},
 {"update_state", _npy_update_state},
 {0, 0}
};
#define KTF KTF_cac1
#define efun efun_cac1
#define ghk ghk_cac1
#define update_state update_state_cac1
 extern double KTF( _internalthreadargsprotocomma_ double );
 extern double efun( _internalthreadargsprotocomma_ double );
 extern double ghk( _internalthreadargsprotocomma_ double , double , double );
 extern double update_state( _internalthreadargsprotocomma_ double , double , double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
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
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"a0_cac1", "/s"},
 {"b0_cac1", "/s"},
 {"l0_cac1", "/s"},
 {"u0_cac1", "/s"},
 {"gmax_cac1", "mho/cm2"},
 {"Ev_cac1", "mV"},
 {0, 0}
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
 {"a0_cac1", &a0_cac1},
 {"b0_cac1", &b0_cac1},
 {"l0_cac1", &l0_cac1},
 {"u0_cac1", &u0_cac1},
 {"az_cac1", &az_cac1},
 {"bz_cac1", &bz_cac1},
 {"lz_cac1", &lz_cac1},
 {"uz_cac1", &uz_cac1},
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
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     0.1, /* gmax */
     -60, /* Ev */
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
    assert(_nrn_mechanism_get_num_vars(_prop) == 24);
 	/*initialize range parameters*/
 	gmax = _parm_default[0]; /* 0.1 */
 	Ev = _parm_default[1]; /* -60 */
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 24);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_cl_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0] = _nrn_mechanism_get_param_handle(prop_ion, 1); /* cli */
 	_ppvar[1] = _nrn_mechanism_get_param_handle(prop_ion, 2); /* clo */
 	_ppvar[2] = _nrn_mechanism_get_param_handle(prop_ion, 3); /* icl */
 	_ppvar[3] = _nrn_mechanism_get_param_handle(prop_ion, 4); /* _ion_dicldv */
 
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

 extern "C" void _cac1_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("cl", -1.0);
 	_cl_sym = hoc_lookup("cl_ion");
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
                                       _nrn_mechanism_field<double>{"gmax"} /* 0 */,
                                       _nrn_mechanism_field<double>{"Ev"} /* 1 */,
                                       _nrn_mechanism_field<double>{"Cs"} /* 2 */,
                                       _nrn_mechanism_field<double>{"C1"} /* 3 */,
                                       _nrn_mechanism_field<double>{"C2"} /* 4 */,
                                       _nrn_mechanism_field<double>{"O1"} /* 5 */,
                                       _nrn_mechanism_field<double>{"O2"} /* 6 */,
                                       _nrn_mechanism_field<double>{"C0"} /* 7 */,
                                       _nrn_mechanism_field<double>{"icl"} /* 8 */,
                                       _nrn_mechanism_field<double>{"g"} /* 9 */,
                                       _nrn_mechanism_field<double>{"a1"} /* 10 */,
                                       _nrn_mechanism_field<double>{"b1"} /* 11 */,
                                       _nrn_mechanism_field<double>{"l1"} /* 12 */,
                                       _nrn_mechanism_field<double>{"u1"} /* 13 */,
                                       _nrn_mechanism_field<double>{"cli"} /* 14 */,
                                       _nrn_mechanism_field<double>{"clo"} /* 15 */,
                                       _nrn_mechanism_field<double>{"DCs"} /* 16 */,
                                       _nrn_mechanism_field<double>{"DC1"} /* 17 */,
                                       _nrn_mechanism_field<double>{"DC2"} /* 18 */,
                                       _nrn_mechanism_field<double>{"DO1"} /* 19 */,
                                       _nrn_mechanism_field<double>{"DO2"} /* 20 */,
                                       _nrn_mechanism_field<double>{"DC0"} /* 21 */,
                                       _nrn_mechanism_field<double>{"v"} /* 22 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 23 */,
                                       _nrn_mechanism_field<double*>{"_ion_cli", "cl_ion"} /* 0 */,
                                       _nrn_mechanism_field<double*>{"_ion_clo", "cl_ion"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"_ion_icl", "cl_ion"} /* 2 */,
                                       _nrn_mechanism_field<double*>{"_ion_dicldv", "cl_ion"} /* 3 */,
                                       _nrn_mechanism_field<int>{"_cvode_ieq", "cvodeieq"} /* 4 */);
  hoc_register_prop_size(_mechtype, 24, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cl_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cac1 /Users/ann/memCPG/CPG_STDP/py/mod_files/cac1.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 0x1.81f0fae775425p+6;
 static double R = 0x1.0a1013e8990bep+3;
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
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
 static int kstates (void* _so, double* _rhs, _internalthreadargsproto_);
 
static int kstates (void* _so, double* _rhs, _internalthreadargsproto_)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<6;_i++){
  	_RHS1(_i) = -_dt1*(_ml->data(_iml, _slist1[_i]) - _ml->data(_iml, _dlist1[_i]));
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
 
double update_state ( _internalthreadargsprotocomma_ double _lv , double _lstate0 , double _lz0 ) {
   double _lupdate_state;
 _lupdate_state = _lstate0 * exp ( _lz0 * FARADAY * _lv / R / ( 273.15 + celsius ) ) ;
   
return _lupdate_state;
 }
 
static void _hoc_update_state(void) {
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
 _r =  update_state ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static double _npy_update_state(Prop* _prop) {
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
 _r =  update_state ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 return(_r);
}
 
double ghk ( _internalthreadargsprotocomma_ double _lv , double _lci , double _lco ) {
   double _lghk;
 double _lnu , _lf ;
 _lf = KTF ( _threadargscomma_ celsius ) / 2.0 ;
   _lnu = _lv / _lf ;
   _lghk = - _lf * ( 1. - ( _lci / _lco ) * exp ( _lnu ) ) * efun ( _threadargscomma_ _lnu ) ;
   
return _lghk;
 }
 
static void _hoc_ghk(void) {
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
 _r =  ghk ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
static double _npy_ghk(Prop* _prop) {
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
 _r =  ghk ( _threadargscomma_ *getarg(1) , *getarg(2) , *getarg(3) );
 return(_r);
}
 
double KTF ( _internalthreadargsprotocomma_ double _lcelsius ) {
   double _lKTF;
 _lKTF = ( ( 25. / 293.15 ) * ( _lcelsius + 273.15 ) ) ;
   
return _lKTF;
 }
 
static void _hoc_KTF(void) {
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
 _r =  KTF ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_KTF(Prop* _prop) {
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
 _r =  KTF ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
double efun ( _internalthreadargsprotocomma_ double _lz ) {
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
 _r =  efun ( _threadargscomma_ *getarg(1) );
 hoc_retpushx(_r);
}
 
static double _npy_efun(Prop* _prop) {
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
 _r =  efun ( _threadargscomma_ *getarg(1) );
 return(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1(_internalthreadargsproto_) {
  int _reset=0;
  {
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<6;_i++) _ml->data(_iml, _dlist1[_i]) = 0.0;}
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
 static int _ode_matsol1(void* _so, double* _rhs, _internalthreadargsproto_) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<6;_i++){
  	_RHS1(_i) = _dt1*(_ml->data(_iml, _dlist1[_i]));
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
  cli = _ion_cli;
  clo = _ion_clo;
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
  cli = _ion_cli;
  clo = _ion_clo;
 _ode_matsol_instance1(_threadargs_);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_spth1].get<void*>()));
   _nrn_destroy_sparseobj_thread(static_cast<SparseObj*>(_thread[_cvspth1].get<void*>()));
 }

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
  C0 = C00;
  C2 = C20;
  C1 = C10;
  Cs = Cs0;
  O2 = O20;
  O1 = O10;
 {
    sparse_thread(&(_thread[_spth1].literal_value<void*>()), 6, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, kstates, _linmat1, _threadargs_);
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
  cli = _ion_cli;
  clo = _ion_clo;
 initmodel(_threadargs_);
 }
}

static double _nrn_current(_internalthreadargsprotocomma_ double _v) {
double _current=0.; v=_v;
{ {
   g = gmax * ( O1 + O2 ) ;
   icl = g * ghk ( _threadargscomma_ v , cli , clo ) ;
   }
 _current += icl;

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
  cli = _ion_cli;
  clo = _ion_clo;
 auto const _g_local = _nrn_current(_threadargscomma_ _v + .001);
 	{ double _dicl;
  _dicl = icl;
 _rhs = _nrn_current(_threadargscomma_ _v);
  _ion_dicldv += (_dicl - icl)/.001 ;
 	}
 _g = (_g_local - _rhs)/.001;
  _ion_icl += icl ;
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
  cli = _ion_cli;
  clo = _ion_clo;
 {  sparse_thread(&(_thread[_spth1].literal_value<void*>()), 6, _slist1, _dlist1, neuron::scopmath::row_view{_ml, _iml}, &t, dt, kstates, _linmat1, _threadargs_);
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
 _slist1[0] = {O2_columnindex, 0};  _dlist1[0] = {DO2_columnindex, 0};
 _slist1[1] = {C0_columnindex, 0};  _dlist1[1] = {DC0_columnindex, 0};
 _slist1[2] = {C2_columnindex, 0};  _dlist1[2] = {DC2_columnindex, 0};
 _slist1[3] = {C1_columnindex, 0};  _dlist1[3] = {DC1_columnindex, 0};
 _slist1[4] = {Cs_columnindex, 0};  _dlist1[4] = {DCs_columnindex, 0};
 _slist1[5] = {O1_columnindex, 0};  _dlist1[5] = {DO1_columnindex, 0};
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/cac1.mod";
    const char* nmodl_file_text = 
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
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
