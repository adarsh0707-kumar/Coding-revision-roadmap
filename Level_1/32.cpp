/*
32. Find the Digital Root

Repeatedly sum the digits until a single digit remains. Example: 9875 → 2.
*/

#include <iostream>
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

    while (n >= 10)
    {
        long long sum = 0;

        while (n > 0)
        {
            sum += n % 10;
            n /= 10;
        }

        n = sum;
    }

    cout << n << '\n';
}