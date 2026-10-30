/*
21. Strong Number

Check whether a number equals the sum of the factorials of its digits. Example: 145 = 1! + 4! + 5!.
*/

#include <iostream>
using namespace std;

int factorial(int n)
{
    int result = 1;

    for (int i = 2; i <= n; i++)
        result *= i;

    return result;
}

int main()
{
    long long n;
    cin >> n;

    if (n <= 0)
    {
        cout << "Not a strong number\n";
        return 0;
    }

    long long temp = n;
    long long sum = 0;

    while (temp > 0)
    {
        int digit = static_cast<int>(temp % 10);
        sum += factorial(digit);
        temp /= 10;
    }

    cout << (sum == n ? "Strong number" : "Not a strong number")
         << '\n';
}