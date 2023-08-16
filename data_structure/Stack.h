#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
// ʵ�ֿ��Զ�̬������ջ���Ƚ����
#define DefaultSize 3
#define IncreaseSize 2
typedef int StackDataType;

typedef struct Stack
{
	StackDataType* ptr;
	int top;      // ָ��ջ��Ԫ�ص��±�
	int capacity;
}Stack;

// ��ʼ��ջ
void StackInit(Stack* ptr);
//���ջ�Ƿ���
void StackCheckCapacity(Stack* ptr);
// ��ջ
void StackPush(Stack* ptr, StackDataType x);
// ��ջ
void StackPop(Stack* ptr);
// ��ȡջ��Ԫ��
StackDataType StackTop(Stack* ptr);
// ջ����ЧԪ�ظ���
int StackSize(Stack* ptr);
// ���ջ�Ƿ�Ϊ��
int StackEmpty(Stack* ptr);
// ����ջ
void StackDestroy(Stack* ptr);