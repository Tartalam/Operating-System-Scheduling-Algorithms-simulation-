//Author: Jahmari Harrison
//Date: 2023-10-10
//Description: Implementation file for SJF Scheduler class representing a system process.
//ID: 2304204

#include "SJFScheduler.h"
#include "Process.h"
#include "FCFS_Scheduler.h"
#include "PP_Scheduler.h"
#include "MLQ_Scheduler.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <climits>

using namespace std;

//Process Class Implementation

Process::Process(string processId, int arrivalTime, int burstTime, int priority)
    : processId(processId), arrivalTime(arrivalTime), burstTime(burstTime), prority(priority),
      completionTime(0), waitingTime(0), turnaroundTime(0), responseTime(0), queueLevel(0) {}

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
int Process::getQueueLevel() const {
    return queueLevel;}
void Process::setCompletionTime(int time) {
    completionTime = time;}
void Process::setWaitingTime(int time) {
    waitingTime = time;}
void Process::setTurnaroundTime(int time) {
    turnaroundTime = time;}
void Process::setResponseTime(int time) {
    responseTime = time;}
void Process::setQueueLevel(int level) {
    queueLevel = level;}

// Display process information
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

//display process info without priority
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

void Process::displayProcessInfoWithQueueLevel() const {
  cout << left << setw(8) << processId
       << setw(12) << arrivalTime
       << setw(10) << burstTime
       << setw(12) << prority
       << setw(12) << queueLevel
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

  readyQueue = priority_queue<Process, vector<Process>, CompareBurstTime>();
}

void SJFScheduler::clearProcessesPP(){
  processes.clear();
  completedProcesses.clear();
  // Clear the priority queue creating a new empty one
  // while (!readyQueue.empty()) {
  //     readyQueue.pop();
  // }
  readyQueuePP = priority_queue<Process, vector<Process>, ComparePriority>();
}

//sort processes by arrival time
void SJFScheduler::sortByArrivalTime() {
  sort(processes.begin(), processes.end(),
      [](const Process &p1, const Process &p2) {
          return p1.getArrivalTime() < p2.getArrivalTime(); //ascending order
      });
}

//calculate scheduling using SJF algorithm with priority queue
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


//print process info with priority column if applicable
void SJFScheduler::printProcessInfo() const {
  if (completedProcesses.empty()) {
      cout << "No completed processes to display." << endl;
      return;
  }

    //check if any process has priority other than -1
  bool hasPriority = false;
  for (const auto &process : completedProcesses) {
    if (process.getPriority() != -1) { //assuming -1 means no priority
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

//print process info without priority column
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

//display execution order of processes
void SJFScheduler::displayExecutionOrder() const {

  if (completedProcesses.empty()) {
      cout << "No completed processes to display execution order." << endl;
      return;
  }
  
  cout << "Execution Order of Processes: ";
  for (const auto &process : completedProcesses) { //display in order of completion
      cout << process.getProcessId() << " ";
  }
  cout << endl;
}

//display Gantt chart for SJF Scheduling
void SJFScheduler::displayGanttChart() const {
  if (completedProcesses.empty()) {
      cout << "No completed processes to display Gantt chart." << endl;
      return;
  }

  cout << "\nGantt Chart:" << endl;
  cout << "Time:  ";
 
  for (const auto &process : completedProcesses) { 
      int startime = process.getCompletionTime() - process.getBurstTime(); //calculate start time
      cout << "| " << process.getProcessId() << " (" << startime << "-" << process.getCompletionTime() << ") "; //display process with its time frame

  }
  cout << "|" << endl;
}

//get average waiting time
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
  if (getTotalExecutionTime() == 0) return 0;
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

//FCFS_Scheduler Class Implementation are below here
//FCFS Scheduler Implementation

void FCFS_Scheduler::executeScheduling() {
    if (processes.empty()) {
        cout << "No processes to schedule." << endl;
        return;
    }
    
    completedProcesses.clear();
    calculateFCFS();
    
    // Use the inherited performance metrics display
    // printPerformanceMetrics();
}

//method to calculate FCFS scheduling
void FCFS_Scheduler::calculateFCFS() {
    // Sort processes by arrival time
    // sort(processes.begin(), processes.end(), 
    //      [](const Process &a, const Process &b) {
    //          return a.getArrivalTime() < b.getArrivalTime();
    //      });

    sortByArrivalTime();
    
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

    setIdleTime(idleTime);
    setTotalExecutionTime(totalExecutionTime);
}

//all preemptive priority scheduling methods are below here
//calculate Preemptive Priority Scheduling

void PP_Scheduler::calculatePP() {
    if (processes.empty()) return;

    // Sort processes by arrival time
    sortByArrivalTime();

    vector<Process> tempProcesses = processes; // Copy of processes to manipulate
    vector<int> remainingTime(tempProcesses.size()); // Track remaining burst time
    vector<bool> started(tempProcesses.size(), false); // Track if process has started
    vector<int> startTime(tempProcesses.size(), -1); // Track when each process first started

    // Initialize remaining times
    for (int i = 0; i < tempProcesses.size(); i++) {
        remainingTime[i] = tempProcesses[i].getBurstTime();
    }

    int currentTime = 0;
    int completedCount = 0;
    int n = tempProcesses.size();
    int trackIdleTime = 0;
    
    Process* currentProcess = nullptr;
    int currentProcessIndex = -1;
    int previousTime = 0;

    cout << "Starting Preemptive Priority Scheduling..." << endl;
    cout << "Execution Order: ";

    

    while (completedCount < n) {
        // Add all processes that have arrived by currentTime to the ready queue
        for (int i = 0; i < n; i++) {
            if (tempProcesses[i].getArrivalTime() <= currentTime && 
                remainingTime[i] > 0) {
                // Process will be automatically sorted by priority in the queue
                bool alreadyInQueue = false;
                
                // Create a temporary queue to check if process is already in queue
                auto tempQueue = readyQueuePP;
                while (!tempQueue.empty()) {
                    if (tempQueue.top().getProcessId() == tempProcesses[i].getProcessId()) {
                        alreadyInQueue = true;
                        break;
                    }
                    tempQueue.pop();
                }
                
                if (!alreadyInQueue) {
                    readyQueuePP.push(tempProcesses[i]);
                }
            }
        }

        if (!readyQueuePP.empty()) {
            // Get the process with the highest priority (lowest priority number)
            Process nextProcess = readyQueuePP.top();
            readyQueuePP.pop();
            
            // Find the index of the next process
            int nextIndex = -1;
            for (int i = 0; i < n; i++) {
                if (tempProcesses[i].getProcessId() == nextProcess.getProcessId() && 
                    remainingTime[i] > 0) {
                    nextIndex = i;
                    break;
                }
            }
            
            if (nextIndex == -1) continue;

            // If a different process is being scheduled, show the transition
            if (currentProcess == nullptr || 
                currentProcess->getProcessId() != tempProcesses[nextIndex].getProcessId()) {
                
                if (currentProcess != nullptr) {
                    // Show completion of previous process segment
                    cout << currentProcess->getProcessId() << "(" << previousTime << "-" << currentTime << ") ";

                    //record the completed segment of the previous process
                    executionHistory.push_back(make_pair(tempProcesses[nextIndex].getProcessId(), 
                                   make_pair(previousTime, currentTime)));
                }
                
                currentProcess = &tempProcesses[nextIndex];
                currentProcessIndex = nextIndex;
                previousTime = currentTime;
                
                // Set response time when process first starts
                if (!started[nextIndex]) {
                    startTime[nextIndex] = currentTime;
                    started[nextIndex] = true;
                }
            }

            // Execute the process for 1 time unit (preemptive)
            remainingTime[nextIndex]--;
            currentTime++;

            // record the final segment of the process execution
            executionHistory.push_back(make_pair(tempProcesses[nextIndex].getProcessId(), 
                                   make_pair(previousTime, currentTime)));

            // Check if process completed
            if (remainingTime[nextIndex] == 0) {
                completedCount++;
                
                // Calculate completion time and other metrics
                int completionTime = currentTime;
                int turnaroundTime = completionTime - tempProcesses[nextIndex].getArrivalTime();
                int waitingTime = turnaroundTime - tempProcesses[nextIndex].getBurstTime();
                int responseTime = startTime[nextIndex] - tempProcesses[nextIndex].getArrivalTime();

                // Update the process with calculated times
                tempProcesses[nextIndex].setCompletionTime(completionTime);
                tempProcesses[nextIndex].setWaitingTime(waitingTime);
                tempProcesses[nextIndex].setTurnaroundTime(turnaroundTime);
                tempProcesses[nextIndex].setResponseTime(responseTime);
                
                completedProcesses.push_back(tempProcesses[nextIndex]);
                
                // Show completion
                cout << tempProcesses[nextIndex].getProcessId() << "(" << previousTime << "-" << currentTime << ") ";
                
                currentProcess = nullptr;
                currentProcessIndex = -1;
            } else if(!readyQueuePP.empty() && readyQueuePP.top().getPriority() < currentProcess->getPriority()) {
                //current process is preempted by higher priority process
                executionHistory.push_back(make_pair(currentProcess->getProcessId(), 
                                                   make_pair(previousTime, currentTime)));
                
            }
        } else {
            // CPU idle - no process in ready queue
            if (completedCount < n) {
                // Find next arriving process
                int nextArrival = INT_MAX;
                for (int i = 0; i < n; i++) {
                    if (remainingTime[i] > 0 && tempProcesses[i].getArrivalTime() > currentTime) {
                        nextArrival = min(nextArrival, tempProcesses[i].getArrivalTime());
                    }
                }
                
                if (nextArrival != INT_MAX) {
                    int idleDuration = nextArrival - currentTime;
                    trackIdleTime += idleDuration;
                    
                    // Show idle time
                    cout << "IDLE(" << currentTime << "-" << nextArrival << ") ";
                    
                    currentTime = nextArrival;
                } else {
                    break; // Should not happen
                }
            }
        }
    }

    // Handle the last process segment if any
    if (currentProcess != nullptr) {
        cout << currentProcess->getProcessId() << "(" << previousTime << "-" << currentTime << ") ";
    
        executionHistory.push_back(make_pair(currentProcess->getProcessId(), 
                                   make_pair(previousTime, currentTime)));
      }

    int totalTime = currentTime;
    
    cout << "\nPreemptive Priority Scheduling Completed." << endl;
    setIdleTime(trackIdleTime);
    setTotalExecutionTime(totalTime);
}

//execute Preemptive Priority Scheduling
void PP_Scheduler::executeScheduling() {
    if (processes.empty()) {
        cout << "No processes to schedule." << endl;
        return;
    }

    executionHistory.clear();
    
    completedProcesses.clear();
    readyQueuePP = priority_queue<Process, vector<Process>, ComparePriority>(); // Clear the priority queue
    calculatePP();
}

//display Gantt chart for Preemptive Priority Scheduling
void PP_Scheduler::displayGanttChart() const {
    if (executionHistory.empty()) {
        cout << "No execution history to display Gantt chart." << endl;
        return;
    }

    cout << "\nPreemptive Priority Gantt Chart:" << endl;
    cout << "Time:  ";
    
    for (const auto &segment : executionHistory) {
        cout << "| " << segment.first << " (" << segment.second.first << "-" << segment.second.second << ") ";
    }
    cout << "|" << endl;
    
    // Also show the timeline
    cout << "       ";
    for (const auto &segment : executionHistory) {
        cout << segment.second.first << "    " << segment.second.second << "   ";
    }
    cout << endl;
}

//print process info for Preemptive Priority Scheduling
void PP_Scheduler::printProcessInfo() const {
    if (completedProcesses.empty()) {
        cout << "No completed processes to display." << endl;
        return;
    }

    cout << "Preemptive Priority Scheduling Results:" << endl;
    cout << string(80, '=') << endl;
    cout << left << setw(8) << "Process"
         << setw(12) << "Arrival"
         << setw(10) << "Burst"
         << setw(12) << "Priority"
         << setw(12) << "Waiting"
         << setw(12) << "Response"
         << setw(15) << "Turnaround"
         << setw(16) << "Completion"
         << endl;
    cout << string(80, '=') << endl;

    for (const auto &process : completedProcesses) {
        process.displayProcessInfo();
    }
}

//MLQ Scheduler Implementation would go below here
// Default constructor
MLQ_Scheduler::MLQ_Scheduler()  {

    initializeQueues(3); // Default to 3 queues
    timeQuanta = {8, 16, INT_MAX}; // Default time quanta for each queue

}

// Parameterized constructor
MLQ_Scheduler::MLQ_Scheduler(int numQueues, const vector<int>& timeQuanta) {
    initializeQueues(numQueues);
    setTimeQuanta(timeQuanta);
}

// Initialize the queues based on the number of levels
void MLQ_Scheduler::initializeQueues(int numQueues) {
    queues.clear();
    queues.resize(numQueues);
}

// Set time quanta for each queue level
void MLQ_Scheduler::addProcess(const string processId, int arrivalTime, int burstTime, int priority, int queueLevel) {
    Process newProcess(processId, arrivalTime, burstTime, priority);
    newProcess.setQueueLevel(queueLevel);
    processes.push_back(newProcess);
}

// Set time quanta for each queue level
void MLQ_Scheduler::setTimeQuanta(const vector<int>& timeQuanta) {
    this->timeQuanta = timeQuanta;
}

// Set number of queues
void MLQ_Scheduler::setNumberOfQueues(int numQueues) {
    initializeQueues(numQueues);
}

void MLQ_Scheduler::calculateMLQ() {
    if (processes.empty()) return;

    //sort processes by arrival time
    sortByArrivalTime();

    vector<Process> tempProcesses = processes; // Copy of processes to manipulate
    vector<int> remainingTime(tempProcesses.size()); // Track remaining burst time
    vector<bool> started(tempProcesses.size(), false); // Track if process has started
    vector<int> startTime(tempProcesses.size(), -1); // Track when each process first started

    //initialize remaining times and distribute processes into their respective queues
    for (int i = 0; i < tempProcesses.size(); i++) {
        remainingTime[i] = tempProcesses[i].getBurstTime();
        int qLevel = tempProcesses[i].getQueueLevel();
        if (qLevel >= 0 && qLevel < queues.size()) {
            queues[qLevel].push(tempProcesses[i]);
        } else {
            // Invalid queue level, assign to lowest priority queue
            queues.back().push(tempProcesses[i]);
        }
    }

    int currentTime = 0;
    int completedCount = 0;
    int n = tempProcesses.size();
    int trackIdleTime = 0;

    cout << "Starting Multi-Level Queue Scheduling..." << endl;
    cout << "Execution Order: ";

    while (completedCount < n) {
        //find the highest priority queue with an available process
        int selectedQueueIndex = -1;
        for(int q = 0; q < queues.size(); q++) {
            if(!queues[q].empty()) {
                // Check if the front process has arrived
                Process frontProcess = queues[q].front();
                if(frontProcess.getArrivalTime() <= currentTime) {
                    selectedQueueIndex = q;
                    break;
                }
            }
        }

        if (selectedQueueIndex != -1) {
            //get the first process from the selected queue
            Process currentProcess = queues[selectedQueueIndex].front();
            queues[selectedQueueIndex].pop();

            //find the actual process index
            int processIndex = -1;
            for (int i = 0; i < n; i++) {
                if (tempProcesses[i].getProcessId() == currentProcess.getProcessId() && 
                    remainingTime[i] > 0) {
                    processIndex = i;
                    break;
                }
            }

            if (processIndex == -1) continue;

            //set response time if not started
            if (!started[processIndex]) {
                startTime[processIndex] = currentTime;
                started[processIndex] = true;
                tempProcesses[processIndex].setResponseTime(currentTime - tempProcesses[processIndex].getArrivalTime());
            }

            int executionStart = currentTime;
            int executionTime = min(remainingTime[processIndex], timeQuanta[selectedQueueIndex]);

            //execute the process for the determined execution time
            if(timeQuanta[selectedQueueIndex] == INT_MAX) {
                //run to completion
                currentTime += remainingTime[processIndex];
                remainingTime[processIndex] = 0;
            } else {
                // RR behavior - execute for time quantum or remaining time
                currentTime += executionTime;
                remainingTime[processIndex] -= executionTime;
            }

            //record execution history
            executionHistory.push_back(make_pair(tempProcesses[processIndex].getProcessId(), 
                                       make_pair(executionStart, currentTime)));

            cout << tempProcesses[processIndex].getProcessId() << "(" << executionStart << "-" << currentTime << ") ";

            //check if process completed
            if (remainingTime[processIndex] == 0) {
                completedCount++;

                //calculate completion time and other metrics
                int completionTime = currentTime;
                int turnaroundTime = completionTime - tempProcesses[processIndex].getArrivalTime();
                int waitingTime = turnaroundTime - tempProcesses[processIndex].getBurstTime();

                //update the process with calculated times
                tempProcesses[processIndex].setCompletionTime(completionTime);
                tempProcesses[processIndex].setWaitingTime(waitingTime);
                tempProcesses[processIndex].setTurnaroundTime(turnaroundTime);

                completedProcesses.push_back(tempProcesses[processIndex]);
            } else {
                //process not completed, demote to lower priority queue if possible
                int newQueueLevel = min(selectedQueueIndex + 1, static_cast<int>(queues.size() - 1));
                tempProcesses[processIndex].setQueueLevel(newQueueLevel);
                queues[newQueueLevel].push(tempProcesses[processIndex]);
            }

        } else {
            // CPU idle - no process in any queue
            // Handle idle time and advance currentTime accordingly
            int nextArrival = INT_MAX;
            for(int i = 0; i < n; i++) {
                if (remainingTime[i] > 0 && tempProcesses[i].getArrivalTime() > currentTime) {
                    nextArrival = min(nextArrival, tempProcesses[i].getArrivalTime());
                }
            }

            if (nextArrival != INT_MAX) {
                int idleDuration = nextArrival - currentTime;
                trackIdleTime += idleDuration;

                // Show idle time
                cout << "IDLE(" << currentTime << "-" << nextArrival << ") ";
                executionHistory.push_back(make_pair("IDLE", make_pair(currentTime, nextArrival)));

                currentTime = nextArrival;
            } else {
                break; // Should not happen
            }
        }
    }

    cout << "\nMulti-Level Queue Scheduling Completed." << endl;
    setIdleTime(trackIdleTime);
    setTotalExecutionTime(currentTime);
}

void MLQ_Scheduler::executeScheduling() {
    if (processes.empty()) {
        cout << "No processes to schedule." << endl;
        return;
    }

    executionHistory.clear();

    completedProcesses.clear();
    // Clear all queues
    for (auto &q : queues) {
        while (!q.empty()) {
            q.pop();
        }
    }

    calculateMLQ();
}

void MLQ_Scheduler::printProcessInfo() const {
    if (completedProcesses.empty()) {
        cout << "No completed processes to display." << endl;
        return;
    }

    cout << "Multi-Level Queue Scheduling Results:" << endl;
    cout << string(85, '=') << endl;
    cout << left << setw(8) << "Process"
         << setw(12) << "Arrival"
         << setw(10) << "Burst"
         << setw(12) << "Priority"
         << setw(12) << "QueueLvl"
         << setw(12) << "Waiting"
         << setw(12) << "Response"
         << setw(15) << "Turnaround"
         << setw(16) << "Completion"
         << endl;
    cout << string(85, '=') << endl;

    for (const auto &process : completedProcesses) {
        process.displayProcessInfoWithQueueLevel();
    }
}

void MLQ_Scheduler::displayGanttChart() const {
    if (executionHistory.empty()) {
        cout << "No execution history to display Gantt chart." << endl;
        return;
    }

    cout << "\nMulti-Level Queue Gantt Chart:" << endl;
    cout << "Time:  ";

    for (const auto &segment : executionHistory) {
        cout << "| " << segment.first << " (" << segment.second.first << "-" << segment.second.second << ") ";
    }
    cout << "|" << endl;

    // Also show the timeline
    cout << "       ";
    for (const auto &segment : executionHistory) {
        cout << segment.second.first << "    " << segment.second.second << "   ";
    }
    cout << endl;

    //Show queue configurations
    cout << "\nQueue Configurations:" << endl;
    for (int i = 0; i < timeQuanta.size(); i++) {
        cout << "Queue " << i << ": Time Quantum = ";
        if (timeQuanta[i] == INT_MAX) {
            cout << "FCFS (No Time Quantum)" << endl;
        } else {
            cout <<"RR with quantum = " << timeQuanta[i] << endl;
        }
    }
}