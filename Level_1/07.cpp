/*
7. Leap year Boolean logic 
· Easy

Leap year
Determine whether a given year is a leap year.Example
Input: 2000
Output: Leap year
*/

#include<iostream>

int main(){

    int year;
    std::cout << "Enter a year: ";
    std::cin >> year;

    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        std::cout << "Leap year" << std::endl;
    }
    else{
        std::cout << "Not leap year" << std::endl;
    }

    return 0;
}