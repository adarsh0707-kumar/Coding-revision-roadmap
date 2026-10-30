/*
5. Largest of three numbersConditional logic 
· EasyLargest of three numbers
Find the largest among three integers without using a sorting function.Example
Input: 14 27 19
Output: 27
*/

#include<iostream>

int main(){

    int a, b, c;
    std::cout << "Enter three Number's: ";
    std::cin >> a >> b >> c;

    if((a >= b) && (a >= c)){
        std::cout << a << " is greater in among three " << a << ", " << b << ", " << c << std::endl;
    }
    else if((b >= a) && (b >= c)){
        std::cout << b << " is greater in among three " << a << ", " << b << ", " << c << std::endl;
    }
    else{
        std::cout << c << " is greater in among three " << a << ", " << b << ", " << c << std::endl;
    }

    return 0;
}