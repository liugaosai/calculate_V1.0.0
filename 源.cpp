#include "stdio.h"
#include "stdlib.h"
#define MAX_SIZE 1000
char element_arr[MAX_SIZE*2];
char oper_lib[MAX_SIZE - 1];
char num_stack[MAX_SIZE];
int element_index = 0, oper_index = 0, num_stack_index=0;
int Push_Element_Arr(char ele)
{
	element_arr[element_index] = ele;
	element_index++;
	return 0;
}
int Push_Oper(char oper)
{
	oper_lib[oper_index] = oper;
	oper_index++;
	return 0;
}
int Push_Num_Stack(int Num)
{
	num_stack[num_stack_index] = Num;
	num_stack_index++;
	return 0;
}
int Pop_Num_Stack()
{
	char tmp;
	num_stack_index--;
	tmp = num_stack[num_stack_index];
	num_stack[num_stack_index] = 0;
	return tmp;
}
char Pop_Oper()
{
	char tmp;
	oper_index--;
	tmp = oper_lib[oper_index];
	oper_lib[oper_index] = '\0';
	return tmp;
}
int youxianji(char a, char b)
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
int Infix_To_Suffix(char str[MAX_SIZE * 2])
{
	int i = 0, temp_i = 0, tmp_num = 0, t,kuohao_flag=0,num_flag=0,tmp_ele_index;
	char temp[10] = " ", tmp_oper = 0;
	while (str[i] != '\0')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			temp[temp_i] = str[i];
			temp_i++;
			i++;
			num_flag = 1;
		}
		if (num_flag == 1)
		{
			Push_Element_Arr(atoi(temp));
			num_flag = 0;
		}

		for (; temp_i > 0; temp_i--)
			temp[temp_i] = 0;


		if (str[i] != '\0')
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
	while (oper_lib[0] != '\0')
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
int Calc_Result()
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
	char str[MAX_SIZE * 2];
	printf("please input a mathematical expression:\n");
	scanf_s("%s", str, sizeof(str));
	printf("***************中缀输出******************\n");
	printf("%s\n", str);
	printf("*****************end*********************\n");
	Infix_To_Suffix(str);
	printf("结果是：%d", Calc_Result());
	return 0;
}