// Online C compiler to run C program online
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main() {
        int    num=0, statval ;
    printf ("%d:  I'm the parent !\n", getpid ( ) ) ;
    printf ("%d:  number = %d\n", getpid ( ), num ) ;
    printf ("%d:  forking ! \n", getpid ( ) ) ;

    if(fork()==0){
        printf ("%d: I'm the child !\n", getpid ( ) ) ;
            printf ("%d: number = %d\n", getpid ( ), num ) ;
            printf ("%d: Enter a number :  ", getpid ( ) ) ;
            scanf ("%d", &num) ;
            printf ("%d: number = %d\n", getpid ( ), num ) ;
            printf ("%d: exiting with value %d\n", getpid ( ), num ) ;
            exit (num) ;
    }
    printf ("%d: number = %d\n", getpid ( ), num ) ;
    printf ("%d: waiting for my kid !\n", getpid ( ) ) ;
    wait (&statval) ;
if(WIFEXITED(statval)){
    printf("%d : my kid exited with status %d, statval %d\n",getpid(),WEXITSTATUS(statval),statval);
    
}
else{
    printf ("%d: My kid was killed off ! ! \n", getpid ( ) ) ;
}
    
 
}