// #ifndef FCFS_SCHEDULER_H
// #define FCFS_SCHEDULER_H

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <iomanip>

// using namespace std;

// class Process {
// public:
//     int id;
//     int arrivalTime;
//     int burstTime;
//     int completionTime;
//     int turnaroundTime;
//     int waitingTime;
//     int startTime;
    
//     Process(int id, int arrival, int burst) {
//         this->id = id;
//         this->arrivalTime = arrival;
//         this->burstTime = burst;
//         this->completionTime = 0;
//         this->turnaroundTime = 0;
//         this->waitingTime = 0;
//         this->startTime = 0;
//     }
// };

// class FCFS_Scheduler {
// private:
//     vector<Process> processes;
//     vector<pair<int, int>> ganttChart; // {process_id, end_time}
    
// public:
//     void addProcess(int id, int arrival, int burst) {
//         processes.push_back(Process(id, arrival, burst));
//     }
    
//     void calculateFCFS() {
//         // Sort processes by arrival time
//         sort(processes.begin(), processes.end(), 
//              [](const Process &a, const Process &b) {
//                  return a.arrivalTime < b.arrivalTime;
//              });
        
//         int currentTime = 0;
//         ganttChart.clear();
        
//         for (auto &p : processes) {
//             // If CPU is idle, jump to process arrival time
//             if (currentTime < p.arrivalTime) {
//                 currentTime = p.arrivalTime;
//             }
            
//             // Set start time and calculate completion time
//             p.startTime = currentTime;
//             p.completionTime = currentTime + p.burstTime;
            
//             // Calculate turnaround and waiting time
//             p.turnaroundTime = p.completionTime - p.arrivalTime;
//             p.waitingTime = p.startTime - p.arrivalTime; // Fixed: waiting time = start - arrival
            
//             // Add to Gantt chart
//             ganttChart.push_back({p.id, p.completionTime});
            
//             // Update current time
//             currentTime = p.completionTime;
//         }
//     }
    
//     void printGanttChart() {
//         cout << "\nGantt Chart:" << endl;
//         cout << "-----------" << endl;
        
//         // Print top border
//         for (size_t i = 0; i < ganttChart.size(); i++) { // Fixed: use size_t
//             cout << "-------";
//         }
//         cout << "-" << endl;
        
//         // Print process IDs
//         cout << "|";
//         for (const auto &entry : ganttChart) {
//             cout << "  P" << entry.first << "  |";
//         }
//         cout << endl;
        
//         // Print bottom border
//         for (size_t i = 0; i < ganttChart.size(); i++) { // Fixed: use size_t
//             cout << "-------";
//         }
//         cout << "-" << endl;
        
//         // Print time points
//         int lastTime = 0;
//         cout << "0";
//         for (const auto &entry : ganttChart) {
//             cout << setw(7) << entry.second;
//             lastTime = entry.second;
//         }
//         cout << endl;
//     }
    
//     void printResults() {
//         cout << "\nFCFS Scheduling Results:" << endl;
//         cout << "PID\tArrival\tBurst\tStart\tCompletion\tTAT\tWT" << endl;
//         cout << "----------------------------------------------------" << endl;
        
//         double avgTAT = 0, avgWT = 0;
        
//         for (const auto &p : processes) {
//             cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime 
//                  << "\t" << p.startTime << "\t" << p.completionTime 
//                  << "\t\t" << p.turnaroundTime << "\t" << p.waitingTime << endl;
            
//             avgTAT += p.turnaroundTime;
//             avgWT += p.waitingTime;
//         }
        
//         int n = processes.size();
//         cout << fixed << setprecision(2);
//         cout << "\nAverage Turnaround Time: " << avgTAT / n << endl;
//         cout << "Average Waiting Time: " << avgWT / n << endl;
//     }
    
//     void printPerformanceMetrics() {
//         int totalTime = 0;
//         int totalBurstTime = 0;
//         int n = processes.size();
        
//         if (n == 0) { // Added: check for empty process list
//             cout << "\nNo processes to calculate metrics." << endl;
//             return;
//         }
        
//         for (const auto &p : processes) {
//             if (p.completionTime > totalTime) {
//                 totalTime = p.completionTime;
//             }
//             totalBurstTime += p.burstTime;
//         }
        
//         if (totalTime == 0) { // Added: prevent division by zero
//             totalTime = 1;
//         }
        
//         double cpuUtilization = (double)totalBurstTime / totalTime * 100;
//         double throughput = (double)n / totalTime;
        
//         cout << "\nPerformance Metrics:" << endl;
//         cout << "-------------------" << endl;
//         cout << fixed << setprecision(2);
//         cout << "CPU Utilization: " << cpuUtilization << "%" << endl;
//         cout << "Throughput: " << throughput << " processes/unit time" << endl;
//         cout << "Total Execution Time: " << totalTime << " units" << endl;
//     }
// };

// #endif