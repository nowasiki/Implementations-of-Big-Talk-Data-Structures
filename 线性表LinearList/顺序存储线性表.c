#include <stdio.h>

#define MAXSIZE 20

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

typedef int ElemType;
typedef int Status;

// 定义线性表
typedef struct
{
	ElemType data[MAXSIZE];
	int length;
} SqList;

// 获取第i个元素
Status GetElem(const SqList* L, int i, ElemType *e)
{
	if (L->length == 0 || i > L->length || i < 1)
	{
		return ERROR;
	}
	*e = L->data[i - 1];
	return OK;
}

// 打印某个元素
Status Visit(ElemType c)
{
	printf("%d ", c);
	return OK;
}

// 插入e到位置i中
Status ListInsert(SqList* L, int i, ElemType e)
{
	int k;
	if (MAXSIZE == L->length) return ERROR;
	if (i > L->length + 1 || i < 1) return ERROR;
	if (i != L->length + 1)
	{
		for (k = L->length; k >= i; k--)
		{
			L->data[k] = L->data[k - 1];
		}
	}
	L->data[i - 1] = e;
	L->length++;
	
	return OK;
}

// 删除第i个元素
Status ListDelete(SqList* L, int i, ElemType* e)
{
	if (L->length == 0) return ERROR;
	if (i < 1 || i > L->length) return ERROR;
	*e = L->data[i - 1];
	if (i < L->length)
	{
		for (int k = i; k < L->length; k++)
		{
			L->data[k - 1] = L->data[k];
		}
	}
	L->length--;
	
	return OK;
}

// 初始化线性表
Status InitList(SqList* L)
{
	L->length = 0;
	return OK;
}

// 线性表是否为空
Status ListEmpty(const SqList* L)
{
	if (L->length == 0) return TRUE;
	else return FALSE;
}

// 清除线性表
Status ClearList(SqList *L)
{
	L->length = 0;
	return OK;
}

// 显示线性表长度
int ListLength(const SqList L)
{
	return L.length;
}

// 打印线性表
Status ListTraverse(const SqList* L)
{
	for (int i = 0; i < L->length ; i++)
	{
		Visit(L->data[i]);
	}
	printf("\n");
	return OK;
}

// 返回第一个和e相同的元素的位序，如果未找到则返回0
int LocateList(const SqList* L, ElemType e)
{
	int i;
	if (L->length == 0) return 0;
	for (i = 0; i < L->length; i++)
	{
		if (L->data[i] == e)
		{
			return i + 1;
		}
	}
	return 0;
}

// 将仅出现在L2中的元素添加在L1的尾部
Status unionL(SqList* L1, const SqList* L2)
{
	int Len_L2 = L2->length;
	int i;
	ElemType e;
	for (i = 1; i <= Len_L2; i++)
	{
		GetElem(L2, i, &e);
		if (!LocateList(L1, e))
		{
			ListInsert(L1, L1->length + 1, e);
		}
	}
	return OK;
}

int main()
{
	SqList L;
	SqList Lb;
	
	ElemType e;
	Status i;
	int j, k;
	
	// 初始化L
	i = InitList(&L);
	printf("初始化L后：L.length=%d\n", L.length);
	
	// 在表头依次插入1～5
	for (j = 1; j <= 5; j++)
		i = ListInsert(&L, 1, j);
	printf("在L的表头依次插入1～5后：L.data=");
	ListTraverse(&L);
	printf("L.length=%d \n", L.length);
	
	// 判断是否为空
	i = ListEmpty(&L);
	printf("L是否空：i=%d(1:是 0:否)\n", i);
	
	// 清空L
	i = ClearList(&L);
	printf("清空L后：L.length=%d\n", L.length);
	i = ListEmpty(&L);
	printf("L是否空：i=%d(1:是 0:否)\n", i);
	
	// 在表尾依次插入1～10
	for (j = 1; j <= 10; j++)
		ListInsert(&L, j, j);
	printf("在L的表尾依次插入1～10后：L.data=");
	ListTraverse(&L);
	printf("L.length=%d \n", L.length);
	
	// 在表头插入0
	ListInsert(&L, 1, 0);
	printf("在L的表头插入0后：L.data=");
	ListTraverse(&L);
	printf("L.length=%d \n", L.length);
	
	// 获取第5个元素
	GetElem(&L, 5, &e);
	printf("第5个元素的值为：%d\n", e);
	
	// 查找元素3和4的位置
	for (j = 3; j <= 4; j++)
	{
		k = LocateList(&L, j);
		if (k)
			printf("第%d个元素的值为%d\n", k, j);
		else
			printf("没有值为%d的元素\n", j);
	}
	
	// 测试删除（边界情况）
	k = ListLength(L);
	for (j = k + 1; j >= k; j--)
	{
		i = ListDelete(&L, j, &e);
		if (i == ERROR)
			printf("删除第%d个数据失败\n", j);
		else
			printf("删除第%d个的元素值为：%d\n", j, e);
	}
	printf("依次输出L的元素：");
	ListTraverse(&L);
	
	// 删除第5个元素
	j = 5;
	ListDelete(&L, j, &e);
	printf("删除第%d个的元素值为：%d\n", j, e);
	printf("依次输出L的元素：");
	ListTraverse(&L);
	
	// 构造Lb（有10个数：15,14,13,...,6）
	i = InitList(&Lb);
	for (j = 6; j <= 15; j++)
		i = ListInsert(&Lb, 1, j);
	
	// 合并L和Lb
	unionL(&L, &Lb);
	printf("依次输出合并了Lb的L的元素：");
	ListTraverse(&L);
	
	return 0;
}
