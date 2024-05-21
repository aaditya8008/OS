// Online C++ compiler to run C++ program online
#include <iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<algorithm>
using namespace std;

class process{
public:
    float at;
    float bt;
    float pid;
    float tat;
    float wt;
    boolean completed;
    process(){
        at=0;
        pid=0;
        bt=0;
        completed=false;
    }
    process(float id,float a,int b ){
        at=a;
        pid=id;
        bt=b;
        completed=false;
    }
};
void printProcesses(process p[], int size) {
   
    cout << "Pid\t" << "Bt\t" << "At\t" << "Tat\t" << "Wt\n";
    for (int i = 0; i < size; i++) {
        cout << p[i].pid << "\t" << p[i].bt << "\t" << p[i].at << "\t"   << p[i].tat << "\t" << p[i].wt << "\n";
    }
}
void sjf(process p[],int size){
   sort(p,p+size,[](process &a,process &b)
   {
      return a.bt<b.bt;
   }
   );
   process *queue[size];
   int currentTime=0;
   for(int i=0;i<size;i++){
    int  s=0;
     for(int j=0;j<size;j++){
         if(!p[j].completed&&p[j].at<=currentTime&&p[j].at>=prev){
             queue[s]=&p[j];
             s++;
         }
     }
       sort(queue+0,queue+s,[](process *a,process *b){
           return a->bt<b->bt;
       });
       if(currentTime<queue[0]->at){
           currentTime=queue[0]->at;
       }
       else{
       currentTime+=queue[0].bt;
       queue[0]->tat=currentTime-queue[0]->at;
       queue[0]->wt=queue[0]->tat-queue[0]->bt;
       
       }
   }
   printProcesses(p,size);
}
int main() {
    int size;
    cout<<"Enter Size:"<<endl;
    cin>>size;
    process p[size];
    for(int i=0;i<size;i++){
    int at,bt;
    cout<<"Enter At:"<<endl;
    cin>>at;
    cout<<"Enter Bt:"<<endl;
    cin>>bt;
    p[i]=process(i+1,at,bt);
    }
    sjf(p,size);
    float sumTat=0,sumWt=0;
    for(int i=0;i<size;i++){
        sumTat+=p[i].tat;
        sumWt+=p[i].wt;
    }
    cout<<"Avg Waiting Time:"<<sumWt/size<<"\n";
     cout<<"Avg TurnAround Time:"<<sumTat/size<<"\n";
    
    return 0;
}