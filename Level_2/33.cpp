/*
33. Sum of Digits Using Recursion

Calculate the sum of an integer's digits recursively.
*/

#include<iostream>

unsigned long long sumOfDigit(unsigned int n){
    
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

    unsigned int magnitude =
        num < 0
            ? 0u - static_cast<unsigned int>(num)
            : static_cast<unsigned int>(num);

    std::cout << "Sum of digit " << num << " is " << sumOfDigit(magnitude) << std::endl;

    return 0;
}