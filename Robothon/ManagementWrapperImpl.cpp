// ManagementWrapperImpl.cpp
#include "ManagementWrapper.cpp"
#include <Python.h>
#include <iostream>
#include <string>

// Initialize Python Interpreter
void init_python() {
    Py_Initialize();

    // Set Python path to include current directory
    PyObject* sysPath = PySys_GetObject("path"); // Borrowed reference, no need to DECREF
    PyObject* programName = PyUnicode_DecodeFSDefault("."); // Represents the current directory
    PyList_Append(sysPath, programName);
    Py_DECREF(programName);
}

// Finalize Python Interpreter
void finalize_python() {
    Py_Finalize();
}

PyObject* Management_new(const char* strategy, double starting_money,
                         PyObject* market_event_securities, PyObject* market_event_queue, 
                         PyObject* securities, const char* host, const char* bot_id) {
    PyObject *pName, *pModule, *pDict, *pClass, *pInstance;

    pName = PyUnicode_DecodeFSDefault("Management");  // Replace with the actual module name
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pDict = PyModule_GetDict(pModule);
        pClass = PyDict_GetItemString(pDict, "Management");

        if (PyCallable_Check(pClass)) {
            PyObject* pArgs = PyTuple_New(7); // Number of constructor arguments

            // Set up the arguments
            PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(strategy));
            PyTuple_SetItem(pArgs, 1, PyFloat_FromDouble(starting_money));
            PyTuple_SetItem(pArgs, 2, market_event_securities); // Assuming this is already a PyObject*
            PyTuple_SetItem(pArgs, 3, market_event_queue);      // Assuming this is already a PyObject*
            PyTuple_SetItem(pArgs, 4, securities);             // Assuming this is already a PyObject*
            PyTuple_SetItem(pArgs, 5, PyUnicode_FromString(host));
            PyTuple_SetItem(pArgs, 6, PyUnicode_FromString(bot_id));

            // Create an instance of the class
            pInstance = PyObject_CallObject(pClass, pArgs);
            Py_DECREF(pArgs);

            if (pInstance != NULL) {
                return pInstance; // Successfully created the instance
            } else {
                PyErr_Print(); // Handle constructor failure
            }
        } else {
            PyErr_Print(); // Handle class not callable error
        }
        Py_DECREF(pModule);
    } else {
        PyErr_Print(); // Handle module import error
    }
    return NULL;
}

bool Management_send_order(PyObject* pManagementObj, PyObject* pOrderObj) {
    if (pManagementObj != NULL && PyCallable_Check(pManagementObj)) {
        // Assuming pOrderObj is already a PyObject* representing the order.
        // If it's not, you need to convert it to PyObject* here.

        // Call the send_order method of the Management class
        PyObject* result = PyObject_CallMethod(pManagementObj, "send_order", "(O)", pOrderObj);

        // Check for Python errors
        if (!result) {
            PyErr_Print();  // Print error and clear error indicators
            return false;   // Return false if there was an error
        }

        // Convert the Python return value to a C++ bool
        bool success = PyObject_IsTrue(result) != 0;
        Py_DECREF(result);  // Decrease the reference count of result
        return success;     // Return the success status
    } else {
        // Error handling if pManagementObj is NULL or not callable
        std::cerr << "Error: pManagementObj is NULL or not callable." << std::endl;
        return false;  // Return false if pManagementObj is invalid
    }
}

void Management_cancel_order(PyObject* pManagementObj, PyObject* pOrderObj) {
    if (pManagementObj != NULL && PyCallable_Check(pManagementObj)) {
        // Assuming pOrderObj is already a PyObject* representing the order.
        // If it's not, you need to convert it to PyObject* here.

        // Call the cancel_order method of the Management class
        PyObject_CallMethod(pManagementObj, "cancel_order", "(O)", pOrderObj);

        // Check for Python errors
        if (PyErr_Occurred()) {
            // Print error and clear error indicators
            PyErr_Print();
        }
    } else {
        // Error handling if pManagementObj is NULL or not callable
        std::cerr << "Error: pManagementObj is NULL or not callable." << std::endl;
    }
}

void Management_final_liquidation(PyObject* pManagementObj, int qty, const char* action, int exec_t, double* penalty, double* pv_final) {
    // Check for NULL pointer
    if (pManagementObj == NULL) {
        *penalty = 0.0;
        *pv_final = 0.0;
        return;
    }

    // Initialize return values
    *penalty = 0.0;
    *pv_final = 0.0;

    if (qty > 0) {
        PyObject* args = PyTuple_Pack(3, PyLong_FromLong(qty), PyUnicode_FromString(action), PyLong_FromLong(exec_t));
        PyObject* result = PyObject_CallMethod(pManagementObj, "final_liquidation", "OOO", args);
        Py_DECREF(args);

        if (result != NULL && PyTuple_Check(result) && PyTuple_Size(result) == 2) {
            *penalty = PyFloat_AsDouble(PyTuple_GetItem(result, 0));
            *pv_final = PyFloat_AsDouble(PyTuple_GetItem(result, 1));
            Py_DECREF(result);
        } else {
            PyErr_Print();  // Handle the error if result is invalid
        }
    }
}

void Management_stop(PyObject* pManagementObj, StatStruct stat, bool log) {
    if (pManagementObj == NULL) {
        return;
    }

    // Convert StatStruct data to Python objects
    PyObject* py_exec_algo = PyUnicode_FromString(stat.strategy.c_str());
    PyObject* py_sym = PyUnicode_FromString(stat.sym.c_str());
    PyObject* py_action = PyUnicode_FromString(stat.action.c_str());
    PyObject* py_pv = PyFloat_FromDouble(stat.pv);
    PyObject* py_qty_target = PyLong_FromLong(stat.qty_target);
    PyObject* py_qty = PyLong_FromLong(stat.qty);
    PyObject* py_bp = PyFloat_FromDouble(stat.bp);
    PyObject* py_vwap = PyFloat_FromDouble(stat.vwap);
    PyObject* py_time_t = PyLong_FromLong(stat.time_t);
    PyObject* py_slices = PyLong_FromLong(stat.slices);
    PyObject* py_log = PyBool_FromLong(log);

    // Prepare arguments tuple
    PyObject* args = PyTuple_Pack(9, py_exec_algo, py_sym, py_action, py_pv, py_qty_target, py_qty, py_bp, py_vwap, py_time_t, py_slices, py_log);

    // Call the stop method of the Management class
    PyObject_CallMethod(pManagementObj, "stop", "O", args);

    // Clean up Python objects
    Py_DECREF(py_exec_algo);
    Py_DECREF(py_sym);
    Py_DECREF(py_action);
    Py_DECREF(py_pv);
    Py_DECREF(py_qty_target);
    Py_DECREF(py_qty);
    Py_DECREF(py_bp);
    Py_DECREF(py_vwap);
    Py_DECREF(py_time_t);
    Py_DECREF(py_slices);
    Py_DECREF(py_log);
    Py_DECREF(args);

    // Check for Python errors
    if (PyErr_Occurred()) {
        PyErr_Print();  // Print error and clear error indicators
    }
}
