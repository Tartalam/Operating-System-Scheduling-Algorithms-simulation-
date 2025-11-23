//Author: Jahmari Harrison
//Date: 2023-10-03
//Description: Header file for scheduler class representing a system process.
//ID: 2304204
#ifndef SJFSCHEDULER_H
#define SJFSCHEDULER_H

#include "Process.h"
#include <vector>
#include <string>
#include <queue>
#include <functional>

using namespace std;

class SJFScheduler {
private:
    vector<Process> processes; // List of processes
    vector<Process> completedProcesses; // List of completed processes

    // priorit queue (min-heap) for ready processses based on burst time
    priority_queue<Process, vector<Process>, CompareBurstTime> readyQueue;

    //helper methods
    void calculateTimesWithPriorityQueue();
    void sortByArrivalTime();
    int totalExecutionTime = 0;
    int idleTime = 0;


public:
    // Add a process to the scheduler
    SJFScheduler();

    //process management
    void addProcess(const Process &process);
    void addProcess(const string processId, int arrivalTime, int burstTime, int priority);
    void addProcess(const string processId, int arrivalTime, int burstTime);
    void clearProcesses();

    //scheduling operations
    void executeScheduling();
    void printProcessInfo() const;
    void printProcessInfoNoPriority() const;
    void displayExecutionOrder() const;
    void displayGanttChart() const;
    void setTotalExecutionTime(int value);
    void setIdleTime(int value);

    //performance metrics
    float getAverageWaitingTime() const;
    float getAverageTurnaroundTime() const;
    float getAverageResponseTime() const;
    float getCPUUtilization() const;
    int getTotalExecutionTime() const;
    int getIdleTime() const;
    float getThroughput() const;
    void printPerformanceMetrics() const;

    //Getters
    vector<Process> getCompletedProcesses() const;
    int getProcessCount() const;
};


#endif// SJFSCHEDULER_H