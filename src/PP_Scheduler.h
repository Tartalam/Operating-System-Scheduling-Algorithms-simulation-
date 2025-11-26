//Author: Jahmari Harrison
//Date: 2023-10-15
//Description: Header file for Preemptive Priority Scheduler class definition.
//ID: 2304204
#ifndef PP_SHCEDULER_H
#define PP_SHCEDULER_H

#include "SJFScheduler.h"
#include "Process.h"
#include <vector>
#include <utility>

using namespace std;
class PP_Scheduler : public SJFScheduler {
private:
    // Use inherited constructors and methods

    // Method to calculate Preemptive Priority scheduling
    void calculatePP();

    vector<pair<string, pair<int, int>>> executionHistory;
public:
    void printProcessInfo() const;
    void displayGanttChart() const;
    // void printPerformanceMetrics() const;
    // Override scheduling operation
    void executeScheduling();
};
#endif