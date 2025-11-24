//Author: Jahmari Harrison
//Date: 2023-10-10
//Description: Implementation file for SJF Scheduler class representing a system process.
//ID: 2304204

#include "SJFScheduler.h"
#include "Process.h"
#include "FCFS_Scheduler.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//Process Class Implementation

Process::Process(string processId, int arrivalTime, int burstTime, int priority)
    : processId(processId), arrivalTime(arrivalTime), burstTime(burstTime), prority(priority),
      completionTime(0), waitingTime(0), turnaroundTime(0), responseTime(0) {}

string Process::getProcessId() const {
    return processId;}
int Process::getArrivalTime() const {
    return arrivalTime;}
int Process::getBurstTime() const {
    return burstTime;}
int Process::getPriority() const {
    return prority;}
int Process::getCompletionTime() const {
    return completionTime;}
int Process::getWaitingTime() const {
    return waitingTime;}
int Process::getTurnaroundTime() const {
    return turnaroundTime;}
int Process::getResponseTime() const {
    return responseTime;}
void Process::setCompletionTime(int time) {
    completionTime = time;}
void Process::setWaitingTime(int time) {
    waitingTime = time;}
void Process::setTurnaroundTime(int time) {
    turnaroundTime = time;}
void Process::setResponseTime(int time) {
    responseTime = time;}

void Process::displayProcessInfo() const {

  cout << left << setw(8) << processId
       << setw(12) << arrivalTime
       << setw(10) << burstTime
       << setw(12) << prority
       << setw(12) << waitingTime
        <<setw(12) <<  responseTime
       << setw(15) << turnaroundTime
       << setw(16) << completionTime
       << endl; 
}

void Process::displayProcessInfoNoPriority() const {

  cout << left << setw(8) << processId
       << setw(12) << arrivalTime
       << setw(10) << burstTime
       << setw(12) << waitingTime
       << setw(12) << responseTime
       << setw(15) << turnaroundTime
       << setw(16) << completionTime
       << endl; 
}

//SJFScheduler Class Implementation
SJFScheduler::SJFScheduler() {}
// FCFS_Scheduler::FCFS_Scheduler() : SJFScheduler() {}
void SJFScheduler::addProcess(const Process& process){
  processes.push_back(process);
}

//overloaded method to add process by parameters with priority
void SJFScheduler::addProcess(const string processId, int arrivalTime, int burstTime, int priority){
  processes.push_back(Process(processId, arrivalTime, burstTime, priority));
}

//overloaded method to add process by parameters without priority
void SJFScheduler::addProcess(const string processId, int arrivalTime, int burstTime){
  processes.push_back(Process(processId, arrivalTime, burstTime, -1)); //default priority 0
}

void SJFScheduler::clearProcesses(){
  processes.clear();
  completedProcesses.clear();
  // Clear the priority queue creating a new empty one
  // while (!readyQueue.empty()) {
  //     readyQueue.pop();
  // }
  readyQueue = priority_queue<Process, vector<Process>, CompareBurstTime>();
}

void SJFScheduler::sortByArrivalTime() {
  sort(processes.begin(), processes.end(),
      [](const Process &p1, const Process &p2) {
          return p1.getArrivalTime() < p2.getArrivalTime();
      });
}

void SJFScheduler::calculateTimesWithPriorityQueue() {
  if (processes.empty()) return;

  // Sort processed by arrival time
  sortByArrivalTime();

  vector<Process> tempProcesses = processes; // Copy of processes to manipulate
  vector<bool> executed(tempProcesses.size(), false); // Track executed processes

  int currentTime = 0;
  int completedCount = 0;
  int n = tempProcesses.size();
  int index = 0; // Index to track processes added to the ready queue
  int trackIdleTime = 0; //Track total idle time of CPU.

  cout << "Starting SJF Scheduling..." << endl;

  while (completedCount < n) {
      // Add all processes that have arrived by currentTime to the ready queue
      while (index < n && tempProcesses[index].getArrivalTime() <= currentTime) {
          readyQueue.push(tempProcesses[index]);
          index++;
      }

      if (!readyQueue.empty()) {
          // Get the process with the shortest burst time
          Process currentProcess = readyQueue.top();
          readyQueue.pop();

          cout << currentProcess.getProcessId() << " ( " << currentTime << "-";

          //calculate completion time
          int completionTime = currentTime + currentProcess.getBurstTime();
          int turnaroundTime = completionTime - currentProcess.getArrivalTime();
          int waitingTime = turnaroundTime - currentProcess.getBurstTime();
          int responseTime = currentTime - currentProcess.getArrivalTime();

          //update the process with the claculated times
          for(auto &proc : tempProcesses) {
              if (proc.getProcessId() == currentProcess.getProcessId()) {
                  proc.setCompletionTime(completionTime);
                  proc.setWaitingTime(waitingTime);
                  proc.setTurnaroundTime(turnaroundTime);
                  proc.setResponseTime(responseTime);
                  completedProcesses.push_back(proc);
                  break;
              }
          }

          cout << completionTime << ") ";
          currentTime = completionTime;
          completedCount++;
          
        } 
        else
        {
          // if no process in ready queue, jump to next arrival time and track idle time
          if (index < n) {
              int nextArrival = tempProcesses[index].getArrivalTime();
              int idleDuration = nextArrival - currentTime;
              trackIdleTime += idleDuration; //update idle time
              currentTime = nextArrival;
          }
          else
          {
              break; //all processes are completed
          }
        }

  }
  int totalTime = currentTime + trackIdleTime;

  cout << "\nSJF Scheduling Completed." << endl;
  setIdleTime(trackIdleTime);
  setTotalExecutionTime(totalTime);
}

//execute scheduling using SJF algorithm with priority queue
void SJFScheduler::executeScheduling() {

  if (processes.empty()) {
      cout << "No processes to schedule." << endl;
      return;
  }

  completedProcesses.clear();
  readyQueue = priority_queue<Process, vector<Process>, CompareBurstTime>();// Clear the priority queue
  
  calculateTimesWithPriorityQueue();

}

void FCFS_Scheduler::executeScheduling() {
    if (processes.empty()) {
        cout << "No processes to schedule." << endl;
        return;
    }
    
    completedProcesses.clear();
    calculateFCFS();
    
    // Use the inherited performance metrics display
    printPerformanceMetrics();
}

void FCFS_Scheduler::calculateFCFS() {
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), 
         [](const Process &a, const Process &b) {
             return a.getArrivalTime() < b.getArrivalTime();
         });
    
    int currentTime = 0;
    int trackIdleTime = 0;
    
    for (auto &p : processes) {
        // If CPU is idle, jump to process arrival time
        if (currentTime < p.getArrivalTime()) {
            int idleDuration = p.getArrivalTime() - currentTime;
            trackIdleTime += idleDuration;
            currentTime = p.getArrivalTime();
        }
        
        // Calculate times
        int completionTime = currentTime + p.getBurstTime();
        int turnaroundTime = completionTime - p.getArrivalTime();
        int waitingTime = turnaroundTime - p.getBurstTime();
        int responseTime = currentTime - p.getArrivalTime();
        
        // Create a copy and set calculated times
        Process completedProcess = p;
        completedProcess.setCompletionTime(completionTime);
        completedProcess.setWaitingTime(waitingTime);
        completedProcess.setTurnaroundTime(turnaroundTime);
        completedProcess.setResponseTime(responseTime);
        
        completedProcesses.push_back(completedProcess);
        
        // Update current time for next process
        currentTime = completionTime;
    }
    
    totalExecutionTime = currentTime;
    idleTime = trackIdleTime;
}



void SJFScheduler::printProcessInfo() const {
  if (completedProcesses.empty()) {
      cout << "No completed processes to display." << endl;
      return;
  }

    //check if any process has priority other than -1
  bool hasPriority = false;
  for (const auto &process : completedProcesses) {
    if (process.getPriority() != -1) {
      hasPriority = true;
      break;
    }
    }
  if (hasPriority) {

  cout << "SJF Scheduling Results: (USing priority Queue/Min-Heap):" << endl;
  cout << string(75 ,'=') << endl;
  cout << left << setw(8) << "Process"
       << setw(12) << "Arrival"
       << setw(10) << "Burst"
       << setw(12) << "Priority"
       << setw(12) << "Waiting"
       <<setw(12) <<  "Response"
       << setw(15) << "Turnaround"
       << setw(16) << "Completion"
       << endl;
  cout << string(75 ,'=') << endl;

  for (const auto &process : completedProcesses) {
      process.displayProcessInfo();
  }
  }else{
    //Display without priority column
    printProcessInfoNoPriority();
  }
}

void SJFScheduler::printProcessInfoNoPriority() const {


  cout << "SJF Scheduling Results: (Using priority Queue/Min-Heap):" << endl;
  cout << string(70 ,'=') << endl;
  cout << left << setw(8) << "Process"
       << setw(12) << "Arrival"
       << setw(10) << "Burst"
       << setw(12) << "Waiting"
       <<setw(12) <<  "Response"
       << setw(15) << "Turnaround"
       << setw(16) << "Completion"
       << endl;
  cout << string(70 ,'=') << endl;

  for (const auto &process : completedProcesses) {
      process.displayProcessInfoNoPriority();
  }
}



void SJFScheduler::displayExecutionOrder() const {

  if (completedProcesses.empty()) {
      cout << "No completed processes to display execution order." << endl;
      return;
  }
  
  cout << "Execution Order of Processes: ";
  for (const auto &process : completedProcesses) {
      cout << process.getProcessId() << " ";
  }
  cout << endl;
}

void SJFScheduler::displayGanttChart() const {
  if (completedProcesses.empty()) {
      cout << "No completed processes to display Gantt chart." << endl;
      return;
  }

  cout << "\nGantt Chart:" << endl;
  cout << "Time:  ";
 
  for (const auto &process : completedProcesses) {
      int startime = process.getCompletionTime() - process.getBurstTime();
      cout << "| " << process.getProcessId() << " (" << startime << "-" << process.getCompletionTime() << ") ";

  }
  cout << "|" << endl;
}

float SJFScheduler::getAverageWaitingTime() const {
  if (completedProcesses.empty()) return 0.0f;

  int totalWaitingTime = 0;
  for (const auto &process : completedProcesses) {
      totalWaitingTime += process.getWaitingTime();
  }
  return static_cast<float>(totalWaitingTime) / completedProcesses.size();
}

//sets the total real world time process took to execute in milliseconds
void SJFScheduler::setTotalExecutionTime(int value) {
  totalExecutionTime = value;
  
}
//gets the total real world time process took to execute in milliseconds
int SJFScheduler::getTotalExecutionTime() const {
  return totalExecutionTime;
}

//gets the throughput of the processes
float SJFScheduler::getThroughput() const {
  return static_cast<float>(completedProcesses.size()) / getTotalExecutionTime();
}

//sets the total idle time of CPU
void SJFScheduler::setIdleTime(int value) {
  idleTime = value;
  
}

//gets the total idle time of CPU
int SJFScheduler::getIdleTime() const {
  return idleTime;
}

//calculates CPU utilization
float SJFScheduler::getCPUUtilization() const {
  if (totalExecutionTime == 0) return 0;
  return static_cast<float>(((getTotalExecutionTime() - getIdleTime()) /getTotalExecutionTime()) * 100.0f);
}

//count amount of processes in queue
int SJFScheduler::getProcessCount() const {
  return static_cast<int>(processes.size());
}

//get caverage turnaround time
float SJFScheduler::getAverageTurnaroundTime() const {
  if (completedProcesses.empty()) return 0.0f;

  int totalTurnaroundTime = 0;
  for (const auto &process : completedProcesses) {
      totalTurnaroundTime += process.getTurnaroundTime();
  }
  return static_cast<float>(totalTurnaroundTime) / completedProcesses.size();
}

//get average response time
float SJFScheduler::getAverageResponseTime() const {
  if (completedProcesses.empty()) return 0.0f;

  int totalResponseTime = 0;
  for (const auto &process : completedProcesses) {
      totalResponseTime += process.getResponseTime();
  }
  return static_cast<float>(totalResponseTime) / completedProcesses.size();
}

//print performance metrics
void SJFScheduler::printPerformanceMetrics() const {
  if (completedProcesses.empty()) {
      cout << "No completed processes to calculate performance metrics." << endl;
      return;
  }

  cout << "\nPerformance Metrics:" << endl;
  cout << "-------------------" << endl;
  cout << "Average Waiting Time: " << fixed << setprecision(2) << getAverageWaitingTime() << endl;
  cout << "Average Turnaround Time: " << fixed << setprecision(2) << getAverageTurnaroundTime() << endl;
  cout << "Average Response Time: " << fixed << setprecision(2) << getAverageResponseTime() << endl;
  cout << "Throughput: " << fixed << setprecision(2) << getThroughput() << " processes/Unit" << endl;
  cout << "CPU Utilization: " << fixed << setprecision(2) << getCPUUtilization() << "%" << endl;
  cout << "Total Execution Time: " << getTotalExecutionTime() << " units" << endl;
  cout << "Idle Time: " << getIdleTime() << " units" << endl;
  cout << "Total processes: " << completedProcesses.size() << endl;
}