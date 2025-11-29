//Author: Alaina Preston
//Date: 2023-10-15
//Description: Header file for Preemptive Priority Scheduler class definition.
//ID: 2307651
//Attributions: This code wsa completed with the help from exteranl libraries.
#ifndef PP_SHCEDULER_H
#define PP_SHCEDULER_H

#include "SJFScheduler.h"
#include "Process.h"
#include <vector>
#include <utility>

using namespace std;
class PP_Scheduler : public SJFScheduler {
private:
   

    void calculatePP();

    vector<pair<string, pair<int, int>>> executionHistory;
    
public:
    void printProcessInfo() const;
    void displayGanttChart() const;
    
    void executeScheduling();
};
#endif