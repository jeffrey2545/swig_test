#include <Python.h>

// Declarations
void init_python();
void finalize_python();
PyObject* Car_new(const char* make, const char* model, int year);
PyObject* Car_get_descriptive_name(PyObject* pCarObj);
PyObject* Car_read_odometer(PyObject* pCarObj);
void Car_update_odometer(PyObject* pCarObj, int mileage);
void Car_increment_odometer(PyObject* pCarObj, int miles);
