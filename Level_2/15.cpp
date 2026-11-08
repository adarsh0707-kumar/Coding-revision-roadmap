/*
15. Character Frequency

Count how many times each character occurs in a string.
*/

#include<iostream>
#include<string>

void charFrequency(std::string &s){

    int strSize = s.size();

    for (int i = 0; i < strSize; i++){
        int freq = 1;

        bool seen = false;

        for (int j = 0; j < i; j++){
            if(s[j] == s[i]){
                seen = true;
                break;
            }
        }

        if(seen)
            continue;

        for(int j = i + 1; j < strSize; j++){
            if(s[j]==s[i]){
                freq++;
            }
        }

        std::cout << s[i] << " " << freq << ", ";
    }
    std::cout << std::endl;
}

int main(){

    std::string s;
    std::cout << "Enter the strings: ";
    std::getline(std::cin, s);

    charFrequency(s);
    return 0;
}