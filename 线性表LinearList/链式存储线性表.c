#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 20

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

// 定义结点
typedef struct Node
{
	ElemType data;
	struct Node* next;
} Node;

// 打印数据
Status visit(ElemType c)
{
	printf("%d ", c);
	return OK;
}

typedef struct Node* LinkList;

// 初始化链式线性表
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node));
	if (!(*L)) return ERROR;
	(*L)->next = NULL;

	return OK;
}

// 判断有头节点的链式列表是否为空
Status ListEmtpy(LinkList *L)
{
	if ((*L)->next == NULL) return TRUE;
	else return FALSE;
}

// 清空释放链式线性表（保留头节点）
Status ClearList(LinkList *L)
{
	LinkList p, q;
	p = (*L)->next;
	while (!q)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}

// 返回元素个数
int ListLength(LinkList L)
{
	LinkList p = L->next;
	int cnt = 0;
	while (p != NULL)
	{
		cnt++;
		p = p->next;
	}
	return cnt;
}

// 用e返回L中第i个数据元素的值
Status GetElem(LinkList L, int i, ElemType *e)
{

	LinkList p = L->next;
	int j = 1;
	while (p && j < i)
	{
		j++;
		p = p->next;
	}
	if (j > i || !p)
	{
		return ERROR;
	}
	*e = p->data;
	return OK;
}

// 返回第一个与e相同元素的位置
int LocateElem(LinkList L, ElemType *e)
{
	if (e == NULL)
	{
		return 0;
	}
	LinkList p = L->next;
	int k = 1;
	while (p && p->data != *e)
	{
		k++;
		p = p->next;
	}
	if (p)
	{
		return k;
	}
	return 0;
}

// 输出L中的每个元素
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;
	while(p){
		visit(p->data);
		p = p->next;
	}
	return OK;
}

// 在L中第i个位置之前插入新的数据元素e，L的长度加1（前插）
Status ListInsert(LinkList *L, int i, ElemType* e){
	if(e == NULL) return ERROR;
	LinkList p = *L;
	int j = 1;
	while (p && j < i){
		j++;
		p = p->next;
	}
	if (!p || j > i) return ERROR;
	LinkList s = (LinkList)malloc(sizeof(Node));
	if(!s) return ERROR;
	s->data = *e;
	s->next = p->next;
	p->next = s;
	return OK;
}

// 删除第i个数据元素
Status Delete(LinkList *L, int i, ElemType *e){
	LinkList p = *L, q;
	int j = 1;
	while (j < i && p->next){
		j++;
		p = p->next;
	}
	if (!(p->next) || j > i) return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

// 头插法随机创建含有n个元素的链式线性表
void CreateListHead(LinkList *L, int n){
	LinkList p;
	int i;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	for (i = 0; i < n; i++){
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100+1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

// 尾插法随机创建含有n个元素的链式线性表
void CreateListTail(LinkList *L, int n){
	LinkList p, q;
	int i;
	srand(time(0));
	*L = (LinkList)malloc(sizeof(Node));
	q = *L;
	for (i = 0; i < n; i++){
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100+1;
		p->next = NULL;
		q->next = p;
		q = p;
	}
}

int main(){
	LinkList L1;
	CreateListTail(&L1, 10);
	printf("length:%d\n", ListLength(L1));
	ListTraverse(L1);
	printf("\n");
	int e = 3;
	int ret = ListInsert(&L1, 200, &e);
	printf("%d\n", ret);
	ListTraverse(L1);
}
