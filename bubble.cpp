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
void bubble_sort(int *arr , int n)
{
    
    for (int i=0; i<n-1; i++) {
        for (int j=0 ; j<n-1-i; j++) {
            if(arr[j]>arr[j+1])
                swap(&arr[j],&arr[j+1]);
        }
    }
    
}

int main()
{
    /* Generate dataset*/
    int min=1,max=1000,n=20000;
    int * dataset= generate_dataset(min,max,n);
    
    auto start = chrono::high_resolution_clock::now();
    
    // Call the function, here sort()
    bubble_sort(dataset, n);

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
