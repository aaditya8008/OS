#include<iostream>
using namespace std;

class process {
public:
    int inst;
    int type;
    int id[5];
    int available[3];
    int max[5][3];
    int allocation[5][3];
    int need[5][3];
    process() {
        inst = 3;
        type = 5;
        for (int i = 0; i < type; i++) {
            id[i] = i;
        }
    }

void request() {
    int additional[3];
    int id;
    cout<<"Enter id:"<<endl;
    cin>>id;
    cout<<"Enter instances:"<<endl;
     for (int j = 0; j < inst; j++) {
            cout << "Enter request for thread " << id << " and resource type " << j << " available:";
            cin >> additional[j];
        }
        bool can_allocate = true;
        for (int i = 0; i < inst; i++) {
            if (additional[i] > available[i]) {
                can_allocate = false;
                break;
            }
        }

        if (can_allocate) {
            for (int i = 0; i < inst; i++) {
                available[i] -= additional[i];
                allocation[id][i] += additional[i];
                need[id][i] -= additional[i];
            }
            cout << "Additional resources allocated successfully." << endl;
        } else {
            cout << "Request cannot be granted. Not enough resources available." << endl;
        }
    }
    
};

int main() {
    process p;
    for (int i = 0; i < p.inst; i++) {
        cout << "Enter resource of type " << i << " available:";
        cin >> p.available[i];
    }

    for (int i = 0; i < p.type; i++) {
        for (int j = 0; j < p.inst; j++) {
            cout << "Enter max resource of thread " << i << " and resource type " << j << " available:";
            cin >> p.max[i][j];
        }
    }
    for (int i = 0; i < p.type; i++) {
        for (int j = 0; j < p.inst; j++) {
            cout << "Enter allocated resource of thread " << i << " and resource type " << j << " available:";
            cin >> p.allocation[i][j];
        }
    }

    for (int i = 0; i < p.type; i++) {
        for (int j = 0; j < p.inst; j++) {
            p.need[i][j] = p.max[i][j] - p.allocation[i][j];
        }
    }
cout<<"Any additional request before allocation?"<<endl;
    int req;
    cin>>req;
    if(req==1){
        p.request();
    }

    for (int i = 0; i < p.type; i++) {
        cout << "Need of thread " << i << " = ";
        for (int j = 0; j < p.inst; j++) {
            cout << p.need[i][j] << " ";
        }
        cout << endl;
    }
    

    bool completed[5] = { false }; // Initialize completed array
    bool flag = true;
    
    while (flag) {
        flag = false;
        for (int i = 0; i < p.type; i++) {
            int count = 0;
            for (int j = 0; j < p.inst; j++) {
                if (p.need[i][j] <= p.available[j] && !completed[i]) {
                    count++;
                }
            }
            if (count == p.inst) {
                for (int k = 0; k < p.inst; k++) {
                    p.available[k] += p.allocation[i][k];
                }
                completed[i] = true;
                flag = true;
                cout << "Completed thread: " << i << endl;
            }
        }
    }

    for (int i = 0; i < p.type; i++) {
        if (!completed[i]) {
            cout << "Unsafe" << endl;
            return 0;
        }
    }
    cout << "Safe" << endl;
    return 0;
}