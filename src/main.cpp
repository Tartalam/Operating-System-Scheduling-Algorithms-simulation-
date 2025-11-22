#include "FCFS_Scheduler.h"

int main() {
    FCFS_Scheduler scheduler;
    
    // Add processes: ID, Arrival Time, Burst Time
    scheduler.addProcess(1, 4, 5);
    scheduler.addProcess(2, 1, 3);
    scheduler.addProcess(3, 2, 8);
    scheduler.addProcess(4, 3, 6);
    
    // Calculate scheduling
    scheduler.calculateFCFS();
    
    // Display results
    scheduler.printResults();
    scheduler.printGanttChart();
    scheduler.printPerformanceMetrics();
    
    return 0;
}