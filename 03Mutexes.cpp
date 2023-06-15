#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include<mutex>
//#include <mutex>



using namespace std;

int main() {
    

    int count(0);
    const int MAX_ITER = 1E6;
    //Lamnda function [](){}
    //Function like this, ir order to pass it as parameter in threads constructor.

    mutex mtx;

    auto func = [&]()
    {
        for (int i = 0; i < MAX_ITER; i++)
        {
            mtx.lock();
            ++count;
            mtx.unlock();
        }
    };




    thread t1(func);
    thread t2(func);
    t1.join();
    t2.join();
    cout<<count<<endl;
    return 0;
}
