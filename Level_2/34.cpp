/*
34. Reverse a String Recursively

Reverse a string using recursion without a built-in reverse function.
*/

#include<iostream>

void reverseString(std::string& str, int start, int end){
    if(start >= end)
        return;

    std::swap(str[start], str[end]);

    reverseString(str, start + 1, end - 1);
}

int main(){

    std::string text;

    std::cout << "Enter the string: ";`
    std::getline(std::cin, text);

    reverseString(text, 0, text.length() - 1);
    std::cout << "Reversed (Recursive): " << text << std::endl; 
    return 0;
}