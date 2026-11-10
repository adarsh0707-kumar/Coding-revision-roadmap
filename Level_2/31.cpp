/*
31. Factorial Using Recursion

Calculate the factorial of a non-negative integer recursively.
*/

#include<iostream>

unsigned long long factorial(int n){
    if(n <=1 )
        return 1;

    return n * factorial(n - 1);
}

int main(){
    int num;
    std::cout << "Enter the number: ";
    std::cin >> num;


    if(num < 0){
        std::cout << "Factorial is not define for negative number";
    }
    else if (num > 20)
    {
        std::cout << "Overflow error: Factorial of " << num
                  << " exceeds the maximum capacity of 64-bit integers (max n = 20).\n";
    }
    else{
        std::cout << "Factorial of " << num << " is " << factorial(num) << std::endl;
    }

    return 0;
}