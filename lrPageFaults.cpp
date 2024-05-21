#include <iostream>
#include <limits.h>
using namespace std;

int main() {
    int rsize;
    int size;

    cout << "Enter reference string length:" << endl;
    cin >> rsize;

    cout << "Enter frame size:" << endl;
    cin >> size;

    int ref[rsize];
    int queue[size];
    int last_used[size]; // This array will keep track of the last used times for LRU
    int length = 0;

    cout << "Enter elements:\n";
    for (int i = 0; i < rsize; i++) {
        cin >> ref[i];
    }

    int faults = 0;

    for (int i = 0; i < rsize; i++) {
        bool flag = false;

        // Check if the page is already in the frame
        for (int j = 0; j < length; j++) {
            if (ref[i] == queue[j]) {
                flag = true;
                last_used[j] = i; // Update the last used time
                break;
            }
        }

        if (!flag) {
            // Page fault occurs
            if (length < size) {
                queue[length] = ref[i];
                last_used[length] = i;
                length++;
            } else {
                // Find the LRU page to replace
                int lru_index = 0;
                for (int j = 1; j < size; j++) {
                    if (last_used[j] < last_used[lru_index]) {
                        lru_index = j;
                    }
                }
                queue[lru_index] = ref[i];
                last_used[lru_index] = i;
            }
            faults++;
        }

        // Print the current frame content
        for (int j = 0; j < length; j++) {
            cout << queue[j] << " ";
        }
        cout << endl;
    }

    cout << "Page Faults: " << faults << endl;
    return 0;
}
  