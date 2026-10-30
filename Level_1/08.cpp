/*
8. Multiplication tableLoops 
· EasyMultiplication table
Print the multiplication table of a given number from 1 to 10.Example
Input: 5
Output: 5 10 15 20 25 30 35 40 45 50
*/

#include<iostream>

int main(){

    int a;
    std::cout << "Enter number for multiplication table: ";
    std::cin >> a;

    for (int i = 1; i <= 10; i++){
        std::cout << i << " * " << a << " = " << i * a << std::endl;
    }

        return 0;
}