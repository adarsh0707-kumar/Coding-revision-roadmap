/*
49. Balanced Parentheses

Given a string containing (), {}, and [], determine whether the brackets are correctly balanced. Use std::stack.
*/

#include <iostream>
#include <stack>
#include <string>

bool isBalanced(const std::string &str)
{
    std::stack<char> brackets;

    for (char ch : str)
    {
        // Push opening brackets onto the stack
        if (ch == '(' || ch == '{' || ch == '[')
        {
            brackets.push(ch);
        }
        // Check closing brackets against the top of the stack
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (brackets.empty())
                return false;

            char top = brackets.top();

            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '['))
            {
                return false;
            }

            brackets.pop();
        }
    }

    // True only if all opening brackets were matched and closed
    return brackets.empty();
}

int main()
{
    std::string tests[] = {
        "{[()]}",
        "([)]",
        "((()))",
        "(()",
        "}{",
        ""};

    for (const auto &test : tests)
    {
        std::cout << "\"" << test << "\" -> "
                  << (isBalanced(test) ? "Balanced" : "Not Balanced") << '\n';
    }

    return 0;
}
