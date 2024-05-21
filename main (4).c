#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    execl("/bin/ps", "ps", NULL);

    printf("%d\n", argc);
    

    return 0;
}