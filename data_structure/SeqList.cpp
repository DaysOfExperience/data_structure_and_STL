#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

typedef int DataType;

class SeqList
{
	friend ostream& operator<<(ostream&, const SeqList&);
private:
    DataType* pdata;
    int size;
    int capacity;
    void CheckCapacity();
    void free()
    {
        delete[] pdata;
        size = capacity = 0;
    }
public:
	// 默认构造函数
	SeqList() :pdata(new DataType[1]), size(0), capacity(1) {}
	// 构造函数：用于另一个数组的拷贝初始化
	SeqList(DataType* p, int size) :pdata(new DataType[size]), size(size), capacity(size)
	{
        // 有问题
		copy(p, p + size, pdata);
		//for (size_t i = 0; i != size; ++i)
		//	pData[i] = p[i];
	}
	SeqList(initializer_list<DataType> ls)
	{
		auto sz = ls.end() - ls.begin();
		pdata = new DataType[sz];
		size_t index = 0;
		for (auto i = ls.begin(); i != ls.end(); ++i)
			pdata[index++] = *i;
		size = capacity = sz;
	}
	// 拷贝构造函数
	SeqList(const SeqList& sl)
	{
		size_t sz = sl.Size();
		pdata = new DataType[sz];
		copy(sl.pdata, sl.pdata + sz, pdata);  // 有问题
		//for (size_t i = 0; i != sz; ++i)
		//	pdata[i] = sl.pdata[i];
		size = capacity = sz;
	}
	SeqList& operator= (const SeqList& sl)
	{
		auto sz = sl.Size();
		DataType* newdata = new DataType[sz];
		for (size_t i = 0; i != sz; ++i)
			newdata[i] = sl.pdata[i];
		free();             // 关键~
		pdata = newdata;
		size = capacity = sz;
		return *this;
	}
	~SeqList()
	{
		free();
	}
public:
	void print()const;
	void push_back(const DataType& data);
	void pop_back();
	void push_front(const DataType& data);
	void pop_front();
	void insert(int pos, const DataType&);
	int find(const DataType&)const;
	void erase(int pos);
	void sort();
	void clean();
	bool empty()const { return size == 0; }
	size_t Size()const { return size; }
	size_t Capacity()const { return capacity; }
	DataType& operator[](int index) { assert(index >= 0 && index <= size - 1); return pdata[index]; }
	const DataType& operator[](int index)const { assert(index >= 0 && index <= size - 1); return pdata[index]; }
	DataType& Front() { assert(size > 0); return pdata[0]; }
	const DataType& Front()const { assert(size > 0); return pdata[0]; }
	DataType& Back() { assert(size > 0); return pdata[size - 1]; }
	const DataType& Back()const { assert(size > 0); return pdata[size - 1]; }
};

inline void SeqList::clean()  // 清空顺序表
{
	size = 0;
}

inline void SeqList::CheckCapacity()
{
	if (size == capacity)
	{
		DataType* newdata = new DataType[size ? size * 2 : 1];
		copy(pdata, pdata + size, newdata);      // 有问题
		delete[] pdata;
		pdata = newdata;
		capacity = size ? size * 2 : 1;
		cout << "增容成功" << endl;
	}
}

inline void SeqList::print()const
{
	if (size > 0)
	{
		for (size_t i = 0; i != size; ++i)
		{
			cout << pdata[i] << " ";
		}
		cout << endl;
	}
	else
		cout << "顺序表为空" << endl;
}

inline void SeqList::push_back(const DataType& data)
{
	CheckCapacity();
	pdata[size] = data;
	size++;
}

inline void SeqList::push_front(const DataType& data)
{
	CheckCapacity();
	for (int i = size - 1; i >= 0; --i)
	{
		pdata[i + 1] = pdata[i];
	}
	pdata[0] = data;
	++size;
}

inline void SeqList::pop_back()
{
	assert(size >= 1);
	--size;
}

inline void SeqList::pop_front()
{
	assert(size >= 1);
	for (int i = 0; i < size - 1; ++i)
		pdata[i] = pdata[i + 1];
	--size;
}

inline void SeqList::insert(int index, const DataType& data)
{
	assert(index >= 0 && index <= size);
	CheckCapacity();
	for (int i = size - 1; i >= index; --i)
		pdata[i + 1] = pdata[i];
	pdata[index] = data;
	++size;
}

// 小丑
int SeqList::find(const DataType& data)const
{
	assert(size > 0);
	for (size_t i = 0; i != size; i++)
	{
		if (pdata[i] == data)
			return i;
	}
	return -1;
}


void SeqList::erase(int pos)
{
	assert(size && pos >= 0 && pos <= size - 1);
	for (int i = pos; i < size - 1; ++i)
		pdata[i] = pdata[i + 1];
	--size;
}

void SeqList::sort()
{
	for (int i = 0; i < size - 1; ++i)
	{
		int flag = 0;
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (pdata[j] > pdata[j + 1])
			{
				flag = 1;
				DataType tmp = pdata[j];
				pdata[j] = pdata[j + 1];
				pdata[j + 1] = tmp;
			}
		}
		if (!flag)
			break;
	}
}

ostream& operator<<(ostream& os, const SeqList& sl)
{
	for (size_t i = 0; i != sl.size; ++i)
		os << sl.pdata[i] << " ";
	return os;
}

//
//int main()
//{
//	SeqList s;
//	s.push_back(1);
//	s.push_back(2);
//	s.push_back(3);
//	s.push_back(4);
//	s.push_back(5);
//	s.print();
//	s.pop_front();
//	s.pop_back();
//	cout << s[1];
//	s.print();
//	s.push_front(6);
//	s.push_front(7);
//	s.sort();
//	s.print();
//	s.erase(s.find(6));
//	s.print();
//
//	SeqList s2(s);
//	s2.push_back(0);
//	s2.print();
//	s.print();
//	s = s2;
//	s.print();
//	return 0;
//}
//
