/*
#  AUTHOR:     Srizan Gangol
#  COURSE:      CSCE 4110
#  ASSIGNMENT:  Assignment #1
*/
// C++ program to sort an array using bucket sort
#include <iostream>
#include <algorithm>
#include <vector>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Function to sort arr[] of size n using bucket sort
/* Function for bucket sort */
void Bucket_Sort(int array[], int n)
{  
    int i, j;  
    int count[n]; 
    for (i = 0; i < n; i++)
        count[i] = 0;
 
    for (i = 0; i < n; i++)
        (count[array[i]])++;
 
    for (i = 0, j = 0; i < n; i++)  
        for(; count[i] > 0; (count[i])--)
            array[j++] = i;
}   



void shuffle(int *arr, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}


void repeatRand(int *arr, size_t n)
{
	srand((unsigned)time(0)); 
     
    for(int i=0; i<n -1; i++){ 
        arr[i] = (rand()%100)+1; 
	}	
}
/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("n");
}

// Driver program to test above functions
int main()
{
	
    int i;
	//int  max = 100000;
	//int  max = 500000;
	//int  max = 1000000;
	int max= 5000;
	

    //int arr[max];
	int arr[max];
    for (i=0; i<max; i++){
        arr[i] = i;
    }
	
	printf("\n Listing the unsorted Array\n");
    //shuffle(arr, max);
	// Repeat Random
	srand((unsigned)time(0)); 
     
    for(int i=0; i<max -1; i++){ 
        arr[i] = (rand()%100)+1; 
	}	
	
	
	printArray(arr, max);
	
	
	
	// Implementing BucketSort
	printf("\n Implenting Bucket Sort\n");
	Bucket_Sort(arr, max); 
	printArray(arr, max);

	
	return 0;
	
	
}

