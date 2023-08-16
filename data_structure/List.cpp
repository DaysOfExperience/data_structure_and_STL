#define _CRT_SECURE_NO_WARNINGS 1
#include"List.h"

Node* CreatNode(const DataType& d)
{
	Node* newnode = new Node{ d };
	return newnode;
}

List::List()   // 默认构造函数，用处初始化那个哨兵位头结点
{
	phead = CreatNode(-1);
	phead->next = phead;
	phead->prev = phead;
}

void List::push_back(const DataType& data)
{
	assert(phead);
	// 可以复用insert
	Node* newnode = CreatNode(data);
	Node* tail = phead->prev;
	tail->next = newnode;
	newnode->prev = tail;
	newnode->next = phead;
	phead->prev = newnode;
}


void List::push_front(const DataType& x)
{
	// 可以复用insert
	assert(phead);
	Node* newnode = CreatNode(x);
	Node* next = phead->next;
	next->prev = newnode;
	newnode->next = next;
	newnode->prev = phead;
	phead->next = newnode;
}

void List::pop_back()
{
	// 可以服用erase
	assert(phead);
	assert(phead->next != phead);

	Node* tail = phead->prev;
	Node* newtail = tail->prev;
	
	newtail->next = phead;
	phead->prev = newtail;
	
	delete tail;
}

void List::pop_front()
{
	// 可以复用erase
	assert(phead);
	assert(phead->next != phead);
	Node* first = phead->next;
	Node* newfirst = first->next;
	newfirst->prev = phead;
	phead->next = newfirst;

	delete first;
}

// p节点前面插入新节点
void List::insert(Node* p, const DataType& x)
{
	assert(p);
	Node* newnode = new Node(x);
	Node* prev = p->prev;
	prev->next = newnode;
	newnode->prev = prev;
	newnode->next = p;
	p->prev = newnode;
}

void List::erase(Node* p)
{
	assert(p);
	assert(p != phead);  // p不是头节点
	assert(phead->next != phead);  // 链表非空
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
}

void List::print()const
{
	assert(phead);
	Node* cur = phead->next;
	while (cur != phead)
	{
		cout << cur->data << "->";
		cur = cur->next;
	}
	cout << "NULL" << endl;
}

int List::size()const
{
	assert(phead);
	int len = 0;
	Node* p = phead->next;
	while (p != phead)
	{
		++len;
		p = p->next;
	}
	return len;
}

void testList1()
{
	List l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.print();
	l1.push_front(5);
	l1.push_front(6);
	l1.push_front(7);
	l1.push_front(8);
	l1.print();
	cout << l1.size() << endl;
	l1.pop_back();
	l1.pop_front();
	l1.print();
	cout << l1.size() << endl;
	List l2(l1);
	l2.push_front(666);
	l2.print();
	l1.print();
	l1 = l2;
	l1.print();
}

int main()
{
    testList1();
    return 0;
}