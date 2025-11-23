#include <iostream>
#include "SJFScheduler.h"
#include "Process.h"

void demonstrateSJFWithPriorityQueue() {
    std::cout << "SHORTEST JOB FIRST (SJF) SCHEDULING ALGORITHM\n";
    std::cout << "Using Priority Queue (Min-Heap) for Burst Time Sorting\n";
    std::cout << "=====================================================\n\n";
    
    SJFScheduler scheduler;
    
    // Add processes - testing arrival time constraint
    scheduler.addProcess("P1", 0, 6);
    scheduler.addProcess("P2", 2, 8);
    scheduler.addProcess("P3", 3, 7);
    scheduler.addProcess("P4", 5, 3);
    
    std::cout << "Number of processes added: " << scheduler.getProcessCount() << std::endl;
    std::cout << "Processes in arrival order:\n";
    std::cout << "P1(0,6), P2(2,8), P3(3,7), P4(5,3)" << std::endl;
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.displayGanttChart();
    scheduler.printPerformanceMetrics();
}

void testArrivalTimeConstraint() {
    std::cout << "\n\nTESTING ARRIVAL TIME CONSTRAINT\n";
    std::cout << "===============================\n";
    
    SJFScheduler scheduler;
    
    // This test shows how arrival time affects scheduling
    // Even though P3 has shorter burst, P2 arrives first
    scheduler.addProcess("P1", 0, 5);
    scheduler.addProcess("P2", 1, 8);  // Arrives before P3 but longer burst
    scheduler.addProcess("P3", 2, 3);  // Shortest burst but arrives later
    scheduler.addProcess("P4", 10, 2); // Arrives much later
    
    std::cout << "Processes: P1(0,5), P2(1,8), P3(2,3), P4(10,2)" << std::endl;
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.printPerformanceMetrics();
}

void testComplexScenario() {
    std::cout << "\n\nCOMPLEX SCENARIO - MIXED ARRIVAL TIMES\n";
    std::cout << "=======================================\n";
    
    SJFScheduler scheduler;
    
    scheduler.addProcess("A", 0, 7);
    scheduler.addProcess("B", 2, 4);  // Short burst, arrives early
    scheduler.addProcess("C", 4, 1);  // Shortest burst
    scheduler.addProcess("D", 5, 4);  // Medium burst
    scheduler.addProcess("E", 10, 2); // Late arrival, short burst
    
    std::cout << "Testing complex arrival pattern..." << std::endl;
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.displayGanttChart();
    scheduler.printPerformanceMetrics();
}

int main() {
    demonstrateSJFWithPriorityQueue();
    testArrivalTimeConstraint();
    testComplexScenario();
    
    return 0;
}