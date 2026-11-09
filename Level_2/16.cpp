/*
16. Check Anagrams

Determine whether two strings contain the same characters with the same frequencies.
*/

#include<iostream>
#include<string>

bool isAnagrams(std::string &s1, std::string &s2){

    if(s1.length() != s2.length()){
        return false;
    }

    int charCount[256] = {};

    for (size_t i = 0; i < s1.length(); i++){

        unsigned char c1 = static_cast<unsigned char>(s1[i]);
        unsigned char c2 = static_cast<unsigned char>(s2[i]);

        charCount[c1]++;
        charCount[c2]--;
    }

    for (int i = 0; i < 256; i++){
        if(charCount[i] != 0)
            return false;
    }

    return true;
}

int main(){

    std::string s1 = "asdf09876";
    std::string s2 = "67890fdas";

    std::cout << s1 << (isAnagrams(s1, s2) ? " Anagrams. " : " Not Anagrams.") << std::endl;

    return 0;
}