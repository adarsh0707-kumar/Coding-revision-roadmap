/*
11. Reverse a String

Reverse a string without using a built-in reverse function.
*/

#include<iostream>
#include<cstring>

void reverseString(std::string &s){
    if(s.length() <= 0){
        std::cout << "String is Empty." << std::endl;
        return;
    }

    int start = 0;
    int end = s.length() - 1;

    while (start < end)
    {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

int main(){
    std::string str = "Mahakal";

    std::cout << "Original String: " << str << std::endl;

    reverseString(str);

    std::cout << "Reversed strings: " << str << std::endl;
    return 0;
}