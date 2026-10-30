/*
19. Least Common Multiple (LCM)

Find the LCM of two integers. Handle zero and reduce the risk of overflow.
*/

#include <iostream>
using namespace std;

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main()
{
    long long a, b;
    cin >> a >> b;

    if (a < 0 || b < 0)
    {
        cout << "Enter non-negative numbers\n";
        return 0;
    }

    if (a == 0 || b == 0)
    {
        cout << 0 << '\n';
        return 0;
    }

    long long g = gcd(a, b);
    long long reduced = a / g;

    if (reduced > LLONG_MAX / b)
    {
        cout << "Overflow\n";
        return 0;
    }

    cout << reduced * b << '\n';
}