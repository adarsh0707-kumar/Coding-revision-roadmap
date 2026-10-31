/*
14. Count Words in a Sentence

Count words while handling repeated spaces and leading or trailing whitespace.
*/

#include<iostream>
#include<string>

int main(){
    std::string str;
    std::cout << "Enter the string : ";
    std::getline(std::cin, str);

    if(str.empty()){
        std::cout << "String is empty." << std::endl;
        return 0;
    }
    int wordCount = 0;
    bool inWord = false;

    for (size_t i = 0; i < str.length(); i++){
        if(str[i] != ' '){
            if(!inWord){
                wordCount++;
                inWord = true;
            }
        }
        else 
            inWord = false;

    }

    std::cout << "Word present in this string '" << str << "' :" << wordCount << std::endl;
    return 0;
}