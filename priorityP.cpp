#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

class process {
public:
    float pid;
    float bt;
    float ct;
    float ar;
    float wt;
    float tat;
    float ex;
    int priority;
    bool completed;
    bool added;

    process() {
        pid = 0;
        bt = 0;
        ar = 0;
        wt = 0;
        tat = 0;
        ct = 0;
        ex = 0;
        completed = false;
        added = false;
    }

    process(float pide,int p, float bte, float are) {
        pid = pide;
        bt = bte;
        ar = are;
        priority=p;
        wt = 0;
        tat = 0;
        ct = 0;
        ex=bt;
        completed = false;
        added = false;
    }
};

bool compareProcesses(const process *a, const process *b) {
    return a->bt < b->bt;
}

void sjf(process p[], int size) {
    sort(p, p + size, [](const process &a, const process &b) {
        return a.ar < b.ar;
    });

    float currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < size) {
        int shortestIndex = -1;
        float shortestPriority = numeric_limits<float>::max();

        // Find the shortest job that has arrived and not yet completed
        for (int i = 0; i < size; i++) {
            if (!p[i].completed && p[i].ar <= currentTime && p[i].priority < shortestPriority) {
                shortestPriority = p[i].priority;
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1) {
            // If no process is available to execute, move time forward to the next arrival time
            currentTime = p[completedProcesses].ar;
        } else {
            // Execute the shortest job
            cout << "Executing: p" << p[shortestIndex].pid << " " << p[shortestIndex].ex << "\n";
            p[shortestIndex].ex--;

            // Update currentTime
            currentTime++;

            if (p[shortestIndex].ex == 0) {
                // Process completed
                cout << "Completed: p" << p[shortestIndex].pid << " " << p[shortestIndex].ex << "\n";
                p[shortestIndex].completed = true;
                p[shortestIndex].ct = currentTime;
                p[shortestIndex].tat = currentTime - p[shortestIndex].ar;
                p[shortestIndex].wt = p[shortestIndex].tat - p[shortestIndex].bt;
                completedProcesses++;
            }
        }
    }
}

void printProcesses(process p[], int size) {
    cout << fixed << setprecision(2); // Set output to display in fixed-point notation with 2 decimal places
    cout << "Pid\t" << "Bt\t" << "At\t" << "Ct\t" << "Tat\t" << "Wt\n";
    for (int i = 0; i < size; i++) {
        cout << p[i].pid << "\t" << p[i].bt << "\t" << p[i].ar << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }
}

int main() {
    int size;
    cout << "Enter Number of Processes:\n";
    cin >> size;
    process p[size];
    for (int i = 0; i < size; i++) {
        float bt, ar, pid;
        cout << "Enter priority:\n";
        cin >> pid;
        cout << "Enter Burst time:\n";
        cin >> bt;
        cout << "Enter Arrival time:\n";
        cin >> ar;
        p[i] = process(i+1,pid, bt, ar);
    }

    sjf(p, size);
    printProcesses(p, size);
    float waitAverage;
float tatAverage;
float sumw=0,sumt=0;

    for(int i=0;i<size;i++){
sumw+=p[i].wt;
sumt+=p[i].tat;

    }
    cout<<"Avg Waiting Time:"<<sumw/size<<"\n";
     cout<<"Avg TurnAround Time:"<<sumt/size<<"\n";

    return 0;
}


// Pid     Bt      At      Ct      Tat     Wt
// 1.00    3.00    0.00    7.00    7.00    4.00
// 2.00    4.00    1.00    5.00    4.00    0.00
// 3.00    6.00    2.00    13.00   11.00   5.00
// 4.00    4.00    3.00    17.00   14.00   10.00
// 5.00    2.00    5.00    19.00   14.00   12.00
// Avg Waiting Time:6.20
// Avg TurnAround Time:10.00
