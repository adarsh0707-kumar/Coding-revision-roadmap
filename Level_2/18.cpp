/*
18. First Non-Repeating Character

Find the first character that appears exactly once.
*/

#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

std::optional<char> firstNonRepeatingChar(const std::string &str)
{
    std::unordered_map<char, int> freq;
    for (char ch : str)
        freq[ch]++;

    for (char ch : str)
    {
        if (freq[ch] == 1)
            return ch;
    }

    return std::nullopt; // Explicitly signals "no value"
}

int main()
{
    std::string s = "afdaeaasfed3";
    auto result = firstNonRepeatingChar(s);

    if (result.has_value())
    { // or simply: if (result)
        std::cout << "First non-repeating character: " << *result << '\n';
    }
    else
    {
        std::cout << "No non-repeating character found.\n";
    }

    return 0;
}