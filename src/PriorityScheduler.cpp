#include "PriorityScheduler.h"

void PriorityScheduler::addProcess(const Process &p) {
    processes.push_back(p);
}

void PriorityScheduler::clearProcesses() {
    processes.clear();
    ganttChart.clear();
}

void PriorityScheduler::executeScheduling() {
    int n = processes.size();
    int time = 0, completed = 0;

    // Initialize remaining times and start times
    for (auto &p : processes) {
        p.remainingTime = p.burstTime;
        p.startTime = -1;
        p.completionTime = 0;
    }

    while (completed != n) {
        int current = -1;
        int bestPriority = numeric_limits<int>::max();

        // Find available process with the highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0) {
                if (processes[i].priority < bestPriority) {
                    bestPriority = processes[i].priority;
                    current = i;
                }
            }
        }

        if (current != -1) {
            // First time the process starts
            if (processes[current].startTime == -1)
                processes[current].startTime = time;

            // Execute for 1 time unit
            processes[current].remainingTime--;

            // Log Gantt chart entry
            ganttChart.push_back({processes[current].Id, time});

            if (processes[current].remainingTime == 0) {
                processes[current].completionTime = time + 1;
                completed++;
            }
        } else {
            ganttChart.push_back({-1, time}); // idle time
        }

        time++;
    }

    // Compute turnaround, wait, response
    for (auto &p : processes) {
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        p.responseTime = p.startTime - p.arrivalTime;
    }
}

void PriorityScheduler::printProcessInfo() const {
    cout << "\nPID\tAT\tBT\tP\tST\tCT\tTAT\tWT\n";
    for (const auto &p : processes) {
        cout << "P" << p.Id << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.priority << "\t"
             << p.startTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\n";
    }
}

void PriorityScheduler::printPerformanceMetrics() const {
    double totalWT = 0, totalTAT = 0, totalRT = 0;

    for (const auto &p : processes) {
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
        totalRT += p.responseTime;
    }

    int n = processes.size();
    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Response Time: " << totalRT / n << "\n";
}

void PriorityScheduler::displayGanttChart() const {
    cout << "\nGantt Chart:\n| ";

    for (auto &g : ganttChart) {
        if (g.first == -1)
            cout << "IDLE | ";
        else
            cout << "P" << g.first << " | ";
    }

    cout << "\n0 ";
    for (int i = 1; i <= ganttChart.size(); i++)
        cout << i << " ";

    cout << endl;
}
