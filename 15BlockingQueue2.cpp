#include <iostream>
#include <thread>
#include <queue>
#include<condition_variable>
#include<mutex>

using namespace std;

template<typename E>
class blocking_queue
{
    private:
        mutex _mtx;
        condition_variable _cond;
        int _max_size;
        queue<E> _queue;


    public:
        blocking_queue(int max_size): _max_size(max_size)
        {

        }

        void push(E e)
        {
            unique_lock<mutex> lock(_mtx);
            _cond.wait(lock,[this](){ return _queue.size()< _max_size; });

            _queue.push(e);

            lock.unlock();

            _cond.notify_one();
        }

        E front()
        {
            unique_lock<mutex> lock(_mtx);
            _cond.wait(lock,[this](){ return !_queue.empty();});

            return _queue.front();
        }

        void pop()
        {
            unique_lock<mutex> lock(_mtx);

            _cond.wait(lock,[this](){ return !_queue.empty();});

            E item = _queue.front();

            _queue.pop();

            lock.unlock();
            _cond.notify_one();
        }

        int size()
        {
            lock_guard<mutex> lock(_mtx);
            return _queue.size();
        }
};

int main()
{

    //One thread is adding to the queue 
    //The second queue is taking items out of the queue.
    blocking_queue<int> qu(5);

    thread t1([&](){
        for(int i = 0; i < 10; i++)
        {
            cout << "Pushing in..." << i <<endl;
            cout << "Queue Size is : "<< qu.size() << endl;
            qu.push(i);
        }
    });

    thread t2([&](){
        for(int i = 0; i < 10; i++)
        {
            auto item = qu.front();
            qu.pop();
            cout << "Poping out ..." << item << endl;
        }
    });

    t1.join();
    t2.join();
    
    return 0;
}