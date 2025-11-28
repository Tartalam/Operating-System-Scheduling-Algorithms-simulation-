//Author: Jahmari Harrison
//Date: 2023-10-20
//Description: Implementation file for main program to run CPU scheduling simulations.
//ID: 2304204
//Attributions: This code wsa completed witht the help fo exteranl libraries and resources including StackOverflow and GeeksforGeeks for console handling techniques.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>
#include "SJFScheduler.h"
#include "Process.h"
#include "FCFS_Scheduler.h"
#include "PP_Scheduler.h"
#include "MLQ_Scheduler.h"


using namespace std;

// Function prototypes
int displayMainMenu();
int displayTestMenu(const string& algorithmName);
int displayReturnMenu();
void runSJFTest(int testType);
void runFCFSTest(int testType);
void runPriorityTest(int testType);
void runMultiLevelQueueTest(int testType);
void runCustomTest(SJFScheduler& scheduler, bool& returnToPrevious);
void runAutomatedTest(SJFScheduler& scheduler, bool& returnToPrevious);
void runCustomTest(FCFS_Scheduler& scheduler, bool& returnToPrevious);
void runAutomatedTest(FCFS_Scheduler& scheduler, bool& returnToPrevious);
void runCustomTest(PP_Scheduler& scheduler, bool& returnToPrevious);
void runAutomatedTest(PP_Scheduler& scheduler, bool& returnToPrevious);
void runCustomTest(MLQ_Scheduler& scheduler, bool& returnToPrevious);
void runAutomatedTest(MLQ_Scheduler& scheduler, bool& returnToPrevious);
void clearConsole();
int getChoiceWithReturn(int minChoice, int maxChoice, bool showReturnOption = false);
int getPositiveInput(const string& prompt, bool allowZero = false);

void clearConsole() {
    // Moves cursor to home position (1,1) and clears screen from cursor to end
    std::cout << "\033[H\033[2J"; 
    std::cout.flush(); // Ensure the output is sent immediately
}

   

int displayMainMenu() {
    
    clearConsole();
    
    cout << "=============================================\n";
    cout << "      CPU SCHEDULING ALGORITHMS SIMULATOR\n";
    cout << "=============================================\n";
    cout << "1. Shortest Job First (SJF) - Non-preemptive\n";
    cout << "2. First Come First Served (FCFS)\n";
    cout << "3. Priority Scheduling (Preemptive)\n";
    cout << "4. Multi-level Queue Scheduling\n";
    cout << "5. Exit\n";
    cout << "=============================================\n";

    
   return getChoiceWithReturn(1, 5);
    
}

int displayTestMenu(const string& algorithmName) {
    clearConsole();
    // Display test menu for the selected algorithm
    cout << "=============================================\n"
         << "          " << algorithmName << " SCHEDULING\n"
         << "=============================================\n"
         << "1. Custom Test - Manual Process Input\n"
         << "2. Automated Test - Random Process Generation\n"
         << "3. Return to Main Menu\n"
         << "=============================================\n";
    return getChoiceWithReturn(1, 3);
}

int displayReturnMenu() {
    clearConsole();
    cout << "\n=============================================\n"
         << "1. Return to Previous Menu\n"
         << "2. Return to Main Menu\n"
         << "3. Exit Program\n"
         << "=============================================\n";
    return getChoiceWithReturn(1, 3);
}

// Get choice input with optional return option
//this method was derived witht he help from code found on StackOverflow
int getChoiceWithReturn(int minChoice, int maxChoice, bool showReturnOption) {
    int choice;
    while (true) {
        if (showReturnOption) {
            cout << "Enter your choice (1-" << maxChoice << ") or 0 to return: " << endl;
        } else {
            cout << "Enter your choice (" << minChoice << "-" << maxChoice << "): " << endl;
        }
        
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        
        if (showReturnOption && choice == 0) {
            return 0; // Return signal
        }
        
        if (choice >= minChoice && choice <= maxChoice) {
            return choice;
        }
        
        cout << "Invalid choice! Please enter " << minChoice << "-" << maxChoice;
        if (showReturnOption) {
            cout << " or 0 to return" << endl;
        }
        cout << "." << endl;
    }
}

// Get positive integer input with optional zero allowance
//this method was derived witht he help from code found on StackOverflow 
int getPositiveInput(const string& prompt, bool allowZero) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        
        if (value == 0 && allowZero) {
            return 0; // Allow zero for return functionality
        }
        
        if (value >= 0) {
            return value;
        }
        
        cout << "Invalid input! Please enter a positive number";
        if (allowZero) {
            cout << " or 0 to return";
        }
        cout << ".\n";
    }
}

void runCustomTest(SJFScheduler& scheduler, bool& returnToPrevious) {
    clearConsole();
    cout << "CUSTOM TEST - MANUAL PROCESS INPUT\n";
    cout << "===================================\n\n";
    
    scheduler.clearProcesses();
    

    
    int numProcesses = getPositiveInput("Enter number of processes (or 0 to return): ", true);
    
    if (numProcesses == 0) {
        returnToPrevious = true;
        return;
    }
    
    if (numProcesses < 1) {
        cout << "Invalid number of processes!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    for (int i = 1; i <= numProcesses; i++) {
        string processId = "P" + to_string(i);
        int arrivalTime, burstTime, priority;
        
        cout << "\nProcess " << processId << " (enter -1 for arrival time to cancel):\n";
        
        // Get arrival time
        arrivalTime = getPositiveInput("Arrival Time: ");
        if (arrivalTime == -1) {
            returnToPrevious = true;
            return;
        }
        
        // Get burst time
        burstTime = getPositiveInput("Burst Time: ");
        if (burstTime == -1) {
            returnToPrevious = true;
            return;
        }
        
        if (burstTime == 0) {
            cout << "Burst time cannot be zero! Please enter a positive number.\n";
            i--; // Retry this process
            continue;
        }
       
            // Use overloaded addProcess without priority
            scheduler.addProcess(processId, arrivalTime, burstTime);
            cout << "Added: " << processId << "(" << arrivalTime << "," << burstTime << ")\n";
        
    }
    
    cout << "\nPress Enter to execute scheduling (or any other key + Enter to cancel)...";
    cin.ignore();
    if (cin.get() != '\n') {
        returnToPrevious = true;
        return;
    }
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.displayGanttChart();
    scheduler.printPerformanceMetrics();
    
    // After results are displayed, show return options
    int returnChoice = displayReturnMenu();
    switch (returnChoice) {
        case 1:
            returnToPrevious = true;
            break;
        case 2:
            returnToPrevious = false; // Will go to main menu
            break;
        case 3:
            exit(0);
            break;
    }
}

void runCustomTest(PP_Scheduler& scheduler, bool& returnToPrevious) {
    clearConsole();
    cout << "CUSTOM TEST - MANUAL PROCESS INPUT\n";
    cout << "===================================\n\n";
    
    scheduler.clearProcesses();
    
    // Ask about priority usage
    char usePriority = 'y';
  
    
    int numProcesses = getPositiveInput("Enter number of processes (or 0 to return): ", true);
    
    if (numProcesses == 0) {
        returnToPrevious = true;
        return;
    }
    
    if (numProcesses < 1) {
        cout << "Invalid number of processes!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    for (int i = 1; i <= numProcesses; i++) {
        string processId = "P" + to_string(i);
        int arrivalTime, burstTime, priority;
        
        cout << "\nProcess " << processId << " (enter -1 for arrival time to cancel):\n";
        
        // Get arrival time
        arrivalTime = getPositiveInput("Arrival Time: ");
        if (arrivalTime == -1) {
            returnToPrevious = true;
            return;
        }
        
        // Get burst time
        burstTime = getPositiveInput("Burst Time: ");
        if (burstTime == -1) {
            returnToPrevious = true;
            return;
        }
        
        if (burstTime == 0) {
            cout << "Burst time cannot be zero! Please enter a positive number.\n";
            i--; // Retry this process
            continue;
        }
        
        if (usePriority == 'y') {
            // Get priority (must be >= 0)
            priority = getPositiveInput("Priority (>= 0): ");
            if (priority == -1) {
                returnToPrevious = true;
                return;
            }
            
            // Use overloaded addProcess with priority
            scheduler.addProcess(processId, arrivalTime, burstTime, priority);
            cout << "Added: " << processId << "(" << arrivalTime << "," << burstTime << "," << priority << ")\n";
        } 
    }
    
    cout << "\nPress Enter to execute scheduling (or any other key + Enter to cancel)...";
    cin.ignore();
    if (cin.get() != '\n') {
        returnToPrevious = true;
        return;
    }
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.displayGanttChart();
    scheduler.printPerformanceMetrics();
    
    // After results are displayed, show return options
    int returnChoice = displayReturnMenu();
    switch (returnChoice) {
        case 1:
            returnToPrevious = true;
            break;
        case 2:
            returnToPrevious = false; // Will go to main menu
            break;
        case 3:
            exit(0);
            break;
    }
}

void runCustomTest(FCFS_Scheduler& scheduler, bool& returnToPrevious) {
    clearConsole();
    cout << "CUSTOM TEST - MANUAL PROCESS INPUT\n";
    cout << "===================================\n\n";
    
    scheduler.clearProcesses();
    
   
    
    int numProcesses = getPositiveInput("Enter number of processes (or 0 to return): ", true);
    
    if (numProcesses == 0) {
        returnToPrevious = true;
        return;
    }
    
    if (numProcesses < 1) {
        cout << "Invalid number of processes!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    for (int i = 1; i <= numProcesses; i++) {
        string processId = "P" + to_string(i);
        int arrivalTime, burstTime, priority;
        
        cout << "\nProcess " << processId << " (enter -1 for arrival time to cancel):\n";
        
        // Get arrival time
        arrivalTime = getPositiveInput("Arrival Time: ");
        if (arrivalTime == -1) {
            returnToPrevious = true;
            return;
        }
        
        // Get burst time
        burstTime = getPositiveInput("Burst Time: ");
        if (burstTime == -1) {
            returnToPrevious = true;
            return;
        }
        
        if (burstTime == 0) {
            cout << "Burst time cannot be zero! Please enter a positive number.\n";
            i--; // Retry this process
            continue;
        }
        

            // Use overloaded addProcess without priority
            scheduler.addProcess(processId, arrivalTime, burstTime);
            cout << "Added: " << processId << "(" << arrivalTime << "," << burstTime << ")\n";
        
    }
    
    cout << "\nPress Enter to execute scheduling (or any other key + Enter to cancel)...";
    cin.ignore();
    if (cin.get() != '\n') {
        returnToPrevious = true;
        return;
    }
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.displayGanttChart();
    scheduler.printPerformanceMetrics();
    
    // After results are displayed, show return options
    int returnChoice = displayReturnMenu();
    switch (returnChoice) {
        case 1:
            returnToPrevious = true;
            break;
        case 2:
            returnToPrevious = false; // Will go to main menu
            break;
        case 3:
            exit(0);
            break;
    }
}

void runAutomatedTest(SJFScheduler& scheduler, bool& returnToPrevious) {
    clearConsole();
    cout << "AUTOMATED TEST - RANDOM PROCESS GENERATION\n";
    cout << "==========================================\n\n";
    
    scheduler.clearProcesses();
    

    
    int numProcesses = getPositiveInput("Enter number of processes to generate (or 0 to return): ", true);
    
    if (numProcesses == 0) {
        returnToPrevious = true;
        return;
    }
    
    if (numProcesses < 1) {
        cout << "Invalid number of processes!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    int maxArrival = getPositiveInput("Maximum arrival time: ");
    int maxBurst = getPositiveInput("Maximum burst time: ");
    
    if (maxBurst == 0) {
        cout << "Maximum burst time cannot be zero!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
 
    
    // Seed random number generator
    srand(time(0));
    
    cout << "\nGenerated Processes:\n";
    for (int i = 1; i <= numProcesses; i++) {
        string processId = "P" + to_string(i);
        int arrivalTime = rand() % (maxArrival + 1);
        int burstTime = 1 + rand() % maxBurst; // Minimum burst time of 1
        
      
        // Use overloaded addProcess without priority
        scheduler.addProcess(processId, arrivalTime, burstTime);
        cout << processId << "(" << arrivalTime << "," << burstTime << ") ";
        
        
        if (i % 4 == 0) cout << endl;
    }
    cout << endl;
    
    cout << "\nPress Enter to execute scheduling (or any other key + Enter to cancel)...";
    cin.ignore();
    if (cin.get() != '\n') {
        returnToPrevious = true;
        return;
    }
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.displayGanttChart();
    scheduler.printPerformanceMetrics();
    
    // After results are displayed, show return options
    int returnChoice = displayReturnMenu();
    switch (returnChoice) {
        case 1:
            returnToPrevious = true;
            break;
        case 2:
            returnToPrevious = false;
            break;
        case 3:
            exit(0);
            break;
    }
}

void runAutomatedTest(FCFS_Scheduler& scheduler, bool& returnToPrevious) {
    clearConsole();
    cout << "AUTOMATED TEST - RANDOM PROCESS GENERATION\n";
    cout << "==========================================\n\n";
    
    scheduler.clearProcesses();
    
    
    int numProcesses = getPositiveInput("Enter number of processes to generate (or 0 to return): ", true);
    
    if (numProcesses == 0) {
        returnToPrevious = true;
        return;
    }
    
    if (numProcesses < 1) {
        cout << "Invalid number of processes!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    int maxArrival = getPositiveInput("Maximum arrival time: ");
    int maxBurst = getPositiveInput("Maximum burst time: ");
    
    if (maxBurst == 0) {
        cout << "Maximum burst time cannot be zero!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    

    
    // Seed random number generator
    srand(time(0));
    
    cout << "\nGenerated Processes:\n";
    for (int i = 1; i <= numProcesses; i++) {
        string processId = "P" + to_string(i);
        int arrivalTime = rand() % (maxArrival + 1);
        int burstTime = 1 + rand() % maxBurst; // Minimum burst time of 1
        
     
        // Use overloaded addProcess without priority
        scheduler.addProcess(processId, arrivalTime, burstTime);
        cout << processId << "(" << arrivalTime << "," << burstTime << ") ";
        
        
        if (i % 4 == 0) cout << endl;
    }
    cout << endl;
    
    cout << "\nPress Enter to execute scheduling (or any other key + Enter to cancel)...";
    cin.ignore();
    if (cin.get() != '\n') {
        returnToPrevious = true;
        return;
    }
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.displayGanttChart();
    scheduler.printPerformanceMetrics();
    
    // After results are displayed, show return options
    int returnChoice = displayReturnMenu();
    switch (returnChoice) {
        case 1:
            returnToPrevious = true;
            break;
        case 2:
            returnToPrevious = false;
            break;
        case 3:
            exit(0);
            break;
    }
}

void runAutomatedTest(PP_Scheduler& scheduler, bool& returnToPrevious) {
    clearConsole();
    cout << "AUTOMATED TEST - RANDOM PROCESS GENERATION\n";
    cout << "==========================================\n\n";
    
    scheduler.clearProcesses();
    
    // Ask about priority usage
    char usePriority = 'y';
 
    
    int numProcesses = getPositiveInput("Enter number of processes to generate (or 0 to return): ", true);
    
    if (numProcesses == 0) {
        returnToPrevious = true;
        return;
    }
    
    if (numProcesses < 1) {
        cout << "Invalid number of processes!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    int maxArrival = getPositiveInput("Maximum arrival time: ");
    int maxBurst = getPositiveInput("Maximum burst time: ");
    
    if (maxBurst == 0) {
        cout << "Maximum burst time cannot be zero!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    int maxPriority = 0;
    if (usePriority == 'y') {
        maxPriority = getPositiveInput("Maximum priority: ");
        if (maxPriority == 0) {
            cout << "Maximum priority cannot be zero when using priority!\n";
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            returnToPrevious = true;
            return;
        }
    }
    
    // Seed random number generator
    srand(time(0));
    
    cout << "\nGenerated Processes:\n";
    for (int i = 1; i <= numProcesses; i++) {
        string processId = "P" + to_string(i);
        int arrivalTime = rand() % (maxArrival + 1);
        int burstTime = 1 + rand() % maxBurst; // Minimum burst time of 1
        
        if (usePriority == 'y') {
            int priority = 1 + rand() % maxPriority; // Priority from 1 to maxPriority
            // Use overloaded addProcess with priority
            scheduler.addProcess(processId, arrivalTime, burstTime, priority);
            cout << processId << "(" << arrivalTime << "," << burstTime << "," << priority << ") ";
        } 
        
        if (i % 4 == 0) cout << endl;
    }
    cout << endl;
    
    cout << "\nPress Enter to execute scheduling (or any other key + Enter to cancel)...";
    cin.ignore();
    if (cin.get() != '\n') {
        returnToPrevious = true;
        return;
    }
    
    scheduler.executeScheduling();
    scheduler.printProcessInfo();
    scheduler.displayGanttChart();
    scheduler.printPerformanceMetrics();
    
    // After results are displayed, show return options
    int returnChoice = displayReturnMenu();
    switch (returnChoice) {
        case 1:
            returnToPrevious = true;
            break;
        case 2:
            returnToPrevious = false;
            break;
        case 3:
            exit(0);
            break;
    }
}

//MLQ Test Runners to be added here

void runCustomTest(MLQ_Scheduler& scheduler, bool& returnToPrevious) {
    clearConsole();
    cout << "CUSTOM TEST - MANUAL PROCESS INPUT\n";
    cout << "===================================\n\n";
    
    // Use the specific queue configuration: 3 queues with time quanta {4, 8, INT_MAX}
    MLQ_Scheduler mlqScheduler(3, {4, 8, INT_MAX});
    
    // Display queue configuration first
    cout << "Queue Configuration:\n";
    cout << "Queue 0: RR with quantum = 4 (Highest Priority)\n";
    cout << "Queue 1: RR with quantum = 8 (Medium Priority)\n";
    cout << "Queue 2: FCFS (No Time Quantum) (Lowest Priority)\n";
    cout << endl;
    
    int numProcesses = getPositiveInput("Enter number of processes (or 0 to return): ", true);
    
    if (numProcesses == 0) {
        returnToPrevious = true;
        return;
    }
    
    if (numProcesses < 1) {
        cout << "Invalid number of processes!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    for (int i = 1; i <= numProcesses; i++) {
        string processId = "P" + to_string(i);
        int arrivalTime, burstTime, priority, queueLevel;
        
        cout << "\nProcess " << processId << " (enter -1 for arrival time to cancel):\n";
        
        // Get arrival time
        arrivalTime = getPositiveInput("Arrival Time: ");
        if (arrivalTime == -1) {
            returnToPrevious = true;
            return;
        }
        
        // Get burst time
        burstTime = getPositiveInput("Burst Time: ");
        if (burstTime == -1) {
            returnToPrevious = true;
            return;
        }
        
        if (burstTime == 0) {
            cout << "Burst time cannot be zero! Please enter a positive number.\n";
            i--; // Retry this process
            continue;
        }
        
        // Get priority
        priority = getPositiveInput("Priority (>= 0): ");
        if (priority == -1) {
            returnToPrevious = true;
            return;
        }
        
        // Get queue level (0-2 for the 3 queues)
        cout << "Queue Level (0-2, where 0=highest priority): ";
        queueLevel = getPositiveInput("", false);
        while (queueLevel < 0 || queueLevel > 2) {
            cout << "Invalid queue level! Please enter between 0 and 2: ";
            queueLevel = getPositiveInput("", false);
        }
        
        // Use MLQ-specific addProcess with queue level
        mlqScheduler.addProcess(processId, arrivalTime, burstTime, priority, queueLevel);
        cout << "Added: " << processId << "(" << arrivalTime << "," << burstTime << "," << priority << ",Q" << queueLevel << ")\n";
    }
    
    cout << "\nPress Enter to execute scheduling (or any other key + Enter to cancel)...";
    cin.ignore();
    if (cin.get() != '\n') {
        returnToPrevious = true;
        return;
    }
    
    mlqScheduler.executeScheduling();
    mlqScheduler.printProcessInfo();
    mlqScheduler.displayGanttChart();
    mlqScheduler.printPerformanceMetrics();
    
    // After results are displayed, show return options
    int returnChoice = displayReturnMenu();
    switch (returnChoice) {
        case 1:
            returnToPrevious = true;
            break;
        case 2:
            returnToPrevious = false; // Will go to main menu
            break;
        case 3:
            exit(0);
            break;
    }
}

void runAutomatedTest(MLQ_Scheduler& scheduler, bool& returnToPrevious) {
    clearConsole();
    cout << "AUTOMATED TEST - RANDOM PROCESS GENERATION\n";
    cout << "==========================================\n\n";
    
    // Use the specific queue configuration: 3 queues with time quanta {4, 8, INT_MAX}
    MLQ_Scheduler mlqScheduler(3, {4, 8, INT_MAX});
    
    // Display queue configuration first
    cout << "Queue Configuration:\n";
    cout << "Queue 0: RR with quantum = 4 (Highest Priority)\n";
    cout << "Queue 1: RR with quantum = 8 (Medium Priority)\n";
    cout << "Queue 2: FCFS (No Time Quantum) (Lowest Priority)\n";
    cout << endl;
    
    int numProcesses = getPositiveInput("Enter number of processes to generate (or 0 to return): ", true);
    
    if (numProcesses == 0) {
        returnToPrevious = true;
        return;
    }
    
    if (numProcesses < 1) {
        cout << "Invalid number of processes!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    int maxArrival = getPositiveInput("Maximum arrival time: ");
    int maxBurst = getPositiveInput("Maximum burst time: ");
    
    if (maxBurst == 0) {
        cout << "Maximum burst time cannot be zero!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    int maxPriority = getPositiveInput("Maximum priority: ");
    if (maxPriority == 0) {
        cout << "Maximum priority cannot be zero!\n";
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        returnToPrevious = true;
        return;
    }
    
    // Seed random number generator
    srand(time(0));
    
    cout << "\nGenerated Processes:\n";
    for (int i = 1; i <= numProcesses; i++) {
        string processId = "P" + to_string(i);
        int arrivalTime = rand() % (maxArrival + 1);
        int burstTime = 1 + rand() % maxBurst; // Minimum burst time of 1
        int priority = 1 + rand() % maxPriority; // Priority from 1 to maxPriority
        int queueLevel = rand() % 3; // Random queue level between 0 and 2
        
        // Use MLQ-specific addProcess with queue level
        mlqScheduler.addProcess(processId, arrivalTime, burstTime, priority, queueLevel);
        cout << processId << "(" << arrivalTime << "," << burstTime << "," << priority << ",Q" << queueLevel << ") ";
        
        if (i % 3 == 0) cout << endl; // New line every 3 processes for better formatting
    }
    cout << endl;
    
    cout << "\nPress Enter to execute scheduling (or any other key + Enter to cancel)...";
    cin.ignore();
    if (cin.get() != '\n') {
        returnToPrevious = true;
        return;
    }
    
    mlqScheduler.executeScheduling();
    mlqScheduler.printProcessInfo();
    mlqScheduler.displayGanttChart();
    mlqScheduler.printPerformanceMetrics();
    
    // After results are displayed, show return options
    int returnChoice = displayReturnMenu();
    switch (returnChoice) {
        case 1:
            returnToPrevious = true;
            break;
        case 2:
            returnToPrevious = false;
            break;
        case 3:
            exit(0);
            break;
    }
}


void runSJFTest(int testType) {
    SJFScheduler scheduler;
    bool returnToPrevious = false;
    
    do {
        switch (testType) {
            case 1:
                runCustomTest(scheduler, returnToPrevious);
                break;
            case 2:
                runAutomatedTest(scheduler, returnToPrevious);
                break;
            default:
                return;
        }
        
        // If returnToPrevious is true, we break out to go back to test menu
        // If false, we break out to go to main menu
        if (!returnToPrevious) {
            break;
        }
    } while (true);
}

void runFCFSTest(int testType) {
     clearConsole();
    FCFS_Scheduler scheduler;
    bool returnToPrevious = false;
    
    do {
        switch (testType) {
            case 1:
                runCustomTest(scheduler, returnToPrevious);
                break;
            case 2:
                runAutomatedTest(scheduler, returnToPrevious);
                break;
            default:
                return;
        }
        
        // If returnToPrevious is true, we break out to go back to test menu
        // If false, we break out to go to main menu
        if (!returnToPrevious) {
            break;
        }
    } while (true);

}

void runPriorityTest(int testType) {
     clearConsole();
    PP_Scheduler scheduler;
    bool returnToPrevious = false;
    
    do {
        switch (testType) {
            case 1:
                runCustomTest(scheduler, returnToPrevious);
                break;
            case 2:
                runAutomatedTest(scheduler, returnToPrevious);
                break;
            default:
                return;
        }
        
        // If returnToPrevious is true, we break out to go back to test menu
        // If false, we break out to go to main menu
        if (!returnToPrevious) {
            break;
        }
    } while (true);

}

void runMultiLevelQueueTest(int testType) {
     clearConsole();
    clearConsole();
    MLQ_Scheduler scheduler;
    bool returnToPrevious = false;
    
    do {
        switch (testType) {
            case 1:
                runCustomTest(scheduler, returnToPrevious);
                break;
            case 2:
                runAutomatedTest(scheduler, returnToPrevious);
                break;
            default:
                return;
        }
        
        // If returnToPrevious is true, we break out to go back to test menu
        // If false, we break out to go to main menu
        if (!returnToPrevious) {
            break;
        }
    } while (true);
}

int main() {
    int choice;
    
    // Seed for random number generation
    srand(time(0));
    
    while (true) {
        choice = displayMainMenu();
        
        switch (choice) {
            case 1: {
                // SJF Scheduling - Fully Implemented
                int testChoice;
                do {
                    testChoice = displayTestMenu("SHORTEST JOB FIRST");
                    
                    switch (testChoice) {
                        case 1:
                            runSJFTest(testChoice);
                            break;
                        case 2:
                            runSJFTest(testChoice);
                            break;
                        case 3:
                            // Return to main menu
                            break;
                    }
                } while (testChoice != 3);
                break;
            }
            case 2: {
                // FCFS Scheduling - Placeholder
                int testChoice;
                do {
                    testChoice = displayTestMenu("FIRST COME FIRST SERVED");
                    
                    switch (testChoice) {
                        case 1:
                            runFCFSTest(testChoice);
                            break;
                        case 2:
                            runFCFSTest(testChoice);
                            break;
                        case 3:
                            break;
                    }
                } while (testChoice != 3);
                break;
            }
            case 3: {
                // Priority Scheduling - Placeholder
                int testChoice;
                do {
                    testChoice = displayTestMenu("PRIORITY PREEMPTIVE");
                    
                    switch (testChoice) {
                        case 1:
                            runPriorityTest(testChoice);
                        case 2:
                            runPriorityTest(testChoice);
                            break;
                        case 3:
                            break;
                    }
                } while (testChoice != 3);
                break;
            }
            case 4: {
                // Multi-level Queue Scheduling - Placeholder
                int testChoice;
                do {
                    testChoice = displayTestMenu("MULTI-LEVEL QUEUE");
                    
                    switch (testChoice) {
                        case 1:
                            runMultiLevelQueueTest(testChoice);
                            break;
                        case 2:
                            runMultiLevelQueueTest(testChoice);
                            break;
                        case 3:
                            break;
                    }
                } while (testChoice != 3);
                break;
            }
            case 5:
                cout << "Thank you for using CPU Scheduling Simulator!\n";
                return 0;
        }
    }
    
    return 0;
}