/*
34. Reverse a String Recursively

Reverse a string using recursion without a built-in reverse function.
*/

#include <iostream>
#include <string>
#include <utility>

void reverseString(std::string &str, std::size_t left = 0)
{
    if (left >= str.size() / 2)
        return;

    std::swap(str[left], str[str.size() - 1 - left]);

    reverseString(str, left + 1);
}

int main()
{
    std::string text;

    std::cout << "Enter the string: ";
    std::getline(std::cin, text);

    reverseString(text);

    std::cout << "Reversed string: " << text << '\n';

    return 0;
}