#include "Sort.h"

void testInsertSort() {
    int arr[] = {4,2,8,5,2,6,1,7,8,3};
    int sz = sizeof(arr)/sizeof (arr[0]);
    InsertSort(arr, sz);
    PrintArray(arr, sz);
}

void testShellSort() {
    int arr[] = {4,2,5,6,1,7,8,3};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    ShellSort(arr, sz);
    PrintArray(arr, sz);
}

void testSelectSort() {
    int arr[] = {9,1,5,6,1,7,8,3};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    SelectSort(arr, sz);
    PrintArray(arr, sz);
}

void testBubbleSort() {
    int arr[] = {9,1,5,6,1,7,8,3};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    BubbleSort(arr, sz);
    PrintArray(arr, sz);
}

void testQuickSort1() {
    int arr[] = {4,2,5,6,1,7,8,3};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
//    QuickSort(arr,sz);
    PrintArray(arr, sz);
}
void testQuickSort() {
//    int arr[] = {4,2,5,6,1,7,8,3};
    int arr[] = {6,1,2,7,9,3,4,5,10,8};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    QuickSort(arr,0,sz-1);
    PrintArray(arr, sz);
}
void testQuickSortNoRecursionStack() {
//    int arr[] = {4,2,5,6,1,7,8,3};
    int arr[] = {6,1,2,7,9,3,4,5,10,8};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    QuickSortNoRecursionStack(arr,0,sz-1);
    PrintArray(arr, sz);
}
void testQuickSortNoRecursionQueue() {
//    int arr[] = {4,2,5,6,1,7,8,3};
    int arr[] = {6,1,2,7,9,3,4,5,10,8};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    QuickSortNoRecursionQueue(arr,0,sz-1);
    PrintArray(arr, sz);
}
void testMergeSort() {
//    int arr[] = {4,2,5,6,1,7,8,3};
    int arr[] = {10,6,7,1,3,9,4,2};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    MergeSort(arr,sz);
    PrintArray(arr, sz);
}
void testMergeSortNoRecursion() {
//    int arr[] = {4,2,5,6,1,7,8,3};
    int arr[] = {10,6,7,1,3,9,4,2};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    MergeSortNoRecursion(arr,sz);
    PrintArray(arr, sz);
}
void testCountSort() {
    int arr[] = {10,15,12,15,16,17,11,12,10,14};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    CountSort(arr,sz);
    PrintArray(arr, sz);
}
void testSortTime() {
    srand(time(nullptr));
    const int N = 1000000;
    int* a1 = (int*)malloc(sizeof(int)*N);
    int* a2 = (int*)malloc(sizeof(int)*N);
    int* a3 = (int*)malloc(sizeof(int)*N);
    int* a4 = (int*)malloc(sizeof(int)*N);
    int* a5 = (int*)malloc(sizeof(int)*N);
    int* a6 = (int*)malloc(sizeof(int)*N);

    for(int i = 0; i < N; ++i) {
        a1[i] = rand();
        a2[i] = a1[i];
        a3[i] = a1[i];
        a4[i] = a1[i];
        a5[i] = a1[i];
        a6[i] = a1[i];
    }

    int begin1 = clock();
//    InsertSort(a1, N); // ²åÈëÅÅÐò
    int end1 = clock();

    int begin2 = clock();
//    ShellSort(a2, N);  // Ï£¶ûÅÅÐò
    int end2 = clock();

    int begin3 = clock();
//    SelectSort(a3, N);  // Ñ¡ÔñÅÅÐò£¬À­¿ç
    int end3 = clock();

    int begin4 = clock();
//    HeapSort(a4, N);         // ¶ÑÅÅ
    int end4 = clock();

    int begin5 = clock();
    QuickSort(a5, 0, N-1);  // ¿ìÅÅ
    int end5 = clock();

    int begin6 = clock();
//    MergeSort(a6, N);       // ¹é²¢
    int end6 = clock();

    printf("InsertSort:%d\n", end1 - begin1);
    printf("ShellSort:%d\n", end2 - begin2);
    printf("SelectSort:%d\n", end3 - begin3);
    printf("HeapSort:%d\n", end4 - begin4);
    printf("QuickSort:%d\n", end5 - begin5);
    printf("MergeSort:%d\n", end6 - begin6);
    free(a1);
    free(a2);
    free(a3);
    free(a4);
    free(a5);
    free(a6);
}

int main()
{
//    testInsertSort();
//    testShellSort();
//    testSelectSort();
//    testBubbleSort();
    testQuickSort();
//    testQuickSortNoRecursionStack();
//    testQuickSortNoRecursionQueue();
//    testMergeSort();
//    testMergeSortNoRecursion();
//    testCountSort();

//    testSortTime();
    return 0;
}