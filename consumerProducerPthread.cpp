#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib> // for rand()
using namespace std;

class bf {
public:
    enum {
        size = 3
    };
    int buffer[size];
    int n;
    int c;
    bf() {
        n = size;
        c = 0;
    }
};

void* child(void* B) {
    bf* b = (bf*)B;
    int out = 0;

    while (true) {
        if (b->c <= 0) {
            cout<<"Empty Consumer\n";
            cout << "Consumer count:" << b->c << endl;
             
            break;
        }

        int next_consumed = b->buffer[out];
        out = (out + 1) % b->n;
        b->c = b->c - 1;
               cout << "Consumer :" << b->c << endl;
               int s=rand()%2+1;
        
          sleep(s);
               
    }
  
    return NULL;
}

void* parent(void* B) {
    bf* b = (bf*)B;
    int in = 0;

    while (true) {
        if (b->c >= b->n) {
            cout<<"FULL Producer\n";
            cout << "Producer count:" << b->c << endl;
            
            break;
        }
         
        b->buffer[in] = rand();
        in = (in + 1) % b->n;int in=0;
        b->c = b->c + 1;
        cout << "Producer :" << b->c << endl;
        int s=rand()%2+1;
       
          sleep(s);
    }

    return NULL;
}

int main() {
    bf b;
    pthread_t t;
    pthread_t z;
            pthread_create(&t, NULL, parent, (void*)&b);
            pthread_create(&z, NULL, child, (void*)&b);
 pthread_join(z, NULL);
   pthread_join(t, NULL);
     
   cout<<"Final Count:"<<b.c;
    return 0;
}
