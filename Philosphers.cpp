#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep
#include <stdlib.h>

#define P_Count 5
#define C_Count 5

using namespace std;

pthread_t philosopher[P_Count];
pthread_mutex_t chopstick[C_Count];

void dine(int n){
    cout << "Philosopher " << n << " is thinking\n";
    pthread_mutex_lock(&chopstick[n]);
    pthread_mutex_lock(&chopstick[(n+1)%C_Count]);
    cout << "Philosopher " << n << " is eating\n ";
    sleep(3);
    pthread_mutex_unlock(&chopstick[n]);
    pthread_mutex_unlock(&chopstick[(n + 1) % C_Count]);
    printf("\nPhilosopher %d finished eating\n ", n);
}

int main(){
    int i, status;
    void *msg;

    for(i = 0; i < C_Count; i++) {
        status = pthread_mutex_init(&chopstick[i], NULL);
        if(status != 0){
            printf("\n Mutex initialization failed");
            exit(1);
        }
    }

    for (i = 0; i < P_Count; i++) {
        status = pthread_create(&philosopher[i], NULL, (void *(*)(void *))dine, (void *)(intptr_t)i);
        if (status != 0) {
            printf("\n Thread creation error \n");
            exit(1);
        }
    }

    for (i = 0; i < P_Count; i++) {
        status = pthread_join(philosopher[i], &msg);
        if (status != 0) {
            printf("\n Thread join failed \n");
            exit(1);
        }
    }

    for (i = 0; i < C_Count; i++) {
        status = pthread_mutex_destroy(&chopstick[i]);
        if (status != 0) {
            printf("\n Mutex Destroyed \n");
            exit(1);
        }
    }

    return 0;
}