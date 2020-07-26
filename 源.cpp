#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define MAX_SIZE 1000
#define PI 3.14159265
float element_arr[MAX_SIZE*2];                             //定义存入元素数组为浮点型
char oper_lib[MAX_SIZE - 1];
float num_stack[MAX_SIZE];
int element_index = 0, oper_index = 0, num_stack_index=0;
int Push_Element_Arr(float ele)                             //定义元素数组
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
int Push_Num_Stack(float Num)                                //数据入栈函数
{
	num_stack[num_stack_index] = Num;
	num_stack_index++;
	return 0;
}
float Pop_Num_Stack()                                       //数据出栈函数
{
	float tmp;
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
		else if (str[i] == '.')
		{
			if ((str[i + 1] >= '0' && str[i + 1] <= '9') && (str[i - 1] >= '0' && str[i - 1] <= '9'))    //检测小数点前后是否有数字，无的话报错退出
			{

			}
			else 
				return 1;
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
	int special_function_flag = 0;                                //用来标志当前是否在计算特殊输入的函数，0无，1有
	int sin_flag = 0, cos_flag = 0, tan_flag = 0;                 //标志当前是哪一类三角函数，加入其它特殊函数，直接添加即可
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')                          //判断是哪一种三角函数，还可以加入任何其它函数，比如开方等
		{
			special_function_flag = 1;                               //此为特殊函数，将标志置1
			switch (str[i])
			{
			case 's':                                                //判断是否是sin函数
				if (str[i + 1] == 'i' && str[i + 2] == 'n')
				{
					i = i + 3;                                       //索引i的大小根据函数名所用的字符数决定
					sin_flag = 1;
				}
				break;
			case 'c':                                                //判断是否是cos函数
				if (str[i + 1] == 'o' && str[i + 2] == 's')
				{
					i = i + 3;
					cos_flag = 1;
				}
				break;
			case 't':                                                //判断是否为tan函数
				if (str[i + 1] == 'a' && str[i + 2] == 'n')
				{
					i = i + 3;
					tan_flag = 1;
				}
				break;
			default:
				printf("尚未定义此函数\n");
				break;
			}
		}
		while ((str[i] >= '0' && str[i] <= '9')||str[i]=='.')                     //将数据字符和操作符分离开，提取连续的数字字符重组
		{
			temp[temp_i] = str[i];
			temp_i++;
			i++;
			num_flag = 1;
		}
		if (special_function_flag)                                  //如果是特殊函数进行特殊函数求解,并将计算结果压入元素栈
		{
			if (sin_flag)
			{
				Push_Element_Arr(sin(atof(temp) * PI / 180));                  //计算sin值将其结果压入元素栈
				sin_flag = 0;
			}
			else if (cos_flag)
			{
				Push_Element_Arr((cos(atof(temp) * PI / 180)));
				cos_flag = 0;
			}
			else if (tan_flag)
			{
				Push_Element_Arr((tan(atof(temp) * PI / 180)));
				tan_flag = 0;
			}
			special_function_flag = 0;
		}
		else if (num_flag == 1)
		{
			Push_Element_Arr(atof(temp));                          //将数字字符串转化为数字
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
					while (!youxianji(str[i], oper_lib[oper_index - 1]) && oper_lib[0] != '\0')           //括号中剩余操作符全部出栈
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
			printf("%c", (char)element_arr[tmp_ele_index]);
		else
			printf("%.3f", element_arr[tmp_ele_index]);
	}
	printf("\n*****************end*********************\n");
	

	return 0;
}
float Calc_Result()                                               //将后缀表达式进行计算，并返回计算结果
{
	int i = 0;
	float L_Val = 0, R_Val = 0;                                   //设置左值右值用于暂存pop出来的两个数字
	for (; element_index > 0; element_index--)
	{
		if (element_arr[i] == '+' || element_arr[i] == '-' || element_arr[i] == '*' || element_arr[i] == '/')
		{
			R_Val = Pop_Num_Stack();
			L_Val = Pop_Num_Stack();
			switch ((char)element_arr[i])
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
	printf("计算结果是：%.3f", Calc_Result());
	return 0;
}