# 🖥️ CPU Scheduling Algorithms Simulation

## 📋 Project Overview
This is a C++ implementation of four CPU scheduling algorithms for our Operating Systems course. The program simulates how an operating system manages processes using different scheduling strategies and provides performance metrics for comparison.

---

## 🚀 Algorithms Implemented

### 1. 🎯 First-Come, First-Served (FCFS)
- **Non-preemptive** scheduling
- Processes are executed in the order they arrive
- Simple but can cause long waiting times

### 2. ⚡ Shortest Job First (SJF) 
- **Non-preemptive** scheduling using priority queue (min-heap)
- Always picks the process with the shortest burst time next
- Minimizes average waiting time

### 3. 🔼 Preemptive Priority Scheduling
- Processes with **higher priority** (lower number) can interrupt running processes
- Uses priority queue for efficient selection
- More responsive for high-priority tasks

### 4. 🎪 Multi-Level Queue (MLQ)
- Uses **3 queues** with different scheduling policies:
  - **Queue 0**: Round Robin (quantum = 4) - **Highest priority**
  - **Queue 1**: Round Robin (quantum = 8) - **Medium priority**  
  - **Queue 2**: FCFS - **Lowest priority**
- Processes can be demoted to lower queues

---

## ✨ Features
- 🖱️ Interactive menu system for easy testing
- 📝 Both manual input and automated random process generation
- 📊 Performance metrics (waiting time, turnaround time, response time, CPU utilization, throughput)
- 📈 Gantt chart visualization
- 📋 Comprehensive process information display

---

## 👥 Group Members
| Name | ID | Role |
|------|----|------|
| Jahmari Harrison | 2304204 | SJF Scheduler, Process Class |
| Alaina Preston | 2307651 | Preemptive Priority Scheduler |
| Dejonte Maxwell | 2301519 | Multi-Level Queue Scheduler |
| Demonia Chung | 2307612 | FCFS Scheduler |
| Nicholas Redwood | 2210210 | Main Program & Menu System |

---

## 🛠️ Build Instructions

### 📋 Prerequisites
- **C++ compiler** (g++ recommended)
- **Make** build system

### 🔧 Step-by-Step Build

1. **Clone the repository**
   ```bash
   git clone https://github.com/Tartalam/Operating-System-Scheduling-Algorithms-simulation-
   cd Operating-System-Scheduling-Algorithms-simulation-
2. **Build using Makefile**
   ```bash
   make
3. **Run the program**
   ```bash
   make file

### 🔄 Alternative Manual Build
if you dont have maek, compile manually:
```bash
cd src
g++ -std=c++11 -o scheduling_simulator *.cpp
./scheduling_simulator
```

###⚙️ Build Options
Command |	Description
--------|------------
make debug  |  Build with debug symbols
make clean  |  Remove build files
make rebuild  |  Clean and rebuild
make run  |  Build and run immediately

### 🎮 How to Use

## 🏃 Running the Program

1. Execute the program using the instructions above

2. Select an algorithm from the main menu (1-4)

2, Choose test type:

  * Custom Test: Enter process details manually

  * Automated Test: Generate random processes

## 📥 Input Format

* Arrival Time: When the process arrives

* Burst Time: How long it needs the CPU

* Priority (for Priority and MLQ): Lower number = higher priority

* Queue Level (for MLQ only): 0, 1, or 2

### 💡 Example Usage
```text
=============================================
      CPU SCHEDULING ALGORITHMS SIMULATOR
=============================================
1. Shortest Job First (SJF) - Non-preemptive
2. First Come First Served (FCFS)
3. Priority Scheduling (Preemptive)
4. Multi-level Queue Scheduling
5. Exit
=============================================
```

### 📊 Program Output

The program displays:

* 🎯 Process execution order

* 📈 Gantt chart showing timeline

* 📋 Detailed table with calculated times

* ⚖️ Performance metrics comparison

* 💻 CPU utilization and throughput

### 🧪 Sample Test Case

Testing SJF with:

8 P1: Arrival=0, Burst=6

* P2: Arrival=1, Burst=4

* P3: Arrival=2, Burst=2

Expected: P1 runs first but gets preempted by shorter jobs

### 🔬 Technical Details

* Language: C++11

* Data Structures: Vectors, priority queues, standard queues

* Time Complexity: O(n log n) for priority-based algorithms

* File Structure: Header files for each scheduler with implementation in SJF_Scheduler.cpp

### 🎓 Academic Context

This project was completed for Year 3 Semester 1 Operating Systems course at University of Technology, Jamaica, demonstrating practical implementation of theoretical scheduling concepts.
