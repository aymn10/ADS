// Implement Heap Sort using Heap Data Structure.
//
// • Construct a Heap from given input
// • Perform Heap Sort in ascending order
// • Display intermediate heap structures
// • Analyze time complexity of Heap Sort

#include <stdio.h>

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void heapify(int arr[],int n,int i)
{
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<n && arr[left]>arr[largest])
    {
        largest=left;
    }

    if(right<n && arr[right]>arr[largest])
    {
        largest=right;
    }

    if(largest!=i)
    {
        swap(&arr[i],&arr[largest]);
        
        heapify(arr,n,largest);
    }
}

void display(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }

    printf("\n");
}

void heapSort(int arr[],int n)
{
    for(int i=n/2-1;i>=0;i--)
    {
        heapify(arr,n,i);
    }

    printf("\nMax Heap Structure:\n");
    display(arr,n);

    for(int i=n-1;i>0;i--)
    {
        swap(&arr[0],&arr[i]);
        printf("\nAfter Swapping:\n");
        display(arr,n);
        heapify(arr,i,0);
        printf("Heap After Heapify:\n");
        display(arr,n);
    }
}

int main()
{
    int arr[100];
    int n;

    printf("Enter Number of Elements: ");
    scanf("%d",&n);

    printf("Enter Elements:\n");

    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    printf("\nOriginal Array:\n");
    display(arr,n);

    heapSort(arr,n);
    printf("\nSorted Array in Ascending Order:\n");
    display(arr,n);

    printf("\nTime Complexity:\n");

    printf("Best Case   : O(n log n)\n");
    printf("Average Case: O(n log n)\n");
    printf("Worst Case  : O(n log n)\n");

    return 0;
}

/*
Input:
5
4 2 8 1 6

Output:
Sorted Array in Ascending Order:
1 2 4 6 8
*/