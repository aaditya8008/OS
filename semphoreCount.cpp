#include <iostream>
#include <random>
#include <unistd.h>
#include <list>

using namespace std;

class process {
public:
    int *val;
    int ex;
    process(int *v, int e) {
        val = v;
        ex = e;
    }
    int exec() {
        if (ex == 0) {
            (*val)--;
            cout << "Executed decrement, new value: " << *val << endl; // Debug output
        }
        else {
            (*val)++;
            cout << "Executed increment, new value: " << *val << endl; // Debug output
        }
        return *val;
    }
};

class semaphore {
public:
    int value;
    list<process*> l;
    semaphore(int c) {
        value = c;
    }
};

void wait(semaphore *S, process *p, int ex) {
    S->value--;
    if (S->value < 0) {
        S->l.push_back(p);
        // No need to sleep here
    }
    else {
        p->exec();
    }
}

void signal(semaphore *S) {
    S->value++;
    if (S->value <= 0 && !S->l.empty()) {
        process* p = S->l.front();
        S->l.pop_front();
        p->exec();
    }
}

void exec(int buffer[], int *c, int n, semaphore s) {
    int in = 0;
    int out = 0;

    while (true) {
        int i = fork();
        if (i != 0) { // Parent process (producer)
            if (*c >= n) {
                cout << "Producer Full" << endl;
                break;
            }
            else {
                wait(&s, new process(c, 1), 1); // Pass a new process pointer
                buffer[in] = rand();
                in = (in + 1) % n;
                cout << "Producer count: " << *c << endl;
                signal(&s);
            }
        }
        else { // Child process (consumer)
            if (*c <= 0) {
                cout << "Consumer Empty" << endl;
                break;
            }
            else {
                wait(&s, new process(c, 0), 0); // Pass a new process pointer
                int next_consumed = buffer[out];
                out = (out + 1) % n;
                cout << "Consumer count: " << *c << endl;
                signal(&s);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter Buffer Size: ";
    cin >> n;
    semaphore s(n);
    int buffer[n];
    int count = 0;
    exec(buffer, &count, n, s);
    cout << "Final Count: " << count << endl;
}