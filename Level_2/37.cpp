/*
37. Tower of Hanoi

Print the steps required to move n disks between three rods, following the puzzle rules.
*/

#include<iostream>

void TOH(int n, char source, char destination, char auxiliary){

    if(n ==1){
        std::cout << "Move disk 1 from " << source << " to " << destination << std::endl;
        return;
    }

    // step 1: move top n-1 disks from source to auxiliary, using destination;

    TOH(n - 1, source, auxiliary, destination);

    // Step 2: Move the remaining nth (largest) disk from source to destination
    std::cout << "Move disk " << n << " from " << source << " to " << destination << std::endl;

    // Step 3: Move the n - 1 disks from auxiliary to destination, using source as helper
    TOH(n - 1, auxiliary, destination, source);
}

int main(){
    int numDisks = 3;
    TOH(numDisks, 'A', 'C', 'B');
    return 0;
}