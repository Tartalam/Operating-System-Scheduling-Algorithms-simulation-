#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "SJFScheduler.h"
#include "Process.h"
#include <vector>
#include <utility>

using namespace std;

class FCFS_Scheduler : public SJFScheduler {
private:
    // Use inherited constructors and methods
    
    // Method to calculate FCFS scheduling
    void calculateFCFS();
    
public:
    // Override scheduling operation
    void executeScheduling();
    
};

#endif