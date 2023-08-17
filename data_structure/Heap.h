#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include <vector>
#include<assert.h>
#include<algorithm>
#include<windows.h>
using namespace std;
typedef int DataType;

class Heap
{
private:
    DataType* a;   // 堆的物理存储结构为顺序结构，逻辑结构为完全二叉树
    int size;
    int capacity;
public:
	Heap() :a(new DataType[1]), size(0), capacity(1) {}
	~Heap()
	{
		delete[]a;
		a = nullptr;
		size = capacity = 0;
	}
public:
	void Push(const DataType& x);
	void Pop();
//	void sort(DataType* arr, int n);
	DataType Top()const { assert(size > 0); return a[0]; }
	bool Empty()const { return size == 0; }
	int Size()const { return size; }
	void print() {
        for (int i = 0; i < size; ++i) {
            cout << a[i] << ' ';
        }
        cout << endl;
    }
public:
	void AdjustUp(int child);
	void AdjustDown(int size, int parent);
};