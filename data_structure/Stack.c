#define _CRT_SECURE_NO_WARNINGS 1

#include"Stack.h"

void StackInit(Stack* p)
{
	p->ptr = (Stack*)malloc(sizeof(StackDataType) * DefaultSize);
	p->top = -1;
	p->capacity = DefaultSize;
}

void StackDestroy(Stack* p)
{
	assert(p);
	free(p->ptr);
	p->ptr = NULL;
	p->top = -1;
	p->capacity = 0;
	printf("栈内存销毁成功\n");
}

void StackCheckCapacity(Stack* p)
{
	assert(p);
	if (p->top + 1 == p->capacity)
	{
		StackDataType* tmp = (StackDataType*)realloc(p->ptr, sizeof(StackDataType) * (p->capacity + IncreaseSize));
		if (!tmp)
		{
			exit("CheckCapacity::calloc");
		}
		else
		{
			p->ptr = tmp;
		}
		p->capacity = p->capacity + IncreaseSize;
		printf("增容成功\n");
	}
}

void StackPush(Stack* p, StackDataType x)
{
	assert(p);
	StackCheckCapacity(p);  //p是一个结构体指针，传过去，check函数里也是一个结构体指针，
	p->ptr[++(p->top)] = x;
}

void StackPop(Stack* p)
{
	assert(p && p->top != -1);
	p->top--;
}

StackDataType StackTop(Stack* p)
{
	assert(p && p->top != -1);
	return p->ptr[p->top];
}

int StackEmpty(Stack* p)
{
	assert(p);
	if (p->top != -1)
		return 1;
	else
		return 0;
}

int StackSize(Stack* p)
{
	assert(p);
	return p->top + 1;
}