/*
17. Remove Duplicate Characters

Remove repeated characters while preserving the first occurrence of each character.
*/

#include <iostream>
#include <string>
#include <vector>

void removeDuplicate(std::string &s)
{
    std::vector<bool> seen(256, false);
    std::string newString = "";

    for (char ch : s)
    {
        // Cast to unsigned char to avoid negative indexing for extended ASCII
        unsigned char uCh = static_cast<unsigned char>(ch);
        if (!seen[uCh])
        {
            seen[uCh] = true;
            newString += ch;
        }
    }

    s = newString; // Modify the original string passed by reference
}

int main()
{
    std::string s;
    std::cout << "Enter the string: ";
    std::getline(std::cin, s);

    removeDuplicate(s);

    std::cout << "Result: " << s << std::endl;
    return 0;
}