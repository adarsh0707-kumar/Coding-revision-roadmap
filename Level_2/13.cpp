/*
13. Count Vowels and Consonants

Count vowels and consonants in a string, handling uppercase and lowercase letters.
*/

#include<iostream>
#include<string>
#include<cctype>

int main(){
    std::string str;
    std::cout << "Enter the string: ";
    std::getline(std::cin, str);

    if(str.empty()){
        std::cout << "String is empty" << std::endl;
        return 0;
    }

    int countVowels = 0;
    int countConsonants = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if(isalpha(str[i])){
            if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
                countVowels++;
            else
                countConsonants++;
        }
    }

    std::cout << "Vowels : " << countVowels << std::endl
        << "Consonants : " << countConsonants << std::endl;

    return 0;
}