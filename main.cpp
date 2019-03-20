#include <iostream>
#include <stdlib.h>     /* rand */
#include<climits>
#include <chrono>

using namespace std;

/** P R O T O T Y P E S **/
int * generate_dataset (int min , int max ,int n);      // complexity O(n)
void swap(int *x, int *y);                              // Complexity O(1)

/** C L A S S E S **/
class MinHeap
{
    int * harr;         //pointer to the heap array
    int capacity;            //the max number the heap could contain
    int heap_size;      //the actual number of elements

public:
    MinHeap (int capacity); //constructor

    void MinHeapify(int ); //heapify the subtree whose root's index is given as a parameter

    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }

    int extractMin ();

    void decreaseKey(int i, int new_val);// Decreases key value of key at index i to new_val

    int getMin() { return harr[0]; }    // Returns the minimum key (key at root) from min heap

    void deleteKey(int i);// Deletes a key stored at index i

    void insertKey(int k);// Inserts a new key 'k'
};

/** I M P L I M E N T A T I O N S **/
    /*Constructor*/
MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}
    /* Inserts a new key 'k'*/
void MinHeap::insertKey(int k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);
    return root;
}

// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

int * heap_sort(int * arr , int n)
{
    MinHeap h(n);
    for (int j = 0; j < n ; j++) {
        h.insertKey(arr[j]);
    }
    int bro=0,c=0;
    while(bro!=INT_MAX)
    {
        bro=arr[c]=h.extractMin();
        c++;
    }
    return arr;
}

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
// A function to merge the two half into a sorted data.
void Merge(int *a, int low, int high, int mid)
{
    // We have low to mid and mid+1 to high already sorted.
    int i, j, k, temp[high-low+1];
    i = low;
    k = 0;
    j = mid + 1;

    // Merge the two parts into temp[].
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            temp[k] = a[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = a[j];
            k++;
            j++;
        }
    }

    // Insert all the remaining values from i to mid into temp[].
    while (i <= mid)
    {
        temp[k] = a[i];
        k++;
        i++;
    }

    // Insert all the remaining values from j to high into temp[].
    while (j <= high)
    {
        temp[k] = a[j];
        k++;
        j++;
    }


    // Assign sorted data stored in temp[] to a[].
    for (i = low; i <= high; i++)
    {
        a[i] = temp[i-low];
    }
}

// A function to split array into two parts.
void MergeSort(int *a, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        // Split the data into two half.
        MergeSort(a, low, mid);
        MergeSort(a, mid+1, high);

        // Merge them to get sorted output.
        Merge(a, low, high, mid);
    }
}

int main() {

    /* Generate dataset*/
    int min=1,max=1000,n=20;
    int * dataset= generate_dataset(min,max,n);

    cout<<"Unsorted data \n{";
       /* Print */
    for (int i = 0; i <n - 1; i++) {
        cout<<dataset[i]<<" ";
    }
    cout<<"}\n";





    // Get starting timepoint
    auto start = chrono::high_resolution_clock::now();


    /* Sort */
    dataset=heap_sort(dataset , n );
    // Get ending timepoint
    auto stop = chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get durarion. To cast it to proper unit
    // use duration cast method
    auto duration_heap = chrono::duration_cast<chrono::microseconds>(stop - start);


    dataset= generate_dataset(min,max,n);


    // Get starting timepoint
    start = chrono::high_resolution_clock::now();


    /* Sort */
    MergeSort(dataset, 0, n-1);

    // Get ending timepoint
    stop = chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get durarion. To cast it to proper unit
    // use duration cast method
    auto duration_merge = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout<<"Sorted data \n{";
    /* Print */
    for (int i = 0; i <n - 1; i++) {
        cout<<dataset[i]<<" ";
    }
    cout<<"}\n";
    cout << "Time taken by Heap Sort function: "
         << duration_heap.count() << " microseconds" << endl;
    cout << "Time taken by Merge Sort function: "
         << duration_merge.count() << " microseconds" << endl;

    return 0;
}
