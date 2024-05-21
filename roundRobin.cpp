#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
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
    bool added;
    bool completed;
    process() {
        pid = 0;
        bt = 0;
        ar = 0;
        wt = 0;
        tat = 0;
        ct = 0;
        ex = 0;
        added=false;
        completed = false;
       
    }

    process(float pide, float bte, float are) {
        pid = pide;
        bt = bte;
        ar = are;
        wt = 0;
        tat = 0;
        ct = 0;
        added=false;
        ex=bt;
        completed = false;
       
    }
};

void rr(process p[],int time, int size) {
       sort(p, p + size, [](const process &a, const process &b) {
        return a.ar < b.ar;
    });
    float currentTime = 0.0;
    bool ex=true;
queue<process*> q;
q.push(&p[0]);
p[0].added=true;

 while(ex) {
     
        if(q.empty()){
            break;
        }
       process *ps=q.front();
          if(ps->ex>=time){
             currentTime += time;
             ps->ex=ps->ex-time;}
       else{
        currentTime+=ps->ex;
        ps->ex=0;
       }
          for (int j = 0; j < size; j++) {
            if (!p[j].completed && p[j].ar <= currentTime && !p[j].added) {
               q.push(&p[j]);
               p[j].added=true;
            }
        }
       cout<<"Executing :"<<ps->ar<<"At :"<<currentTime<<endl;
       q.pop();
       ps->added=false;
     
        
if(ps->ex==0){
ps->ct = currentTime;
ps->completed = true;
ps->tat = currentTime - ps->ar;
ps->wt = ps->tat - ps->bt;
}
else{
    q.push(ps);
    ps->added=true;
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
    int time;
    cout<<"Enter Time Quatum:\n";
    cin>>time;
    for (int i = 0; i < size; i++) {
        float bt, ar;
        
        cout << "Enter Burst time:\n";
        cin >> bt;
        cout << "Enter Arrival time:\n";
        cin >> ar;
        p[i] = process(i+1, bt, ar);
    }

    rr(p,time, size);
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



