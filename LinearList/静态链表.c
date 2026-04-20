#include <stdio.h>

#define MAXSIZE 1000
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef char ElemType;
typedef int Status;

typedef struct
{
	ElemType data;
	int cur; // 为0时代表无指向
}Component, StaticLinkList[MAXSIZE];
// 等同于typedef Component StaticLinkList[MAXSIZE]

Status visit(ElemType c)
{
	printf("%c ", c);
	return OK;
}


// 将一维数组space中各分量链成一个备用链表，space[0].cur为头指针，"0"表示空指针
Status InitList(StaticLinkList space)
{
	int i;
	for(i = 0; i < MAXSIZE-1; i++)
	{
		space[i].cur = i + 1;
	}
	space[MAXSIZE - 1].cur = 0;
	return OK;
}

// 获得一个空闲的节点的下标，否则返回0
int Malloc_SSL(StaticLinkList space)
{
	int i = space[0].cur;
	if (i)
	{
		space[0].cur = space[i].cur;
	}
	return i;
}

// 将下标为k的空闲节点回收到备用链表
Status Free_SSL(StaticLinkList space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;	
	return OK;
}

// 返回L中的元素个数
int ListLength(StaticLinkList L){
	int i = L[MAXSIZE - 1].cur;
	int k = 0;
	while(i)
	{
		k++;
		i = L[i].cur;
	}
	return k;
}

// 输出所有的元素
Status ListTraverse(StaticLinkList L)
{
	int i = L[MAXSIZE - 1].cur;
	int j = 0;
	while(i)
	{
		visit(L[i].data);
		j++;
		i = L[i].cur;
	}
	//printf("NumOfTheElement:%d\n", j);
	return OK;
}

// 在L中第i个元素之前插入新的数据元素e
// 找到第i个元素（从哨兵位置开始）
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
	int k, j, l;
	k = MAXSIZE - 1;
	if (i < 1 || i > ListLength(L) + 1)
	{
		return ERROR;
	}
	j = Malloc_SSL(L);
	if (j)
	{
		L[j].data = e;
		for(l = 1; l <= i - 1; l++)
		{
			k = L[k].cur;
		}
		L[j].cur = L[k].cur;
		L[k].cur = j;
		return OK;
	}
	return ERROR;
}


// 删除L中第i个数据元素
Status ListDelete(StaticLinkList L, int i)
{
	int k = MAXSIZE - 1, j;
	if (i < 1 || i > ListLength(L))
	{
		return ERROR;
	}
	for(j = 1; j < i; j++)
	{
		k = L[k].cur;
	}
	j = L[k].cur;
	L[k].cur = L[j].cur;
	Free_SSL(L, j);
	return OK;
}

int main()
{
	StaticLinkList L;
	Status i;
	i=InitList(L);
	printf("初始化L后：L.length=%d\n",ListLength(L));
	
	i=ListInsert(L,1,'F');
	i=ListInsert(L,1,'E');
	i=ListInsert(L,1,'D');
	i=ListInsert(L,1,'B');
	i=ListInsert(L,1,'A');
	
	printf("\n在L的表头依次插入FEDBA后：\nL.data=");
	ListTraverse(L); 
	
	i=ListInsert(L,3,'C');
	printf("\n在L的“B”与“D”之间插入“C”后：\nL.data=");
	ListTraverse(L); 
	
	i=ListDelete(L,1);
	printf("\n在L的删除“A”后：\nL.data=");
	ListTraverse(L); 
	
	printf("\n");
	
	return 0;
}
