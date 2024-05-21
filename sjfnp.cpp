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
    bool completed;
    bool added;

    process() {
        pid = 0.0;
        bt = 0.0;
        ar = 0.0;
        wt = 0.0;
        tat = 0.0;
        ct = 0.0;
        ex = 0.0;
        completed = false;
        added = false;
    }

    process(float pide, float bte, float are) {
        pid = pide;
        bt = bte;
        ar = are;
        wt = 0.0;
        tat = 0.0;
        ct = 0.0;
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

    int k = 0;
    float currentTime = 0.0;
    float prec = currentTime;
    process *queu[size];
    int s = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!p[j].completed && p[j].ar <= currentTime && p[j].ar >= prec && !p[j].added) {
                queu[s] = &p[j];
                s++;
            }
        }

        sort(queu + k, queu + s, compareProcesses);
        prec = currentTime;
        cout << "QUEUE:\n";
        for (int x = k; x < s; x++) {
            cout << "PID: " << queu[x]->pid << "\n";
        }

        if (currentTime < queu[k]->ar) {
            currentTime = queu[k]->ar;
        }
        currentTime += queu[k]->bt;
        queu[k]->ct = currentTime;
        queu[k]->completed = true;
        queu[k]->tat = currentTime - queu[k]->ar;
        queu[k]->wt = queu[k]->tat - queu[k]->bt;
        k++;
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
    float size;
    cout << "Enter Number of Processes:\n";
    cin >> size;
    process p[int(size)];
    for (int i = 0; i < size; i++) {
        float bt, ar, pid;
        cout << "Enter pid:\n";
        cin >> pid;
        cout << "Enter Burst time:\n";
        cin >> bt;
        cout << "Enter Arrival time:\n";
        cin >> ar;
        p[i] = process(pid, bt, ar);
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

// Pid	Bt	At	Ct	Tat	Wt
// 4.00	3.00	0.00	3.00	3.00	0.00
// 3.00	8.00	1.00	23.00	22.00	14.00
// 1.00	6.00	2.00	9.00	7.00	1.00
// 5.00	4.00	4.00	15.00	11.00	7.00
// 2.00	2.00	5.00	11.00	6.00	4.00
// Avg Waiting Time:5.20
// Avg TurnAround Time:9.80



