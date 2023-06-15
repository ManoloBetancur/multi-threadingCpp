#include<iostream>
#include<thread>
#include<chrono>
#include<atomic>


using namespace std;

int main()
{
    atomic<bool> ready(false);
    
    
    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(5000));
        ready = true;
    });

    t1.join();

    //INSTEAD OF WAITING HERE with a while loop we could use a condition variable to know. 
    //You can see the condition variable in use in the next script.
    while(!ready)
    {
        cout<<"CHEKING >>>"<<endl;
        this_thread::sleep_for(chrono::milliseconds(100));   
    }

    cout << "Is it ready ? "<<ready<<endl; 

    

    return 0;
}