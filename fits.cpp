#include <iostream>
using namespace std;

void firstFit(int *arr, int *proc,int *block, int size, int psize) {
    for (int i = 0; i < psize; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[j] >= proc[i] && proc[i] != 0) {
                arr[j] -= proc[i];
                block[i]=j;
                proc[i] = 0;
            }
        }
    }
}
void bestFit(int *arr, int *proc, int *block, int size, int psize) {
    for (int i = 0; i < psize; i++) {
        int min = -1; // Initialize min to an invalid index
        for (int j = 0; j < size; j++) {
            if (arr[j] >= proc[i] && proc[i] != 0 && (min == -1 || arr[j] < arr[min])) {
               min = j; 
            }
        }
        if (min != -1) {
            block[i] = min;
            arr[min] -= proc[i];
            proc[i] = 0;
        }
    }
}

void worstFit(int *arr, int *proc, int *block, int size, int psize) {
    for (int i = 0; i < psize; i++) {
        int max = -1; // Initialize max to an invalid index
        for (int j = 0; j < size; j++) {
            if (arr[j] >= proc[i] && proc[i] != 0 && (max == -1 || arr[j] > arr[max])) {
                max = j;
            }
        }
        if (max != -1) {
            block[i] = max;
            arr[max] -= proc[i];
            proc[i] = 0;
        }
    }
}


void find(int *arr, int *proc,int *block , int size, int psize) {
    cout << "Remaining memory:\n";
    int sum = 0;
    for (int i = 0; i < size; i++) {
        cout << "B" << i << " :";
        cout << arr[i];
        sum += arr[i];
        cout << endl;
    }
    cout << "Processes status:\n";
    for (int i = 0; i < psize; i++) {
        cout << "P" << i << " :";
        cout << proc[i];
        cout << " B" << i << " :";
        cout<<block[i];
        cout << endl;
    }
    cout << "Fragmentation:" << sum;
}

int main() {
    int size;
    cout << "Enter the number of memory holes:";
    cin >> size;
    int *arr = new int[size];
    int psize;
    cout << "Enter the number of processes:";
    cin >> psize;
    int *proc = new int[psize];
    int *block=new int[psize];
    cout << "Enter holes size:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "B" << i << " :";
        cin >> arr[i];
        cout << endl;
    }
    for (int i = 0; i < psize; i++) {
        cout << "P" << i << " :";
        cin >> proc[i];
        block[i]=-1;
        
        cout << endl;
    }
    
    int choice;
    cout << "Enter choice 1-3:" << endl;
    struct timespec s;
    struct timespec e;
    cin >> choice;
    double tt=-1;
    switch (choice) {
        case 1:
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &s);
            firstFit(arr, proc,block, size, psize);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e);
            tt = (e.tv_sec - s.tv_sec) + (e.tv_nsec - s.tv_nsec) / (1000000000.0);
            cout << "Time Taken: " << tt << endl;
            break;
        case 2:
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &s);
            bestFit(arr, proc,block, size, psize);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e);
            tt = (e.tv_sec - s.tv_sec) + (e.tv_nsec - s.tv_nsec) / (1000000000.0);
            cout << "Time Taken: " << tt << endl;
            break;
        case 3:
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &s);
            worstFit(arr, proc,block, size, psize);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e);
            tt = (e.tv_sec - s.tv_sec) + (e.tv_nsec - s.tv_nsec) / (1000000000.0);
            cout << "Time Taken: " << tt << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }
    find(arr, proc,block, size, psize);
    delete[] arr;
    delete[] proc;
    return 0;
}