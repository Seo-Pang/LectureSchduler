#pragma once

#include <stdio.h>
#include <string.h>

//숫자가 너무 크면 스택이 감당 못함

#define MAX_LECTURE 1341 //자료에 있는 강의의 숫자
#define MAX_LEN 150 //글자의 최대 숫자 

typedef struct Lecture
{
	int index;					//인덱스
	char name[MAX_LEN];			//강의명
	char lec_number[MAX_LEN];	//학수번호
	char lec_room[MAX_LEN];		//강의실
	char department[MAX_LEN];	//학과(강의 설립 학과)
	char cmp_clf[MAX_LEN];		//이수 구분(Complete Classfication)
	int year;					//학년
	int credit;					//학점
	int start_time;				//시작시간 //만약 [월1,2 화3,4]인 경우 103으로 표시
	int end_time;				//종료시간 //만약 [월1,2 화3,4]인 경우 204으로 표시
	int week;					//요일, 월요일(1) ~ 금요일(5)
} Lecture;

typedef struct LecArray
{
	int index;		//강의 인덱스
	int weight;		// 가중치
}LecArray;

//Lecture 구조체의 값을 출력
void lec_print(Lecture lec)
{
	printf("인덱스 : %d\n", lec.index);
	printf("강의명 : %s\n", lec.name);
	printf("학과 : %s\n", lec.department);
	printf("학년 : %d\n", lec.year);
	printf("학수번호 : %s\n", lec.lec_number);
	printf("이수구분 : %s\n", lec.cmp_clf);
	printf("강의실 : %s\n", lec.lec_room);
	printf("학점 : %d\n", lec.credit);
	printf("시작시간 : %d\n", lec.start_time);
	printf("종료시간 : %d\n", lec.end_time);
	printf("요일 : %d\n", lec.week);
	printf("\n\n");
}

// 강의 리스트 확인을 위한 출력 방식
// 간단하게 학수번호, 강의명, 학점의 확인이 가능
void lec_printList(Lecture lec) {
	printf("                          [ %4d ]    %8s    %38s    %2d학점 \n", lec.index, lec.lec_number, lec.name, lec.credit);
}

//자료에서 n번째의 적힌 자료의 정보가 담긴 구조체를 반환(idx = 0, 1, ...)
Lecture lec_search(int idx)
{
	FILE* data = fopen("교과목.txt", "r");
	int line = 2 + (idx * 32); //0번째줄부터 시작하고, 메모장에서 idx번째의 정보가 담긴 구조체의 시작 라인
	Lecture temp; //리턴 구조체
	char str[MAX_LEN];

	//메모장에서 idx번째의 자료가 시작되는 줄로 이동
	for (int i = 0; i < line; i++)
	{
		fgets(str, MAX_LEN, data);
	}

	char temp_char[MAX_LEN] = "";
	//자료 추출 시작
	do 
	{
		temp.index = idx;
		fgets(str, MAX_LEN, data);
		if(strstr(str, "SBJ_NM") != NULL)
		{
			//강의명
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.name, temp_char);
			
		}
		else if (strstr(str, "SBJ_NO") != NULL)
		{
			//학수번호
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.lec_number, temp_char);
		}

		else if (strstr(str, "EST_DEPT_INFO") != NULL)
		{
			//학과
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.department, temp_char);
		}

		else if (strstr(str, "CRS_SHYR") != NULL)
		{
			//학년
			strcpy(temp_char, strstr(str, ": ") + 2);
			temp_char[strlen(temp_char) - 2] = NULL;
			temp.year = (int)(temp_char[0] - '0');
		}


		else if (strstr(str, "CMP_DIV_NM") != NULL)
		{
			//이수구분
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.cmp_clf, temp_char);
		}

		else if (strstr(str, "LECT_TIME_ROOM") != NULL)
		{
			//강의실
			strcpy(temp_char, strstr(str, ": \"") + 3);
			temp_char[strlen(temp_char) - 3] = NULL;
			strcpy(temp.lec_room, temp_char);

			//시작시간
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
			//시작시간이 2개인 경우
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
			
			//종료시간
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
			//종료시간이 2개인 경우
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

			//요일
			temp.week = 0;
			strcpy(temp_char, strstr(str, ": \"") + 3);
			if (strstr(temp_char, "월") != NULL)
			{
				temp.week *= 10;
				temp.week += 1;
			}
			if (strstr(temp_char, "화") != NULL)
			{
				temp.week *= 10;
				temp.week += 2;
			}
			if (strstr(temp_char, "수") != NULL)
			{
				temp.week *= 10;
				temp.week += 3;
			}
			if (strstr(temp_char, "목") != NULL)
			{
				temp.week *= 10;
				temp.week += 4;
			}
			if (strstr(temp_char, "금") != NULL)
			{
				temp.week *= 10;
				temp.week += 5;
			}
			if (strstr(temp_char, "토") != NULL)
			{
				temp.week *= 10;
				temp.week += 6;
			}
			if (strstr(temp_char, "일") != NULL)
			{
				temp.week *= 10;
				temp.week += 7;
			}
		}
		else if (strstr(str, "CDT") != NULL)
		{
			//학점
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
	} while (strstr(str, "}") == NULL); //idx번재의 자료가 끝남을 알려주는 "}"가 나오면 반복문 종료
	fclose(data);
	return temp;
}

