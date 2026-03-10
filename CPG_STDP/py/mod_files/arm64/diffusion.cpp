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
static constexpr auto number_of_datum_variables = 2;
static constexpr auto number_of_floating_point_variables = 19;
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
 
#define nrn_init _nrn_init__diff3D
#define _nrn_initial _nrn_initial__diff3D
#define nrn_cur _nrn_cur__diff3D
#define _nrn_current _nrn_current__diff3D
#define nrn_jacob _nrn_jacob__diff3D
#define nrn_state _nrn_state__diff3D
#define _net_receive _net_receive__diff3D 
 
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
#define nu _ml->template fpfield<0>(_iml)
#define nu_columnindex 0
#define alpha _ml->template fpfield<1>(_iml)
#define alpha_columnindex 1
#define Deff _ml->template fpfield<2>(_iml)
#define Deff_columnindex 2
#define c0cleft _ml->template fpfield<3>(_iml)
#define c0cleft_columnindex 3
#define rPSD _ml->template fpfield<4>(_iml)
#define rPSD_columnindex 4
#define meandist _ml->template fpfield<5>(_iml)
#define meandist_columnindex 5
#define Popeak _ml->template fpfield<6>(_iml)
#define Popeak_columnindex 6
#define includir _ml->template fpfield<7>(_iml)
#define includir_columnindex 7
#define incluspill _ml->template fpfield<8>(_iml)
#define incluspill_columnindex 8
#define h _ml->template fpfield<9>(_iml)
#define h_columnindex 9
#define tx1 _ml->template fpfield<10>(_iml)
#define tx1_columnindex 10
#define dir _ml->template fpfield<11>(_iml)
#define dir_columnindex 11
#define spill _ml->template fpfield<12>(_iml)
#define spill_columnindex 12
#define subs _ml->template fpfield<13>(_iml)
#define subs_columnindex 13
#define Podir _ml->template fpfield<14>(_iml)
#define Podir_columnindex 14
#define Pospill _ml->template fpfield<15>(_iml)
#define Pospill_columnindex 15
#define v _ml->template fpfield<16>(_iml)
#define v_columnindex 16
#define _g _ml->template fpfield<17>(_iml)
#define _g_columnindex 17
#define _tsav _ml->template fpfield<18>(_iml)
#define _tsav_columnindex 18
#define _nd_area *_ml->dptr_field<0>(_iml)
 /* Thread safe. No static _ml, _iml or _ppvar. */
 static int hoc_nrnpointerindex =  -1;
 static _nrn_mechanism_std_vector<Datum> _extcall_thread;
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
#define a a_diff3D
 double a = 0.02;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"a_diff3D", "um"},
 {"nu", "/um2"},
 {"Deff", "um2/ms"},
 {"c0cleft", "uM"},
 {"rPSD", "um"},
 {"meandist", "um"},
 {"h", "um"},
 {"tx1", "ms"},
 {"dir", "uM"},
 {"spill", "uM"},
 {"subs", "uM"},
 {0, 0}
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 {"a_diff3D", &a_diff3D},
 {0, 0}
};
 static DoubVec hoc_vdoub[] = {
 {0, 0, 0}
};
 static double _sav_indep;
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 static void nrn_alloc(Prop*);
static void nrn_init(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_state(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void nrn_cur(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
static void nrn_jacob(_nrn_model_sorted_token const&, NrnThread*, Memb_list*, int);
 static void _hoc_destroy_pnt(void* _vptr) {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"diff3D",
 "nu",
 "alpha",
 "Deff",
 "c0cleft",
 "rPSD",
 "meandist",
 "Popeak",
 "includir",
 "incluspill",
 "h",
 "tx1",
 0,
 "dir",
 "spill",
 "subs",
 "Podir",
 "Pospill",
 0,
 0,
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     1, /* nu */
     5, /* alpha */
     0.2, /* Deff */
     1, /* c0cleft */
     0.28, /* rPSD */
     0.29, /* meandist */
     0.6, /* Popeak */
     1, /* includir */
     1, /* incluspill */
     0, /* h */
     0, /* tx1 */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
  if (nrn_point_prop_) {
    _nrn_mechanism_access_alloc_seq(_prop) = _nrn_mechanism_access_alloc_seq(nrn_point_prop_);
    _ppvar = _nrn_mechanism_access_dparam(nrn_point_prop_);
  } else {
   _ppvar = nrn_prop_datum_alloc(_mechtype, 2, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 19);
 	/*initialize range parameters*/
 	nu = _parm_default[0]; /* 1 */
 	alpha = _parm_default[1]; /* 5 */
 	Deff = _parm_default[2]; /* 0.2 */
 	c0cleft = _parm_default[3]; /* 1 */
 	rPSD = _parm_default[4]; /* 0.28 */
 	meandist = _parm_default[5]; /* 0.29 */
 	Popeak = _parm_default[6]; /* 0.6 */
 	includir = _parm_default[7]; /* 1 */
 	incluspill = _parm_default[8]; /* 1 */
 	h = _parm_default[9]; /* 0 */
 	tx1 = _parm_default[10]; /* 0 */
  }
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 19);
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

 extern "C" void _diffusion_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 1,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
 hoc_register_parm_default(_mechtype, &_parm_default);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  register_nmodl_text_and_filename(_mechtype);
#endif
   _nrn_mechanism_register_data_fields(_mechtype,
                                       _nrn_mechanism_field<double>{"nu"} /* 0 */,
                                       _nrn_mechanism_field<double>{"alpha"} /* 1 */,
                                       _nrn_mechanism_field<double>{"Deff"} /* 2 */,
                                       _nrn_mechanism_field<double>{"c0cleft"} /* 3 */,
                                       _nrn_mechanism_field<double>{"rPSD"} /* 4 */,
                                       _nrn_mechanism_field<double>{"meandist"} /* 5 */,
                                       _nrn_mechanism_field<double>{"Popeak"} /* 6 */,
                                       _nrn_mechanism_field<double>{"includir"} /* 7 */,
                                       _nrn_mechanism_field<double>{"incluspill"} /* 8 */,
                                       _nrn_mechanism_field<double>{"h"} /* 9 */,
                                       _nrn_mechanism_field<double>{"tx1"} /* 10 */,
                                       _nrn_mechanism_field<double>{"dir"} /* 11 */,
                                       _nrn_mechanism_field<double>{"spill"} /* 12 */,
                                       _nrn_mechanism_field<double>{"subs"} /* 13 */,
                                       _nrn_mechanism_field<double>{"Podir"} /* 14 */,
                                       _nrn_mechanism_field<double>{"Pospill"} /* 15 */,
                                       _nrn_mechanism_field<double>{"v"} /* 16 */,
                                       _nrn_mechanism_field<double>{"_g"} /* 17 */,
                                       _nrn_mechanism_field<double>{"_tsav"} /* 18 */,
                                       _nrn_mechanism_field<double*>{"_nd_area", "area"} /* 0 */,
                                       _nrn_mechanism_field<Point_process*>{"_pntproc", "pntproc"} /* 1 */);
  hoc_register_prop_size(_mechtype, 19, 2);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 diff3D /Users/ann/memCPG/CPG_STDP/py/mod_files/diffusion.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 3.1415927;
static int _reset;
static const char *modelname = "3D diffusion";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{  Prop* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _nrn_mechanism_cache_instance _ml_real{_pnt->_prop};
  auto* const _ml = &_ml_real;
  size_t const _iml{};
   _thread = nullptr; double* _globals = nullptr; _nt = (NrnThread*)_pnt->_vnt;   _ppvar = _nrn_mechanism_access_dparam(_pnt->_prop);
  if (_tsav > t){ hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   tx1 = t ;
   } }

static void initmodel(_internalthreadargsproto_) {
  int _i; double _save;{
 {
   subs = 0.0 ;
   dir = 0.0 ;
   spill = 0.0 ;
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
 _tsav = -1e20;
   _v = _vec_v[_ni[_iml]];
 v = _v;
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
 {
   at_time ( _nt, tx1 ) ;
   if ( t <= tx1 ) {
     subs = 0.0 ;
     dir = 0.0 ;
     spill = 0.0 ;
     Podir = 0.0 ;
     Pospill = 0.0 ;
     }
   if ( t > tx1 ) {
      dir = ( 2.0 * c0cleft * alpha / ( sqrt ( 4.0 * PI * Deff * ( t - tx1 ) ) * sqrt ( 4.0 * PI * Deff * ( t - tx1 ) ) * sqrt ( 4.0 * PI * Deff * ( t - tx1 ) ) ) ) * ( 1.0 - exp ( h / ( 4.0 * Deff * ( tx1 - t ) ) ) ) ;
     if ( dir > c0cleft ) {
       dir = c0cleft ;
       }
     c0cleft = c0cleft + 0.000001 ;
     spill = 2.0 * nu * c0cleft * rPSD * rPSD * PI * alpha * ( 1.0 / sqrt ( 4.0 * PI * Deff * ( t - tx1 ) ) ) * ( exp ( meandist * meandist / ( 4.0 * Deff * ( tx1 - t ) ) ) - exp ( rPSD * rPSD / ( 4.0 * Deff * ( tx1 - t ) ) ) ) ;
     subs = ( 2.0 * c0cleft * PI * a * alpha * rPSD * rPSD * exp ( h / ( 4.0 * Deff * ( tx1 - t ) ) ) ) / sqrt ( 4.0 * 4.0 * 4.0 * PI * PI * PI * Deff * Deff * Deff * ( t - tx1 ) * ( t - tx1 ) * ( t - tx1 ) ) ;
     if ( subs > c0cleft ) {
       subs = c0cleft ;
       }
     Podir = ( 0.94 * exp ( ( tx1 - t ) / 0.37 ) + 0.06 * exp ( ( tx1 - t ) / 2.2 ) - exp ( ( tx1 - t ) / 0.199 ) ) / 0.249 * ( 0.43 / 0.484 ) * Popeak ;
     Pospill = ( 0.39 * exp ( ( tx1 - t ) / 2.0 ) + 0.61 * exp ( ( tx1 - t ) / 9.1 ) - exp ( ( tx1 - t ) / 0.44 ) ) / 0.682 * ( 0.125 / 0.484 ) * Popeak ;
     }
   }
}}

}

static void terminal(){}

static void _initlists(){
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if NMODL_TEXT
static void register_nmodl_text_and_filename(int mech_type) {
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/diffusion.mod";
    const char* nmodl_file_text = 
  "TITLE 3D diffusion\n"
  "NEURON{\n"
  "	POINT_PROCESS diff3D\n"
  "	RANGE    subs,rPSD,h,nu,dir,spill,c0cleft\n"
  "	RANGE Deff,meandist,rabs,alpha,h,Rmf  \n"
  "	RANGE includir,incluspill, Popeak,alpha,Podir,Pospill \n"
  "	RANGE ts1,td1,tx1}\n"
  "\n"
  "UNITS{\n"
  "		(molar)=(1/liter)\n"
  "		(uM)=(micromolar)\n"
  "		(um)=(micron)\n"
  "		(nA)=(nanoamp)\n"
  "}\n"
  "CONSTANT {\n"
  "	PI=3.1415927\n"
  "}\n"
  "PARAMETER { \n"
  "	nu=1(/um2)\n"
  "	alpha=5 \n"
  "	Deff=0.2 (um2/ms):effective diffusion coefficient\n"
  "	c0cleft = 1 (uM):initial quantity subs\n"
  "	rPSD=0.28 (um) :  radius \n"
  "	meandist=0.29 (um) : lowest limit\n"
  "	a=0.02 (um)\n"
  "	Popeak=0.6\n"
  "	includir=1 : inclusion of direct component\n"
  "	incluspill=1 : inclusion of spillover component\n"
  "	h(um)\n"
  "	 tx1(ms)\n"
  "\n"
  " }\n"
  "ASSIGNED{\n"
  "   dir (uM)\n"
  "   spill(uM)\n"
  "   subs (uM)\n"
  "   Podir\n"
  "   Pospill \n"
  "}\n"
  "INITIAL {\n"
  "	:tx1=10\n"
  "	subs=0\n"
  "	dir=0\n"
  "	spill=0\n"
  "}\n"
  "BREAKPOINT\n"
  "{\n"
  "	at_time(tx1)\n"
  "	if (t<=tx1){\n"
  "		subs=0\n"
  "		dir=0\n"
  "		spill=0\n"
  "		Podir=0\n"
  "		Pospill=0\n"
  "}\n"
  "if(t>tx1) {\n"
  "UNITSOFF\n"
  "	dir= (2*c0cleft*alpha/(sqrt(4*PI*Deff*(t-tx1))*sqrt(4*PI*Deff*(t-tx1))*sqrt(4*PI*Deff*(t-tx1))))*(1-exp(h/(4*Deff*(tx1-t))))\n"
  "	if(dir>c0cleft){dir=c0cleft}\n"
  "	c0cleft=c0cleft+0.000001\n"
  "	: if (t>100){tx1=100}\n"
  "	spill = 2*nu*c0cleft*rPSD*rPSD*PI*alpha*(1/sqrt(4*PI*Deff*(t-tx1)))*(exp(meandist*meandist/(4*Deff*(tx1-t)))-exp(rPSD*rPSD/(4*Deff*(tx1-t))))\n"
  "	subs= (2*c0cleft*PI*a*alpha*rPSD*rPSD*exp(h/(4*Deff*(tx1-t))))/sqrt(4*4*4*PI*PI*PI*Deff*Deff*Deff*(t-tx1)*(t-tx1)*(t-tx1))\n"
  "    if(subs>c0cleft){subs=c0cleft}\n"
  "\n"
  "    :subs= ((2*c0cleft)*exp(h/(4*Deff*(tx1-t))))/(sqrt(4*PI*Deff*(t-tx1))*sqrt(4*PI*Deff*(t-tx1))*sqrt(4*PI*Deff*(t-tx1)))\n"
  "   \n"
  ": Experimental waveforms\n"
  "Podir=(0.94*exp((tx1-t)/0.37(ms))+0.06*exp((tx1-t)/2.2(ms))\n"
  "  -exp((tx1-t)/0.199(ms)))/0.249*(0.43/0.484)*Popeak\n"
  "Pospill=(0.39*exp((tx1-t)/2.0(ms))+0.61*exp((tx1-t)/9.1(ms))-\n"
  " exp((tx1-t)/0.44(ms)))/0.682*(0.125/0.484)*Popeak\n"
  "}\n"
  "}\n"
  "NET_RECEIVE (weight)\n"
  "{\n"
  "tx1=t \n"
  "}\n"
  "\n"
  "\n"
  "\n"
  "\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
