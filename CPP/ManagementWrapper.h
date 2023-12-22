// ManagementWrapper.h

#ifndef MANAGEMENT_WRAPPER_H
#define MANAGEMENT_WRAPPER_H

#include <Python.h>
#include "StatStruct.h"

// Declarations
void init_python();
void finalize_python();
PyObject* Management_new(const char* strategy, double starting_money,
                         PyObject* market_event_securities, PyObject* market_event_queue, 
                         PyObject* securities, const char* host, const char* bot_id);
bool Management_send_order(PyObject* pManagementObj, PyObject* pOrderObj);
void Management_cancel_order(PyObject* pManagementObj, PyObject* pOrderObj);
void Management_final_liquidation(PyObject* pManagementObj, int qty, const char* action, int exec_t, double* penalty, double* pv_final);
void Management_stop(PyObject* pManagementObj, StatStruct stat, bool log);

#endif // MANAGEMENT_WRAPPER_H
