#include <stdio.h>
#include<sys/wait.h>
#include <unistd.h>
int main() {
   int res;
 printf("Parent's id:%d\n",getpid());
   res=fork();
if(res==0){
    sleep(4);
    printf("Child's pid is %d\n", getppid ( ),res);

}
else{
     printf ("Parent id:%d\n", getpid ( ) ) ;
}
    return 0;
}