#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <stdio.h>

static PyObject* lib_system(PyObject* self, PyObject* args)  // args is always a tuple of arguments
{
    const char* command;
    int sts;
    if (!PyArg_ParseTuple(args, "s", &command)) {
        return NULL;
    }
    return PyLong_FromLong(100L);
}

static PyMethodDef LibMethods[] = {
    {"system",  lib_system, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef libmodule = {
    PyModuleDef_HEAD_INIT,
    "lib",   /* name of module */
    "some docs", /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    LibMethods
};

PyMODINIT_FUNC PyInit_liblib(void)
{
    printf("hello\n");
    return PyModule_Create(&libmodule);
}

