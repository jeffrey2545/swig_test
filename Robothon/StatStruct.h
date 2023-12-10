// StatStruct.h
#ifndef STAT_STRUCT_H
#define STAT_STRUCT_H

#include <string>

struct StatStruct {
    std::string strategy;
    std::string sym;
    std::string action;
    double pv;
    int qty_target;
    int qty;
    double bp; // Benchmark price
    double vwap;
    int time_t;
    int slices;
};

#endif // STAT_STRUCT_H
