#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Process {
public:
    float br;
    float ar;
    float wait;

    Process(float br, float ar) : br(br), ar(ar), wait(0) {}

    bool operator<(const Process& other) const {
        if (ar != other.ar)
            return ar > other.ar;
        else
            return br > other.br;
    }
};

int main() {
    priority_queue<Process> pq;
    cout << "Enter Number of processes:\n";
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        float ar, br;
        cout << "Enter burst time:";
        cin >> br;
        cout << "Enter arrival time:";
        cin >> ar;
        pq.push(Process(br, ar));
    }

    vector<int> waiting(n);
    vector<int> tat(n);
    int k = 0;
    int pr = 0;
    cout << "Burst time\tArrival time\n";
    int clock = 0;
    vector<Process> prc;
    stack<Process> processing;
    int wait = 0;

    for (int time = 0; time < 100; time++) {
        Process p;
        if (processing.empty()) {
            p = pq.top();
            pq.pop();
            p.wait = wait - p.ar;
            if (p.ar == time) {
                processing.push(p);
            }
        } else if (!pq.empty() && pq.top().ar <= time) {
            p = pq.top();
            pq.pop();
            processing.push(p);
        } else if (!processing.empty() && p.br == 0) {
            prc.push_back(processing.top());
            processing.pop();
        } else {
            p.br--;
        }
    }

    for (int i = 0; i < prc.size(); i++) {
        cout << "Waiting Time :" << prc[i].wait << endl;
    }
    return 0;
}
