/*
15. Sum of Digits

Calculate the sum of all digits in an integer. Example: 583 → 16.
*/

#include <iostream>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    if (n < 0)
        n = -n;

    int sum = 0;

    do
    {
        sum += static_cast<int>(n % 10);
        n /= 10;
    } while (n > 0);

    cout << sum << '\n';
}