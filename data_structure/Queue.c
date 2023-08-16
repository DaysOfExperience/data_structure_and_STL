#define _CRT_SECURE_NO_WARNINGS 1

#include"Queue.h"

void QueueInit(Queue* p)
{
	assert(p);
	p->front = 0;
	p->rear = 0;
}

void QueuePush(Queue* p, QueueDataType x)
{
	assert(p);
	if ((p->rear + 1) % MAX_SIZE == p->front)
	{
		exit("QueuePush::队列已满");
	}
	p->a[p->rear] = x;
	p->rear = (p->rear + 1) % MAX_SIZE;
}

void QueuePop(Queue* p)
{
	assert(p && p->front != p->rear);
	p->front = (p->front + 1) % MAX_SIZE;
}

int QueueSize(const Queue* p)
{
    // 注意，此时rear的下标处为空的。
	int tmp = p->front;
	int num = 0;
	while (tmp != p->rear)
	{
		tmp = (tmp + 1) % MAX_SIZE;
		num++;
	}
	return num;
}

QueueDataType QueueBack(const Queue* p)
{
	assert(p && p->front != p->rear);
    // 分情况
	return p->rear == 0 ? p->a[MAX_SIZE - 1] : p->a[p->rear - 1];
}

QueueDataType QueueFront(const Queue* p)
{
	assert(p && p->front != p->rear);
	return p->a[p->front];
}

bool QueueEmpty(const Queue* p)
{
	return p->front == p->rear ? true : false;
}

