#define _CRT_SECURE_NO_WARNINGS 1

#include"Heap.h"

// 完全二叉树的末尾加新元素，且向上调整即可
void Heap::Push(const DataType& x)
{
	if (size == capacity)
	{
		int newcapacity = capacity == 0 ? 1 : capacity * 2;
		DataType* tmp = new DataType[newcapacity];
		assert(tmp);
		std::copy(a, a + size, tmp);   // 有问题~这是浅拷贝
		delete a;
		a = tmp;
		capacity = newcapacity;
	}
	a[size] = x;
	AdjustUp(size);
	++size;
}

// 注意：堆的删除只能删除堆顶的元素
// 删除堆顶元素：交换完全二叉树的根节点和最后一个叶子结点，再从根结点处向下调整即可
void Heap::Pop() // 删除堆顶的数据
{
	assert(size > 0);
	std::swap(a[0], a[size - 1]);
	size--;
	AdjustDown(size, 0);
}

// 23817
void Heap::AdjustUp(int child) {
    // 向上调整。
    int parent = (child - 1) / 2;
    while(child > 0) {
        if(a[parent] < a[child]) {
            std::swap(a[parent], a[child]);
            child = parent;
            parent = (child - 1) / 2;
        }
        else {
            break;  // 此时满足大根堆的条件
        }
    }
}

// old
//void Heap::AdjustUp(int child)
//{
//    // 小根堆
//	int parent = (child - 1) / 2;
//	while (child > 0)
//	{
//		if (a[parent] > a[child])
//		{
//			std::swap(a[parent], a[child]);
//			child = parent;
//			parent = (child - 1) / 2;
//		}
//		else
//		{
//			break;
//		}
//	}
////	int parent = (child - 1) / 2;
////	if(child > 0)
////	{
////		if (a[parent] > a[child])
////		{
////			Swap(a[parent], a[child]);
////			child = parent;
////			AdjustUp(child);
////		}
////		else
////		{
////			return;
////		}
////	}
//}
// 23817
// size 是总大小，parent是从哪里开始向下调整(下标，因为堆的物理结构是数组）
void Heap::AdjustDown(int size, int parent) {
    // 从parent这里开始向下调整
    int child = parent * 2 + 1;  // 左孩子
    while(child < size) {
        if(child + 1 < size && a[child + 1] > a[child]) {
            // 右孩子存在且右孩子更大，则要判断大根堆，就找出孩子里最大的来判断，因为目标是父是最大的
            child += 1;
        }
        if(a[parent] < a[child]) {
            // 不符合大根堆
            std::swap(a[parent], a[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        else {
            break;
        }
    }
}
//void Heap::AdjustDown(int size, int parent) // size 是总大小，parent是从哪里开始向下调整(下标，因为堆的物理结构是数组）
//{
//	int child = parent * 2 + 1;
//	while (child < size)
//	{
//		if (child + 1 < size && a[child + 1] < a[child])
//			child++;
//		if (a[child] < a[parent])
//		{
//			std::swap(a[child], a[parent]);
//			parent = child;
//			child = parent * 2 + 1;
//		}
//		else
//		{
//			break;
//		}
//	}
//}

void testHeap1()
{
	int n = 0;
	Heap h1;
	while (cin >> n)
	{
		h1.Push(n);
		h1.print();
	}
}

// 小堆的向上调整
void AdjustUp(int* a, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[parent] > a[child])
		{
			swap(a[parent], a[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

// 小堆的向下调整
void AdjustDown(int* a,int size, int parent) // size 是总大小，parent是从哪里开始向下调整 
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && a[child + 1] < a[child])
			child++;
		if (a[child] < a[parent])
		{
			swap(a[child], a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* a, int n) {
	// 将传入的数组看作一个完全二叉树，然后调整为堆。
	// 升序调整为大根堆，降序小根堆。
	
	// 建堆方式1： O(N*LogN)
	// 利用向上调整算法,其实就是堆的插入函数
	//for (int i = 1; i < n; ++i)
	//{
	//	AdjustUp(a, i);
	//}
	
	// 建堆方式2： O(N)
	// 利用向下调整算法：从第一个非叶子结点开始，也就是最后一个叶子结点的父节点开始，到根节点一直向下调整
	for (int i = ((n - 1) - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}
	// 建好堆之后排序 目前是一个小堆，小堆用来排降序
    // 利用堆的删除思想来排序
    // 5 13 17 19 22 27 32 35 38 42 45
    // O(N * LogN);
    while(--n) {
        // 进行n-1次删除思想即可
        std::swap(a[0], a[n]);
        AdjustDown(a, n, 0);
    }
}

// 23817，此处默认求k个最大的
void TopK(int *arr, int n, int k) {
    if(n < k) {
        std::cerr << "fuck you" << std::endl;
        exit(-1);
    }
    // 1.建k个元素的小堆
    // 建堆：向下调整
    for(int i = (k-1 -1)/ 2; i >= 0; --i) {
        AdjustDown(arr, k, i);  // 对前k个进行建小堆
    }
    // 2. 用剩余N-K个与堆顶最小元素依次进行比较
    for(int i = k; i < n; ++i) {
        if(arr[i] > arr[0]) {
            std::swap(arr[i], arr[0]);
            AdjustDown(arr, k, 0);
        }
    }
}

// old
void Print_Heap_Topk(int* a, int n, int k)
{
	int* KMaxHeap = new int[k];   // 最大堆存最小的K个数
	for (int i = 0; i < k; ++i)
	{
		KMaxHeap[i] = a[i];
	}
	for (int i = (k - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(KMaxHeap, k, i);
	}
	for (int i = k; i < n; ++i)
	{
		if (a[i] > KMaxHeap[0])
			KMaxHeap[0] = a[i];
		AdjustDown(KMaxHeap, k, 0);
	}
	for (int i = 0; i < k; ++i)
	{
		cout << KMaxHeap[i] << " ";
	}
	cout << endl;
    delete []KMaxHeap;
}

void test_TopK()
{
	int n = 10000;
	int* a = new int[n];
	srand(time(0));
	for (int i = 0; i < n; ++i)
		a[i] = rand() % 1000000;
	a[5] = 1000000 + 1;
	a[1231] = 1000000 + 2;
	a[531] = 1000000 + 3;
	a[5121] = 1000000 + 4;
	a[120] = 1000000 + 5;
	a[99] = 1000000 + 6;
	a[0] = 1000000 + 7;
	a[76] = 1000000 + 8;
	a[423] = 1000000 + 9;
	a[3144] = 1000000 + 10;
	a[333] = -100;
	a[999] = -200;
	a[777] = -500;
	a[888] = -800;
	a[111] = -1000;
	a[798] = -1;
	a[1111] = -250;
	a[2222] = -350;
	a[3333] = -450;
	a[4444] = -550;
//	Print_Heap_Topk(a, n, 10);
    TopK(a, n, 10);
    for(int i = 0; i < 10; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void test_sort() {
	int arr[] = { 32,43,45,65,41,33,36,38,40,30,22,24,27,15,7,3 };
	for (int i = 0; i < 16; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	HeapSort(arr, 16);
	for (int i = 0; i < 16; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main()
{
//    testHeap1();
//    test_sort();
    test_TopK();
	return 0;
}
