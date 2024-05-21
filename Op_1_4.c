#include <stdio.h>
#include<sys/wait.h>
int main() {
   int pid;
   int status;
    printf("Parent id before Fork :%d\n",getpid());
   pid=fork();
  
if(pid==0){
    printf("In Child\n");
}
else{
     printf("In Parent\n");
     printf("Parent id :%d\n",getpid());
    wait(&status);
   
    printf("Child id:%d",status);
}
    return 0;
}