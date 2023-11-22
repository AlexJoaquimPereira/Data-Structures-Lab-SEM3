#include <stdio.h>
#include <stdlib.h>
int arr2[100],arr3[100];
// insertion merge quick heap
void insertionsort()
{
    int n, i, k, j;
    printf("Enter no of terms in array : ");
    scanf("%d", &n);
    char arr[n];
    getchar();
    printf("Enter Array terms\n");
    for (i = 0; i < n; i++)
    {
        scanf(" %c", &arr[i]);
    }
    for (i = 1; i < n; i++)
    {
        k = arr[i];
        for (j = i - 1; j >= 0 && k < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = k;
    }
    printf("Sorted Array:\n");
    for (i = 0; i < n; i++)
    {
        printf("%c ", arr[i]);
    }
    printf("\n");

    printf("Enter no of terms in array(descending order) : ");
    scanf("%d", &n);
    getchar();
    printf("Enter Array terms\n");
    for (i = 0; i < n; i++)
    {
        scanf(" %c", &arr[i]);
    }
    for (i = 1; i < n; i++)
    {
        k = arr[i];
        for (j = i - 1; j >= 0 && k > arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = k;
    }
    printf("Sorted Array (Descending Order):\n");
    for (i = 0; i < n; i++)
    {
        printf("%c ", arr[i]);
    }
    printf("\n");
}

void restoreDown(int arr[], int i, int size) {
    int left = 2 * i, right = left + 1;
    int num = arr[i];
    while (right <= size) {
        if (num >= arr[left] && num >= arr[right]) {
            arr[i] = num;
            return;
        } else if (arr[left] > arr[right]) {
            arr[i] = arr[left];
            i = left;
        } else {
            arr[i] = arr[right];
            i = right;
        }
        left = 2 * i;
        right = left + 1;
    }
    if (left == size && num < arr[left]) {
        arr[i] = arr[left];
        i = left;
    }
    arr[i] = num;
}

void buildHeap(int arr[], int size) {
    int i;
    for (i = size / 2; i >= 1; i--)
        restoreDown(arr, i, size);
}

int del_root(int arr[], int *size) {
    int max = arr[1];
    arr[1] = arr[*size];
    (*size)--;
    restoreDown(arr, 1, *size);
    return max;
}

void heap_sort() {
    int size;
    printf("Enter no of terms in array : ");
    scanf("%d", &size);
    int arr[size + 1]; // Increase the size by 1 to use arr[1] as the root
    getchar();
    printf("Enter Array terms\n");
    for (int i = 1; i <= size; i++) // Start from index 1
    {
        scanf("%d", &arr[i]);
    }
    int max;
    buildHeap(arr, size);
    printf("Sorted Array (Ascending Order): ");
    int sortedSize = size;
    while (sortedSize > 0) {
        max = del_root(arr, &sortedSize);
        printf("%d ", max);
    }
    printf("\n");
}

void heap_sortdesc() {
    int size;
    printf("Enter no of terms in array : ");
    scanf("%d", &size);
    int arr[size + 1]; // Increase the size by 1 to use arr[1] as the root
    getchar();
    printf("Enter Array terms\n");
    for (int i = 1; i <= size; i++) // Start from index 1
    {
        scanf("%d", &arr[i]);
    }
    int max;
    buildHeap(arr, size);
    printf("Sorted Array (Descending Order): ");
    while (size > 0) // Change the condition to > 0
    {
        max = del_root(arr, &size);
        printf("%d ", max);
    }
    printf("\n");
}

int partition(int arr[], int low, int up) {
    int pivot, temp, i, j;
    pivot = arr[low];
    i = low + 1;
    j = up;
    while (i <= j) {
        while (i <= up && arr[i] <= pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i < j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    arr[low] = arr[j];
    arr[j] = pivot;
    return j;
}

int partitiondesc(int arr[], int low, int up) {
    int pivot, temp, i, j;
    pivot = arr[low];
    i = low + 1;
    j = up;
    while (i <= j) {
        while (i <= up && arr[i] >= pivot)
            i++;
        while (arr[j] < pivot)
            j--;
        if (i < j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    arr[low] = arr[j];
    arr[j] = pivot;
    return j;
}


void quick(int arr[], int low, int up)
{
    int pivloc;
    if (low > up)
        return;
    pivloc = partition(arr, low, up);
    quick(arr, low, pivloc - 1);
    quick(arr, pivloc + 1, up);
}

void quickdesc(int arr[], int low, int up)
{
    int pivloc;
    if (low > up)
        return;
    pivloc = partitiondesc(arr, low, up);
    quickdesc(arr, low, pivloc - 1);
    quickdesc(arr, pivloc + 1, up);
}



int main()
{
    int choice, n;

    do
    {
        printf("\nMenu:\n");
        printf("1. Insertion Sort\n");
        printf("2. Ascending Quicksort\n");
        printf("3. Descending Quicksort\n");
        printf("4. Ascending Heapsort\n");
        printf("5. Descending Heapsort\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insertionsort();
            break;
        case 2:
            printf("Enter no of terms in array : ");
            scanf("%d", &n);
            getchar();
            printf("Enter Array terms\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr2[i]);
            }
            quick(arr2, 0, n - 1);
            printf("Sorted Array using Ascending Quicksort: ");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", arr2[i]);
            }
            printf("\n");
            break;
        case 3:
            printf("Enter no of terms in array : ");
            scanf("%d", &n);
            getchar();
            printf("Enter Array terms\n");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr3[i]);
            }
            quickdesc(arr3, 0, n - 1);
            printf("Sorted Array using Descending Quicksort: ");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", arr3[i]);
            }
            printf("\n");
            break;
        case 4:
            heap_sort();
            break;
        case 5:
            heap_sortdesc();
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 6);

    return 0;
}