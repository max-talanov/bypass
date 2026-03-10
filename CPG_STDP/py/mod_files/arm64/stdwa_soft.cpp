/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
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
#include <vector>
using std::size_t;
static auto& std_cerr_stream = std::cerr;
static constexpr auto number_of_datum_variables = 3;
static constexpr auto number_of_floating_point_variables = 10;
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
 
#define nrn_init _nrn_init__StdwaSA
#define _nrn_initial _nrn_initial__StdwaSA
#define nrn_cur _nrn_cur__StdwaSA
#define _nrn_current _nrn_current__StdwaSA
#define nrn_jacob _nrn_jacob__StdwaSA
#define nrn_state _nrn_state__StdwaSA
#define _net_receive _net_receive__StdwaSA 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _internalthreadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
#define _internalthreadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *hoc_getarg(int);
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define wmax _ml->template fpfield<0>(_iml)
#define wmax_columnindex 0
#define aLTP _ml->template fpfield<1>(_iml)
#define aLTP_columnindex 1
#define aLTD _ml->template fpfield<2>(_iml)
#define aLTD_columnindex 2
#define interval _ml->template fpfield<3>(_iml)
#define interval_columnindex 3
#define tlast_pre _ml->template fpfield<4>(_iml)
#define tlast_pre_columnindex 4
#define tlast_post _ml->template fpfield<5>(_iml)
#define tlast_post_columnindex 5
#define M _ml->template fpfield<6>(_iml)
#define M_columnindex 6
#define P _ml->template fpfield<7>(_iml)
#define P_columnindex 7
#define deltaw _ml->template fpfield<8>(_iml)
#define deltaw_columnindex 8
#define _tsav _ml->template fpfield<9>(_iml)
#define _tsav_columnindex 9
#define _nd_area *_ml->dptr_field<0>(_iml)
#define wsyn	*_ppvar[2].get<double*>()
#define _p_wsyn _ppvar[2].literal_value<void*>()
 static _nrn_mechanism_cache_instance _ml_real{nullptr};
static _nrn_mechanism_cache_range *_ml{&_ml_real};
static size_t _iml{0};
static Datum *_ppvar;
 static int hoc_nrnpointerindex =  2;
 /* external NEURON variables */
 /* declaration of user functions */
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mechtype);
#endif
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(Object* _ho) { void* create_point_process(int, Object*);
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt(void*);
 static double _hoc_loc_pnt(void* _vptr) {double loc_point_process(int, void*);
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(void* _vptr) {double has_loc_point(void*);
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(void* _vptr) {
 double get_loc_point_process(void*); return (get_loc_point_process(_vptr));
}
 static void _hoc_setdata(void*);
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 {0, 0}
};
 static Member_func _member_func[] = {
 {"loc", _hoc_loc_pnt},
 {"has_loc", _hoc_has_loc},
 {"get_loc", _hoc_get_loc_pnt},
 {0, 0}
};
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define on on_StdwaSA
 double on = 1;
#define tauLTD tauLTD_StdwaSA
 double tauLTD = 20;
#define tauLTP tauLTP_StdwaSA
 double tauLTP = 20;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"tauLTP_StdwaSA", "ms"},
 {"tauLTD_StdwaSA", "ms"},
 {"interval", "ms"},
 {"tlast_pre", "ms"},
 {"tlast_post", "ms"},
 {0, 0}
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"tauLTP_StdwaSA", &tauLTP_StdwaSA},
 {"tauLTD_StdwaSA", &tauLTD_StdwaSA},
 {"on_StdwaSA", &on_StdwaSA},
 {0, 0}
};
 static DoubVec hoc_vdoub[] = {
 {0, 0, 0}
};
 static double _sav_indep;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 neuron::legacy::set_globals_from_prop(_prop, _ml_real, _ml, _iml);
_ppvar = _nrn_mechanism_access_dparam(_prop);
 Node * _node = _nrn_mechanism_access_node(_prop);
v = _nrn_mechanism_access_voltage(_node);
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 static void nrn_alloc(Prop*);
static void nrn_init(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_state(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void _hoc_destroy_pnt(void* _vptr) {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"StdwaSA",
 "wmax",
 "aLTP",
 "aLTD",
 0,
 "interval",
 "tlast_pre",
 "tlast_post",
 "M",
 "P",
 "deltaw",
 0,
 0,
 "wsyn",
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     1, /* wmax */
     0.001, /* aLTP */
     0.00106, /* aLTD */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
  if (nrn_point_prop_) {
    _nrn_mechanism_access_alloc_seq(_prop) = _nrn_mechanism_access_alloc_seq(nrn_point_prop_);
    _ppvar = _nrn_mechanism_access_dparam(nrn_point_prop_);
  } else {
   _ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 10);
 	/*initialize range parameters*/
 	wmax = _parm_default[0]; /* 1 */
 	aLTP = _parm_default[1]; /* 0.001 */
 	aLTD = _parm_default[2]; /* 0.00106 */
  }
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 10);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _stdwa_soft_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nullptr, nullptr, nullptr, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"wmax"} /* 0 */,
                                       _nrn_mechanism_field<double>{"aLTP"} /* 1 */,
                                       _nrn_mechanism_field<double>{"aLTD"} /* 2 */,
                                       _nrn_mechanism_field<double>{"interval"} /* 3 */,
                                       _nrn_mechanism_field<double>{"tlast_pre"} /* 4 */,
                                       _nrn_mechanism_field<double>{"tlast_post"} /* 5 */,
                                       _nrn_mechanism_field<double>{"M"} /* 6 */,
                                       _nrn_mechanism_field<double>{"P"} /* 7 */,
                                       _nrn_mechanism_field<double>{"deltaw"} /* 8 */,
                                       _nrn_mechanism_field<double>{"_tsav"} /* 9 */,
                                       _nrn_mechanism_field<double*>{"_nd_area", "area"} /* 0 */,
                                       _nrn_mechanism_field<Point_process*>{"_pntproc", "pntproc"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"wsyn", "pointer"} /* 2 */);
  hoc_register_prop_size(_mechtype, 10, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 StdwaSA /Users/ann/memCPG/CPG_STDP/py/mod_files/stdwa_soft.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{   neuron::legacy::set_globals_from_prop(_pnt->_prop, _ml_real, _ml, _iml);
    _ppvar = _nrn_mechanism_access_dparam(_pnt->_prop);
  if (_tsav > t){ hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   if ( _args[0] >= 0.0 ) {
     P = P * exp ( ( tlast_pre - t ) / tauLTP ) + aLTP ;
     interval = tlast_post - t ;
     tlast_pre = t ;
     deltaw = wmax * M * exp ( interval / tauLTD ) ;
     }
   else {
     M = M * exp ( ( tlast_post - t ) / tauLTD ) - aLTD ;
     interval = t - tlast_pre ;
     tlast_post = t ;
     deltaw = wmax * P * exp ( - interval / tauLTP ) ;
     }
   if ( on ) {
     wsyn = wsyn + deltaw ;
     if ( wsyn > wmax ) {
       wsyn = wmax ;
       }
     if ( wsyn < 0.0 ) {
       wsyn = 0.0 ;
       }
     }
   } }

static void initmodel() {
  int _i; double _save;_ninits++;
{
 {
   interval = 0.0 ;
   tlast_pre = 0.0 ;
   tlast_post = 0.0 ;
   M = 0.0 ;
   P = 0.0 ;
   deltaw = 0.0 ;
   }

}
}

static void nrn_init(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
Node *_nd; double _v; int* _ni; int _cntml;
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
_ml = &_lmr;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
 _tsav = -1e20;
   _v = _vec_v[_ni[_iml]];
 v = _v;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_state(_nrn_model_sorted_token const& _sorted_token, NrnThread* _nt, Memb_list* _ml_arg, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _cntml;
_nrn_mechanism_cache_range _lmr{_sorted_token, *_nt, *_ml_arg, _type};
auto* const _vec_v = _nt->node_voltage_storage();
_ml = &_lmr;
_ni = _ml_arg->_nodeindices;
_cntml = _ml_arg->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _ppvar = _ml_arg->_pdata[_iml];
 _nd = _ml_arg->_nodelist[_iml];
   _v = _vec_v[_ni[_iml]];
 v=_v;
{
}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/stdwa_soft.mod";
    const char* nmodl_file_text = 
  "COMMENT\n"
  "Spike Timing Dependent Weight Adjuster\n"
  "based on Song and Abbott, 2001.\n"
  "Andrew Davison, UNIC, CNRS, 2003-2004\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "	POINT_PROCESS StdwaSA\n"
  "	RANGE interval, tlast_pre, tlast_post, M, P\n"
  "	RANGE deltaw, wmax, aLTP, aLTD\n"
  "	GLOBAL tauLTP, tauLTD, on\n"
  "	POINTER wsyn\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	interval	(ms)	: since last spike of the other kind\n"
  "	tlast_pre	(ms)	: time of last presynaptic spike\n"
  "	tlast_post	(ms)	: time of last postsynaptic spike\n"
  "	M			: LTD function\n"
  "	P			: LTP function\n"
  "	deltaw			: change in weight\n"
  "	wsyn			: weight of the synapse\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	interval = 0\n"
  "	tlast_pre = 0\n"
  "	tlast_post = 0\n"
  "	M = 0\n"
  "	P = 0\n"
  "	deltaw = 0\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	tauLTP  = 20	(ms)    : decay time for LTP part ( values from           )\n"
  "	tauLTD  = 20	(ms)    : decay time for LTD part ( Song and Abbott, 2001 )\n"
  "	wmax    = 1		: min and max values of synaptic weight\n"
  "	aLTP    = 0.001		: amplitude of LTP steps\n"
  "	aLTD    = 0.00106	: amplitude of LTD steps\n"
  "	on	= 1		: allows learning to be turned on and off globally\n"
  "}\n"
  "\n"
  "NET_RECEIVE (w) {\n"
  "	if (w >= 0) {				: this is a pre-synaptic spike\n"
  "		P = P*exp((tlast_pre-t)/tauLTP) + aLTP\n"
  "		interval = tlast_post - t	: interval is negative\n"
  "		tlast_pre = t\n"
  "		deltaw = wmax * M * exp(interval/tauLTD)\n"
  "	} else {				: this is a post-synaptic spike\n"
  "		M = M*exp((tlast_post-t)/tauLTD) - aLTD\n"
  "		interval = t - tlast_pre	: interval is positive\n"
  "		tlast_post = t\n"
  "		deltaw = wmax * P * exp(-interval/tauLTP)\n"
  "	}\n"
  "	if (on) {\n"
  "		wsyn = wsyn + deltaw\n"
  "		if (wsyn > wmax) {\n"
  "			wsyn = wmax\n"
  "		}\n"
  "		if (wsyn < 0) {\n"
  "			wsyn = 0\n"
  "		}\n"
  "	}\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
