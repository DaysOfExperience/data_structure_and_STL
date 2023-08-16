#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
using namespace std;

typedef int DataType;

struct Node
{
	DataType data;
	struct Node* next;
};

class SList
{
private:
    Node* head;
public:
	SList() :head(nullptr) {}
	SList(const SList& sl) { head = copySList(sl); }
	SList& operator=(const SList& sl)
	{
		Node* p = copySList(sl);
		free();
		head = p;
		return *this;
	}
	~SList() { free(); }
public:
	void push_back(const DataType&);    // ON
	void push_front(const DataType&);
	void pop_back();
	void pop_front();
	void print()const;
	Node* find(const DataType&);   // 以某值为索引，查找某节点
	void insert(Node* p, const DataType&);  // 在p结点之后插入一个值
	void erase(Node* p);   // 删除p结点
private:
	void free()
	{
		while (head != nullptr)
		{
			Node* next = head->next;
			delete head;
			head = next;
		}
		head = nullptr;
	}
	Node* copySList(const SList& sl)
	{
		//SList newsl;
		//Node* cur = sl.head;
		//while (cur != NULL)
		//{
		//	newsl.push_back(cur->data);
		//	cur = cur->next;
		//}
		//return newsl.head;
		Node ret{ 0,NULL };
		Node* node = &ret;
		Node* cur = sl.head;
		while (cur != NULL)
		{
			Node* tmp = new Node{ cur->data,NULL };
			node->next = tmp;
			node = node->next;
			cur = cur->next;
		}
		return ret.next;
	}
	Node* CreatNode(const DataType& x)
	{
		Node* newnode = new Node{ x, nullptr };
		//newnode->data = x;
		//newnode->next = nullptr;
		return newnode;
	}
};