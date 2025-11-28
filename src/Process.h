//Author: Jahmari Harrison
//Date: 2023-10-03
//Description: Header file for Process class definition.
//ID: 2304204
//Attributions: This code wsa completed witht he help from exteranl libraries.
#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include<functional>

using namespace std;

class Process {
private:
    string processId;   // Process ID
    int arrivalTime;   // Arrival Time
    int burstTime;     // Burst Time
    int prority;      // Priority (if needed)
    int completionTime; // Completion Time
    int waitingTime;    // Waiting Time
    int turnaroundTime; // Turnaround Time
    int throughput;      // Throughput
    int cpuUtilization; // CPU Utilization
    int responseTime;   // Response Time
    int queueLevel;    // Queue Level for Multi-level Queue Scheduling

    

public:

    //constructor
    Process(string processId, int arrivalTime, int burstTime, int Priority);
    // Getters
    string getProcessId() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;
    int getCompletionTime() const;
    int getWaitingTime() const;
    int getTurnaroundTime() const;
    int getResponseTime() const;

    // Setters
    void setCompletionTime(int time);
    void setWaitingTime(int time);
    void setTurnaroundTime(int time);
    void setResponseTime(int time);
    //MLQ Getters and Setters
    int getQueueLevel() const;
    void setQueueLevel(int level);

    // Display process information
    void displayProcessInfo() const;
    void displayProcessInfoNoPriority() const;
    // Display process information with queue level
    void displayProcessInfoWithQueueLevel() const;

};

//Comparison function for sorting processes by burst time
struct CompareBurstTime
{
  bool operator()(const Process &p1, const Process &p2)
  {
    //lower burst time has higher priority
    return p1.getBurstTime() > p2.getBurstTime();
  }
};

struct ComparePriority
{
  bool operator()(const Process &p1, const Process &p2)
  {
    //lower priority number has higher priority
    return p1.getPriority() > p2.getPriority();
  }
};


#endif // PROCESS_H
