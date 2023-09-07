/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
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
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define wmax _p[0]
#define wmax_columnindex 0
#define aLTP _p[1]
#define aLTP_columnindex 1
#define aLTD _p[2]
#define aLTD_columnindex 2
#define interval _p[3]
#define interval_columnindex 3
#define tlast_pre _p[4]
#define tlast_pre_columnindex 4
#define tlast_post _p[5]
#define tlast_post_columnindex 5
#define M _p[6]
#define M_columnindex 6
#define P _p[7]
#define P_columnindex 7
#define deltaw _p[8]
#define deltaw_columnindex 8
#define _tsav _p[9]
#define _tsav_columnindex 9
#define _nd_area  *_ppvar[0]._pval
#define wsyn	*_ppvar[2]._pval
#define _p_wsyn	_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  2;
 /* external NEURON variables */
 /* declaration of user functions */
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
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
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 0, 0
};
 /* declare global and static user variables */
#define on on_StdwaSA
 double on = 1;
#define tauLTD tauLTD_StdwaSA
 double tauLTD = 20;
#define tauLTP tauLTP_StdwaSA
 double tauLTP = 20;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "tauLTP_StdwaSA", "ms",
 "tauLTD_StdwaSA", "ms",
 "interval", "ms",
 "tlast_pre", "ms",
 "tlast_post", "ms",
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "tauLTP_StdwaSA", &tauLTP_StdwaSA,
 "tauLTD_StdwaSA", &tauLTD_StdwaSA,
 "on_StdwaSA", &on_StdwaSA,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
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
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 10, _prop);
 	/*initialize range parameters*/
 	wmax = 1;
 	aLTP = 0.001;
 	aLTD = 0.00106;
  }
 	_prop->param = _p;
 	_prop->param_size = 10;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _stdwa_soft_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,(void*)0, (void*)0, (void*)0, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 10, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 StdwaSA /home/max/PROJECTS/memristive-spinal-cord/memristive-spinal-cord/NEURON/second_layer/neuron+python/mod_files/stdwa_soft.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
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

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel();
}}

static double _nrn_current(double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
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
static const char* nmodl_filename = "/home/max/PROJECTS/memristive-spinal-cord/memristive-spinal-cord/NEURON/second_layer/neuron+python/mod_files/stdwa_soft.mod";
static const char* nmodl_file_text = 
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
#endif
