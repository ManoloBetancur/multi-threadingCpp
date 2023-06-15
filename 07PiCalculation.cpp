#include<iostream>
#include<thread>
#include<cmath>
#include<iomanip>

using namespace std;



//Leibneiz formula for pi
double calculate_pi(int n)
{
    double sum = 0.0;
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
    // Number of iterations in the series that calculates pi
    int i = 1E8;
    double pi = calculate_pi(i);
    cout<<setprecision(15)<<pi<<endl;
    return 0;
}