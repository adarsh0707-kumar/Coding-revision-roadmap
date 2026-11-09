/*
24. Function Overloading

Create overloaded functions that calculate the area of a circle, rectangle, and square.
*/

#include <iostream>
#include <cmath>

// 1. Area of Circle (Radius)
double area(double radius)
{
    const double PI = 3.14159265358979323846;
    return PI * radius * radius;
}

// 2. Area of Rectangle (Length, Breadth)
double area(double length, double breadth)
{
    return length * breadth;
}

// 3. Area of Square (Side length, explicit shape tag to avoid signature collision with Circle)
enum Shape
{
    SQUARE
};
double area(double side, Shape)
{
    return side * side;
}

int main()
{
    double r, side, length, breadth;

    std::cout << "Enter radius of circle: ";
    std::cin >> r;

    std::cout << "Enter side of square: ";
    std::cin >> side;

    std::cout << "Enter length and breadth of rectangle: ";
    std::cin >> length >> breadth;

    std::cout << "\n--- Calculated Areas ---\n";
    std::cout << "Area of Circle:    " << area(r) << '\n';
    std::cout << "Area of Square:    " << area(side, SQUARE) << '\n';
    std::cout << "Area of Rectangle: " << area(length, breadth) << '\n';

    return 0;
}