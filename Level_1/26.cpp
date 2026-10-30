/*
26. Check a Prime Number in an Optimized Way

Improve your prime checker to test divisors only up to \(\sqrt{n}\). Explain why it works.
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