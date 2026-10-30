/*
16. Armstrong Number

Check whether a non-negative integer equals the sum of its digits, each raised to the power of the number of digits. Example: 153 is an Armstrong number.
*/

#include <iostream>
using namespace std;

long long integerPower(int base, int exp)
{
    long long result = 1;

    while (exp-- > 0)
        result *= base;

    return result;
}

int main()
{
    long long n;
    cin >> n;

    if (n < 0)
    {
        cout << "Not an Armstrong number\n";
        return 0;
    }

    long long temp = n;
    int digits = 0;

    do
    {
        digits++;
        temp /= 10;
    } while (temp > 0);

    temp = n;
    long long sum = 0;

    do
    {
        int digit = static_cast<int>(temp % 10);
        sum += integerPower(digit, digits);
        temp /= 10;
    } while (temp > 0);

    cout << (sum == n ? "Armstrong number" : "Not an Armstrong number")
         << '\n';
}