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
static constexpr auto number_of_datum_variables = 2;
static constexpr auto number_of_floating_point_variables = 14;
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
 
#define nrn_init _nrn_init__SpikeGenerator
#define _nrn_initial _nrn_initial__SpikeGenerator
#define nrn_cur _nrn_cur__SpikeGenerator
#define _nrn_current _nrn_current__SpikeGenerator
#define nrn_jacob _nrn_jacob__SpikeGenerator
#define nrn_state _nrn_state__SpikeGenerator
#define _net_receive _net_receive__SpikeGenerator 
#define event_time event_time__SpikeGenerator 
#define init_sequence init_sequence__SpikeGenerator 
#define seed seed__SpikeGenerator 
 
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
#define interval _ml->template fpfield<0>(_iml)
#define interval_columnindex 0
#define number _ml->template fpfield<1>(_iml)
#define number_columnindex 1
#define start _ml->template fpfield<2>(_iml)
#define start_columnindex 2
#define noise _ml->template fpfield<3>(_iml)
#define noise_columnindex 3
#define k _ml->template fpfield<4>(_iml)
#define k_columnindex 4
#define speed _ml->template fpfield<5>(_iml)
#define speed_columnindex 5
#define y _ml->template fpfield<6>(_iml)
#define y_columnindex 6
#define freq _ml->template fpfield<7>(_iml)
#define freq_columnindex 7
#define event _ml->template fpfield<8>(_iml)
#define event_columnindex 8
#define on _ml->template fpfield<9>(_iml)
#define on_columnindex 9
#define end _ml->template fpfield<10>(_iml)
#define end_columnindex 10
#define ml0 _ml->template fpfield<11>(_iml)
#define ml0_columnindex 11
#define time _ml->template fpfield<12>(_iml)
#define time_columnindex 12
#define _tsav _ml->template fpfield<13>(_iml)
#define _tsav_columnindex 13
#define _nd_area *_ml->dptr_field<0>(_iml)
 static _nrn_mechanism_cache_instance _ml_real{nullptr};
static _nrn_mechanism_cache_range *_ml{&_ml_real};
static size_t _iml{0};
static Datum *_ppvar;
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_event_time(void*);
 static double _hoc_frequency(void*);
 static double _hoc_init_sequence(void*);
 static double _hoc_invl(void*);
 static double _hoc_seed(void*);
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
 {"event_time", _hoc_event_time},
 {"frequency", _hoc_frequency},
 {"init_sequence", _hoc_init_sequence},
 {"invl", _hoc_invl},
 {"seed", _hoc_seed},
 {0, 0}
};
#define frequency frequency_SpikeGenerator
#define invl invl_SpikeGenerator
 extern double frequency( double );
 extern double invl( double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
#define maxlen maxlen_SpikeGenerator
 double maxlen = 200;
#define ml ml_SpikeGenerator
 double ml = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {"interval", 1e-09, 1e+09},
 {"noise", 0, 1},
 {"number", 0, 1e+09},
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"interval", "ms"},
 {"start", "ms"},
 {"freq", "ms"},
 {0, 0}
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"ml_SpikeGenerator", &ml_SpikeGenerator},
 {"maxlen_SpikeGenerator", &maxlen_SpikeGenerator},
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
"SpikeGenerator",
 "interval",
 "number",
 "start",
 "noise",
 "k",
 "speed",
 0,
 "y",
 "freq",
 0,
 0,
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     10, /* interval */
     10000, /* number */
     50, /* start */
     0, /* noise */
     0.009, /* k */
     150, /* speed */
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
    assert(_nrn_mechanism_get_num_vars(_prop) == 14);
 	/*initialize range parameters*/
 	interval = _parm_default[0]; /* 10 */
 	number = _parm_default[1]; /* 10000 */
 	start = _parm_default[2]; /* 50 */
 	noise = _parm_default[3]; /* 0 */
 	k = _parm_default[4]; /* 0.009 */
 	speed = _parm_default[5]; /* 150 */
  }
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 14);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 
#define _tqitem &(_ppvar[2])
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _pregen_reg() {
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
                                       _nrn_mechanism_field<double>{"interval"} /* 0 */,
                                       _nrn_mechanism_field<double>{"number"} /* 1 */,
                                       _nrn_mechanism_field<double>{"start"} /* 2 */,
                                       _nrn_mechanism_field<double>{"noise"} /* 3 */,
                                       _nrn_mechanism_field<double>{"k"} /* 4 */,
                                       _nrn_mechanism_field<double>{"speed"} /* 5 */,
                                       _nrn_mechanism_field<double>{"y"} /* 6 */,
                                       _nrn_mechanism_field<double>{"freq"} /* 7 */,
                                       _nrn_mechanism_field<double>{"event"} /* 8 */,
                                       _nrn_mechanism_field<double>{"on"} /* 9 */,
                                       _nrn_mechanism_field<double>{"end"} /* 10 */,
                                       _nrn_mechanism_field<double>{"ml0"} /* 11 */,
                                       _nrn_mechanism_field<double>{"time"} /* 12 */,
                                       _nrn_mechanism_field<double>{"_tsav"} /* 13 */,
                                       _nrn_mechanism_field<double*>{"_nd_area", "area"} /* 0 */,
                                       _nrn_mechanism_field<Point_process*>{"_pntproc", "pntproc"} /* 1 */,
                                       _nrn_mechanism_field<void*>{"_tqitem", "netsend"} /* 2 */);
  hoc_register_prop_size(_mechtype, 14, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "netsend");
 add_nrn_has_net_event(_mechtype);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 SpikeGenerator /Users/ann/memCPG/CPG_STDP/py/mod_files/pregen.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int event_time();
static int init_sequence(double);
static int seed(double);
 
static int  seed (  double _lx ) {
   set_seed ( _lx ) ;
    return 0; }
 
static double _hoc_seed(void* _vptr) {
 double _r;
    auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _setdata(_p);
 _r = 1.;
 seed (  *getarg(1) );
 return(_r);
}
 
static int  init_sequence (  double _lt ) {
   if ( number > 0.0 ) {
     on = 1.0 ;
     event = _lt ;
     interval = 1000.0 / frequency ( _threadargscomma_ _lt ) ;
     end = _lt + 1e-6 + invl ( _threadargscomma_ interval ) * ( number - 1.0 ) ;
     }
    return 0; }
 
static double _hoc_init_sequence(void* _vptr) {
 double _r;
    auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _setdata(_p);
 _r = 1.;
 init_sequence (  *getarg(1) );
 return(_r);
}
 
double frequency (  double _lt ) {
   double _lfrequency;
 ml0 = ml ;
   if ( _lt <= start ) {
     time = 0.0 ;
     }
   if ( _lt > start ) {
     time = _lt - start ;
     }
   ml = ( maxlen / pow ( ( k * ( time + 1.0 ) ) , 1.5 ) ) * ( 1.0 - exp ( 1.0 / ( k * ( time + 1.0 ) ) ) ) ;
   _lfrequency = 4.3 * pow ( fabs ( ml - ml0 ) , 0.6 ) + 82.0 ;
   if ( ( _lt - start ) > speed ) {
     _lfrequency = 10.0 ;
     }
   freq = _lfrequency ;
   
return _lfrequency;
 }
 
static double _hoc_frequency(void* _vptr) {
 double _r;
    auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _setdata(_p);
 _r =  frequency (  *getarg(1) );
 return(_r);
}
 
double invl (  double _linterval ) {
   double _linvl;
 if ( noise  == 0.0 ) {
     _linvl = _linterval ;
     }
   else {
     _linvl = ( 1. - noise ) * ( _linterval ) + noise * ( _linterval ) * exprand ( 1.0 ) ;
     }
   
return _linvl;
 }
 
static double _hoc_invl(void* _vptr) {
 double _r;
    auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _setdata(_p);
 _r =  invl (  *getarg(1) );
 return(_r);
}
 
static int  event_time (  ) {
   if ( number > 0.0 ) {
     interval = 1000.0 / frequency ( _threadargscomma_ t ) ;
     event = event + invl ( _threadargscomma_ interval ) ;
     }
   if ( event > end ) {
     on = 0.0 ;
     }
    return 0; }
 
static double _hoc_event_time(void* _vptr) {
 double _r;
    auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _setdata(_p);
 _r = 1.;
 event_time (  );
 return(_r);
}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{   neuron::legacy::set_globals_from_prop(_pnt->_prop, _ml_real, _ml, _iml);
    _ppvar = _nrn_mechanism_access_dparam(_pnt->_prop);
  if (_tsav > t){ hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = nullptr;}
 {
   if ( _lflag  == 0.0 ) {
     if ( _args[0] > 0.0  && on  == 0.0 ) {
       init_sequence ( _threadargscomma_ t ) ;
       net_send ( _tqitem, _args, _pnt, t +  0.0 , 1.0 ) ;
       }
     else if ( _args[0] < 0.0  && on  == 1.0 ) {
       on = 0.0 ;
       }
     }
   if ( _lflag  == 3.0 ) {
     if ( on  == 0.0 ) {
       init_sequence ( _threadargscomma_ t ) ;
       net_send ( _tqitem, _args, _pnt, t +  0.0 , 1.0 ) ;
       }
     }
   if ( _lflag  == 1.0  && on  == 1.0 ) {
     y = 2.0 ;
     net_event ( _pnt, t ) ;
     event_time ( _threadargs_ ) ;
     if ( on  == 1.0 ) {
       net_send ( _tqitem, _args, _pnt, t +  event - t , 1.0 ) ;
       }
     net_send ( _tqitem, _args, _pnt, t +  .1 , 2.0 ) ;
     }
   if ( _lflag  == 2.0 ) {
     y = 0.0 ;
     }
   } }

static void initmodel() {
  int _i; double _save;_ninits++;
{
 {
   on = 0.0 ;
   y = 0.0 ;
   if ( noise < 0.0 ) {
     noise = 0.0 ;
     }
   if ( noise > 1.0 ) {
     noise = 1.0 ;
     }
   if ( start >= 0.0  && number > 0.0 ) {
     interval = 1000.0 / frequency ( _threadargscomma_ t ) ;
     event = start + invl ( _threadargscomma_ interval ) ;
     net_send ( _tqitem, nullptr, _ppvar[1].get<Point_process*>(), t +  event , 3.0 ) ;
     }
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
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/pregen.mod";
    const char* nmodl_file_text = 
  ": pregen.mod,v 1.4 1999/01/22 18:47:54 hines Exp\n"
  ": comments at end\n"
  "\n"
  "NEURON	{ \n"
  "  POINT_PROCESS SpikeGenerator\n"
  "  RANGE y\n"
  "  RANGE interval, number, start\n"
  "  RANGE noise, freq, k, speed\n"
  "}\n"
  "PARAMETER {\n"
  "	interval = 10 (ms) <1e-9,1e9>: time between spikes (msec)\n"
  "	number = 10000 <0,1e9>	: number of spikes\n"
  "	start = 50 (ms)	: start of first spike\n"
  "	noise = 0 <0,1>	: amount of randomeaness (0.0 - 1.0)\n"
  "	ml = 0\n"
  "	maxlen = 200\n"
  "	k = 0.009\n"
  "	speed = 150\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	y\n"
  "	event (ms)\n"
  "	on\n"
  "	end (ms)\n"
  "	ml0\n"
  "	freq (ms)\n"
  "	time\n"
  "}\n"
  "\n"
  "PROCEDURE seed(x) {\n"
  "	set_seed(x)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	on = 0\n"
  "	y = 0\n"
  "	if (noise < 0) {\n"
  "		noise = 0\n"
  "	}\n"
  "	if (noise > 1) {\n"
  "		noise = 1\n"
  "	}\n"
  "	if (start >= 0 && number > 0) {\n"
  "		: randomize the first spike so on average it occurs at start+interval\n"
  "		interval = 1000/frequency(t)\n"
  "		event = start + invl(interval)\n"
  "		net_send(event, 3)\n"
  "	}\n"
  "}	\n"
  "\n"
  "PROCEDURE init_sequence(t(ms)) {\n"
  "	if (number > 0) {\n"
  "		on = 1\n"
  "		event = t\n"
  "		interval = 1000/frequency(t)\n"
  "		end = t + 1e-6 + invl(interval)*(number-1)\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION frequency(t (ms)) (ms) {\n"
  "	ml0 = ml\n"
  "	if (t<=start){time = 0}\n"
  "	if (t>start){time = t - start}\n"
  "	ml = (maxlen/pow((k*(time+1)),1.5))*(1-exp(1/(k*(time+1))))\n"
  "	frequency = 4.3*pow(fabs(ml - ml0),0.6) + 82\n"
  "	if ((t-start) > speed){frequency = 10}\n"
  "	freq = frequency\n"
  "}\n"
  "\n"
  "FUNCTION invl(interval (ms)) (ms) {\n"
  "	if (noise == 0) {\n"
  "		invl = interval\n"
  "	}else{\n"
  "		invl = (1. - noise)*(interval) + noise*(interval)*exprand(1)\n"
  "	}\n"
  "}\n"
  "\n"
  "PROCEDURE event_time() {\n"
  "	if (number > 0) {\n"
  "		interval = 1000/frequency(t)\n"
  "		event = event + invl(interval)\n"
  "	}\n"
  "	if (event > end) {\n"
  "		on = 0\n"
  "	}\n"
  "}\n"
  "\n"
  "NET_RECEIVE (w) {\n"
  "	if (flag == 0) { : external event\n"
  "		if (w > 0 && on == 0) { : turn on spike sequence\n"
  "			init_sequence(t)\n"
  "			net_send(0, 1)\n"
  "		}else if (w < 0 && on == 1) { : turn off spiking\n"
  "			on = 0\n"
  "		}\n"
  "	}\n"
  "	if (flag == 3) { : from INITIAL\n"
  "		if (on == 0) {\n"
  "			init_sequence(t)\n"
  "			net_send(0, 1)\n"
  "		}\n"
  "	}\n"
  "	if (flag == 1 && on == 1) {\n"
  "		y = 2\n"
  "		net_event(t)\n"
  "		event_time()\n"
  "		if (on == 1) {\n"
  "			net_send(event - t, 1)\n"
  "		}\n"
  "		net_send(.1, 2)\n"
  "	}\n"
  "	if (flag == 2) {\n"
  "		y = 0\n"
  "	}\n"
  "}\n"
  "\n"
  "COMMENT\n"
  "Presynaptic spike generator\n"
  "---------------------------\n"
  "\n"
  "This mechanism has been written to be able to use synapses in a single\n"
  "neuron receiving various types of presynaptic trains.  This is a \"fake\"\n"
  "presynaptic compartment containing a spike generator.  The trains\n"
  "of spikes can be either periodic or noisy (Poisson-distributed)\n"
  "\n"
  "Parameters;\n"
  "   noise: 	between 0 (no noise-periodic) and 1 (fully noisy)\n"
  "   interval: 	mean time between spikes (ms)\n"
  "   number: 	mean number of spikes\n"
  "\n"
  "Written by Z. Mainen, modified by A. Destexhe, The Salk Institute\n"
  "\n"
  "Modified by Michael Hines for use with CVode\n"
  "The intrinsic bursting parameters have been removed since\n"
  "generators can stimulate other generators to create complicated bursting\n"
  "patterns with independent statistics (see below)\n"
  "\n"
  "Modified by Michael Hines to use logical event style with NET_RECEIVE\n"
  "This stimulator can also be triggered by an input event.\n"
  "If the stimulator is in the on=0 state and receives a positive weight\n"
  "event, then the stimulator changes to the on=1 state and goes through\n"
  "its entire spike sequence before changing to the on=0 state. During\n"
  "that time it ignores any positive weight events. If, in the on=1 state,\n"
  "the stimulator receives a negative weight event, the stimulator will\n"
  "change to the off state. In the off state, it will ignore negative weight\n"
  "events. A change to the on state immediately fires the first spike of\n"
  "its sequence.\n"
  "\n"
  "ENDCOMMENT\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
