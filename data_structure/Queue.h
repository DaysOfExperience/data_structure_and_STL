// 虽然此队列是用数组实现的，但是Pop依旧是O(1)
// 缺点是：此队列空间有上限~，若链式结构实现，则无上限
#include<stdio.h>
#include<assert.h>
#include<stdbool.h>
typedef int QueueDataType;
#define MAX_SIZE 6

typedef struct Queue
{
	QueueDataType a[MAX_SIZE];
	int front;
	int rear;
}Queue;

//初始化
void QueueInit(Queue* p);
//入队
void QueuePush(Queue* p, QueueDataType x);
//出队
void QueuePop(Queue* p);
//队尾
QueueDataType QueueBack(const Queue* p);
//队首
QueueDataType QueueFront(const Queue* p);
//有效元素个数
int QueueSize(const Queue* p);
//判空
bool QueueEmpty(const Queue* p);  //这样是为了提高效率，如果采用传Queue的话，会创建一个临时结构体对象