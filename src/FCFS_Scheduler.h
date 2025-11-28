//Author: Jahmari Harrison
//Date: 2023-10-15
//Description: Header file for First-Come, First-Served (FCFS) Scheduler
//ID: 2304204
//Attributions: This code wsa completed with the help from exteranl libraries.
#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "SJFScheduler.h"
#include "Process.h"
#include <vector>
#include <utility>

using namespace std;

class FCFS_Scheduler : public SJFScheduler {
private:

    void calculateFCFS();
    
public:
    // Override scheduling operation
    void executeScheduling();
    
};

#endif