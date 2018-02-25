/*
#  AUTHOR:     Srizan Gangol
#  COURSE:      CSCE 4110
#  ASSIGNMENT:  Assignment #1
*/
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

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


// A utility function to swap two elements
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element

	for (int j = low; j <= high- 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (arr[j] <= pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
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
	
	
	
	
    int arr[max];
    for (i=0; i<max; i++){
        arr[i] = i;
    }
    // 1------------------------------------
	shuffle(arr, max);
	
	/*
	// 2 -----------------------------------
	// Repeat Random
	srand((unsigned)time(0)); 
     
    for(int i=0; i<max -1; i++){ 
        arr[i] = (rand()%100)+1; 
	}	
	*/
	
	
	printArray(arr, max);


	// Implementing QuickSort
	printf("\n Implenting Quick Sort\n");
	int n = sizeof(arr)/sizeof(arr[0]);
	quickSort(arr, 0, n-1);
	//bucketSort(arr, n);
	printf("Sorted array: n");
	printArray(arr, n);
	
	return 0;
}

