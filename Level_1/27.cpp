/*
27. Print All Primes in a Range

Print every prime number between two given integers.
*/
#include <iostream>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i <= n / i; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

int main()
{
    int start, end;
    cin >> start >> end;

    if (start > end)
    {
        cout << "Invalid range\n";
        return 0;
    }

    for (int n = start;; n++)
    {
        if (isPrime(n))
            cout << n << ' ';

        if (n == end)
            break;
    }

    cout << '\n';
}