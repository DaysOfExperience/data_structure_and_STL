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

void testQuickSort() {
//    int arr[] = {4,2,5,6,1,7,8,3};
    int arr[] = {6,1,2,7,9,3,4,5,10,8};
    int sz = sizeof(arr)/sizeof (arr[0]);
    PrintArray(arr, sz);
    QuickSortHoare(arr, 0, sz-1);
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
    int arr[] = {10,6,7,1,3,9,4};
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
// 针对此情况，计数是最棒的，其次归并，其次是快排和希尔
    srand(time(nullptr));
    const int N = 10000000;
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
//    InsertSort(a1, N);   // 太慢了  N^2
    int end1 = clock();
std::cout << "11" << std::endl;
    int begin2 = clock();
    ShellSort(a2, N);
    int end2 = clock();
    std::cout << "11" << std::endl;

    int begin3 = clock();
//    SelectSort(a3, N);    // 太慢了 N^2
    int end3 = clock();
    std::cout << "11" << std::endl;

    int begin4 = clock();
    CountSort(a4, N);
    int end4 = clock();
    std::cout << "11" << std::endl;

    int begin5 = clock();
    QuickSortHoare(a5, 0, N-1);
    int end5 = clock();
    std::cout << "11" << std::endl;

    int begin6 = clock();
    MergeSort(a6, N);
    int end6 = clock();
    std::cout << "11" << std::endl;

    printf("InsertSort:%d\n", end1 - begin1);
    printf("ShellSort:%d\n", end2 - begin2);
    printf("SelectSort:%d\n", end3 - begin3);
    printf("CountSort:%d\n", end4 - begin4);
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
//    testQuickSort();
//    testQuickSortNoRecursionStack();
//    testQuickSortNoRecursionQueue();
//    testMergeSort();
//    testMergeSortNoRecursion();
//    testCountSort();

    testSortTime();
    return 0;
}