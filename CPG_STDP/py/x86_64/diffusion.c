/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
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
 
#define nrn_init _nrn_init__diff3D
#define _nrn_initial _nrn_initial__diff3D
#define nrn_cur _nrn_cur__diff3D
#define _nrn_current _nrn_current__diff3D
#define nrn_jacob _nrn_jacob__diff3D
#define nrn_state _nrn_state__diff3D
#define _net_receive _net_receive__diff3D 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define nu _p[0]
#define nu_columnindex 0
#define alpha _p[1]
#define alpha_columnindex 1
#define Deff _p[2]
#define Deff_columnindex 2
#define c0cleft _p[3]
#define c0cleft_columnindex 3
#define rPSD _p[4]
#define rPSD_columnindex 4
#define meandist _p[5]
#define meandist_columnindex 5
#define Popeak _p[6]
#define Popeak_columnindex 6
#define includir _p[7]
#define includir_columnindex 7
#define incluspill _p[8]
#define incluspill_columnindex 8
#define h _p[9]
#define h_columnindex 9
#define tx1 _p[10]
#define tx1_columnindex 10
#define dir _p[11]
#define dir_columnindex 11
#define spill _p[12]
#define spill_columnindex 12
#define subs _p[13]
#define subs_columnindex 13
#define Podir _p[14]
#define Podir_columnindex 14
#define Pospill _p[15]
#define Pospill_columnindex 15
#define v _p[16]
#define v_columnindex 16
#define _g _p[17]
#define _g_columnindex 17
#define _tsav _p[18]
#define _tsav_columnindex 18
#define _nd_area  *_ppvar[0]._pval
 
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
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
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
 _extcall_prop = _prop;
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
#define a a_diff3D
 double a = 0.02;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "a_diff3D", "um",
 "nu", "/um2",
 "Deff", "um2/ms",
 "c0cleft", "uM",
 "rPSD", "um",
 "meandist", "um",
 "h", "um",
 "tx1", "ms",
 "dir", "uM",
 "spill", "uM",
 "subs", "uM",
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "a_diff3D", &a_diff3D,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
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
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 19, _prop);
 	/*initialize range parameters*/
 	nu = 1;
 	alpha = 5;
 	Deff = 0.2;
 	c0cleft = 1;
 	rPSD = 0.28;
 	meandist = 0.29;
 	Popeak = 0.6;
 	includir = 1;
 	incluspill = 1;
 	h = 0;
 	tx1 = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 19;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 2, _prop);
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

 void _diffusion_reg() {
	int _vectorized = 1;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 1,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 19, 2);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 diff3D /home/max/PROJECTS/memristive-spinal-cord/memristive-spinal-cord/NEURON/second_layer/neuron+python/mod_files/diffusion.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double PI = 3.1415927;
static int _reset;
static char *modelname = "3D diffusion";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{  double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   _thread = (Datum*)0; _nt = (NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   tx1 = t ;
   } }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
 {
   subs = 0.0 ;
   dir = 0.0 ;
   spill = 0.0 ;
   }

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/max/PROJECTS/memristive-spinal-cord/memristive-spinal-cord/NEURON/second_layer/neuron+python/mod_files/diffusion.mod";
static const char* nmodl_file_text = 
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
#endif
