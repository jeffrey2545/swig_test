#include "CarWrapper.cpp"

// Initialize Python Interpreter
void init_python() {
    Py_Initialize();
}

// Finalize Python Interpreter
void finalize_python() {
    Py_Finalize();
}

// Function to create a new Car object
PyObject* Car_new(const char* make, const char* model, int year) {
    PyObject *pName, *pModule, *pDict, *pClass, *pArgs, *pValue;

    pName = PyUnicode_DecodeFSDefault("carClass");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pDict = PyModule_GetDict(pModule);
        pClass = PyDict_GetItemString(pDict, "Car");

        if (PyCallable_Check(pClass)) {
            pArgs = PyTuple_Pack(3, PyUnicode_FromString(make), PyUnicode_FromString(model), PyLong_FromLong(year));
            pValue = PyObject_CallObject(pClass, pArgs);
            Py_DECREF(pArgs);
            return pValue;
        }
    }
    return NULL;
}

// Wrapper for get_descriptive_name
PyObject* Car_get_descriptive_name(PyObject* pCarObj) {
    PyObject *pResult = PyObject_CallMethod(pCarObj, "get_descriptive_name", NULL);
    return pResult;
}

// Wrapper for read_odometer
PyObject* Car_read_odometer(PyObject* pCarObj) {
    PyObject *pResult = PyObject_CallMethod(pCarObj, "read_odometer", NULL);
    return pResult;
}

// Wrapper for update_odometer
void Car_update_odometer(PyObject* pCarObj, int mileage) {
    PyObject_CallMethod(pCarObj, "update_odometer", "(i)", mileage);
}

// Wrapper for increment_odometer
void Car_increment_odometer(PyObject* pCarObj, int miles) {
    PyObject_CallMethod(pCarObj, "increment_odometer", "(i)", miles);
}
