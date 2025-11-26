#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include <vector>
#include <iostream>
#include <limits>
#include "Process.h"
using namespace std;

class PriorityScheduler {
private:
    vector<Process> processes;
    vector<pair<int, int>> ganttChart; // (pid, time)

public:
    void addProcess(const Process& p);
    void clearProcesses();

    void executeScheduling();
    void printProcessInfo() const;
    void printPerformanceMetrics() const;
    void displayGanttChart() const;
};

#endif
