#include<iostream>
#include<random>
#include <unistd.h>
using namespace std;

void exec(int buffer[],int *c,int n){
    int in=0;
    int out=0;
  
    int next_produced;
   bool flag[2];
int i=0;
int j;

int turn;
for(int k=0;k<2;k++){
    flag[k]=false;
}
     
while(true){
     i=fork();
     if(i!=0){
         i = (i == 0) ? 0 : 1;
   
        
        flag[i]=true;
     j=1-i;
     turn=j;
     
        if((flag[j]&&turn==j)||*c>=n){
            
          cout<<"Producer Full\n";
            break;
        }
          
        buffer[in]=rand();
        in=(in+1)%n;
        *c=*c+1;
        
        cout<<"Producer count:"<<*c<<endl;
        
        flag[i]=false;
       sleep(rand()%2+1);
      
    }
else{
    int next_consumed;
         i = (i == 0) ? 0 : 1;
   
        
        flag[i]=true;
     j=1-i;
     turn=j;
     
        if((flag[j]&&turn==j)||*c<=0){
            
          cout<<"Consumer Empty\n";
            break;
        }
 next_consumed=buffer[out];
        out=(out+1)%n;
        *c=*c-1;
         cout<<"Consumer count:"<<*c<<endl;
         flag[i]=false;
       
       sleep(rand()%2+1);
       
    }
 
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