// Online C compiler to run C program online
#include <stdio.h>
#include<sys/wait.h>
#include <unistd.h>
int main() {
   int res;
 printf("Parent's id:%d\n",getpid());
   res=fork();
if(res!=0){
    printf("%d:  My child's pid is %d\n", getpid ( ),res);
}
else{
     printf ("Child id:%d\n", getpid ( ) ) ;
}
    return 0;
}