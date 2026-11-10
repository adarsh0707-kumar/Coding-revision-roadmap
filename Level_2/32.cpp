/*
32. Fibonacci Using Recursion

Generate Fibonacci numbers using a recursive function.
*/

#include<iostream>
#include<vector>

unsigned long long fibonacci(int n, std::vector<unsigned long long>& memo){
    if(n <= 1)
        return n;

    if(memo[n] != 0)
        return memo[n];

    memo[n] = fibonacci(n - 1, memo) + fibonacci(n - 2, memo);
    return memo[n];
}

int main(){
    int num;
    std::cout << "Enter the number: ";

    if(!(std::cin>>num)){
        std::cerr << "Invalid input!"<<std::endl;
        return 1;
    }

    if(num < 0){
        std::cout << "Fibonacci is not define for negative number!" << std::endl;
    }
    else{
        std::vector<unsigned long long> memo(num + 1, 0);
        std::cout << "Fibonacci sequence up to  " << num << " : " << std::endl;

        for (int i = 0; i <= num; i++){
            std::cout << fibonacci(i, memo) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}