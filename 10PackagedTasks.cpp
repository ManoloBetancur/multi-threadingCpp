#include<iostream>
#include<thread>
#include<cmath>
#include<future>
#include<iomanip>



using namespace std;


std::atomic<int> currentProgress{ 0 };
std::atomic<int> totalProgress{ 0 };



//Leibneiz formula for pi
double calculate_pi(int n)
{
    double sum = 0.0;
    if(n < 1)
    {
        throw runtime_error("Invalid number of terms to calculate");
    }
    for (int i = 0; i < n; i++)
    {
        int sign = pow(-1,i);
        double term = 1.0/(i*2+1);
        sum += sign*term;
    }
    cout<<"FINISHED !"<<endl;
    return sum*4;

}


int main()
{    
    const int MAX_ITER = 1E6;


    packaged_task<double(int)> task1(calculate_pi);


    future<double> future1 = task1.get_future();

    thread t1(move(task1),MAX_ITER);

    double pi = future1.get();
    cout<<setprecision(15)<< pi <<endl;
    
    t1.join();

    return 0;
}