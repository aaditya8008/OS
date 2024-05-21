#include <iostream>
#include <limits.h> // For INT_MAX
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
                break;
            }
        }

        if (!flag) {
            // Page fault occurs
            if (length < size) {
                // If there's space in the frame, add the page
                queue[length] = ref[i];
                length++;
            } else {
                // Find the optimal page to replace
                int maxIdx = -1;
                int farthest = -1;

                for (int j = 0; j < size; j++) {
                    int k;
                    for (k = i + 1; k < rsize; k++) {
                        if (ref[k] == queue[j]) {
                            if (k > farthest) {
                                farthest = k;
                                maxIdx = j;
                            }
                            break;
                        }
                    }
                    // If the page is not going to be used again, replace it
                    if (k == rsize) {
                        maxIdx = j;
                        break;
                    }
                }

                queue[maxIdx] = ref[i];
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
