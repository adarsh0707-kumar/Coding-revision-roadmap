/*
30. Convert Binary to Decimal

Convert a binary number represented as digits into its decimal value. Validate that the input contains only 0 and 1.
*/

#include <iostream>
#include <string>
#include <climits>
using namespace std;

int main()
{
    string binary;
    cin >> binary;

    if (binary.empty())
    {
        cout << "Invalid binary number\n";
        return 0;
    }

    long long decimal = 0;

    for (char bit : binary)
    {
        if (bit != '0' && bit != '1')
        {
            cout << "Invalid binary number\n";
            return 0;
        }

        int digit = bit - '0';

        if (decimal > (LLONG_MAX - digit) / 2)
        {
            cout << "Number is too large\n";
            return 0;
        }

        decimal = decimal * 2 + digit;
    }

    cout << decimal << '\n';
}