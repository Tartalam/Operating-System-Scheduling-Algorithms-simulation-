//Author: Jahmari Harrison
//Date: 2023-10-03
//Description: Header file for Multi-Level Queue Scheduler class definition.
//ID: 2304204
#ifndef MLQ_SCHEDULER_H
#define MLQ_SCHEDULER_H

#include "SJFScheduler.h"
#include "Process.h"
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class MLQ_Scheduler : public SJFScheduler {

  private:
    //methods specific to MLQ scheduling
    vector<queue<Process>> queues; // Vector of queues for different levels
    vector<int> timeQuanta; // Time quantum for each queue level
    vector<pair<string, pair<int, int>>> executionHistory; // To track execution for Gantt chart

    // Method to calculate Multi-Level Queue scheduling
    void calculateMLQ();

    //helper methods
    void initializeQueues(int numQueues);
    int getNextQueueLevel();

  public:
  //constructors
    MLQ_Scheduler();
    MLQ_Scheduler(int numQueues, const vector<int>& timeQuanta);

    void addProcess(const string processId, int arrivalTime, int burstTime, int priority, int queueLevel);

    // Override scheduling operation
    void executeScheduling() override;
    void printProcessInfo() const override;
    void displayGanttChart() const override;

    //queue management
    void setTimeQuanta(const vector<int>& timeQuanta);
    void setNumberOfQueues(int numQueues);

    // Add clearProcesses method
    void clearProcesses() {
        SJFScheduler::clearProcesses();
        for (auto& queue : queues) {
            while (!queue.empty()) {
                queue.pop();
            }
        }
        executionHistory.clear();
    }
};

#endif