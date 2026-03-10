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
static constexpr auto number_of_floating_point_variables = 18;
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
 
#define nrn_init _nrn_init__STDP_mini
#define _nrn_initial _nrn_initial__STDP_mini
#define nrn_cur _nrn_cur__STDP_mini
#define _nrn_current _nrn_current__STDP_mini
#define nrn_jacob _nrn_jacob__STDP_mini
#define nrn_state _nrn_state__STDP_mini
#define _net_receive _net_receive__STDP_mini 
#define adjustweight adjustweight__STDP_mini 
 
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
#define tauhebb _ml->template fpfield<0>(_iml)
#define tauhebb_columnindex 0
#define tauanti _ml->template fpfield<1>(_iml)
#define tauanti_columnindex 1
#define hebbwt _ml->template fpfield<2>(_iml)
#define hebbwt_columnindex 2
#define antiwt _ml->template fpfield<3>(_iml)
#define antiwt_columnindex 3
#define wmax _ml->template fpfield<4>(_iml)
#define wmax_columnindex 4
#define softthresh _ml->template fpfield<5>(_iml)
#define softthresh_columnindex 5
#define STDPon _ml->template fpfield<6>(_iml)
#define STDPon_columnindex 6
#define verbose _ml->template fpfield<7>(_iml)
#define verbose_columnindex 7
#define skip _ml->template fpfield<8>(_iml)
#define skip_columnindex 8
#define tlastpre _ml->template fpfield<9>(_iml)
#define tlastpre_columnindex 9
#define tlastpost _ml->template fpfield<10>(_iml)
#define tlastpost_columnindex 10
#define tlasthebbelig _ml->template fpfield<11>(_iml)
#define tlasthebbelig_columnindex 11
#define tlastantielig _ml->template fpfield<12>(_iml)
#define tlastantielig_columnindex 12
#define interval _ml->template fpfield<13>(_iml)
#define interval_columnindex 13
#define deltaw _ml->template fpfield<14>(_iml)
#define deltaw_columnindex 14
#define newweight _ml->template fpfield<15>(_iml)
#define newweight_columnindex 15
#define gv _ml->template fpfield<16>(_iml)
#define gv_columnindex 16
#define _tsav _ml->template fpfield<17>(_iml)
#define _tsav_columnindex 17
#define _nd_area *_ml->dptr_field<0>(_iml)
#define synweight	*_ppvar[2].get<double*>()
#define _p_synweight _ppvar[2].literal_value<void*>()
 static _nrn_mechanism_cache_instance _ml_real{nullptr};
static _nrn_mechanism_cache_range *_ml{&_ml_real};
static size_t _iml{0};
static Datum *_ppvar;
 static int hoc_nrnpointerindex =  2;
 /* external NEURON variables */
 /* declaration of user functions */
 static double _hoc_adjustweight(void*);
 static double _hoc_softthreshold(void*);
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
 {"adjustweight", _hoc_adjustweight},
 {"softthreshold", _hoc_softthreshold},
 {0, 0}
};
#define softthreshold softthreshold_STDP_mini
 extern double softthreshold( double );
 /* declare global and static user variables */
 #define gind 0
 #define _gth 0
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 {0, 0, 0}
};
 static HocParmUnits _hoc_parm_units[] = {
 {"tauhebb", "ms"},
 {"tauanti", "ms"},
 {"tlastpre", "ms"},
 {"tlastpost", "ms"},
 {"tlasthebbelig", "ms"},
 {"tlastantielig", "ms"},
 {"interval", "ms"},
 {0, 0}
};
 static double v = 0;
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
"STDP_mini",
 "tauhebb",
 "tauanti",
 "hebbwt",
 "antiwt",
 "wmax",
 "softthresh",
 "STDPon",
 "verbose",
 "skip",
 0,
 "tlastpre",
 "tlastpost",
 "tlasthebbelig",
 "tlastantielig",
 "interval",
 "deltaw",
 "newweight",
 "gv",
 0,
 0,
 "synweight",
 0};
 
 /* Used by NrnProperty */
 static _nrn_mechanism_std_vector<double> _parm_default{
     17, /* tauhebb */
     34, /* tauanti */
     0.01, /* hebbwt */
     -0.02, /* antiwt */
     15, /* wmax */
     1, /* softthresh */
     1, /* STDPon */
     0, /* verbose */
     0, /* skip */
 }; 
 
 
extern Prop* need_memb(Symbol*);
static void nrn_alloc(Prop* _prop) {
  Prop *prop_ion{};
  Datum *_ppvar{};
  if (nrn_point_prop_) {
    _nrn_mechanism_access_alloc_seq(_prop) = _nrn_mechanism_access_alloc_seq(nrn_point_prop_);
    _ppvar = _nrn_mechanism_access_dparam(nrn_point_prop_);
  } else {
   _ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
    _nrn_mechanism_access_dparam(_prop) = _ppvar;
     _nrn_mechanism_cache_instance _ml_real{_prop};
    auto* const _ml = &_ml_real;
    size_t const _iml{};
    assert(_nrn_mechanism_get_num_vars(_prop) == 18);
 	/*initialize range parameters*/
 	tauhebb = _parm_default[0]; /* 17 */
 	tauanti = _parm_default[1]; /* 34 */
 	hebbwt = _parm_default[2]; /* 0.01 */
 	antiwt = _parm_default[3]; /* -0.02 */
 	wmax = _parm_default[4]; /* 15 */
 	softthresh = _parm_default[5]; /* 1 */
 	STDPon = _parm_default[6]; /* 1 */
 	verbose = _parm_default[7]; /* 0 */
 	skip = _parm_default[8]; /* 0 */
  }
 	 assert(_nrn_mechanism_get_num_vars(_prop) == 18);
 	_nrn_mechanism_access_dparam(_prop) = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 
#define _tqitem &(_ppvar[3])
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
void _nrn_thread_table_reg(int, nrn_thread_table_check_t);
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 extern "C" void _stdp_mini_reg() {
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
                                       _nrn_mechanism_field<double>{"tauhebb"} /* 0 */,
                                       _nrn_mechanism_field<double>{"tauanti"} /* 1 */,
                                       _nrn_mechanism_field<double>{"hebbwt"} /* 2 */,
                                       _nrn_mechanism_field<double>{"antiwt"} /* 3 */,
                                       _nrn_mechanism_field<double>{"wmax"} /* 4 */,
                                       _nrn_mechanism_field<double>{"softthresh"} /* 5 */,
                                       _nrn_mechanism_field<double>{"STDPon"} /* 6 */,
                                       _nrn_mechanism_field<double>{"verbose"} /* 7 */,
                                       _nrn_mechanism_field<double>{"skip"} /* 8 */,
                                       _nrn_mechanism_field<double>{"tlastpre"} /* 9 */,
                                       _nrn_mechanism_field<double>{"tlastpost"} /* 10 */,
                                       _nrn_mechanism_field<double>{"tlasthebbelig"} /* 11 */,
                                       _nrn_mechanism_field<double>{"tlastantielig"} /* 12 */,
                                       _nrn_mechanism_field<double>{"interval"} /* 13 */,
                                       _nrn_mechanism_field<double>{"deltaw"} /* 14 */,
                                       _nrn_mechanism_field<double>{"newweight"} /* 15 */,
                                       _nrn_mechanism_field<double>{"gv"} /* 16 */,
                                       _nrn_mechanism_field<double>{"_tsav"} /* 17 */,
                                       _nrn_mechanism_field<double*>{"_nd_area", "area"} /* 0 */,
                                       _nrn_mechanism_field<Point_process*>{"_pntproc", "pntproc"} /* 1 */,
                                       _nrn_mechanism_field<double*>{"synweight", "pointer"} /* 2 */,
                                       _nrn_mechanism_field<void*>{"_tqitem", "netsend"} /* 3 */);
  hoc_register_prop_size(_mechtype, 18, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
  hoc_register_dparam_semantics(_mechtype, 3, "netsend");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 
    hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 STDP_mini /Users/ann/memCPG/CPG_STDP/py/mod_files/stdp_mini.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static const char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int adjustweight(double);
 
double softthreshold (  double _lrawwc ) {
   double _lsoftthreshold;
 if ( _lrawwc >= 0.0 ) {
     _lsoftthreshold = _lrawwc * ( 1.0 - synweight / wmax ) ;
     }
   else {
     _lsoftthreshold = _lrawwc * synweight / wmax ;
     }
   
return _lsoftthreshold;
 }
 
static double _hoc_softthreshold(void* _vptr) {
 double _r;
    auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _setdata(_p);
 _r =  softthreshold (  *getarg(1) );
 return(_r);
}
 
static int  adjustweight (  double _lwc ) {
   synweight = synweight + _lwc ;
   printf ( "ajustweight synweight = %f" , synweight ) ;
   if ( synweight > wmax ) {
     synweight = wmax ;
     }
   if ( synweight < 0.0 ) {
     synweight = 0.0 ;
     }
    return 0; }
 
static double _hoc_adjustweight(void* _vptr) {
 double _r;
    auto* const _pnt = static_cast<Point_process*>(_vptr);
  auto* const _p = _pnt->_prop;
  if (!_p) {
    hoc_execerror("POINT_PROCESS data instance not valid", NULL);
  }
   _setdata(_p);
 _r = 1.;
 adjustweight (  *getarg(1) );
 return(_r);
}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{   neuron::legacy::set_globals_from_prop(_pnt->_prop, _ml_real, _ml, _iml);
    _ppvar = _nrn_mechanism_access_dparam(_pnt->_prop);
  if (_tsav > t){ hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = nullptr;}
 {
   deltaw = 0.0 ;
   skip = 0.0 ;
   if ( verbose > 1.0 ) {
     printf ( "t=%f (BEFORE) tlaspre=%f, tlastpost=%f, flag=%f, w=%f, deltaw=%f \n" , t , tlastpre , tlastpost , _lflag , _args[0] , deltaw ) ;
     }
   if ( ( _lflag  == - 1.0 )  && ( tlastpre  != t - 1.0 ) ) {
     skip = 1.0 ;
     deltaw = ( hebbwt + gv * synweight ) * exp ( - interval / tauhebb ) ;
     if ( softthresh  == 1.0 ) {
       deltaw = softthreshold ( _threadargscomma_ deltaw ) ;
       }
     adjustweight ( _threadargscomma_ deltaw ) ;
     if ( verbose > 1.0 ) {
       printf ( "Hebbian STDP event: t = %f ms; tlastpre = %f; w = %f; deltaw = %f\n" , t , tlastpre , _args[0] , deltaw ) ;
       }
     }
   else if ( ( _lflag  == 1.0 )  && ( tlastpost  != t - 1.0 ) ) {
     skip = 1.0 ;
     deltaw = ( antiwt * synweight + gv * synweight ) * exp ( interval / tauanti ) ;
     if ( softthresh  == 1.0 ) {
       deltaw = softthreshold ( _threadargscomma_ deltaw ) ;
       }
     adjustweight ( _threadargscomma_ deltaw ) ;
     if ( verbose > 1.0 ) {
       printf ( "anti-Hebbian STDP event: t = %f ms; deltaw = %f\n" , t , deltaw ) ;
       }
     }
   if ( skip  == 0.0 ) {
     if ( _args[0] >= 0.0 ) {
       interval = tlastpost - t ;
       if ( ( tlastpost > - 1.0 )  && ( - interval > 1.0 ) ) {
         if ( STDPon  == 1.0 ) {
           if ( verbose > 1.0 ) {
             printf ( "net_send(1,1)\n" ) ;
             }
           net_send ( _tqitem, _args, _pnt, t +  1.0 , 1.0 ) ;
           }
         }
       tlastpre = t ;
       }
     else {
       interval = t - tlastpre ;
       if ( ( tlastpre > - 1.0 )  && ( interval > 1.0 ) ) {
         if ( STDPon  == 1.0 ) {
           if ( verbose > 1.0 ) {
             printf ( "net_send(1,-1)\n" ) ;
             }
           net_send ( _tqitem, _args, _pnt, t +  1.0 , - 1.0 ) ;
           }
         }
       tlastpost = t ;
       }
     }
   if ( verbose > 1.0 ) {
     printf ( "t=%f (AFTER) tlaspre=%f, tlastpost=%f, flag=%f, w=%f, deltaw=%f \n" , t , tlastpre , tlastpost , _lflag , _args[0] , deltaw ) ;
     }
   } }

static void initmodel() {
  int _i; double _save;_ninits++;
{
 {
   tlastpre = - 1.0 ;
   tlastpost = - 1.0 ;
   tlasthebbelig = - 1.0 ;
   tlastantielig = - 1.0 ;
   interval = 0.0 ;
   deltaw = 0.0 ;
   newweight = 0.0 ;
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
    const char* nmodl_filename = "/Users/ann/memCPG/CPG_STDP/py/mod_files/stdp_mini.mod";
    const char* nmodl_file_text = 
  "COMMENT\n"
  "\n"
  "STDP + RL weight adjuster mechanism\n"
  "\n"
  "Original STDP code adapted from:\n"
  "http://senselab.med.yale.edu/modeldb/showmodel.asp?model=64261&file=\\bfstdp\\stdwa_songabbott.mod\n"
  "\n"
  "Adapted to implement a \"nearest-neighbor spike-interaction\" model (see\n"
  "Scholarpedia article on STDP) that just looks at the last-seen pre- and\n"
  "post-synaptic spikes, and implementing a reinforcement learning algorithm based\n"
  "on (Chadderdon et al., 2012):\n"
  "http://www.plosone.org/article/info%3Adoi%2F10.1371%2Fjournal.pone.0047251\n"
  "\n"
  "Example Python usage:\n"
  "\n"
  "from neuron import h\n"
  "\n"
  "## Create cells\n"
  "dummy = h.Section() # Create a dummy section to put the point processes in\n"
  "ncells = 2\n"
  "cells = []\n"
  "for c in range(ncells): cells.append(h.IntFire4(0,sec=dummy)) # Create the cells\n"
  "\n"
  "## Create synapses\n"
  "threshold = 10 # Set voltage threshold\n"
  "delay = 1 # Set connection delay\n"
  "singlesyn = h.NetCon(cells[0],cells[1], threshold, delay, 0.5) # Create a connection between the cells\n"
  "stdpmech = h.STDP(0,sec=dummy) # Create the STDP mechanism\n"
  "presyn = h.NetCon(cells[0],stdpmech, threshold, delay, 1) # Feed presynaptic spikes to the STDP mechanism -- must have weight >0\n"
  "pstsyn = h.NetCon(cells[1],stdpmech, threshold, delay, -1) # Feed postsynaptic spikes to the STDP mechanism -- must have weight <0\n"
  "h.setpointer(singlesyn._ref_weight[0],'synweight',stdpmech) # Point the STDP mechanism to the connection weight\n"
  "\n"
  "Version: 2013oct24 by cliffk\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "    POINT_PROCESS STDP_mini : Definition of mechanism\n"
  "    POINTER synweight : Pointer to the weight (in a NetCon object) to be adjusted.\n"
  "    RANGE tauhebb, tauanti : LTP/LTD decay time constants (in ms) for the Hebbian (pre-before-post-synaptic spikes), and anti-Hebbian (post-before-pre-synaptic) cases.\n"
  "    RANGE hebbwt, antiwt : Maximal adjustment (can be positive or negative) for Hebbian and anti-Hebbian cases (i.e., as inter-spike interval approaches zero).  This should be set positive for LTP and negative for LTD.\n"
  "    RANGE wmax : The maximum weight for the synapse.\n"
  "    RANGE softthresh : Flag turning on \"soft thresholding\" for the maximal adjustment parameters.\n"
  "    RANGE STDPon : Flag for turning STDP adjustment on / off.\n"
  "    RANGE verbose : Flag for turning off prints of weight update events for debugging.\n"
  "    RANGE tlastpre, tlastpost : Remembered times for last pre- and post-synaptic spikes.\n"
  "    RANGE tlasthebbelig, tlastantielig : Remembered times for Hebbian anti-Hebbian eligibility traces.\n"
  "    RANGE interval : Interval between current time t and previous spike.\n"
  "    RANGE deltaw : The calculated weight change.\n"
  "    RANGE newweight : New calculated weight.\n"
  "    RANGE skip : Flag to skip 2nd set of conditions\n"
  "    RANGE gv : random gaussian\n"
  "}\n"
  "PARAMETER {\n"
  "    tauhebb  = 17  (ms)\n"
  "    tauanti  = 34  (ms)\n"
  "    hebbwt = 0.01\n"
  "    antiwt = -0.02\n"
  "    wmax  = 15.0\n"
  "    softthresh = 1\n"
  "    STDPon = 1\n"
  "    verbose = 0\n"
  "    skip = 0\n"
  "}\n"
  "\n"
  "\n"
  "ASSIGNED {\n"
  "    synweight\n"
  "    tlastpre   (ms)\n"
  "    tlastpost  (ms)\n"
  "    tlasthebbelig   (ms)\n"
  "    tlastantielig  (ms)\n"
  "    interval    (ms)\n"
  "    deltaw\n"
  "    newweight\n"
  "    gv\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    tlastpre = -1            : no spike yet\n"
  "    tlastpost = -1           : no spike yet\n"
  "    tlasthebbelig = -1      : no eligibility yet\n"
  "    tlastantielig = -1  : no eligibility yet\n"
  "    interval = 0\n"
  "    deltaw = 0\n"
  "    newweight = 0\n"
  "}\n"
  "\n"
  "\n"
  "FUNCTION softthreshold(rawwc) {\n"
  "    if (rawwc >= 0) { softthreshold = rawwc * (1.0 - synweight / wmax) } : If the weight change is non-negative, scale by 1 - weight / wmax.\n"
  "    else { softthreshold = rawwc * synweight / wmax } : Otherwise (the weight change is negative), scale by weight / wmax.\n"
  "}\n"
  "\n"
  "PROCEDURE adjustweight(wc) {\n"
  "   synweight = synweight + wc : apply the synaptic modification, and then clip the weight if necessary to make sure it's between 0 and wmax.\n"
  "   printf(\"ajustweight synweight = %f\", synweight)\n"
  "\n"
  "   if (synweight > wmax) { synweight = wmax }\n"
  "   if (synweight < 0) { synweight = 0 }\n"
  "}\n"
  "\n"
  "\n"
  "NET_RECEIVE (w) {\n"
  "    deltaw = 0.0 : Default the weight change to 0.\n"
  "    skip = 0\n"
  "\n"
  "    if (verbose > 1)  {\n"
  "        printf(\"t=%f (BEFORE) tlaspre=%f, tlastpost=%f, flag=%f, w=%f, deltaw=%f \\n\",t,tlastpre, tlastpost,flag,w,deltaw) }\n"
  "\n"
  "    : Hebbian weight update happens 1ms later to check for simultaneous spikes (otherwise bug when using mpi)\n"
  "    if ((flag == -1) && (tlastpre != t-1)) {\n"
  "        skip = 1 : skip the 2nd set of conditions since this was artificial net event to update weights\n"
  "        deltaw = (hebbwt + gv*synweight) * exp(-interval / tauhebb) : Use the Hebbian decay to set the Hebbian weight adjustment.\n"
  "        if (softthresh == 1) { deltaw = softthreshold(deltaw) } : If we have soft-thresholding on, apply it.\n"
  "        adjustweight(deltaw) : Adjust the weight.\n"
  "        if (verbose > 1) {\n"
  "            printf(\"Hebbian STDP event: t = %f ms; tlastpre = %f; w = %f; deltaw = %f\\n\",t,tlastpre,w,deltaw)\n"
  "            } : Show weight update information if debugging on.\n"
  "        }\n"
  "\n"
  "    : Ant-hebbian weight update happens 1ms later to check for simultaneous spikes (otherwise bug when using mpi)\n"
  "    else if ((flag == 1) && (tlastpost != t-1)) { :update weight 1ms later to check for simultaneous spikes (otherwise bug when using mpi)\n"
  "        skip = 1 : skip the 2nd set of conditions since this was artificial net event to update weights\n"
  "        deltaw = (antiwt*synweight + gv*synweight)* exp(interval / tauanti) : Use the anti-Hebbian decay to set the anti-Hebbian weight adjustment.\n"
  "        if (softthresh == 1) { deltaw = softthreshold(deltaw) } : If we have soft-thresholding on, apply it.\n"
  "        adjustweight(deltaw) : Adjust the weight.\n"
  "        if (verbose > 1) {\n"
  "        printf(\"anti-Hebbian STDP event: t = %f ms; deltaw = %f\\n\",t,deltaw) } : Show weight update information if debugging on.\n"
  "        }\n"
  "\n"
  "\n"
  "    : If we receive a non-negative weight value, we are receiving a pre-synaptic spike (and thus need to check for an anti-Hebbian event, since the post-synaptic weight must be earlier).\n"
  "    if (skip == 0) {\n"
  "        if (w >= 0) {\n"
  "            interval = tlastpost - t  : Get the interval; interval is negative\n"
  "            if  ((tlastpost > -1) && (-interval > 1.0)) { : If we had a post-synaptic spike and a non-zero interval...\n"
  "                if (STDPon == 1) { : If STDP learning is turned on...\n"
  "                    if (verbose > 1) {printf(\"net_send(1,1)\\n\")}\n"
  "                    net_send(1,1) : instead of updating weight directly, use net_send to check if simultaneous spike occurred (otherwise bug when using mpi)\n"
  "                }\n"
  "            }\n"
  "            tlastpre = t : Remember the current spike time for next NET_RECEIVE.\n"
  "\n"
  "        : Else, if we receive a negative weight value, we are receiving a post-synaptic spike (and thus need to check for a Hebbian event, since the pre-synaptic weight must be earlier).\n"
  "        } else {\n"
  "            interval = t - tlastpre : Get the interval; interval is positive\n"
  "            if  ((tlastpre > -1) && (interval > 1.0)) { : If we had a pre-synaptic spike and a non-zero interval...\n"
  "                if (STDPon == 1) { : If STDP learning is turned on...\n"
  "                    if (verbose > 1) {printf(\"net_send(1,-1)\\n\")}\n"
  "                    net_send(1,-1) : instead of updating weight directly, use net_send to check if simultaneous spike occurred (otherwise bug when using mpi)\n"
  "                }\n"
  "            }\n"
  "            tlastpost = t : Remember the current spike time for next NET_RECEIVE.\n"
  "        }\n"
  "    }\n"
  "    if (verbose > 1)  {\n"
  "        printf(\"t=%f (AFTER) tlaspre=%f, tlastpost=%f, flag=%f, w=%f, deltaw=%f \\n\",t,tlastpre, tlastpost,flag,w,deltaw) }\n"
  "}\n"
  ;
    hoc_reg_nmodl_filename(mech_type, nmodl_filename);
    hoc_reg_nmodl_text(mech_type, nmodl_file_text);
}
#endif
