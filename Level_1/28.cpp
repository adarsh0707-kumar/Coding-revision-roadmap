/*
28. Prime Factorization

Print the prime factors of a positive integer, including repeated factors. Example: 12 → 2 2 3.
*/

#include <iostream>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    if (n < 2)
    {
        cout << "Enter a number greater than 1\n";
        return 0;
    }

    for (long long i = 2; i <= n / i; i++)
    {
        while (n % i == 0)
        {
            cout << i << ' ';
            n /= i;
        }
    }

    if (n > 1)
        cout << n;

    cout << '\n';
}