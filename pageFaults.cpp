#include<iostream>
using namespace std;

int main(){
    int rsize;
    int size;
    cout<<"Enter refrence string length:"<<endl;
    cin>>rsize;
    cout<<"Enter frame size:"<<endl;
    cin>>size;
    int ref[rsize];
    int queue[size];
    int length=0;
    cout<<"Enter elements:\n";
    for(int i=0;i<rsize;i++){
        cin>>ref[i];
    }
    int idx=0;
    int faults=0;
    for(int i=0;i<rsize;i++){
       bool flag=false;
       for(int j=0;j<length;j++){
        if(ref[i]==queue[j]){
            flag=true;
        } 
       }
       if(!flag){
        queue[idx]=ref[i];
        idx++;
        faults++;
        if(length<size){
            length++;
        }
        if(idx==size){
            idx=0;
        }

         for(int i=0;i<length;i++){
        cout<<queue[i]<<" ";
       }
       cout<<endl;
       }  
    }
    cout<<"Page Faults: "<<faults<<endl;
}