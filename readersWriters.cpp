#include <iostream>
#include <chrono>
#include <unistd.h> // For sleep function in Unix-like systems
using namespace std;

int rw_mutex = 1;
int mutex = 1;
int read_count = 0;

void wait(int &S) {
    while (S <= 0)
        ;
    S--;
}

void signal(int &S) {
    S++;
}

void read() {
    wait(mutex);
    read_count++;
    if (read_count == 1)
        wait(rw_mutex);
    signal(mutex);
    // Read operation
    cout << "Reading...!!" << endl;
    // Simulating read operation
    sleep(1); // Sleep for 1 second
    wait(mutex);
    read_count--;
    if (read_count == 0)
        signal(rw_mutex);
    signal(mutex);
}

void write() {
    wait(rw_mutex);
    // Write operation
    cout << "Writing...!!" << endl;
    // Simulating write operation
    sleep(2); // Sleep for 2 seconds
    signal(rw_mutex);
}

int main() {
    while (true) {
        int x=fork();
        if(x==0)
        read();

        else
        write();
    }

    return 0;
}


