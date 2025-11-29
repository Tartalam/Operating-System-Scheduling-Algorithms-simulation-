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
