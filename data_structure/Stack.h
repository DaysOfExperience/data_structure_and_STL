#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
// 实现可以动态增长的栈：先进后出
#define DefaultSize 3
#define IncreaseSize 2
typedef int StackDataType;

typedef struct Stack
{
	StackDataType* ptr;
	int top;      // 指向栈顶元素的下标
	int capacity;
}Stack;

// 初始化栈
void StackInit(Stack* ptr);
//检查栈是否满
void StackCheckCapacity(Stack* ptr);
// 入栈
void StackPush(Stack* ptr, StackDataType x);
// 出栈
void StackPop(Stack* ptr);
// 获取栈顶元素
StackDataType StackTop(Stack* ptr);
// 栈中有效元素个数
int StackSize(Stack* ptr);
// 检查栈是否为空
int StackEmpty(Stack* ptr);
// 销毁栈
void StackDestroy(Stack* ptr);