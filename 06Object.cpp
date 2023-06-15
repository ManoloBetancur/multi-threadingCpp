#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include<mutex>

using namespace std;

const int MAX_ITER = 1E6;


class App
{
    private:
        int count = 0;
        mutex mtx;
    public:
        void operator()()
        {
            for (int i = 0; i < MAX_ITER; i++)
            {
                const lock_guard<mutex> guard(mtx);
                ++count;
            }
        }
        int get_count()
        {
            return count;
        }
};





int main() {

    // Passing all arguments by reference using reference wrapper
    App app;


    thread t1(ref(app));
    thread t2(ref(app));
    t2.join();
    cout<<app.get_count()<<endl;
    return 0;
}
