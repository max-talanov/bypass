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
 
#define nrn_init _nrn_init__IaGenerator
#define _nrn_initial _nrn_initial__IaGenerator
#define nrn_cur _nrn_cur__IaGenerator
#define _nrn_current _nrn_current__IaGenerator
#define nrn_jacob _nrn_jacob__IaGenerator
#define nrn_state _nrn_state__IaGenerator
#define _net_receive _net_receive__IaGenerator 
#define event_time event_time__IaGenerator 
#define init_sequence init_sequence__IaGenerator 
#define seed seed__IaGenerator 
 
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
#define number _p[0]
#define number_columnindex 0
#define start _p[1]
#define start_columnindex 1
#define noise _p[2]
#define noise_columnindex 2
#define freq _p[3]
#define freq_columnindex 3
#define mean _p[4]
#define mean_columnindex 4
#define interval _p[5]
#define interval_columnindex 5
#define y _p[6]
#define y_columnindex 6
#define vel _p[7]
#define vel_columnindex 7
#define event _p[8]
#define event_columnindex 8
#define on _p[9]
#define on_columnindex 9
#define end _p[10]
#define end_columnindex 10
#define t0 _p[11]
#define t0_columnindex 11
#define v0 _p[12]
#define v0_columnindex 12
#define fhill0 _p[13]
#define fhill0_columnindex 13
#define len2 _p[14]
#define len2_columnindex 14
#define _tsav _p[15]
#define _tsav_columnindex 15
#define _nd_area  *_ppvar[0]._pval
#define fhill	*_ppvar[2]._pval
#define _p_fhill	_ppvar[2]._pval
#define fhill2	*_ppvar[3]._pval
#define _p_fhill2	_ppvar[3]._pval
 
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
 static double _hoc_event_time(void*);
 static double _hoc_init_sequence(void*);
 static double _hoc_invl(void*);
 static double _hoc_seed(void*);
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
 "event_time", _hoc_event_time,
 "init_sequence", _hoc_init_sequence,
 "invl", _hoc_invl,
 "seed", _hoc_seed,
 0, 0
};
#define invl invl_IaGenerator
 extern double invl( double );
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "interval", 1e-09, 1e+09,
 "noise", 0, 1,
 "number", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "start", "ms",
 "interval", "ms",
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
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
"IaGenerator",
 "number",
 "start",
 "noise",
 "freq",
 "mean",
 "interval",
 0,
 "y",
 "vel",
 0,
 0,
 "fhill",
 "fhill2",
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
 	_p = nrn_prop_data_alloc(_mechtype, 16, _prop);
 	/*initialize range parameters*/
 	number = 10;
 	start = 50;
 	noise = 0;
 	freq = 0;
 	mean = 1;
 	interval = 10;
  }
 	_prop->param = _p;
 	_prop->param_size = 16;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
 
#define _tqitem &(_ppvar[4]._pvoid)
 static void _net_receive(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _iagen_reg() {
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
  hoc_register_prop_size(_mechtype, 16, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "pointer");
  hoc_register_dparam_semantics(_mechtype, 3, "pointer");
  hoc_register_dparam_semantics(_mechtype, 4, "netsend");
 add_nrn_has_net_event(_mechtype);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 IaGenerator /home/yulia/bypass/CPG_STDP/py/mod_files/iagen.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int event_time(double);
static int init_sequence(double);
static int seed(double);
 
static int  seed (  double _lx ) {
   set_seed ( _lx ) ;
    return 0; }
 
static double _hoc_seed(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 seed (  *getarg(1) );
 return(_r);
}
 
static int  init_sequence (  double _lt ) {
   if ( number > 0.0 ) {
     on = 1.0 ;
     event = _lt ;
     end = _lt + 1e-6 + invl ( _threadargscomma_ _lt ) * ( number - 1.0 ) ;
     }
    return 0; }
 
static double _hoc_init_sequence(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 init_sequence (  *getarg(1) );
 return(_r);
}
 
double invl (  double _lt ) {
   double _linvl;
 len2 = 1.5 * fhill2 * ( _lt - t0 ) ;
   if ( fhill > fhill0 ) {
     vel = v0 + len2 + 0.15 * fhill * ( _lt - t0 ) * ( _lt - t0 ) ;
     if ( vel < 0.0 ) {
       vel = 1.0 ;
       }
     }
   else {
     vel = v0 - len2 - 0.4 * fhill * ( _lt - t0 ) * ( _lt - t0 ) ;
     if ( vel < 0.0 ) {
       vel = 1.0 ;
       }
     }
   v0 = vel ;
   fhill0 = fhill ;
   mean = 1000.0 / vel ;
   printf ( "time: %g, mean: %g \n" , _lt , mean ) ;
   t0 = _lt ;
   if ( noise  == 0.0 ) {
     _linvl = mean ;
     }
   else {
     _linvl = ( 1. - noise ) * mean + noise * mean * exprand ( 1.0 ) ;
     }
   
return _linvl;
 }
 
static double _hoc_invl(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r =  invl (  *getarg(1) );
 return(_r);
}
 
static int  event_time (  double _lt ) {
   if ( number > 0.0 ) {
     event = event + invl ( _threadargscomma_ _lt ) ;
     }
   if ( event > end ) {
     on = 0.0 ;
     }
    return 0; }
 
static double _hoc_event_time(void* _vptr) {
 double _r;
    _hoc_setdata(_vptr);
 _r = 1.;
 event_time (  *getarg(1) );
 return(_r);
}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
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
     event_time ( _threadargscomma_ t ) ;
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
   t0 = start ;
   v0 = 50.0 ;
   freq = 80.0 ;
   fhill0 = 0.0 ;
   interval = 1000.0 / freq ;
   if ( noise < 0.0 ) {
     noise = 0.0 ;
     }
   if ( noise > 1.0 ) {
     noise = 1.0 ;
     }
   if ( start >= 0.0  && number > 0.0 ) {
     event = start + invl ( _threadargscomma_ t ) ;
     net_send ( _tqitem, (double*)0, _ppvar[1]._pvoid, t +  event , 3.0 ) ;
     }
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
static const char* nmodl_filename = "/home/yulia/bypass/CPG_STDP/py/mod_files/iagen.mod";
static const char* nmodl_file_text = 
  "NEURON	{\n"
  "  POINT_PROCESS IaGenerator\n"
  "    POINTER fhill, fhill2\n"
  "  RANGE y\n"
  "  RANGE interval, number, start\n"
  "  RANGE noise, freq, mean, vel, invl\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	number	= 10 <0,1e9>	: number of spikes\n"
  "	start		= 50 (ms)	: start of first spike\n"
  "	noise		= 0 <0,1>	: amount of randomeaness (0.0 - 1.0)\n"
  "	freq\n"
  "  mean = 1\n"
  "	interval	= 10 (ms) <1e-9,1e9>: time between spikes (msec)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	y\n"
  "	event (ms)\n"
  "	on\n"
  "	end (ms)\n"
  "  t0\n"
  "  v0\n"
  "  fhill\n"
  "  vel\n"
  "  fhill0\n"
  "  fhill2\n"
  "  len2\n"
  "}\n"
  "\n"
  "PROCEDURE seed(x) {\n"
  "	set_seed(x)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	on = 0\n"
  "	y = 0\n"
  "  t0 = start\n"
  "  v0 = 50\n"
  "  freq = 80\n"
  "  fhill0 = 0\n"
  "	interval = 1000/freq\n"
  "	if (noise < 0) {\n"
  "		noise = 0\n"
  "	}\n"
  "	if (noise > 1) {\n"
  "		noise = 1\n"
  "	}\n"
  "	if (start >= 0 && number > 0) {\n"
  "		: randomize the first spike so on average it occurs at start+interval\n"
  "		event = start + invl(t)\n"
  "		net_send(event, 3)\n"
  "	}\n"
  "}\n"
  "\n"
  "PROCEDURE init_sequence(t(ms)) {\n"
  "	if (number > 0) {\n"
  "		on = 1\n"
  "		event = t\n"
  "		end = t + 1e-6 + invl(t)*(number-1)\n"
  "	}\n"
  "}\n"
  "\n"
  "FUNCTION invl(t (ms)) (ms) {\n"
  "  len2 = 1.5*fhill2*(t-t0)\n"
  "  if (fhill > fhill0){\n"
  "    vel = v0 + len2 + 0.15*fhill*(t-t0)*(t-t0)\n"
  "    if (vel < 0){vel = 1}\n"
  "  }else{\n"
  "    vel = v0 - len2 - 0.4*fhill*(t-t0)*(t-t0)\n"
  "    if (vel < 0){vel = 1}\n"
  "  }\n"
  "  v0 = vel\n"
  "  fhill0 = fhill\n"
  "  mean = 1000/vel\n"
  "  printf(\"time: %g, mean: %g \\n\", t, mean)\n"
  "\n"
  "  t0 = t\n"
  "	if (noise == 0) {\n"
  "		invl = mean\n"
  "	}else{\n"
  "		invl = (1. - noise)*mean + noise*mean*exprand(1)\n"
  "	}\n"
  "}\n"
  "\n"
  "PROCEDURE event_time(t (ms)) {\n"
  "	if (number > 0) {\n"
  "		event = event + invl(t)\n"
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
  "		event_time(t)\n"
  "		if (on == 1) {\n"
  "			net_send(event - t, 1)\n"
  "		}\n"
  "		net_send(.1, 2)\n"
  "	}\n"
  "	if (flag == 2) {\n"
  "		y = 0\n"
  "	}\n"
  "}\n"
  ;
#endif
