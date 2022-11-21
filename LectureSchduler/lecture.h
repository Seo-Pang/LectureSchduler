#pragma once

#include <stdio.h>
#include <string.h>

//���ڰ� �ʹ� ũ�� ������ ���� ����

#define MAX_LECTURE 1341 //������ ����
#define MAX_LEN 150 //������ �ִ� ���� 

typedef struct Lecture
{
	int index;					//�ε���
	char name[MAX_LEN];			//���Ǹ�
	char lec_number[MAX_LEN];	//�м���ȣ
	char lec_room[MAX_LEN];		//���ǽ�
	char department[MAX_LEN];	//�а�(���� ���� �а�)
	char major[MAX_LEN];		//�̼� ����
	int credit;					//����
	int start_time;				//���۽ð� //���� [��1,2 ȭ3,4]�� ��� 103���� ǥ��
	int end_time;				//����ð� //���� [��1,2 ȭ3,4]�� ��� 204���� ǥ��
	int week;					//����, ������(1) ~ �ݿ���(5)
} Lecture;

//Lecture ����ü�� ���� ���
void lec_print(Lecture lec)
{
	printf("�ε��� : %d\n", lec.index);
	printf("���Ǹ� : %s\n", lec.name);
	printf("�а� : %s\n", lec.department);
	printf("�м���ȣ : %s\n", lec.lec_number);
	printf("�̼����� : %s\n", lec.major);
	printf("���ǽ� : %s\n", lec.lec_room);
	printf("���� : %d\n", lec.credit);
	printf("���۽ð� : %d\n", lec.start_time);
	printf("����ð� : %d\n", lec.end_time);
	printf("���� : %d\n", lec.week);
	printf("\n\n");
}

//�ڷῡ�� n��°�� ���� �ڷ��� ������ ��� ����ü�� ��ȯ(idx = 0, 1, ...)
Lecture lec_search(int idx)
{
	int line = 2 + (idx * 32); //0��°�ٺ��� �����ϰ�, �޸��忡�� idx��°�� ������ ��� ����ü�� ���� ����
	Lecture temp; //���� ����ü
	FILE* data = fopen("������.txt", "r");
	char str[MAX_LEN];

	//�޸��忡�� idx��°�� �ڷᰡ ���۵Ǵ� �ٷ� �̵�
	for (int i = 0; i < line; i++)
	{
		fgets(str, MAX_LEN, data);
	}

	char temp_char[MAX_LEN] = "";
	//�ڷ� ���� ����
	do 
	{
		temp.index = idx;
		fgets(str, MAX_LEN, data);
		if(strstr(str, "SBJ_NM") != NULL)
		{
			//���Ǹ�
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.name, temp_char);
			
		}
		else if (strstr(str, "SBJ_NO") != NULL)
		{
			//�м���ȣ
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.lec_number, temp_char);
		}

		else if (strstr(str, "EST_DEPT_INFO") != NULL)
		{
			//�а�
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.department, temp_char);
		}

		else if (strstr(str, "CMP_DIV_NM") != NULL)
		{
			//�̼�����
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.major, temp_char);
		}

		else if (strstr(str, "LECT_TIME_ROOM") != NULL)
		{
			//���ǽ�
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.lec_room, temp_char);

			//���۽ð�
			strcpy(temp_char, strstr(str, ": \"") + 5);
			temp.start_time = 0;
			if ((temp_char[1] == ',')||(temp_char[1] == '('))
			{
				temp_char[1] = NULL;
			}
			else
			{
				temp_char[2] = NULL;
			}
			if (strlen(temp_char) == 1)
			{
				temp.start_time = (int)(temp_char[0] - '0') * 100;
			}
			else
			{
				temp.start_time = (int)(temp_char[0] - '0') * 1000 + (int)(temp_char[1] - '0')* 100;
			}
			//���۽ð��� 2���� ���
			strcpy(temp_char, strstr(str, "(") + 2);
			if (strstr(temp_char, "(") != NULL)
			{
				strcpy(temp_char, strstr(str, ")") + 4);
				if ((temp_char[1] == ',') || (temp_char[1] == '('))
				{
					temp_char[1] = NULL;
				}
				else
				{
					temp_char[2] = NULL;
				}
				if (strlen(temp_char) == 1)
				{
					temp.start_time += (int)(temp_char[0] - '0');
				}
				else
				{
					temp.start_time += (int)(temp_char[0] - '0') * 10 + (int)(temp_char[1] - '0');
				}
			}
			
			//����ð�
			temp.end_time = 0;
			strcpy(temp_char, strstr(str, "(") - 2);
			if (((int)(temp_char[0] - '0') < 0) || ((int)(temp_char[0] - '0') > 10))
			{
				strcpy(temp_char, temp_char + 1);
			}
			if (temp_char[1] == '(')
			{
				temp_char[1] = NULL;
			}
			else
			{
				temp_char[2] = NULL;
			}
			if (strlen(temp_char) == 1)
			{
				temp.end_time = (int)(temp_char[0] - '0') * 100;
			}
			else
			{
				temp.end_time = (int)(temp_char[0] - '0') * 1000 + (int)(temp_char[1] - '0') * 100;
			}
			//����ð��� 2���� ���
			strcpy(temp_char, strstr(str, "(") + 2);
			if (strstr(temp_char, "(") != NULL)
			{
				strcpy(temp_char, strstr(temp_char, "(") - 2);
				if (((int)(temp_char[0] - '0') < 0) || ((int)(temp_char[0] - '0') > 10))
				{
					strcpy(temp_char, temp_char + 1);
				}
				if (temp_char[1] == '(')
				{
					temp_char[1] = NULL;
				}
				else
				{
					temp_char[2] = NULL;
				}
				if (strlen(temp_char) == 1)
				{
					temp.end_time += (int)(temp_char[0] - '0');
				}
				else
				{
					temp.end_time += (int)(temp_char[0] - '0') * 10 + (int)(temp_char[1] - '0');
				}
			}

			//����
			temp.week = 0;
			strcpy(temp_char, strstr(str, ": \"") + 3);
			if (strstr(temp_char, "��") != NULL)
			{
				temp.week *= 10;
				temp.week += 1;
			}
			if (strstr(temp_char, "ȭ") != NULL)
			{
				temp.week *= 10;
				temp.week += 2;
			}
			if (strstr(temp_char, "��") != NULL)
			{
				temp.week *= 10;
				temp.week += 3;
			}
			if (strstr(temp_char, "��") != NULL)
			{
				temp.week *= 10;
				temp.week += 4;
			}
			if (strstr(temp_char, "��") != NULL)
			{
				temp.week *= 10;
				temp.week += 5;
			}
			if (strstr(temp_char, "��") != NULL)
			{
				temp.week *= 10;
				temp.week += 6;
			}
			if (strstr(temp_char, "��") != NULL)
			{
				temp.week *= 10;
				temp.week += 7;
			}
		}
		else if (strstr(str, "CDT") != NULL)
		{
			//����
			strcpy(temp_char, strstr(str, ": ") + 2);
			temp_char[strlen(temp_char) - 2] = NULL;
			if (strlen(temp_char) == 1)
			{
				temp.credit = (int)(temp_char[0] - '0');
			}
			else
			{
				temp.credit = (int)(temp_char[0] - '0') * 10 + (int)(temp_char[1] - '0');
			}
		}
	} while (strstr(str, "}") == NULL); //idx������ �ڷᰡ ������ �˷��ִ� "}"�� ������ �ݺ��� ����
	fclose(data);
	return temp;
}
