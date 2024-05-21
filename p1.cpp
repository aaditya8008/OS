
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
 

int main(void)
{
    int pid = fork();
     
    if ( pid == 0 )
    {
      cout<<"Zombie pid:"<<getpid()<<endl;
      cout<<"Child killed"<<endl;
      exit(34);
    }
 
 else{
     cout<<"Parent pid:"<<getpid()<<endl;
     sleep(2);
     cout<<"Process running:"<<endl;
     system("ps");
     
 }
 
 
    int status;
    waitpid(pid, &status, 0);
    int exit_status = WEXITSTATUS(status); 
 

    if (WEXITSTATUS(status); )
    {
              
        cout<<"Normal Exit status of the child was "<<
                                     exit_status<<endl;
    }
    else{
        cout<<"Abnormal Exit status of the child was "<<
                                     exit_status<<endl;
    }

    return 0;
}