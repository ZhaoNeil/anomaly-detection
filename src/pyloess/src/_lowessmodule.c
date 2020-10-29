/* File: _lowessmodule.c
 * This file is auto-generated with f2py (version:2).
 * f2py is a Fortran to Python Interface Generator (FPIG), Second Edition,
 * written by Pearu Peterson <pearu@cens.ioc.ee>.
 * Generation date: Tue Oct 27 18:02:38 2020
 * Do not edit this file directly unless you know what you are doing!!!
 */

#ifdef __cplusplus
extern "C" {
#endif

/*********************** See f2py2e/cfuncs.py: includes ***********************/
#include "Python.h"
#include <stdarg.h>
#include "fortranobject.h"
#include <math.h>

/**************** See f2py2e/rules.py: mod_rules['modulebody'] ****************/
static PyObject *_lowess_error;
static PyObject *_lowess_module;

/*********************** See f2py2e/cfuncs.py: typedefs ***********************/
/*need_typedefs*/

/****************** See f2py2e/cfuncs.py: typedefs_generated ******************/
/*need_typedefs_generated*/

/********************** See f2py2e/cfuncs.py: cppmacros **********************/
#if defined(PREPEND_FORTRAN)
#if defined(NO_APPEND_FORTRAN)
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) _##F
#else
#define F_FUNC(f,F) _##f
#endif
#else
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) _##F##_
#else
#define F_FUNC(f,F) _##f##_
#endif
#endif
#else
#if defined(NO_APPEND_FORTRAN)
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) F
#else
#define F_FUNC(f,F) f
#endif
#else
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) F##_
#else
#define F_FUNC(f,F) f##_
#endif
#endif
#endif
#if defined(UNDERSCORE_G77)
#define F_FUNC_US(f,F) F_FUNC(f##_,F##_)
#else
#define F_FUNC_US(f,F) F_FUNC(f,F)
#endif

#define rank(var) var ## _Rank
#define shape(var,dim) var ## _Dims[dim]
#define old_rank(var) (PyArray_NDIM((PyArrayObject *)(capi_ ## var ## _tmp)))
#define old_shape(var,dim) PyArray_DIM(((PyArrayObject *)(capi_ ## var ## _tmp)),dim)
#define fshape(var,dim) shape(var,rank(var)-dim-1)
#define len(var) shape(var,0)
#define flen(var) fshape(var,0)
#define old_size(var) PyArray_SIZE((PyArrayObject *)(capi_ ## var ## _tmp))
/* #define index(i) capi_i ## i */
#define slen(var) capi_ ## var ## _len
#define size(var, ...) f2py_size((PyArrayObject *)(capi_ ## var ## _tmp), ## __VA_ARGS__, -1)

#define CHECKSCALAR(check,tcheck,name,show,var)\
    if (!(check)) {\
        char errstring[256];\
        sprintf(errstring, "%s: "show, "("tcheck") failed for "name, var);\
        PyErr_SetString(_lowess_error,errstring);\
        /*goto capi_fail;*/\
    } else 
#ifdef DEBUGCFUNCS
#define CFUNCSMESS(mess) fprintf(stderr,"debug-capi:"mess);
#define CFUNCSMESSPY(mess,obj) CFUNCSMESS(mess) \
    PyObject_Print((PyObject *)obj,stderr,Py_PRINT_RAW);\
    fprintf(stderr,"\n");
#else
#define CFUNCSMESS(mess)
#define CFUNCSMESSPY(mess,obj)
#endif

#ifndef max
#define max(a,b) ((a > b) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a > b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a < b) ? (a) : (b))
#endif


/************************ See f2py2e/cfuncs.py: cfuncs ************************/
static int f2py_size(PyArrayObject* var, ...)
{
  npy_int sz = 0;
  npy_int dim;
  npy_int rank;
  va_list argp;
  va_start(argp, var);
  dim = va_arg(argp, npy_int);
  if (dim==-1)
    {
      sz = PyArray_SIZE(var);
    }
  else
    {
      rank = PyArray_NDIM(var);
      if (dim>=1 && dim<=rank)
        sz = PyArray_DIM(var, dim-1);
      else
        fprintf(stderr, "f2py_size: 2nd argument value=%d fails to satisfy 1<=value<=%d. Result will be 0.\n", dim, rank);
    }
  va_end(argp);
  return sz;
}

static int double_from_pyobj(double* v,PyObject *obj,const char *errmess) {
    PyObject* tmp = NULL;
    if (PyFloat_Check(obj)) {
#ifdef __sgi
        *v = PyFloat_AsDouble(obj);
#else
        *v = PyFloat_AS_DOUBLE(obj);
#endif
        return 1;
    }
    tmp = PyNumber_Float(obj);
    if (tmp) {
#ifdef __sgi
        *v = PyFloat_AsDouble(tmp);
#else
        *v = PyFloat_AS_DOUBLE(tmp);
#endif
        Py_DECREF(tmp);
        return 1;
    }
    if (PyComplex_Check(obj))
        tmp = PyObject_GetAttrString(obj,"real");
    else if (PyString_Check(obj) || PyUnicode_Check(obj))
        /*pass*/;
    else if (PySequence_Check(obj))
        tmp = PySequence_GetItem(obj,0);
    if (tmp) {
        PyErr_Clear();
        if (double_from_pyobj(v,tmp,errmess)) {Py_DECREF(tmp); return 1;}
        Py_DECREF(tmp);
    }
    {
        PyObject* err = PyErr_Occurred();
        if (err==NULL) err = _lowess_error;
        PyErr_SetString(err,errmess);
    }
    return 0;
}

static int int_from_pyobj(int* v,PyObject *obj,const char *errmess) {
    PyObject* tmp = NULL;
    if (PyInt_Check(obj)) {
        *v = (int)PyInt_AS_LONG(obj);
        return 1;
    }
    tmp = PyNumber_Int(obj);
    if (tmp) {
        *v = PyInt_AS_LONG(tmp);
        Py_DECREF(tmp);
        return 1;
    }
    if (PyComplex_Check(obj))
        tmp = PyObject_GetAttrString(obj,"real");
    else if (PyString_Check(obj) || PyUnicode_Check(obj))
        /*pass*/;
    else if (PySequence_Check(obj))
        tmp = PySequence_GetItem(obj,0);
    if (tmp) {
        PyErr_Clear();
        if (int_from_pyobj(v,tmp,errmess)) {Py_DECREF(tmp); return 1;}
        Py_DECREF(tmp);
    }
    {
        PyObject* err = PyErr_Occurred();
        if (err==NULL) err = _lowess_error;
        PyErr_SetString(err,errmess);
    }
    return 0;
}


/********************* See f2py2e/cfuncs.py: userincludes *********************/
/*need_userincludes*/

/********************* See f2py2e/capi_rules.py: usercode *********************/


/* See f2py2e/rules.py */
extern void F_FUNC(lowess,LOWESS)(double*,double*,int*,double*,int*,double*,double*,double*,double*);
extern void F_FUNC(lowest,LOWEST)(double*,double*,int*,double*,double*,int*,int*,double*,int*,double*,int*);
extern void F_FUNC(ssort,SSORT)(float*,int*);
/*eof externroutines*/

/******************** See f2py2e/capi_rules.py: usercode1 ********************/


/******************* See f2py2e/cb_rules.py: buildcallback *******************/
/*need_callbacks*/

/*********************** See f2py2e/rules.py: buildapi ***********************/

/*********************************** lowess ***********************************/
static char doc_f2py_rout__lowess_lowess[] = "\
ys,rw,res = lowess(x,y,f,nsteps,delta,[n])\n\nWrapper for ``lowess``.\
\n\nParameters\n----------\n"
"x : input rank-1 array('d') with bounds (n)\n"
"y : input rank-1 array('d') with bounds (n)\n"
"f : input float\n"
"nsteps : input int\n"
"delta : input float\n"
"\nOther Parameters\n----------------\n"
"n : input int, optional\n    Default: len(x)\n"
"\nReturns\n-------\n"
"ys : rank-1 array('d') with bounds (n)\n"
"rw : rank-1 array('d') with bounds (n)\n"
"res : rank-1 array('d') with bounds (n)";
/* extern void F_FUNC(lowess,LOWESS)(double*,double*,int*,double*,int*,double*,double*,double*,double*); */
static PyObject *f2py_rout__lowess_lowess(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(double*,double*,int*,double*,int*,double*,double*,double*,double*)) {
  PyObject * volatile capi_buildvalue = NULL;
  volatile int f2py_success = 1;
/*decl*/

  double *x = NULL;
  npy_intp x_Dims[1] = {-1};
  const int x_Rank = 1;
  PyArrayObject *capi_x_tmp = NULL;
  int capi_x_intent = 0;
  PyObject *x_capi = Py_None;
  double *y = NULL;
  npy_intp y_Dims[1] = {-1};
  const int y_Rank = 1;
  PyArrayObject *capi_y_tmp = NULL;
  int capi_y_intent = 0;
  PyObject *y_capi = Py_None;
  int n = 0;
  PyObject *n_capi = Py_None;
  double f = 0;
  PyObject *f_capi = Py_None;
  int nsteps = 0;
  PyObject *nsteps_capi = Py_None;
  double delta = 0;
  PyObject *delta_capi = Py_None;
  double *ys = NULL;
  npy_intp ys_Dims[1] = {-1};
  const int ys_Rank = 1;
  PyArrayObject *capi_ys_tmp = NULL;
  int capi_ys_intent = 0;
  double *rw = NULL;
  npy_intp rw_Dims[1] = {-1};
  const int rw_Rank = 1;
  PyArrayObject *capi_rw_tmp = NULL;
  int capi_rw_intent = 0;
  double *res = NULL;
  npy_intp res_Dims[1] = {-1};
  const int res_Rank = 1;
  PyArrayObject *capi_res_tmp = NULL;
  int capi_res_intent = 0;
  static char *capi_kwlist[] = {"x","y","f","nsteps","delta","n",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
  if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
    "OOOOO|O:_lowess.lowess",\
    capi_kwlist,&x_capi,&y_capi,&f_capi,&nsteps_capi,&delta_capi,&n_capi))
    return NULL;
/*frompyobj*/
  /* Processing variable x */
  ;
  capi_x_intent |= F2PY_INTENT_IN;
  capi_x_tmp = array_from_pyobj(NPY_DOUBLE,x_Dims,x_Rank,capi_x_intent,x_capi);
  if (capi_x_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting 1st argument `x' of _lowess.lowess to C/Fortran array" );
  } else {
    x = (double *)(PyArray_DATA(capi_x_tmp));

  /* Processing variable f */
    f2py_success = double_from_pyobj(&f,f_capi,"_lowess.lowess() 3rd argument (f) can't be converted to double");
  if (f2py_success) {
  /* Processing variable nsteps */
    f2py_success = int_from_pyobj(&nsteps,nsteps_capi,"_lowess.lowess() 4th argument (nsteps) can't be converted to int");
  if (f2py_success) {
  /* Processing variable delta */
    f2py_success = double_from_pyobj(&delta,delta_capi,"_lowess.lowess() 5th argument (delta) can't be converted to double");
  if (f2py_success) {
  /* Processing variable n */
  if (n_capi == Py_None) n = len(x); else
    f2py_success = int_from_pyobj(&n,n_capi,"_lowess.lowess() 1st keyword (n) can't be converted to int");
  if (f2py_success) {
  CHECKSCALAR(len(x)>=n,"len(x)>=n","1st keyword n","lowess:n=%d",n) {
  /* Processing variable ys */
  ys_Dims[0]=n;
  capi_ys_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_ys_tmp = array_from_pyobj(NPY_DOUBLE,ys_Dims,ys_Rank,capi_ys_intent,Py_None);
  if (capi_ys_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting hidden `ys' of _lowess.lowess to C/Fortran array" );
  } else {
    ys = (double *)(PyArray_DATA(capi_ys_tmp));

  /* Processing variable rw */
  rw_Dims[0]=n;
  capi_rw_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_rw_tmp = array_from_pyobj(NPY_DOUBLE,rw_Dims,rw_Rank,capi_rw_intent,Py_None);
  if (capi_rw_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting hidden `rw' of _lowess.lowess to C/Fortran array" );
  } else {
    rw = (double *)(PyArray_DATA(capi_rw_tmp));

  /* Processing variable res */
  res_Dims[0]=n;
  capi_res_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_res_tmp = array_from_pyobj(NPY_DOUBLE,res_Dims,res_Rank,capi_res_intent,Py_None);
  if (capi_res_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting hidden `res' of _lowess.lowess to C/Fortran array" );
  } else {
    res = (double *)(PyArray_DATA(capi_res_tmp));

  /* Processing variable y */
  y_Dims[0]=n;
  capi_y_intent |= F2PY_INTENT_IN;
  capi_y_tmp = array_from_pyobj(NPY_DOUBLE,y_Dims,y_Rank,capi_y_intent,y_capi);
  if (capi_y_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting 2nd argument `y' of _lowess.lowess to C/Fortran array" );
  } else {
    y = (double *)(PyArray_DATA(capi_y_tmp));

/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(x,y,&n,&f,&nsteps,&delta,ys,rw,res);
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
    if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
    CFUNCSMESS("Building return value.\n");
    capi_buildvalue = Py_BuildValue("NNN",capi_ys_tmp,capi_rw_tmp,capi_res_tmp);
/*closepyobjfrom*/
/*end of closepyobjfrom*/
    } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  if((PyObject *)capi_y_tmp!=y_capi) {
    Py_XDECREF(capi_y_tmp); }
  }  /*if (capi_y_tmp == NULL) ... else of y*/
  /* End of cleaning variable y */
  }  /*if (capi_res_tmp == NULL) ... else of res*/
  /* End of cleaning variable res */
  }  /*if (capi_rw_tmp == NULL) ... else of rw*/
  /* End of cleaning variable rw */
  }  /*if (capi_ys_tmp == NULL) ... else of ys*/
  /* End of cleaning variable ys */
  } /*CHECKSCALAR(len(x)>=n)*/
  } /*if (f2py_success) of n*/
  /* End of cleaning variable n */
  } /*if (f2py_success) of delta*/
  /* End of cleaning variable delta */
  } /*if (f2py_success) of nsteps*/
  /* End of cleaning variable nsteps */
  } /*if (f2py_success) of f*/
  /* End of cleaning variable f */
  if((PyObject *)capi_x_tmp!=x_capi) {
    Py_XDECREF(capi_x_tmp); }
  }  /*if (capi_x_tmp == NULL) ... else of x*/
  /* End of cleaning variable x */
/*end of cleanupfrompyobj*/
  if (capi_buildvalue == NULL) {
/*routdebugfailure*/
  } else {
/*routdebugleave*/
  }
  CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
  return capi_buildvalue;
}
/******************************* end of lowess *******************************/

/*********************************** lowest ***********************************/
static char doc_f2py_rout__lowess_lowest[] = "\
lowest(x,y,xs,ys,nleft,nright,w,userw,rw,ok,[n])\n\nWrapper for ``lowest``.\
\n\nParameters\n----------\n"
"x : input rank-1 array('d') with bounds (n)\n"
"y : input rank-1 array('d') with bounds (n)\n"
"xs : input float\n"
"ys : input float\n"
"nleft : input int\n"
"nright : input int\n"
"w : input rank-1 array('d') with bounds (n)\n"
"userw : input int\n"
"rw : input rank-1 array('d') with bounds (n)\n"
"ok : input int\n"
"\nOther Parameters\n----------------\n"
"n : input int, optional\n    Default: len(x)";
/* extern void F_FUNC(lowest,LOWEST)(double*,double*,int*,double*,double*,int*,int*,double*,int*,double*,int*); */
static PyObject *f2py_rout__lowess_lowest(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(double*,double*,int*,double*,double*,int*,int*,double*,int*,double*,int*)) {
  PyObject * volatile capi_buildvalue = NULL;
  volatile int f2py_success = 1;
/*decl*/

  double *x = NULL;
  npy_intp x_Dims[1] = {-1};
  const int x_Rank = 1;
  PyArrayObject *capi_x_tmp = NULL;
  int capi_x_intent = 0;
  PyObject *x_capi = Py_None;
  double *y = NULL;
  npy_intp y_Dims[1] = {-1};
  const int y_Rank = 1;
  PyArrayObject *capi_y_tmp = NULL;
  int capi_y_intent = 0;
  PyObject *y_capi = Py_None;
  int n = 0;
  PyObject *n_capi = Py_None;
  double xs = 0;
  PyObject *xs_capi = Py_None;
  double ys = 0;
  PyObject *ys_capi = Py_None;
  int nleft = 0;
  PyObject *nleft_capi = Py_None;
  int nright = 0;
  PyObject *nright_capi = Py_None;
  double *w = NULL;
  npy_intp w_Dims[1] = {-1};
  const int w_Rank = 1;
  PyArrayObject *capi_w_tmp = NULL;
  int capi_w_intent = 0;
  PyObject *w_capi = Py_None;
  int userw = 0;
  PyObject *userw_capi = Py_None;
  double *rw = NULL;
  npy_intp rw_Dims[1] = {-1};
  const int rw_Rank = 1;
  PyArrayObject *capi_rw_tmp = NULL;
  int capi_rw_intent = 0;
  PyObject *rw_capi = Py_None;
  int ok = 0;
  PyObject *ok_capi = Py_None;
  static char *capi_kwlist[] = {"x","y","xs","ys","nleft","nright","w","userw","rw","ok","n",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
  if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
    "OOOOOOOOOO|O:_lowess.lowest",\
    capi_kwlist,&x_capi,&y_capi,&xs_capi,&ys_capi,&nleft_capi,&nright_capi,&w_capi,&userw_capi,&rw_capi,&ok_capi,&n_capi))
    return NULL;
/*frompyobj*/
  /* Processing variable x */
  ;
  capi_x_intent |= F2PY_INTENT_IN;
  capi_x_tmp = array_from_pyobj(NPY_DOUBLE,x_Dims,x_Rank,capi_x_intent,x_capi);
  if (capi_x_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting 1st argument `x' of _lowess.lowest to C/Fortran array" );
  } else {
    x = (double *)(PyArray_DATA(capi_x_tmp));

  /* Processing variable xs */
    f2py_success = double_from_pyobj(&xs,xs_capi,"_lowess.lowest() 3rd argument (xs) can't be converted to double");
  if (f2py_success) {
  /* Processing variable ys */
    f2py_success = double_from_pyobj(&ys,ys_capi,"_lowess.lowest() 4th argument (ys) can't be converted to double");
  if (f2py_success) {
  /* Processing variable nleft */
    f2py_success = int_from_pyobj(&nleft,nleft_capi,"_lowess.lowest() 5th argument (nleft) can't be converted to int");
  if (f2py_success) {
  /* Processing variable nright */
    f2py_success = int_from_pyobj(&nright,nright_capi,"_lowess.lowest() 6th argument (nright) can't be converted to int");
  if (f2py_success) {
  /* Processing variable userw */
    userw = (int)PyObject_IsTrue(userw_capi);
    f2py_success = 1;
  if (f2py_success) {
  /* Processing variable ok */
    ok = (int)PyObject_IsTrue(ok_capi);
    f2py_success = 1;
  if (f2py_success) {
  /* Processing variable n */
  if (n_capi == Py_None) n = len(x); else
    f2py_success = int_from_pyobj(&n,n_capi,"_lowess.lowest() 1st keyword (n) can't be converted to int");
  if (f2py_success) {
  CHECKSCALAR(len(x)>=n,"len(x)>=n","1st keyword n","lowest:n=%d",n) {
  /* Processing variable w */
  w_Dims[0]=n;
  capi_w_intent |= F2PY_INTENT_IN;
  capi_w_tmp = array_from_pyobj(NPY_DOUBLE,w_Dims,w_Rank,capi_w_intent,w_capi);
  if (capi_w_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting 7th argument `w' of _lowess.lowest to C/Fortran array" );
  } else {
    w = (double *)(PyArray_DATA(capi_w_tmp));

  /* Processing variable rw */
  rw_Dims[0]=n;
  capi_rw_intent |= F2PY_INTENT_IN;
  capi_rw_tmp = array_from_pyobj(NPY_DOUBLE,rw_Dims,rw_Rank,capi_rw_intent,rw_capi);
  if (capi_rw_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting 9th argument `rw' of _lowess.lowest to C/Fortran array" );
  } else {
    rw = (double *)(PyArray_DATA(capi_rw_tmp));

  /* Processing variable y */
  y_Dims[0]=n;
  capi_y_intent |= F2PY_INTENT_IN;
  capi_y_tmp = array_from_pyobj(NPY_DOUBLE,y_Dims,y_Rank,capi_y_intent,y_capi);
  if (capi_y_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting 2nd argument `y' of _lowess.lowest to C/Fortran array" );
  } else {
    y = (double *)(PyArray_DATA(capi_y_tmp));

/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(x,y,&n,&xs,&ys,&nleft,&nright,w,&userw,rw,&ok);
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
    if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
    CFUNCSMESS("Building return value.\n");
    capi_buildvalue = Py_BuildValue("");
/*closepyobjfrom*/
/*end of closepyobjfrom*/
    } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  if((PyObject *)capi_y_tmp!=y_capi) {
    Py_XDECREF(capi_y_tmp); }
  }  /*if (capi_y_tmp == NULL) ... else of y*/
  /* End of cleaning variable y */
  if((PyObject *)capi_rw_tmp!=rw_capi) {
    Py_XDECREF(capi_rw_tmp); }
  }  /*if (capi_rw_tmp == NULL) ... else of rw*/
  /* End of cleaning variable rw */
  if((PyObject *)capi_w_tmp!=w_capi) {
    Py_XDECREF(capi_w_tmp); }
  }  /*if (capi_w_tmp == NULL) ... else of w*/
  /* End of cleaning variable w */
  } /*CHECKSCALAR(len(x)>=n)*/
  } /*if (f2py_success) of n*/
  /* End of cleaning variable n */
  } /*if (f2py_success) of ok*/
  /* End of cleaning variable ok */
  } /*if (f2py_success) of userw*/
  /* End of cleaning variable userw */
  } /*if (f2py_success) of nright*/
  /* End of cleaning variable nright */
  } /*if (f2py_success) of nleft*/
  /* End of cleaning variable nleft */
  } /*if (f2py_success) of ys*/
  /* End of cleaning variable ys */
  } /*if (f2py_success) of xs*/
  /* End of cleaning variable xs */
  if((PyObject *)capi_x_tmp!=x_capi) {
    Py_XDECREF(capi_x_tmp); }
  }  /*if (capi_x_tmp == NULL) ... else of x*/
  /* End of cleaning variable x */
/*end of cleanupfrompyobj*/
  if (capi_buildvalue == NULL) {
/*routdebugfailure*/
  } else {
/*routdebugleave*/
  }
  CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
  return capi_buildvalue;
}
/******************************* end of lowest *******************************/

/*********************************** ssort ***********************************/
static char doc_f2py_rout__lowess_ssort[] = "\
ssort(a,[n])\n\nWrapper for ``ssort``.\
\n\nParameters\n----------\n"
"a : input rank-1 array('f') with bounds (n)\n"
"\nOther Parameters\n----------------\n"
"n : input int, optional\n    Default: len(a)";
/* extern void F_FUNC(ssort,SSORT)(float*,int*); */
static PyObject *f2py_rout__lowess_ssort(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(float*,int*)) {
  PyObject * volatile capi_buildvalue = NULL;
  volatile int f2py_success = 1;
/*decl*/

  float *a = NULL;
  npy_intp a_Dims[1] = {-1};
  const int a_Rank = 1;
  PyArrayObject *capi_a_tmp = NULL;
  int capi_a_intent = 0;
  PyObject *a_capi = Py_None;
  int n = 0;
  PyObject *n_capi = Py_None;
  static char *capi_kwlist[] = {"a","n",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
  if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
    "O|O:_lowess.ssort",\
    capi_kwlist,&a_capi,&n_capi))
    return NULL;
/*frompyobj*/
  /* Processing variable a */
  ;
  capi_a_intent |= F2PY_INTENT_IN;
  capi_a_tmp = array_from_pyobj(NPY_FLOAT,a_Dims,a_Rank,capi_a_intent,a_capi);
  if (capi_a_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lowess_error,"failed in converting 1st argument `a' of _lowess.ssort to C/Fortran array" );
  } else {
    a = (float *)(PyArray_DATA(capi_a_tmp));

  /* Processing variable n */
  if (n_capi == Py_None) n = len(a); else
    f2py_success = int_from_pyobj(&n,n_capi,"_lowess.ssort() 1st keyword (n) can't be converted to int");
  if (f2py_success) {
  CHECKSCALAR(len(a)>=n,"len(a)>=n","1st keyword n","ssort:n=%d",n) {
/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(a,&n);
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
    if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
    CFUNCSMESS("Building return value.\n");
    capi_buildvalue = Py_BuildValue("");
/*closepyobjfrom*/
/*end of closepyobjfrom*/
    } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  } /*CHECKSCALAR(len(a)>=n)*/
  } /*if (f2py_success) of n*/
  /* End of cleaning variable n */
  if((PyObject *)capi_a_tmp!=a_capi) {
    Py_XDECREF(capi_a_tmp); }
  }  /*if (capi_a_tmp == NULL) ... else of a*/
  /* End of cleaning variable a */
/*end of cleanupfrompyobj*/
  if (capi_buildvalue == NULL) {
/*routdebugfailure*/
  } else {
/*routdebugleave*/
  }
  CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
  return capi_buildvalue;
}
/******************************** end of ssort ********************************/
/*eof body*/

/******************* See f2py2e/f90mod_rules.py: buildhooks *******************/
/*need_f90modhooks*/

/************** See f2py2e/rules.py: module_rules['modulebody'] **************/

/******************* See f2py2e/common_rules.py: buildhooks *******************/

/*need_commonhooks*/

/**************************** See f2py2e/rules.py ****************************/

static FortranDataDef f2py_routine_defs[] = {
  {"lowess",-1,{{-1}},0,(char *)F_FUNC(lowess,LOWESS),(f2py_init_func)f2py_rout__lowess_lowess,doc_f2py_rout__lowess_lowess},
  {"lowest",-1,{{-1}},0,(char *)F_FUNC(lowest,LOWEST),(f2py_init_func)f2py_rout__lowess_lowest,doc_f2py_rout__lowess_lowest},
  {"ssort",-1,{{-1}},0,(char *)F_FUNC(ssort,SSORT),(f2py_init_func)f2py_rout__lowess_ssort,doc_f2py_rout__lowess_ssort},

/*eof routine_defs*/
  {NULL}
};

static PyMethodDef f2py_module_methods[] = {

  {NULL,NULL}
};

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "_lowess",
  NULL,
  -1,
  f2py_module_methods,
  NULL,
  NULL,
  NULL,
  NULL
};
#endif

#if PY_VERSION_HEX >= 0x03000000
#define RETVAL m
PyMODINIT_FUNC PyInit__lowess(void) {
#else
#define RETVAL
PyMODINIT_FUNC init_lowess(void) {
#endif
  int i;
  PyObject *m,*d, *s, *tmp;
#if PY_VERSION_HEX >= 0x03000000
  m = _lowess_module = PyModule_Create(&moduledef);
#else
  m = _lowess_module = Py_InitModule("_lowess", f2py_module_methods);
#endif
  Py_TYPE(&PyFortran_Type) = &PyType_Type;
  import_array();
  if (PyErr_Occurred())
    {PyErr_SetString(PyExc_ImportError, "can't initialize module _lowess (failed to import numpy)"); return RETVAL;}
  d = PyModule_GetDict(m);
  s = PyString_FromString("$Revision: $");
  PyDict_SetItemString(d, "__version__", s);
  Py_DECREF(s);
#if PY_VERSION_HEX >= 0x03000000
  s = PyUnicode_FromString(
#else
  s = PyString_FromString(
#endif
    "This module '_lowess' is auto-generated with f2py (version:2).\nFunctions:\n"
"  ys,rw,res = lowess(x,y,f,nsteps,delta,n=len(x))\n"
"  lowest(x,y,xs,ys,nleft,nright,w,userw,rw,ok,n=len(x))\n"
"  ssort(a,n=len(a))\n"
".");
  PyDict_SetItemString(d, "__doc__", s);
  Py_DECREF(s);
  _lowess_error = PyErr_NewException ("_lowess.error", NULL, NULL);
  /*
   * Store the error object inside the dict, so that it could get deallocated.
   * (in practice, this is a module, so it likely will not and cannot.)
   */
  PyDict_SetItemString(d, "__lowess_error", _lowess_error);
  Py_DECREF(_lowess_error);
  for(i=0;f2py_routine_defs[i].name!=NULL;i++) {
    tmp = PyFortranObject_NewAsAttr(&f2py_routine_defs[i]);
    PyDict_SetItemString(d, f2py_routine_defs[i].name, tmp);
    Py_DECREF(tmp);
  }



/*eof initf2pywraphooks*/
/*eof initf90modhooks*/

/*eof initcommonhooks*/


#ifdef F2PY_REPORT_ATEXIT
  if (! PyErr_Occurred())
    on_exit(f2py_report_on_exit,(void*)"_lowess");
#endif
  return RETVAL;
}
#ifdef __cplusplus
}
#endif
