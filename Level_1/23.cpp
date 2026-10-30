/*
23. Count Even and Odd Digits

Count the even and odd digits in an integer. Example: 123456 → 3 even, 3 odd.*/

#include <iostream>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    int evenCount = 0, oddCount = 0;

    do
    {
        int digit = static_cast<int>(n % 10);

        if (digit % 2 == 0)
            evenCount++;
        else
            oddCount++;

        n /= 10;
    } while (n != 0);

    cout << "Even digits: " << evenCount << '\n';
    cout << "Odd digits: " << oddCount << '\n';
}