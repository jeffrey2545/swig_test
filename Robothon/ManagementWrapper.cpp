#include <Python.h>

// Declarations
void init_python();
void finalize_python();
PyObject* Management_new(const char* strategy, double starting_money, PyObject* market_event_securities, PyObject* market_event_queue, PyObject* securities, const char* host, const char* bot_id);
extern "C" void Management_cancel_order(PyObject* pManagementObj, PyObject* pOrderObj);
extern "C" bool Management_send_order(PyObject* pManagementObj, PyObject* pOrderObj);
extern "C" void Management_callback_for_trades(PyObject* pManagementObj, PyObject* pTradeObj);
extern "C" void Management_callback_for_acks(PyObject* pManagementObj, PyObject* pAMobj);
extern "C" void Management_callback_for_levels(PyObject* pManagementObj, PyObject* pTobObj);
extern "C" void Management_callback_for_clearing(PyObject* pManagementObj, PyObject* pObjObj);
extern "C" PyObject* Management_final_orders(PyObject* pManagementObj, double qty, const char* action, double exec_t);
extern "C" void Management_stop(PyObject* pManagementObj, PyObject* pStat, bool log);
extern "C" void Management_exit(PyObject* pManagementObj, int status);
extern "C" void Management_final_liquidation(PyObject* pManagementObj, int qty, const char* action, int exec_t, double* penalty, double* pv_final);
extern "C" void Management_save_record(PyObject* pManagementObj, const char* exec_algo, const char* sym, const char* action, int qty, int slices, int time_t, int qty_exec, double tc, double penalty, double bp, double vwap);