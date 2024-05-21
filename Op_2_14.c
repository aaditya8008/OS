#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
  
main ( ) 
{ 
     pid_t  whichone, first, second ; 
     int  howmany, status ; 
  
     if ( (first = fork ( ) ) == 0 )           /* Parent spawns 1st child */ 
     { 
          printf ("Hi, I am the first child, and my ID is %d\n", getpid ( ) ) ; 
          sleep (10) ; 
          exit (0) ; 
     } 
     else if (first == -1) 
     { 
          perror ("1st fork: something went wrong\n") ; 
          exit (1) ; 
     } 
     else if ( ( second = fork ( ) ) == 0 )    /* Parent spawns 2nd child */ 
     { 
          
          printf ("Hi, I am the second child, and my ID is %d\n", getpid ( ) ) ; 
          sleep (15) ; 
          exit (0) ; 
      } 
     else if (second == -1) 
     { 
          perror ("2nd fork: something went wrong\n") ; 
          exit (1) ; 
     } 
  
     printf ("This is parent\n") ; 
  
     howmany = 0 ; 
     while (howmany < 2)                  /* Wait Twice */ 
     { 
           whichone = wait(&status) ; 
           howmany++ ; 
      
     if (whichone == first) 
          printf ("First child exited\n") ; 
     else 
          printf ("Second child exited\n") ; 
  
     if ( (status & 0xffff) == 0 ) 
         printf ("correctly\n") ; 
     else 
        printf ("uncorrectly\n") ; 
   } 
}