#define _CRT_SECURE_NO_WARNINGS 1

#include"SList.h"

void SList::push_back(const DataType& x)
{
	Node* newnode = CreatNode(x);
	if (head == nullptr)
	{
		head = newnode;
		return;
	}
	Node* cur = head;
	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
	cur->next = newnode;
}

void SList::push_front(const DataType& x)
{
	Node* newnode = CreatNode(x);
	newnode->next = head;
	head = newnode;
}

void SList::pop_back()
{
	assert(head);
	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		Node* cur = head;
		while (cur->next->next != nullptr)
		{
			cur = cur->next;
		}
		delete cur->next;
		cur->next = nullptr;
	}
}

void SList::pop_front()
{
	Node* tmp = head;
	head = head->next;
	delete tmp;
}

void SList::print()const
{
	if (head == nullptr)
		cout << "null" << endl;
	else
	{
		Node* cur = head;
		while (cur != nullptr)
		{
			cout << cur->data << " -> ";
			cur = cur->next;
		}
		cout << "null" << endl;
	}
}

Node* SList::find(const DataType& x)   // 以某值为索引，查找某节点
{
	assert(head);
	Node* cur = head;
	while (cur != nullptr)
	{
		if (cur->data == x)
			return cur;
		cur = cur->next;
	}
	return nullptr;
}

void SList::insert(Node* p, const DataType& x)
{
	Node* newnode = CreatNode(x);
	assert(p);
	newnode->next = p->next;
	p->next = newnode;
}

void SList::erase(Node* p)
{
	assert(p);
	if (head == p)
	{
		Node* tmp = head->next;
		delete head;
		head = tmp;
	}
    else
    {
		Node* cur = head;
		while (cur->next != p)
		{
			cur = cur->next;
		}
		cur->next = cur->next->next;
		delete p;
	}
}



void testSList()
{
	SList sl1;
	sl1.push_back(1);
	sl1.push_back(2);
	sl1.push_back(3);
	sl1.push_back(4);
	sl1.push_back(5);
	sl1.push_front(6);
	sl1.push_front(7);
	sl1.push_front(8);
	sl1.print();
	sl1.pop_back();
	sl1.pop_front();
	sl1.print();
	sl1.insert(sl1.find(6), 66);
	sl1.print();
	sl1.erase(sl1.find(6));
	sl1.print();
	SList sl2(sl1);
	sl2.push_back(88);
	sl2.print();
	sl1.print();
	sl1 = sl2;
	sl1.print();
}

//
//int main()
//{
//	testSList();
//	return 0;
//}