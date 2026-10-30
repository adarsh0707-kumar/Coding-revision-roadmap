/*
3. Even or oddOperators 
· Very EasyEven or odd
Read an integer and determine whether it is even or odd.Example
Input: 17
Output: Odd
*/

#include<iostream>

int main(){
    int num;

    std::cout << "Enter the number ";
    std::cin >> num;

    if(num %2 == 0){
        std::cout << "Even" << std::endl ;
    }
    else{
        std::cout << "Odd" << std::endl;
    }
    return 0;
}