#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include<mutex>
//#include <mutex>

const int MAX_ITER = 1E6;

using namespace std;

//Use normal function instead of lambda funcion

void work(int &count, mutex &mtx){

    for (int i = 0; i < MAX_ITER; i++)
        {
            mtx.lock();
            ++count;
            mtx.unlock();
        }
    
}

int main() {
    

    int count(0);
    mutex mtx;
    // Passing all arguments by reference using reference wrapper
    thread t1(work, ref(count),ref(mtx));
    thread t2(work, ref(count),ref(mtx));
    t1.join();
    t2.join();
    cout<<count<<endl;
    return 0;
}
