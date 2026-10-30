/*
9. Sum from 1 to NLoops and arithmetic 
· EasySum from 1 to N
Read N and calculate 1 + 2 + ... + N using a loop.Example
Input: 5
Output: 15
*/

#include<iostream>

int main(){
    long long n;
    std::cout << "Enter the number: ";
    std::cin >> n;

    long long sum = (n * (n + 1)) / 2;

    std::cout << "Sum = " << sum << std::endl;

    return 0;
}