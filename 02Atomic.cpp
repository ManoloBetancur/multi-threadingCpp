#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

/*Si dos threads manipulan la misma variable o los mismos datos es posible que los dos 
interfieran en las operaciones del otro thread no completandose de manera correta.*/


using namespace std;


int main() {
    //Lamnda function [](){}

    atomic<int> count(0);
    const int MAX_ITER = 1E6;
    thread t1([&count](){
        for (int i = 0; i < MAX_ITER; i++)
        {
            ++count;
        }
    });
    thread t2([&count](){
        for (int i = 0; i < MAX_ITER; i++)
        {
            ++count;
        }
    });
    t1.join();
    t2.join();
    cout<<count<<endl;
    return 0;
}
