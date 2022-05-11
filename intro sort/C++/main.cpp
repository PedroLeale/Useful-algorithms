#include <bits/stdc++.h>
#include "header.h"
#define size 10
using namespace std;


int main(){
    int array[size];
    // initialize random seed:
    srand (time(NULL));
    
    for(int i = 0; i < size; i++){
        array[i] = rand() % 100;
        //randomize number between 0 and 1000
    }

    printArray(array, size);

    Introsort(array, array, array + size-1);
    // if you don't know the size of the array, do this:
    //int n = sizeof(array) / sizeof(array[0]);
    //Introsort(array, array, array + n - 1);

    printArray(array, size);
}