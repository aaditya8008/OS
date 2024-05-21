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
    process(){
        at=0;
        pid=0;
        bt=0;
    }
    process(float id,float a,int b ){
        at=a;
        pid=id;
        bt=b;
    }
};
void printProcesses(process p[], int size) {
   
    cout << "Pid\t" << "Bt\t" << "At\t" << "Tat\t" << "Wt\n";
    for (int i = 0; i < size; i++) {
        cout << p[i].pid << "\t" << p[i].bt << "\t" << p[i].at << "\t"   << p[i].tat << "\t" << p[i].wt << "\n";
    }
}
void fcfs(process p[],int size){
   sort(p,p+size,[](process &a,process &b)
   {
      return a.at<b.at;
   }
   );
   int currentTime=0;
   for(int i=0;i<size;i++){
       if(currentTime<p[i].at){
           currentTime=p[i].at;
       }
       else{
       currentTime+=p[i].bt;
       p[i].tat=currentTime-p[i].at;
       p[i].wt=p[i].tat-p[i].bt;}
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
    fcfs(p,size);
    float sumTat=0,sumWt=0;
    for(int i=0;i<size;i++){
        sumTat+=p[i].tat;
        sumWt+=p[i].wt;
    }
    cout<<"Avg Waiting Time:"<<sumWt/size<<"\n";
     cout<<"Avg TurnAround Time:"<<sumTat/size<<"\n";
    
    return 0;
}


