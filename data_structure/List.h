#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
#include<stdlib.h>
#include<stack>
using namespace std;

typedef int DataType;

struct Node
{
public:
	Node(const DataType& d = DataType()) :data(d), next(nullptr), prev(nullptr) {}
	~Node() = default;
public:
	DataType data;
	struct Node* next;
	struct Node* prev;
};

class List
{
    Node* phead;  // 哨兵位
public:
	List();  // 默认构造函数
	List(const List& ls)  // 拷贝构造函数
	{
		phead = copyList(ls);
	}
	List& operator=(const List& ls)  // 拷贝赋值运算符
	{
		Node* newhead = copyList(ls);
		destroy();
		phead = newhead;
		return *this;
	}
	~List() { destroy(); }
public:
	void push_back(const DataType&);
	void push_front(const DataType&);
	void pop_back();
	void pop_front();
	void insert(Node*, const DataType&);  // 在指针指向元素之前插入一个新元素
	void erase(Node*);
	void print()const;
	bool empty()const { assert(phead); return phead->next == phead; }
	int size()const;
private:
	Node* copyList(const List& ls)
	{
		Node* cur = ls.phead->next;
		Node* newhead = new Node(-1);
		newhead->next = newhead;
		newhead->prev = newhead;
		while (cur != ls.phead)
		{
			Node* newnode = new Node(cur->data);
			// 进行尾插
			//Node* tail = newhead->prev;
			//tail->next = newnode;
			//newnode->next = newhead;
			//newhead->prev = newnode;
			//newnode->prev = tail;
			newhead->prev->next = newnode;
			newnode->prev = newhead->prev;
			newnode->next = newhead;
			newhead->prev = newnode;

			cur = cur->next;
		}
		return newhead;
	}
	void destroy()
	{
		Node* cur = phead->next;
		while (cur != phead)
		{
			Node* next = cur->next;
			delete cur;
			cur = next;
		}
		delete phead;
		phead = nullptr;
	}
};