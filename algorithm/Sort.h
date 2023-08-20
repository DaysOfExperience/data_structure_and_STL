//
// Created by yangzilong on 2022/7/6.
//

#ifndef SORT_SORT_H
#define SORT_SORT_H
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cassert>
#include <stack>
#include <queue>
#include <cstring>
using namespace  std;

void PrintArray(int* p, int n);
// 插入排序
void InsertSort(int* p, int n);
// 希尔排序
void ShellSort(int* p, int n);
// 选择排序
void SelectSort(int* p, int n);
// 冒泡排序
void BubbleSort(int* p, int n);
// 快速排序
void QuickSort(int* p, int n1, int n2);
// 快速排序非递归栈实现
void QuickSortNoRecursionStack(int* p, int n1, int n2);  // NoRecursion
// 快速排序非递归队列实现
void QuickSortNoRecursionQueue(int* p, int n1, int n2);  // NoRecursion
// 归并排序
void MergeSort(int* p, int n);
// 归并排序非递归实现
void MergeSortNoRecursion(int* p, int n);
// 归并排序非递归实现：memcpy位置修改
void MergeSortNoRecursion2(int* p, int n);
// 计数排序
void CountSort(int*p, int n);

#endif //SORT_SORT_H
