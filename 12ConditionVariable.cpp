#include<iostream>
#include<thread>
#include<chrono>
#include<atomic>
#include<condition_variable>

using namespace std;

int main()
{
    condition_variable condition;
    mutex mtx;
    bool ready = false;
    
    
    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(10000));
        unique_lock<mutex> lock(mtx);
        ready = true;
        lock.unlock();
        condition.notify_one();
    });
    

    unique_lock<mutex> lock(mtx);


    while(!ready)
    {
        //THIS PART ONLY EXECUTE ONCE
        cout<<"WAITING ..."<<endl;
        //Waits the thread to be done.
        condition.wait(lock);
    }

    cout << "Is it ready ? "<<ready<<endl; 

    
    t1.join();
    return 0;
}