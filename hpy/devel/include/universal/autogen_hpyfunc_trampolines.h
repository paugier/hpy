
/*
   DO NOT EDIT THIS FILE!

   This file is automatically generated by tools/autogen.py from tools/public_api.h.
   Run this to regenerate:
       make autogen

*/

typedef struct {
    cpy_PyObject *arg;
    cpy_PyObject * result;
} _HPyFunc_args_UNARY;

#define _HPyFunc_TRAMPOLINE_HPyFunc_UNARY(SYM, IMPL) \
    static cpy_PyObject *SYM(cpy_PyObject *arg) \
    { \
        _HPyFunc_args_UNARY a = { arg }; \
        _HPy_CallRealFunctionFromTrampoline( \
           _ctx_for_trampolines, HPyFunc_UNARY, IMPL, &a); \
        return a.result; \
    }

typedef struct {
    cpy_PyObject *arg;
    cpy_PyObject * result;
} _HPyFunc_args_REPR;

#define _HPyFunc_TRAMPOLINE_HPyFunc_REPR(SYM, IMPL) \
    static cpy_PyObject *SYM(cpy_PyObject *arg) \
    { \
        _HPyFunc_args_REPR a = { arg }; \
        _HPy_CallRealFunctionFromTrampoline( \
           _ctx_for_trampolines, HPyFunc_REPR, IMPL, &a); \
        return a.result; \
    }

typedef struct {
    cpy_PyObject *arg;
    HPy_ssize_t size;
    cpy_PyObject * result;
} _HPyFunc_args_SSIZEARG;

#define _HPyFunc_TRAMPOLINE_HPyFunc_SSIZEARG(SYM, IMPL) \
    static cpy_PyObject *SYM(cpy_PyObject *arg, HPy_ssize_t size) \
    { \
        _HPyFunc_args_SSIZEARG a = { arg, size }; \
        _HPy_CallRealFunctionFromTrampoline( \
           _ctx_for_trampolines, HPyFunc_SSIZEARG, IMPL, &a); \
        return a.result; \
    }
