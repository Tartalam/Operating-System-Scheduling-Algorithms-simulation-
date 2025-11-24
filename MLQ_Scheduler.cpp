#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, arrival, burst, remaining, qid;
    int start = -1, finish = -1;
    int wait = 0, turn = 0, response = -1;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Process> P(n);
    for (int i = 0; i < n; i++) {
        cin >> P[i].arrival >> P[i].burst >> P[i].qid;
        P[i].id = i + 1;
        P[i].remaining = P[i].burst;
        P[i].qid = min(max(P[i].qid, 0), 2);
    }

    // Queue quantums (Q2 = FCFS with huge quantum)
    const int Q[3] = {4, 8, INT_MAX};

    // Arrival order
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return P[a].arrival < P[b].arrival;
    });

    deque<int> Qs[3];
    int nextA = 0, done = 0, t = 0;
    int cur = -1, slice = 0;
    long long busy = 0;

    auto enqueueArrivals = [&](int now) {
        while (nextA < n && P[ord[nextA]].arrival <= now) {
            Qs[P[ord[nextA]].qid].push_back(ord[nextA]);
            nextA++;
        }
    };

    // Start at earliest arrival
    t = P[ord[0]].arrival;
    enqueueArrivals(t);

    while (done < n) {

        // Pick new process if CPU idle
        if (cur == -1) {
            for (int q = 0; q < 3; q++)
                if (!Qs[q].empty()) { cur = Qs[q].front(); Qs[q].pop_front(); break; }

            // If still none, jump to next arrival
            if (cur == -1) {
                t = P[ord[nextA]].arrival;
                enqueueArrivals(t);
                continue;
            }

            slice = 0;
            if (P[cur].start == -1) {
                P[cur].start = t;
                P[cur].response = t - P[cur].arrival;
            }
        }

        // Execute for 1 time unit
        P[cur].remaining--;
        slice++;
        busy++;
        t++;

        enqueueArrivals(t);

        // Finished
        if (P[cur].remaining == 0) {
            P[cur].finish = t;
            P[cur].turn = t - P[cur].arrival;
            P[cur].wait = P[cur].turn - P[cur].burst;
            done++;
            cur = -1;
            continue;
        }

        // Preemption: if higher queue has new processes
        for (int q = 0; q < P[cur].qid; q++) {
            if (!Qs[q].empty()) {
                Qs[P[cur].qid].push_front(cur);
                cur = -1;
                break;
            }
        }
        if (cur == -1) continue;

        // Time quantum expired (RR queues only)
        if (slice >= Q[P[cur].qid]) {
            Qs[P[cur].qid].push_back(cur);
            cur = -1;
        }
    }

    // Metrics
    int makespan = 0;
    for (auto &p : P) makespan = max(makespan, p.finish);

    double avgW = 0, avgT = 0, avgR = 0;
    for (auto &p : P) {
        avgW += p.wait;
        avgT += p.turn;
        avgR += p.response;
    }
    avgW /= n; avgT /= n; avgR /= n;
    double util = 100.0 * busy / makespan;
    double thr = double(n) / makespan;

    // Output
    cout << "MLQ Scheduling Results (Q0=RR4, Q1=RR8, Q2=FCFS)\n";
    cout << "ID Arr Burst Q Start Finish Turn Wait Resp\n";

    for (auto &p : P) {
        cout << p.id << "  " << p.arrival << "   " << p.burst << "   "
             << p.qid << "   " << p.start << "    " << p.finish << "      "
             << p.turn << "    " << p.wait << "    " << p.response << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAvg Wait: " << avgW
         << "\nAvg Turn: " << avgT
         << "\nAvg Resp: " << avgR
         << "\nCPU Util: " << util << "%"
         << "\nThroughput: " << thr
         << "\nMakespan: " << makespan << "\n";

    return 0;
}
