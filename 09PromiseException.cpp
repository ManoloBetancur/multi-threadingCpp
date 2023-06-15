#include<iostream>
#include<thread>
#include<cmath>
#include<future>
#include<iomanip>
#include<exception>


using namespace std;

//FUTURE.get() will wait until getting the promise, if there is an exception during the process the program will hang...



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
    
    return sum*4;

}


int main()
{
    promise<double> promise;

    auto do_calculation = [&](int terms){
        try
        {
            auto result = calculate_pi(terms);
            promise.set_value(result);
        }
        catch(...)//Catch any exception
        {
            promise.set_exception(current_exception());//Catching the exception in the promise
        }
    };

    thread t1(do_calculation, 1E6);

    future<double> future = promise.get_future();

    //FUTURE.get() will wait until getting the promise, if there is an exception during the process the program will hang...
    try
    {
        //FUTURE.get() will wait until getting the promise, if there is an exception during the process the program will hang...
        cout<<setprecision(15)<<future.get()<<endl;
    }
    catch(const exception& e)
    {
        cout<<e.what()<<endl;
    }
    
    t1.join();
    return 0;
}