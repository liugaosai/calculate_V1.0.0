#include "stdio.h"
#include "stdlib.h"
#define MAX_SIZE 1000
char element_arr[MAX_SIZE];
char oper_lib[MAX_SIZE - 1];
int element_index = 0, oper_index = 0;
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
int Separate_Num_Storage(char str[MAX_SIZE * 2])
{
	int i = 0, temp_i = 0, tmp_num = 0, t,kuohao_flag=0,num_flag=0;
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

	printf("t:\t");
	for (--element_index; element_index >= 0; element_index--)
	{
		if(element_arr[element_index]=='+'|| element_arr[element_index] == '-'|| element_arr[element_index] == '*'|| element_arr[element_index] == '/')
			printf("%c", element_arr[element_index]);
		else
			printf("%d", element_arr[element_index]);
	}
	printf("\n");
	

	return 0;
}
int Calc_Result()
{
	int L_Val = 0, R_Val = 0, res = 0, num_i = 0, oper_i = 0;
	int tmp_num[MAX_SIZE], tmp_oper[MAX_SIZE];



	while (oper_index != 0)
	{
		/*	tmp_num[num_i] = num_lib[i];
			tmp_oper[oper_i] = Pop_Oper();
			if()*/
	}

	return 0;
}
int main()
{
	int i;
	char str[MAX_SIZE * 2];
	printf("please input a mathematical expression:\n");
	scanf_s("%s", str, sizeof(str));
	printf("*********************************\n");
	printf("%s\n", str);
	Separate_Num_Storage(str);
	/*for (i = 0; i < 10; i++)
		printf("%d\t", num_lib[i]);*/
	printf("½á¹ûÊÇ£º%d", Calc_Result());
	return 0;
}