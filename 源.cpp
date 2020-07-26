#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define MAX_SIZE 1000
#define PI 3.14159265
float element_arr[MAX_SIZE*2];                             //�������Ԫ������Ϊ������
char oper_lib[MAX_SIZE - 1];
float num_stack[MAX_SIZE];
int element_index = 0, oper_index = 0, num_stack_index=0;
int Push_Element_Arr(float ele)                             //����Ԫ������
{
	element_arr[element_index] = ele;
	element_index++;
	return 0;
}
int Push_Oper(char oper)                                   //��������ջ����
{
	oper_lib[oper_index] = oper;
	oper_index++;
	return 0;
}
char Pop_Oper()                                          //��������ջ���� 
{
	char tmp;
	oper_index--;
	tmp = oper_lib[oper_index];
	oper_lib[oper_index] = '\0';
	return tmp;
}
int Push_Num_Stack(float Num)                                //������ջ����
{
	num_stack[num_stack_index] = Num;
	num_stack_index++;
	return 0;
}
float Pop_Num_Stack()                                       //���ݳ�ջ����
{
	float tmp;
	num_stack_index--;
	tmp = num_stack[num_stack_index];
	num_stack[num_stack_index] = 0;
	return tmp;
}

int Detection_Input_Val(char str[MAX_SIZE * 2]) //����1��ʾ����Ч���ݣ�0Ϊ��Ч
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
			if ((str[i + 1] >= '0' && str[i + 1] <= '9') && (str[i - 1] >= '0' && str[i - 1] <= '9'))    //���С����ǰ���Ƿ������֣��޵Ļ������˳�
			{

			}
			else 
				return 1;
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '\\')
		{
			if (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' || str[i + 1] == '\\' || str[i + 1] == '\0'||i==0) //���ʽ��ͷΪ���������������������������˳�����
				return 1;
		}
		else if (str[i] >= 'a' && str[i] <= 'z')                      //�ڴ˴����Լ���Ϸ������
		{
			switch (str[i])
			{
			case 's':                                                //�ж��Ƿ���sin����
				if (str[i + 1] == 'i' && str[i + 2] == 'n')
					i = i + 2;
				else
					return 1;
				break;
			case 'c':                                                 //�ж��Ƿ���cos����
				if (str[i + 1] == 'o' && str[i + 2] == 's')
					i = i + 2;
				else
					return 1;
				break;
			case 't':                                                  //�ж��Ƿ�Ϊtan����
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
int youxianji(char a, char b)                                          //�ж���������ȼ�����1��ʾa�����ȼ��߷���0��ʾͬ����ͼ�
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
int Infix_To_Suffix(char str[MAX_SIZE * 2])                        //����׺���ʽת��Ϊ��׺���ʽ
{
	int i = 0, temp_i = 0, tmp_num = 0, t,kuohao_flag=0,num_flag=0,tmp_ele_index;
	char temp[10] = " ", tmp_oper = 0;
	int special_function_flag = 0;                                //������־��ǰ�Ƿ��ڼ�����������ĺ�����0�ޣ�1��
	int sin_flag = 0, cos_flag = 0, tan_flag = 0;                 //��־��ǰ����һ�����Ǻ����������������⺯����ֱ����Ӽ���
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')                          //�ж�����һ�����Ǻ����������Լ����κ��������������翪����
		{
			special_function_flag = 1;                               //��Ϊ���⺯��������־��1
			switch (str[i])
			{
			case 's':                                                //�ж��Ƿ���sin����
				if (str[i + 1] == 'i' && str[i + 2] == 'n')
				{
					i = i + 3;                                       //����i�Ĵ�С���ݺ��������õ��ַ�������
					sin_flag = 1;
				}
				break;
			case 'c':                                                //�ж��Ƿ���cos����
				if (str[i + 1] == 'o' && str[i + 2] == 's')
				{
					i = i + 3;
					cos_flag = 1;
				}
				break;
			case 't':                                                //�ж��Ƿ�Ϊtan����
				if (str[i + 1] == 'a' && str[i + 2] == 'n')
				{
					i = i + 3;
					tan_flag = 1;
				}
				break;
			default:
				printf("��δ����˺���\n");
				break;
			}
		}
		while ((str[i] >= '0' && str[i] <= '9')||str[i]=='.')                     //�������ַ��Ͳ��������뿪����ȡ�����������ַ�����
		{
			temp[temp_i] = str[i];
			temp_i++;
			i++;
			num_flag = 1;
		}
		if (special_function_flag)                                  //��������⺯���������⺯�����,����������ѹ��Ԫ��ջ
		{
			if (sin_flag)
			{
				Push_Element_Arr(sin(atof(temp) * PI / 180));                  //����sinֵ������ѹ��Ԫ��ջ
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
			Push_Element_Arr(atof(temp));                          //�������ַ���ת��Ϊ����
			num_flag = 0;
		}

		for (; temp_i > 0; temp_i--)                               //�����ʱ����
			temp[temp_i] = 0;


		if (str[i] != '\0')                                        //ʵ����׺���ʽ����׺���ʽ
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
					while (!youxianji(str[i], oper_lib[oper_index - 1]) && oper_lib[0] != '\0')           //������ʣ�������ȫ����ջ
						Push_Element_Arr(Pop_Oper());
					Push_Oper(str[i]);
				}
				
			}
			i++;
		}

	}
	while (oper_lib[0] != '\0')                                  //������ȫ����ջ
		Push_Element_Arr(Pop_Oper());

	printf("***************��׺���******************\n");
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
float Calc_Result()                                               //����׺���ʽ���м��㣬�����ؼ�����
{
	int i = 0;
	float L_Val = 0, R_Val = 0;                                   //������ֵ��ֵ�����ݴ�pop��������������
	printf("��������Ԫ����:%d\n", element_index);
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
	char str[MAX_SIZE * 2];                                      //���ڴ洢�������ѧ���ʽ
	printf("please input a mathematical expression:\n");
	scanf_s("%s", str, sizeof(str));
	if (Detection_Input_Val(str))                                //����Ƿ��зǷ��ַ�����
	{
		printf("���ڷǷ����������ֹ................\n");
		return 0;
	}
	printf("***************��׺���******************\n");
	printf("%s\n", str);
	printf("*****************end*********************\n");
	Infix_To_Suffix(str);
	printf("�������ǣ�%.3f", Calc_Result());
	return 0;
}