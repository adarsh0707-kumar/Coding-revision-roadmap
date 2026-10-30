/*
29. Convert Decimal to Binary

Convert a non-negative decimal integer to binary without using a conversion library.
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    if (n < 0)
    {
        cout << "Enter a non-negative number\n";
        return 0;
    }

    long long original = n;
    string binary;

    if (n == 0)
    {
        binary = "0";
    }
    else
    {
        while (n > 0)
        {
            binary += char('0' + n % 2);
            n /= 2;
        }

        reverse(binary.begin(), binary.end());
    }

    cout << "Binary of " << original << " is " << binary << '\n';
}