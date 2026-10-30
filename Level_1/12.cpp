/*
12. Check for a Prime Number

Determine whether an integer is prime. Handle numbers less than 2 and avoid checking every divisor up to n - 1.
*/

#include <iostream>
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
    int n;
    cin >> n;
    cout << (isPrime(n) ? "Prime" : "Not prime") << '\n';
}