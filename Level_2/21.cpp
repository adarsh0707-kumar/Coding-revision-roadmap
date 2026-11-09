/*
21. Prime Numbers Using Functions

Create a function that checks whether a number is prime and use it to print primes in a range.
*/
#include <iostream>
#include <limits>

using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;

    if (n <= 3)
        return true;

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i <= n / i; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

int main()
{
    int start, end;

    cout << "Enter the starting and ending numbers: ";

    if (!(cin >> start >> end))
    {
        cout << "Error: Invalid input.\n";
        return 1;
    }

    if (start > end)
    {
        cout << "Error: Starting number cannot exceed ending number.\n";
        return 1;
    }

    cout << "Prime numbers between " << start << " and " << end << ":\n";

    for (int n = start;; ++n)
    {
        if (isPrime(n))
            cout << n << " ";

        // Prevent signed integer overflow when end == INT_MAX.
        if (n == end)
            break;
    }

    cout << '\n';

    return 0;
}