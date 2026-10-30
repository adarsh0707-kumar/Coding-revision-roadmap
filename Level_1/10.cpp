/*
10. Reverse an integerDigit manipulation 
· EasyReverse an integer
Reverse the digits of a non-negative integer without converting it to a string. Consider what happens if the result exceeds the integer type's range.Example
Input: 1234
Output: 4321
*/

#include <iostream>
#include <climits>
using namespace std;

bool reverseInteger(int num, int &result)
{
    long long reversed = 0;
    int sign = (num < 0) ? -1 : 1;
    long long n = num;

    if (n < 0)
        n = -n;

    while (n > 0)
    {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }

    reversed *= sign;

    if (reversed < INT_MIN || reversed > INT_MAX)
        return false;

    result = static_cast<int>(reversed);
    return true;
}

int main()
{
    int num, result;
    cin >> num;

    if (reverseInteger(num, result))
        cout << result << '\n';
    else
        cout << "Overflow\n";
}