/*
12. Check a String Palindrome

Determine whether a string reads the same forward and backward.
*/

#include<iostream>
#include<string>

bool isPalindrome(std::string &s){

    if(s.empty())
        return true;
    
    int start = 0;
    int end = s.length() - 1;

    while (start < end)
    {
        if(s[start] != s[end])
            return false;
        start++;
        end--;
    }
    return true;
}

int main(){
    std::string str;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);

    if(str.empty()){
        std::cout << "String is empty." << std::endl;
        return 0;
    }

    std::cout << "Given string " << '"'<<str <<'"'<< (isPalindrome(str) ? " is Palindrome " : " is not Palindrome ") << std::endl;

    return 0;
}