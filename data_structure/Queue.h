// ��Ȼ�˶�����������ʵ�ֵģ�����Pop������O(1)
// ȱ���ǣ��˶��пռ�������~������ʽ�ṹʵ�֣���������
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

//��ʼ��
void QueueInit(Queue* p);
//���
void QueuePush(Queue* p, QueueDataType x);
//����
void QueuePop(Queue* p);
//��β
QueueDataType QueueBack(const Queue* p);
//����
QueueDataType QueueFront(const Queue* p);
//��ЧԪ�ظ���
int QueueSize(const Queue* p);
//�п�
bool QueueEmpty(const Queue* p);  //������Ϊ�����Ч�ʣ�������ô�Queue�Ļ����ᴴ��һ����ʱ�ṹ�����