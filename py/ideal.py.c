/* See compilation notes in build.python*/
#include <Python.h>
#include "../ideal.h"

static PyObject *ideal_py(PyObject *self, PyObject *args){
    double intemp;
    if (!PyArg_ParseTuple(args, "d", &intemp)) return NULL;
    double out = ideal_pressure(.temp=intemp);
    return Py_BuildValue("d", out);
}

static PyMethodDef method_list[] = {
    {"pressure_from_temp",  ideal_py, METH_VARARGS,
     "Get the pressure from the temperature of one mole of gunk"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initpvnrt(void) {
    Py_InitModule("pvnrt", method_list);
}
