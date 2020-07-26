#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define MAX_SIZE 1000
char element_arr[MAX_SIZE*2];
char oper_lib[MAX_SIZE - 1];
char num_stack[MAX_SIZE];
int element_index = 0, oper_index = 0, num_stack_index=0;
int Push_Element_Arr(char ele)                             //定义元素数组
{
	element_arr[element_index] = ele;
	element_index++;
	return 0;
}
int Push_Oper(char oper)                                   //操作符入栈函数
{
	oper_lib[oper_index] = oper;
	oper_index++;
	return 0;
}
char Pop_Oper()                                          //操作符出栈函数 
{
	char tmp;
	oper_index--;
	tmp = oper_lib[oper_index];
	oper_lib[oper_index] = '\0';
	return tmp;
}
int Push_Num_Stack(int Num)                                //数据入栈函数
{
	num_stack[num_stack_index] = Num;
	num_stack_index++;
	return 0;
}
int Pop_Num_Stack()                                       //数据出栈函数
{
	char tmp;
	num_stack_index--;
	tmp = num_stack[num_stack_index];
	num_stack[num_stack_index] = 0;
	return tmp;
}

int Detection_Input_Val(char str[MAX_SIZE * 2]) //返回1表示有无效数据，0为有效
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')                       
		{
			;
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '\\')
		{
			if (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' || str[i + 1] == '\\' || str[i + 1] == '\0'||i==0) //表达式开头为运算符或连续出现两个运算符则退出报错
				return 1;
		}
		else if (str[i] >= 'a' && str[i] <= 'z')                      //在此处可以加入合法运算符
		{
			switch (str[i])
			{
			case 's':                                                //判断是否是sin函数
				if (str[i + 1] == 'i' && str[i + 2] == 'n')
					i = i + 2;
				else
					return 1;
				break;
			case 'c':                                                 //判断是否是cos函数
				if (str[i + 1] == 'o' && str[i + 2] == 's')
					i = i + 2;
				else
					return 1;
				break;
			case 't':                                                  //判断是否为tan函数
				if (str[i + 1] == 'a' && str[i + 2] == 'n')
					i = i + 2;
				else
					return 1;
				break;
			default:
				break;
			}
		}
		else
			return 1;
	}
	return 0;
}
int youxianji(char a, char b)                                          //判断运算符优先级返回1表示a的优先级高返回0表示同级或低级
{
	if (a == '+' || a == '-')
		return 0;
	else
	{
		if (b == '+' || b == '-')
			return 1;
		else
			return 0;
	}
}
int Infix_To_Suffix(char str[MAX_SIZE * 2])                        //将中缀表达式转化为后缀表达式
{
	int i = 0, temp_i = 0, tmp_num = 0, t,kuohao_flag=0,num_flag=0,tmp_ele_index;
	char temp[10] = " ", tmp_oper = 0;
	while (str[i] != '\0')
	{
		while (str[i] >= '0' && str[i] <= '9')                      //将数据字符和操作符分离开，提取连续的数字字符重组
		{
			temp[temp_i] = str[i];
			temp_i++;
			i++;
			num_flag = 1;
		}
		if (num_flag == 1)
		{
			Push_Element_Arr(atoi(temp));                          //将数字字符串转化为数字
			num_flag = 0;
		}

		for (; temp_i > 0; temp_i--)                               //清空临时数组
			temp[temp_i] = 0;


		if (str[i] != '\0')                                        //实现中缀表达式到后缀表达式
		{
			if(oper_lib[0]=='\0'&& str[i] != '(')
				Push_Oper(str[i]);
			else
			{
				if (str[i] == '(')
				{
					Push_Oper(str[i]);
					kuohao_flag++;
				}
				else if (str[i] == ')')
				{
					while (oper_lib[oper_index-1] != '(')
						Push_Element_Arr(Pop_Oper());
					Pop_Oper();
					kuohao_flag--;
				}
				else if (kuohao_flag != 0)
				{
					if (oper_lib[oper_index - 1] == '(')
						Push_Oper(str[i]);
					else 
					{
						while (!youxianji(str[i], oper_lib[oper_index - 1]) && oper_lib[oper_index - 1] != '(')
							Push_Element_Arr(Pop_Oper());
						Push_Oper(str[i]);
					}
				}
				else
				{
					while (!youxianji(str[i], oper_lib[oper_index - 1]) && oper_lib[0] != '\0')
						Push_Element_Arr(Pop_Oper());
					Push_Oper(str[i]);
				}
				
			}
			i++;
		}

	}
	while (oper_lib[0] != '\0')                                  //操作符全部出栈
		Push_Element_Arr(Pop_Oper());

	printf("***************后缀输出******************\n");
	for (tmp_ele_index=0; tmp_ele_index < element_index; tmp_ele_index++)
	{
		if(element_arr[tmp_ele_index]=='+'|| element_arr[tmp_ele_index] == '-'|| element_arr[tmp_ele_index] == '*'|| element_arr[tmp_ele_index] == '/')
			printf("%c", element_arr[tmp_ele_index]);
		else
			printf("%d", element_arr[tmp_ele_index]);
	}
	printf("\n*****************end*********************\n");
	

	return 0;
}
int Calc_Result()                                               //将后缀表达式进行计算，并返回计算结果
{
	int i=0,L_Val=0, R_Val = 0;
	printf("数组中总元素数:%d\n", element_index);
	for (; element_index > 0; element_index--)
	{
		if (element_arr[i] == '+' || element_arr[i] == '-' || element_arr[i] == '*' || element_arr[i] == '/')
		{
			R_Val = Pop_Num_Stack();
			L_Val = Pop_Num_Stack();
			switch (element_arr[i])
			{
			case '+':
				Push_Num_Stack(L_Val + R_Val);
				break;
			case '-':
				Push_Num_Stack(L_Val - R_Val);
				break;
			case '*':
				Push_Num_Stack(L_Val * R_Val);
				break;
			case '/':
				Push_Num_Stack(L_Val / R_Val);
				break;
			default:
				break;
			}
		}
		else
		{
			Push_Num_Stack(element_arr[i]);
		}
		i++;
	}
	return Pop_Num_Stack();
}
int main()
{
	int i;
	char str[MAX_SIZE * 2];                                      //由于存储输入的数学表达式
	printf("please input a mathematical expression:\n");
	scanf_s("%s", str, sizeof(str));
	if (Detection_Input_Val(str))                                //检测是否有非法字符输入
	{
		printf("存在非法输入程序终止................\n");
		return 0;
	}
	printf("***************中缀输出******************\n");
	printf("%s\n", str);
	printf("*****************end*********************\n");
	Infix_To_Suffix(str);
	printf("结果是：%d", Calc_Result());
	return 0;
}