/*
19. Build a Calculator Using Functions

Implement addition, subtraction, multiplication, and division in separate functions.
*/

#include<iostream>

void addition(int a, int b){
    long long sum = static_cast<long long>(a) + b;
    std::cout << "Sum of : " << a << " + " << b << " is " << sum << std::endl;
}

void subtraction(int a, int b){
    long long sub = static_cast<long long>(a) - b;
    std::cout << "Sub of : " << a << " - " << b << " is " << sub << std::endl;
}

void multiplication(int a, int b){

    long long mul = static_cast<long long>(a) * b;

    std::cout << "Multiply of : " << a << " X " << b << " is " << mul << std::endl;
}

void division(int a, int b){

    if(b == 0){
        std::cout << "Error: Division by zero is undefined!" << std::endl;
        return;
    }

    double result = static_cast<double>(a) / b;

    std::cout << "Division of : " << a << " / " << b << " is " << result << std::endl;
}

int main(){

    int a, b;
    char op;

    std::cout << "Enter the operator : ";
    std::cin >> op;

    std::cout << "Enter the number for calculation(+,-,*,/) : ";
    std::cin >> a>> b;


    switch(op){
    
        case '+':
            addition(a, b);
            break;
        case '-':
            subtraction(a, b);
            break;
        case '*':
            multiplication(a, b);
            break;
        
        case '/':
            division(a, b);
            break;
        default:
            std::cout << "Error: Invalid operator ('" << op << "')" << std::endl;

    }

    return 0;
}