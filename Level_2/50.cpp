/*
50. Two Sum

Given an integer array and a target, find two distinct elements whose sum equals the target. Try a brute-force solution first, then improve it using std::unordered_map.
*/

#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstddef>

void twoSum(std::vector<int>& arr, int target){
    if(arr.size() < 2){
        std::cout << "Need at least two elements!\n";
        return;
    }

    int sizeArr = arr.size();

    for (int i = 0; i < sizeArr; i++){
        for (int j = i+1; j < sizeArr; j++){
            if(target == arr[i] + arr[j]){
                std::cout << arr[i] << " + " << arr[j] << " = " << target << std::endl;
            }
        }
    }
}

void twoSumOptimal(const std::vector<int> &arr, int target)
{
    if (arr.size() < 2)
    {
        std::cout << "Need at least two elements!\n";
        return;
    }

    // Stores {number, index} of elements seen so far
    std::unordered_map<int, std::size_t> seen;

    for (std::size_t i = 0; i < arr.size(); ++i)
    {
        int complement = target - arr[i];

        // Check if the matching partner was seen earlier in the array
        if (auto it = seen.find(complement); it != seen.end())
        {
            std::cout << complement << " + " << arr[i] << " = " << target
                      << " (indices " << it->second << " and " << i << ")\n";
        }

        // Record current number and its index after checking (ensures distinct indices)
        seen[arr[i]] = i;
    }
}

int main(){

    std::vector<int> arr = {0, -90, 30, 4, 5, 25, -10, 45, -5, 10};

    int target = 35;

    twoSum(arr, target);

    std::cout << "Optimal \n";

    std::cout << "Pairs summing to " << target << ":\n";
    twoSumOptimal(arr, target);
}