#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

int main()
{
    condition_variable condition;
    mutex mtx;
    bool ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout<<"T1 acquiring lock "<<endl;
        unique_lock<mutex> lock(mtx);
        ready = true;
        lock.unlock();
        cout<<"T1 Released lock ... Notifying "<<endl;
        condition.notify_one();
    });

    cout<<"Main thread acquiring lock"<<endl;
    unique_lock<mutex> lock(mtx);

    cout<<"Main thread acquired lock; waiting"<<endl;
    condition.wait(lock,[&](){ return ready;});

    cout<<"Main thread finished waiting"<<endl;
    cout << "Ready ?" << ready << endl;

    t1.join();
    return 0;
}