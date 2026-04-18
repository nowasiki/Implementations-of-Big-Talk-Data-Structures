#include <stdio.h>

// 栈最大容量
#define MAXSIZE 1000
// 状态码：成功
#define OK 1
// 状态码：失败
#define ERROR 0

// 状态类型别名，用于函数返回值
typedef int Status;

// 静态数组实现的栈结构
typedef struct
{
	// 存储栈元素的数组
	int data[MAXSIZE];
	// 栈顶指针，-1 表示空栈
	int top;
}Stack;

// 初始化栈
Status InitStack(Stack* S)
{
	// 栈顶置为 -1，表示空栈
	S->top = -1;
	return OK;
}

// 入栈操作：将元素 e 压入栈 S
Status Push(Stack* S, int e)
{
	// 栈满，无法入栈
	if (S->top == MAXSIZE - 1) return ERROR;
	// 栈顶上移，存入元素
	S->data[++(S->top)] = e;
	return OK;
}

// 出栈操作：将栈顶元素弹出到 e 中
Status Pop(Stack* S, int* e)
{
	// 栈空，无法出栈
	if (S->top == -1) return ERROR;
	// 取出栈顶元素
	*e = S->data[S->top];
	// 栈顶下移
	S->top--;
	return OK;
}

// 根据运算符 c 对 e1 和 e2 进行计算
// 注意：e1 是先出栈的数，e2 是后出栈的数（运算顺序重要）
int Calculate(char c, int e1, int e2)
{
	if (c == '+')
		return e1 + e2;
	else if (c == '-')
		return e1 - e2;
	else if (c == '*')
		return e1 * e2;
	else if (c == '/')
		return e1 / e2;
	else
		return -1;
}

// 后缀表达式（逆波兰表达式）求值核心函数
Status EvalPostfix(char* arr)
{
	Stack S;
	// 初始化栈
	InitStack(&S);
	int i = 0;
	// 用于拼接多位数（如 10、123）
	int num = 0;
	
	// 遍历整个表达式字符串
	while (arr[i] != '\0')
	{
		// 如果是数字，拼接成完整数值
		if (arr[i] >= '0' && arr[i] <= '9')
		{
			num = 10 * num + arr[i] - '0';
		}
		// 如果是空格，表示一个数字结束
		else if (arr[i] == ' ')
		{
			if (num != 0)
			{
				// 将拼接好的数字入栈
				Push(&S, num);
				num = 0;
			}
		}
		// 如果是运算符
		else
		{
			if (num != 0)
			{
				// 先把前面的数字入栈
				Push(&S, num);
				num = 0;
			}
			
			// 识别四则运算符
			if (arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/')
			{
				int e2, e1;
				// 注意顺序：先弹出的是右操作数
				Pop(&S, &e2);
				// 后弹出的是左操作数
				Pop(&S, &e1);
				// 计算
				int ret = Calculate(arr[i], e1, e2);
				// 结果入栈
				Push(&S, ret);
			}
		}
		i++;
	}
	
	// 处理表达式最后一个数字
	if (num != 0) Push(&S, num);
	
	// 最终栈中只剩一个元素：计算结果
	int result;
	Pop(&S, &result);
	return result;
}

// 测试主函数
int main()
{
	// 后缀表达式示例：9 3 1 - 3 * + 10 2 / +
	// 对应中缀：9 + (3-1)*3 + 10/2 = 20
	char arr[100] = "9 3 1 - 3 * + 10 2 / +";
	
	printf("计算结果：%d\n", EvalPostfix(arr));
	return 0;
}
