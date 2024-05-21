#include<iostream>
#include<random>
#include <unistd.h>
using namespace std;

void exec(int buffer[],int *c,int n){
    int in=0;
    int out=0;
    int ex;
    int next_produced;
   

     ex=n;
while(true){
     int x=fork();
     
     if(ex==0){
         break;
     }
     if(x!=0){
    while (true)
    {
        if(*c>=n){
           
            break;
        }
          cout<<"Producer count:"<<*c<<endl;
        buffer[in]=rand();
        in=(in+1)%n;
        *c=*c+1;
    }}
    int next_consumed;
    if(x==0){
     while (true)
    {
        if(*c<=0){
           
            break;
        }
         
          cout<<"Consumer count:"<<*c<<endl;
      next_consumed=buffer[out];
        out=(out+1)%n;
        *c=*c-1;
    }
  }
ex--;
}

}

int main(){

    int n;
    cout<<"Enter Buffer Size:";
    cin>>n;
    int buffer[n];
    int count =0;
    exec(buffer,&count,n);
    
}