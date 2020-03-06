#include <Python.h>
#include <stdlib.h>
#include "api.h"

#if defined(_MSC_VER)
# include <malloc.h>   /* for alloca() */
#else
# include <stdint.h>
# if (defined (__SVR4) && defined (__sun)) || defined(_AIX) || defined(__hpux)
#  include <alloca.h>
# endif
#endif


static PyModuleDef empty_moduledef = {
    PyModuleDef_HEAD_INIT
};

// this malloc a result which will never be freed. Too bad
static PyMethodDef *
create_method_defs(HPyModuleDef *hpydef)
{
    // count the methods
    Py_ssize_t count;
    if (hpydef->m_methods == NULL) {
        count = 0;
    }
    else {
        count = 0;
        while (hpydef->m_methods[count].ml_name != NULL)
            count++;
    }

    // allocate&fill the result
    PyMethodDef *result = PyMem_Malloc(sizeof(PyMethodDef) * (count+1));
    if (result == NULL) {
        PyErr_NoMemory();
        return NULL;
    }
    for(int i=0; i<count; i++) {
        HPyMethodDef *src = &hpydef->m_methods[i];
        PyMethodDef *dst = &result[i];
        dst->ml_name = src->ml_name;
        dst->ml_doc = src->ml_doc;

        if (src->ml_flags & _HPy_METH) {
            // HPy function: cal ml_meth to get pointers to the impl_func and
            // the cpy trampoline
            void *impl_func;
            PyCFunction trampoline_func;
            src->ml_meth(&impl_func, &trampoline_func);
            dst->ml_meth = (PyCFunction)trampoline_func;
            dst->ml_flags = src->ml_flags & ~_HPy_METH;
        }
        else {
            // legacy function: ml_meth already contains a function pointer
            // with the correct CPython signature
            dst->ml_meth = (PyCFunction)src->ml_meth;
            dst->ml_flags = src->ml_flags;
        }
    }
    result[count] = (PyMethodDef){NULL, NULL, 0, NULL};
    return result;
}


static HPy
ctx_Module_Create(HPyContext ctx, HPyModuleDef *hpydef)
{
    // create a new PyModuleDef

    // we can't free this memory because it is stitched into moduleobject. We
    // just make it immortal for now, eventually we should think whether or
    // not to free it if/when we unload the module
    PyModuleDef *def = PyMem_Malloc(sizeof(PyModuleDef));
    if (def == NULL) {
        PyErr_NoMemory();
        return HPy_NULL;
    }
    memcpy(def, &empty_moduledef, sizeof(PyModuleDef));
    def->m_name = hpydef->m_name;
    def->m_doc = hpydef->m_doc;
    def->m_size = hpydef->m_size;
    def->m_methods = create_method_defs(hpydef);
    if (def->m_methods == NULL)
        return HPy_NULL;
    PyObject *result = PyModule_Create(def);
    return _py2h(result);
}

/* HPy object protocol */

static HPy
ctx_GetAttr(HPyContext ctx, HPy obj, HPy name) {
  return _py2h(PyObject_GetAttr(_h2py(obj), _h2py(name)));
}

static HPy
ctx_GetAttr_s(HPyContext ctx, HPy obj, const char *name) {
  return _py2h(PyObject_GetAttrString(_h2py(obj), name));
}

static int
ctx_HasAttr(HPyContext ctx, HPy obj, HPy name) {
  return PyObject_HasAttr(_h2py(obj), _h2py(name));
}

static int
ctx_HasAttr_s(HPyContext ctx, HPy obj, const char *name) {
  return PyObject_HasAttrString(_h2py(obj), name);
}

static int
ctx_SetAttr(HPyContext ctx, HPy obj, HPy name, HPy value) {
  return PyObject_SetAttr(_h2py(obj), _h2py(name), _h2py(value));
}

static int
ctx_SetAttr_s(HPyContext ctx, HPy obj, const char *name, HPy value) {
  return PyObject_SetAttrString(_h2py(obj), name, _h2py(value));
}

static HPy
ctx_GetItem(HPyContext ctx, HPy obj, HPy key) {
  return _py2h(PyObject_GetItem(_h2py(obj), _h2py(key)));
}

static HPy
ctx_GetItem_i(HPyContext ctx, HPy obj, HPy_ssize_t idx) {
  PyObject* key = PyLong_FromSsize_t(idx);
  if (key == NULL)
    return HPy_NULL;
  HPy result = _py2h(PyObject_GetItem(_h2py(obj), key));
  Py_DECREF(key);
  return result;
}

static HPy
ctx_GetItem_s(HPyContext ctx, HPy obj, const char *key) {
  PyObject* key_o = PyUnicode_FromString(key);
  if (key_o == NULL)
    return HPy_NULL;
  HPy result = _py2h(PyObject_GetItem(_h2py(obj), key_o));
  Py_DECREF(key_o);
  return result;
}

static int
ctx_SetItem(HPyContext ctx, HPy obj, HPy key, HPy value) {
  return PyObject_SetItem(_h2py(obj), _h2py(key), _h2py(value));
}

static int
ctx_SetItem_i(HPyContext ctx, HPy obj, HPy_ssize_t idx, HPy value) {
  PyObject* key = PyLong_FromSsize_t(idx);
  if (key == NULL)
    return -1;
  int result = PyObject_SetItem(_h2py(obj), key, _h2py(value));
  Py_DECREF(key);
  return result;
}

static int
ctx_SetItem_s(HPyContext ctx, HPy obj, const char *key, HPy value) {
  PyObject* key_o = PyUnicode_FromString(key);
  if (key_o == NULL)
    return -1;
  int result = PyObject_SetItem(_h2py(obj), key_o, _h2py(value));
  Py_DECREF(key_o);
  return result;
}

/* HPyMeth */

typedef HPy (*HPyMeth_NoArgs)(HPyContext, HPy self);
typedef HPy (*HPyMeth_O)(HPyContext, HPy self, HPy arg);
typedef HPy (*HPyMeth_VarArgs)(HPyContext, HPy self, HPy *args, HPy_ssize_t);
typedef HPy (*HPyMeth_Keywords)(HPyContext, HPy self, HPy *args, HPy_ssize_t,
                                HPy kw);

static struct _object *
ctx_CallRealFunctionFromTrampoline(HPyContext ctx, struct _object *self,
                               struct _object *args, struct _object *kw,
                               void *func, int ml_flags)
{
    switch (ml_flags)
    {
    case HPy_METH_NOARGS: {
        HPyMeth_NoArgs f = (HPyMeth_NoArgs)func;
        return _h2py(f(ctx, _py2h(self)));
    }
    case HPy_METH_O: {
        HPyMeth_O f = (HPyMeth_O)func;
        return _h2py(f(ctx, _py2h(self), _py2h(args)));
    }
    case HPy_METH_VARARGS: {
        HPyMeth_VarArgs f = (HPyMeth_VarArgs)func;
        Py_ssize_t nargs = PyTuple_GET_SIZE(args);
        HPy *h_args = alloca(nargs * sizeof(HPy));
        for (Py_ssize_t i = 0; i < nargs; i++) {
            h_args[i] = _py2h(PyTuple_GET_ITEM(args, i));
        }
        return _h2py(f(ctx, _py2h(self), h_args, nargs));
    }
    case HPy_METH_KEYWORDS: {
       HPyMeth_Keywords f = (HPyMeth_Keywords)func;
       Py_ssize_t nargs = PyTuple_GET_SIZE(args);
       HPy *h_args = alloca(nargs * sizeof(HPy));
       for (Py_ssize_t i = 0; i < nargs; i++) {
           h_args[i] = _py2h(PyTuple_GET_ITEM(args, i));
       }
       return _h2py(f(ctx, _py2h(self), h_args, nargs, _py2h(kw)));
    }
    default:
        abort();  // XXX
    }
}

static HPy
ctx_FromPyObject(HPyContext ctx, struct _object *obj)
{
    Py_INCREF(obj);
    return _py2h(obj);
}

static struct _object *
ctx_AsPyObject(HPyContext ctx, HPy h)
{
    PyObject *obj = _h2py(h);
    Py_INCREF(obj);
    return obj;
}

static void
ctx_Close(HPyContext ctx, HPy h)
{
    _hclose(h);
}

static HPy
ctx_Dup(HPyContext ctx, HPy h)
{
    PyObject *obj = _h2py(h);
    Py_XINCREF(obj);
    return _py2h(obj);
}

/* expand impl functions as:
 *     static ctx_Long_FromLong(...);
 *
 * Then, they are automatically stored in the global context by
 * autogen_ctx_def
 */
#define HPyAPI_STORAGE static
#define _HPy_IMPL_NAME(name) ctx_##name
#include "common/autogen_impl.h"
#undef _HPy_IMPL_NAME

#include "autogen_ctx_def.h"
