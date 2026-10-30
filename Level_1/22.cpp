/*
22. Power Without std::pow()

    Calculate \(a ^ b\) using a loop,
    where b is a non - negative integer.Consider overflow and the case \(0 ^ 0\).
*/

#include <iostream>
using namespace std;

int main()
{
    double base;
    int exponent;
    cin >> base >> exponent;

    if (base == 0 && exponent < 0)
    {
        cout << "Undefined\n";
        return 0;
    }

    double result = 1.0;
    long long e = exponent;

    if (e < 0)
        e = -e;

    for (long long i = 0; i < e; i++)
        result *= base;

    if (exponent < 0)
        result = 1.0 / result;

    cout << result << '\n';
}