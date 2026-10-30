/*
20. Perfect Number

Determine whether a positive integer equals the sum of its positive proper divisors. Example: 6 = 1 + 2 + 3.
*/

#include <iostream>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    if (n <= 1)
    {
        cout << "Not a perfect number\n";
        return 0;
    }

    long long sum = 1;

    for (long long i = 2; i <= n / i; i++)
    {
        if (n % i == 0)
        {
            sum += i;

            long long other = n / i;
            if (other != i)
                sum += other;
        }
    }

    cout << (sum == n ? "Perfect number" : "Not a perfect number")
         << '\n';
}