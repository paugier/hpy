#ifndef HPy_CPYTHON_H
#define HPy_CPYTHON_H

/* XXX: it would be nice if we could include hpy.h WITHOUT bringing in all the
   stuff from Python.h, to make sure that people don't use the CPython API by
   mistake. How to achieve it, though? Is defining Py_LIMITED_API enough? */

/* XXX: should we:
 *    - enforce PY_SSIZE_T_CLEAN in hpy
 *    - make it optional
 *    - make it the default but give a way to disable it?
 */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#ifdef __GNUC__
#define HPyAPI_STORAGE __attribute__((unused)) static inline
#else
#define HPyAPI_STORAGE static inline
#endif /* __GNUC__ */

#define HPyAPI_FUNC(restype) HPyAPI_STORAGE restype

#ifdef __GNUC__
#define _HPy_HIDDEN  __attribute__((visibility("hidden")))
#else
#define _HPy_HIDDEN
#endif /* __GNUC__ */

#define HPyAPI_RUNTIME_FUNC(restype) _HPy_HIDDEN restype

typedef struct { PyObject *_o; } HPy;
typedef struct { Py_ssize_t _lst; } HPyListBuilder;
typedef struct { Py_ssize_t _tup; } HPyTupleBuilder;
typedef struct { void *_o; } HPyTracker;
typedef Py_ssize_t HPy_ssize_t;
typedef Py_hash_t HPy_hash_t;

/* For internal usage only. These should be #undef at the end of this header.
   If you need to convert HPy to PyObject* and vice-versa, you should use
   HPy_AsPyObject and HPy_FromPyObject.
*/
#define _h2py(x) (x._o)
#define _py2h(o) ((HPy){o})

// this should maybe autogenerated from public_api.h
typedef struct _HPyContext_s {
    /* Constants */
    HPy h_None;
    HPy h_True;
    HPy h_False;
    /* Exceptions */
    HPy h_BaseException;
    HPy h_Exception;
    HPy h_StopAsyncIteration;
    HPy h_StopIteration;
    HPy h_GeneratorExit;
    HPy h_ArithmeticError;
    HPy h_LookupError;
    HPy h_AssertionError;
    HPy h_AttributeError;
    HPy h_BufferError;
    HPy h_EOFError;
    HPy h_FloatingPointError;
    HPy h_OSError;
    HPy h_ImportError;
    HPy h_ModuleNotFoundError;
    HPy h_IndexError;
    HPy h_KeyError;
    HPy h_KeyboardInterrupt;
    HPy h_MemoryError;
    HPy h_NameError;
    HPy h_OverflowError;
    HPy h_RuntimeError;
    HPy h_RecursionError;
    HPy h_NotImplementedError;
    HPy h_SyntaxError;
    HPy h_IndentationError;
    HPy h_TabError;
    HPy h_ReferenceError;
    HPy h_SystemError;
    HPy h_SystemExit;
    HPy h_TypeError;
    HPy h_UnboundLocalError;
    HPy h_UnicodeError;
    HPy h_UnicodeEncodeError;
    HPy h_UnicodeDecodeError;
    HPy h_UnicodeTranslateError;
    HPy h_ValueError;
    HPy h_ZeroDivisionError;
    HPy h_BlockingIOError;
    HPy h_BrokenPipeError;
    HPy h_ChildProcessError;
    HPy h_ConnectionError;
    HPy h_ConnectionAbortedError;
    HPy h_ConnectionRefusedError;
    HPy h_ConnectionResetError;
    HPy h_FileExistsError;
    HPy h_FileNotFoundError;
    HPy h_InterruptedError;
    HPy h_IsADirectoryError;
    HPy h_NotADirectoryError;
    HPy h_PermissionError;
    HPy h_ProcessLookupError;
    HPy h_TimeoutError;
    /* Warnings */
    HPy h_Warning;
    HPy h_UserWarning;
    HPy h_DeprecationWarning;
    HPy h_PendingDeprecationWarning;
    HPy h_SyntaxWarning;
    HPy h_RuntimeWarning;
    HPy h_FutureWarning;
    HPy h_ImportWarning;
    HPy h_UnicodeWarning;
    HPy h_BytesWarning;
    HPy h_ResourceWarning;
    /* Types */
    HPy h_BaseObjectType;
    HPy h_TypeType;
    HPy h_LongType;
    HPy h_UnicodeType;
    HPy h_TupleType;
    HPy h_ListType;
} *HPyContext;

/* XXX! should be defined only once, not once for every .c! */
static struct _HPyContext_s _global_ctx;

#define HPy_NULL ((HPy){NULL})
#define HPy_IsNull(x) ((x)._o == NULL)

// XXX: we need to decide whether these are part of the official API or not,
// and maybe introduce a better naming convetion. For now, they are needed for
// ujson
static inline HPy HPy_FromVoidP(void *p) { return (HPy){(PyObject*)p}; }
static inline void* HPy_AsVoidP(HPy h) { return (void*)h._o; }


HPyAPI_FUNC(HPyContext)
_HPyGetContext(void) {
    HPyContext ctx = &_global_ctx;
    if (HPy_IsNull(ctx->h_None)) {
        // XXX: we need to find a better way to check whether the ctx is
        // initialized or not
        /* Constants */
        ctx->h_None = _py2h(Py_None);
        ctx->h_True = _py2h(Py_True);
        ctx->h_False = _py2h(Py_False);
        /* Exceptions */
        ctx->h_BaseException = _py2h(PyExc_BaseException);
        ctx->h_Exception = _py2h(PyExc_Exception);
        ctx->h_StopAsyncIteration = _py2h(PyExc_StopAsyncIteration);
        ctx->h_StopIteration = _py2h(PyExc_StopIteration);
        ctx->h_GeneratorExit = _py2h(PyExc_GeneratorExit);
        ctx->h_ArithmeticError = _py2h(PyExc_ArithmeticError);
        ctx->h_LookupError = _py2h(PyExc_LookupError);
        ctx->h_AssertionError = _py2h(PyExc_AssertionError);
        ctx->h_AttributeError = _py2h(PyExc_AttributeError);
        ctx->h_BufferError = _py2h(PyExc_BufferError);
        ctx->h_EOFError = _py2h(PyExc_EOFError);
        ctx->h_FloatingPointError = _py2h(PyExc_FloatingPointError);
        ctx->h_OSError = _py2h(PyExc_OSError);
        ctx->h_ImportError = _py2h(PyExc_ImportError);
        ctx->h_ModuleNotFoundError = _py2h(PyExc_ModuleNotFoundError);
        ctx->h_IndexError = _py2h(PyExc_IndexError);
        ctx->h_KeyError = _py2h(PyExc_KeyError);
        ctx->h_KeyboardInterrupt = _py2h(PyExc_KeyboardInterrupt);
        ctx->h_MemoryError = _py2h(PyExc_MemoryError);
        ctx->h_NameError = _py2h(PyExc_NameError);
        ctx->h_OverflowError = _py2h(PyExc_OverflowError);
        ctx->h_RuntimeError = _py2h(PyExc_RuntimeError);
        ctx->h_RecursionError = _py2h(PyExc_RecursionError);
        ctx->h_NotImplementedError = _py2h(PyExc_NotImplementedError);
        ctx->h_SyntaxError = _py2h(PyExc_SyntaxError);
        ctx->h_IndentationError = _py2h(PyExc_IndentationError);
        ctx->h_TabError = _py2h(PyExc_TabError);
        ctx->h_ReferenceError = _py2h(PyExc_ReferenceError);
        ctx->h_SystemError = _py2h(PyExc_SystemError);
        ctx->h_SystemExit = _py2h(PyExc_SystemExit);
        ctx->h_TypeError = _py2h(PyExc_TypeError);
        ctx->h_UnboundLocalError = _py2h(PyExc_UnboundLocalError);
        ctx->h_UnicodeError = _py2h(PyExc_UnicodeError);
        ctx->h_UnicodeEncodeError = _py2h(PyExc_UnicodeEncodeError);
        ctx->h_UnicodeDecodeError = _py2h(PyExc_UnicodeDecodeError);
        ctx->h_UnicodeTranslateError = _py2h(PyExc_UnicodeTranslateError);
        ctx->h_ValueError = _py2h(PyExc_ValueError);
        ctx->h_ZeroDivisionError = _py2h(PyExc_ZeroDivisionError);
        ctx->h_BlockingIOError = _py2h(PyExc_BlockingIOError);
        ctx->h_BrokenPipeError = _py2h(PyExc_BrokenPipeError);
        ctx->h_ChildProcessError = _py2h(PyExc_ChildProcessError);
        ctx->h_ConnectionError = _py2h(PyExc_ConnectionError);
        ctx->h_ConnectionAbortedError = _py2h(PyExc_ConnectionAbortedError);
        ctx->h_ConnectionRefusedError = _py2h(PyExc_ConnectionRefusedError);
        ctx->h_ConnectionResetError = _py2h(PyExc_ConnectionResetError);
        ctx->h_FileExistsError = _py2h(PyExc_FileExistsError);
        ctx->h_FileNotFoundError = _py2h(PyExc_FileNotFoundError);
        ctx->h_InterruptedError = _py2h(PyExc_InterruptedError);
        ctx->h_IsADirectoryError = _py2h(PyExc_IsADirectoryError);
        ctx->h_NotADirectoryError = _py2h(PyExc_NotADirectoryError);
        ctx->h_PermissionError = _py2h(PyExc_PermissionError);
        ctx->h_ProcessLookupError = _py2h(PyExc_ProcessLookupError);
        ctx->h_TimeoutError = _py2h(PyExc_TimeoutError);
        /* Warnings */
        ctx->h_Warning = _py2h(PyExc_Warning);
        ctx->h_UserWarning = _py2h(PyExc_UserWarning);
        ctx->h_DeprecationWarning = _py2h(PyExc_DeprecationWarning);
        ctx->h_PendingDeprecationWarning = _py2h(PyExc_PendingDeprecationWarning);
        ctx->h_SyntaxWarning = _py2h(PyExc_SyntaxWarning);
        ctx->h_RuntimeWarning = _py2h(PyExc_RuntimeWarning);
        ctx->h_FutureWarning = _py2h(PyExc_FutureWarning);
        ctx->h_ImportWarning = _py2h(PyExc_ImportWarning);
        ctx->h_UnicodeWarning = _py2h(PyExc_UnicodeWarning);
        ctx->h_BytesWarning = _py2h(PyExc_BytesWarning);
        ctx->h_ResourceWarning = _py2h(PyExc_ResourceWarning);
        /* Types */
        ctx->h_BaseObjectType = _py2h((PyObject *)&PyBaseObject_Type);
        ctx->h_TypeType = _py2h((PyObject *)&PyType_Type);
        ctx->h_LongType = _py2h((PyObject *)&PyLong_Type);
        ctx->h_UnicodeType = _py2h((PyObject *)&PyUnicode_Type);
        ctx->h_TupleType = _py2h((PyObject *)&PyTuple_Type);
        ctx->h_ListType = _py2h((PyObject *)&PyList_Type);
    }
    return ctx;
}


HPyAPI_FUNC(HPy)
HPy_Dup(HPyContext ctx, HPy handle)
{
    Py_XINCREF(_h2py(handle));
    return handle;
}

HPyAPI_FUNC(void)
HPy_Close(HPyContext ctx, HPy handle)
{
    Py_XDECREF(_h2py(handle));
}

HPyAPI_FUNC(HPy)
HPy_FromPyObject(HPyContext ctx, PyObject *obj)
{
    Py_XINCREF(obj);
    return _py2h(obj);
}

HPyAPI_FUNC(PyObject *)
HPy_AsPyObject(HPyContext ctx, HPy h)
{
    PyObject *result = _h2py(h);
    Py_XINCREF(result);
    return result;
}

/* expand impl functions as:
 *     static inline HPyLong_FromLong(...);
 *
 */
#define _HPy_IMPL_NAME(name) HPy##name
#define _HPy_IMPL_NAME_NOPREFIX(name) HPy_##name
#include "../common/implementation.h"
#undef _HPy_IMPL_NAME_NOPREFIX
#undef _HPy_IMPL_NAME

#include "../common/cpy_types.h"

#include "../common/macros.h"
#include "../common/runtime/argparse.h"

#include "../common/hpyfunc.h"
#include "../common/hpydef.h"
#include "../common/hpytype.h"
#include "../common/hpymodule.h"
#include "../common/runtime/ctx_call.h"
#include "../common/runtime/ctx_module.h"
#include "../common/runtime/ctx_object.h"
#include "../common/runtime/ctx_type.h"
#include "../common/runtime/ctx_listbuilder.h"
#include "../common/runtime/ctx_tracker.h"
#include "../common/runtime/ctx_tuple.h"
#include "../common/runtime/ctx_tuplebuilder.h"

HPyAPI_FUNC(HPy)
HPyModule_Create(HPyContext ctx, HPyModuleDef *mdef)
{
    return ctx_Module_Create(ctx, mdef);
}

HPyAPI_FUNC(HPy)
HPyType_FromSpec(HPyContext ctx, HPyType_Spec *spec, HPyType_SpecParam *params)
{
    return ctx_Type_FromSpec(ctx, spec, params);
}

HPyAPI_FUNC(HPy)
_HPy_New(HPyContext ctx, HPy h, void **data)
{
    return ctx_New(ctx, h, data);
}

HPyAPI_FUNC(void) _Py_NO_RETURN
HPy_FatalError(HPyContext ctx, const char *message)
{
    Py_FatalError(message);
}

HPyAPI_FUNC(HPy)
HPyType_GenericNew(HPyContext ctx, HPy type, HPy *args, HPy_ssize_t nargs, HPy kw)
{
    return ctx_Type_GenericNew(ctx, type, args, nargs, kw);
}

HPyAPI_FUNC(void*)
HPy_Cast(HPyContext ctx, HPy h)
{
    return ctx_Cast(ctx, h);
}

HPyAPI_FUNC(void*)
HPy_CastLegacy(HPyContext ctx, HPy h)
{
    return ctx_CastLegacy(ctx, h);
}

HPyAPI_FUNC(HPy)
HPy_CallTupleDict(HPyContext ctx, HPy callable, HPy args, HPy kw)
{
    return ctx_CallTupleDict(ctx, callable, args, kw);
}

HPyAPI_FUNC(void)
_HPy_Dump(HPyContext ctx, HPy h)
{
    return ctx_Dump(ctx, h);
}

HPyAPI_FUNC(int)
HPy_TypeCheck(HPyContext ctx, HPy h_obj, HPy h_type)
{
    return ctx_TypeCheck(ctx, h_obj, h_type);
}

HPyAPI_FUNC(HPyListBuilder)
HPyListBuilder_New(HPyContext ctx, HPy_ssize_t initial_size)
{
    return ctx_ListBuilder_New(ctx, initial_size);
}

HPyAPI_FUNC(void)
HPyListBuilder_Set(HPyContext ctx, HPyListBuilder builder,
                   HPy_ssize_t index, HPy h_item)
{
    ctx_ListBuilder_Set(ctx, builder, index, h_item);
}

HPyAPI_FUNC(HPy)
HPyListBuilder_Build(HPyContext ctx, HPyListBuilder builder)
{
    return ctx_ListBuilder_Build(ctx, builder);
}

HPyAPI_FUNC(void)
HPyListBuilder_Cancel(HPyContext ctx, HPyListBuilder builder)
{
    ctx_ListBuilder_Cancel(ctx, builder);
}

HPyAPI_FUNC(HPyTupleBuilder)
HPyTupleBuilder_New(HPyContext ctx, HPy_ssize_t initial_size)
{
    return ctx_TupleBuilder_New(ctx, initial_size);
}

HPyAPI_FUNC(void)
HPyTupleBuilder_Set(HPyContext ctx, HPyTupleBuilder builder,
                    HPy_ssize_t index, HPy h_item)
{
    ctx_TupleBuilder_Set(ctx, builder, index, h_item);
}

HPyAPI_FUNC(HPy)
HPyTupleBuilder_Build(HPyContext ctx, HPyTupleBuilder builder)
{
    return ctx_TupleBuilder_Build(ctx, builder);
}

HPyAPI_FUNC(void)
HPyTupleBuilder_Cancel(HPyContext ctx, HPyTupleBuilder builder)
{
    ctx_TupleBuilder_Cancel(ctx, builder);
}

HPyAPI_FUNC(HPy)
HPyTuple_FromArray(HPyContext ctx, HPy items[], HPy_ssize_t n)
{
    return ctx_Tuple_FromArray(ctx, items, n);
}

HPyAPI_FUNC(HPyTracker)
HPyTracker_New(HPyContext ctx, HPy_ssize_t size)
{
    return ctx_Tracker_New(ctx, size);
}

HPyAPI_FUNC(int)
HPyTracker_Add(HPyContext ctx, HPyTracker ht, HPy h)
{
    return ctx_Tracker_Add(ctx, ht, h);
}

HPyAPI_FUNC(void)
HPyTracker_ForgetAll(HPyContext ctx, HPyTracker ht)
{
    ctx_Tracker_ForgetAll(ctx, ht);
}

HPyAPI_FUNC(void)
HPyTracker_Close(HPyContext ctx, HPyTracker ht)
{
    ctx_Tracker_Close(ctx, ht);
}

#endif /* !HPy_CPYTHON_H */
