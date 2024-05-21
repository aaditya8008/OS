#include <stdio.h>
#include<unistd.h>
 #include <signal.h>
#include<stdlib.h>
int main() {
    // Write C code here
  int pid;
  pid=fork();

  if(pid!=0){
     
      sleep(5);
      system("ps");
  }
  else{
      printf("Child pid : %d, Parent pid : %d\n",getpid(),getppid());
      exit(42);
  }
    

    return 0;
}
