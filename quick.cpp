#include <iostream>
#include <chrono>

using namespace std;

// A utility function to swap two elements
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// A utility function to generate dataset
int * generate_dataset (int min , int max ,int n)   // n is the size of the dataset
{
    int *dataset = (int *)malloc(sizeof(int)*n)  , data ;
    for (int i = 0; i < n; i++) {
        data = rand() % max + min;                  //generate random number
        dataset[i]=data;                            //add to the array
    }
    return dataset;
}
/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("n");
}
/* This function takes last element as pivot, places
 the pivot element at its correct position in sorted
 array, and places all smaller (smaller than pivot)
 to left of pivot and all greater elements to right
 of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
 low  --> Starting index,
 high  --> Ending index */
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
int main()
{
    /* Generate dataset*/
    int min=1,max=1000,n=20000;
    int * dataset= generate_dataset(min,max,n);

    auto start = chrono::high_resolution_clock::now();

    // Call the function, here sort()
    quickSort(dataset, 0, n-1);

    // Get ending timepoint
    auto stop = chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get durarion. To cast it to proper unit
    // use duration cast method
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    printArray(dataset, n);

    cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl;

    return 0;
}
