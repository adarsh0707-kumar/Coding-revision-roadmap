/*
35. Calculate Power Recursively

Calculate \(a^b\) recursively for a non-negative exponent.
*/

#include<iostream>

double powerFast(double x, long long n){
    // Base case
    if(n==0)
        return 1.0;

    if(n < 0)
        return 1.0 / powerFast(x, -n);

    double half = powerFast(x, n / 2);

    if(n%2 ==0){
        return half * half;
    }else{
        return x * half * half;
    }
}

int main(){
    double base, pow;
    std::cout << "Enter the number base and pow(x^n): ";
    std::cin >> base >> pow;

    std::cout << "Power of " << base << "^" << pow << " : " << powerFast(base, pow) << std::endl;

    return 0;
}