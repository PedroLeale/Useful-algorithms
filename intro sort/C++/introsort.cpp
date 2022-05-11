//This algorithm uses 4 different sorting algorithms, and chooses
//the best one based on depth limit (basically the maximum depth of the recursion).
//It is one of the fastes sorting algorithms, HOWEVER, it has it's issues.
//First of all, it is not a stable algorithm., and if the data can't fit in the array,
//it cannot be used.
//Source: geeks for geeks.

#include <bits/stdc++.h>
#include "header.h"
using namespace std;

void Introsort(int arr[], int* begin, int* end){ 
    int depthLimit = 2 * log(end - begin);
 
    IntrosortUtil(arr, begin, end, depthLimit);
}

// A utility function ot print an array of size n
void printArray(int arr[], int n){
    for (int i = 0; i < n; i++)
        cout << arr[i] << " \n"[i + 1 == n];
}

void IntrosortUtil(int arr[], int* begin, int* end, int depthLimit){
    int size = end - begin;

    // If partition size is low then do insertion sort
    if (size < 16) {
        InsertionSort(arr, begin, end);
        return;
    }
 
    // If the depth is zero use heapsort
    if (depthLimit == 0) {
        make_heap(begin, end + 1);
        sort_heap(begin, end + 1);
        return;
    }
 
    // Else use a median-of-three concept to
    // find a good pivot
    int* pivot = MedianOfThree(begin, begin + size / 2, end);
 
    // Swap the values pointed by the two pointers
    swapValue(pivot, end);
 
    // Perform Quick Sort
    int* partitionPoint = Partition(arr, begin - arr, end - arr);
    IntrosortUtil(arr, begin, partitionPoint - 1, depthLimit - 1);
    IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1);
 
    return;
}

/* -------Sorting Function------- */

void InsertionSort(int arr[], int* begin, int* end){
    int left = begin - arr;
    int right = end - arr;
 
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
 
    return;
}



/* -------Support Functions------- */

// A function to partition the array and return
// the partition point
int* Partition(int arr[], int low, int high){
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element
 
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            // increment index of smaller element
            i++;
 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (arr + i + 1);
}



// A function that find the middle of the
// values pointed by the pointers a, b, c
// and return that pointer.
// This function will leave some warnings
int* MedianOfThree(int* a, int* b, int* c){
    if (*a < *b && *b < *c)
        return (b);
 
    if (*a < *c && *c <= *b)
        return (c);
 
    if (*b <= *a && *a < *c)
        return (a);
 
    if (*b < *c && *c <= *a)
        return (c);
 
    if (*c <= *a && *a < *b)
        return (a);
 
    if (*c <= *b && *b <= *a)
        return (b);

}

void swapValue(int* a, int* b){
    int* temp = a;
    a = b;
    b = temp;
    return;
}
 