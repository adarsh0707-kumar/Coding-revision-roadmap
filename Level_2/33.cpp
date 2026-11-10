/*
33. Sum of Digits Using Recursion

Calculate the sum of an integer's digits recursively.
*/

#include<iostream>

unsigned long long sumOfDigit(int n){
    if(n < 0)
        n = -n;

    if(n == 0)
        return 0;

    return (n % 10) + sumOfDigit(n / 10);
}

int main(){
    int num;
    std::cout << "Enter the number: ";

    if(!(std::cin>>num)){
        std::cerr << "Invalid Input!";
        return 1;
    }

    std::cout << "Sum of digit " << num << " is " << sumOfDigit(num) << std::endl;

    return 0;
}