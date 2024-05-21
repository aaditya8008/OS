#include <iostream>
#include <algorithm>
#include <iomanip>
#include<limits>
using namespace std;

class process {
public:
    float pid;
    float bt;
    float ct;
    float ar;
    float wt;
    float wait;
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
        wait=0;
        completed = false;
        added = false;
    }

    process(float pide,int p, float bte, float are) {
        pid = pide;
        bt = bte;
        ar = are;
        priority=p;
        wait=0;
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
        cout<<"Ex";
        int shortestIndex = -1;
        float shortestPriority = numeric_limits<float>::max();
        int s=0;
         process *queue[size];
        for (int i = 0; i < size; i++) {
            if (!p[i].completed && p[i].ar <= currentTime && p[i].priority < shortestPriority) {
                shortestPriority = p[i].priority;
                shortestIndex = i;
                queue[s]=&p[i];
                s++;
                
            }
        }


        if (shortestIndex == -1) {
             
            currentTime = p[completedProcesses].ar;
        } else {
         
         
          
            cout << "Executing: p" << p[shortestIndex].pid << " " << p[shortestIndex].ex << "\n";
            p[shortestIndex].ex--;

           
            currentTime++;
            for(int k=0;k<s;k++){
              process *p=queue[k];
              if(p->pid!=shortestIndex){
                  p->wait++;
                  if(p->wait==3&&p->priority>1){
                      p->wait=0;
                      if(p->priority-1>=1){
                          p->priority=p->priority-1;
                      }
                      
                  }
              }
          }

            if (queue[0]->ex == 0) {
               
                cout << "Completed: p" << queue[0]->pid << " at " << currentTime<< "\n";
                queue[0]->completed = true;
                queue[0]->ct = currentTime;
                queue[0]->tat = currentTime - queue[0]->ar;
                queue[0]->wt = queue[0]->tat - queue[0]->bt;
                completedProcesses++;
            }
        }
    }
}

void printProcesses(process p[], int size) {
    cout << fixed << setprecision(2); // Set output to display in fixed-point notation with 2 decimal places
    cout << "Pid\t" << "Bt\t" << "At\t" << "Ct\t" << "Tat\t" << "Wt\t"<<"Priority\n";
    for (int i = 0; i < size; i++) {
        cout << p[i].pid << "\t" << p[i].bt << "\t" << p[i].ar << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\t"<<p[i].priority<<"\n";
    }
}

int main() {
    int size;
    cout << "Enter Number of Processes:\n";
    cin >> size;
    process p[size];
    for (int i = 0; i < size; i++) {
        float bt, ar, pr;
        cout << "Enter priority:\n";
        cin >> pr;
        cout << "Enter Burst time:\n";
        cin >> bt;
        cout << "Enter Arrival time:\n";
        cin >> ar;
        p[i] = process(i+1,pr, bt, ar);
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