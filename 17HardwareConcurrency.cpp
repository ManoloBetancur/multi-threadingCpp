#include<iostream>
#include<thread>


using namespace std;


int main(){

    //NUMBER of threads at the same time you can run in this computer.
    cout<<thread::hardware_concurrency()<<endl;
    return 0;
}