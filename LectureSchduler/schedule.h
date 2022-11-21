#pragma once

#include "lecture.h"
#define LATEST_TIME 21

typedef int Day;
//월화수목금의 시간을 담은 시간표
typedef struct Schedule
{
	//0번째 값은 1교시에 그 값에 해당하는 수업이 있다는 뜻
	Day mon[LATEST_TIME]; //mon[0]은 월요일 1교시, fri[8]은 금요일 9교시
	Day tus[LATEST_TIME];
	Day wed[LATEST_TIME];
	Day thu[LATEST_TIME];
	Day fri[LATEST_TIME];

}Schedule;


//sche의 시간표를 참고하여 lec를 넣는 함수
Schedule push_lec(Lecture lec, Schedule sche)
{
	Schedule except = sche; //예외가 일어날 경우 대신 반환할 데이터
	if (lec.week > 10) //수업이 일주일에 여러번 있는 경우
	{
		int lec_start_time = lec.start_time;
		int lec_end_time = lec.end_time;
		int lec_week = lec.week;
		while (lec.week != 0)
		{
			lec_week = lec.week % 10;
			lec_start_time = lec.start_time % 100;
			lec_end_time = lec.end_time % 100;

			for (int i = lec_start_time; i <= lec_end_time; i++)
			{
				switch (lec_week)
				{
				case 1:
					if (sche.mon[i] != 0) //만약 데이터가 있다면
					{
						fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
						return except;
					}
					sche.mon[i] = lec.index;
					break;
				case 2:
					if (sche.tus[i] != 0) //만약 데이터가 있다면
					{
						fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
						return except;
					}
					sche.tus[i] = lec.index;
					break;
				case 3:
					if (sche.wed[i] != 0) //만약 데이터가 있다면
					{
						fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
						return except;
					}
					sche.wed[i] = lec.index;
					break;
				case 4:
					if (sche.thu[i] != 0) //만약 데이터가 있다면
					{
						fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
						return except;
					}
					sche.thu[i] = lec.index;
					break;
				case 5:
					if (sche.fri[i] != 0) //만약 데이터가 있다면
					{
						fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
						return except;
					}
					sche.fri[i] = lec.index;
					break;
				default:
					break;
				}
			}
			lec.week = lec.week / 10;
			lec.start_time = lec.start_time / 100;
			lec.end_time = lec.end_time / 100;
		}
	}
	else
	{
		int lec_start_time = lec.start_time / 100 - 1; //300 => 3교시 =>day[2]
		int lec_end_time = lec.end_time / 100 - 1; //500 => 5교시 => day[4]
		int lec_hours = lec.end_time - lec.start_time + 1; //강의 시간
		
		printf("DEBUG: %d %d %d", lec_start_time, lec_end_time, lec_hours);
		for (int i = lec_start_time; i <= lec_end_time; i++)
		{
			switch (lec.week)
			{
			case 1:
				if (sche.mon[i] != 0) //만약 데이터가 있다면
				{
					fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
					return except;
				}
				sche.mon[i] = lec.index;
				break;
			case 2:
				if (sche.tus[i] != 0) //만약 데이터가 있다면
				{
					fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
					return except;
				}
				sche.tus[i] = lec.index;
				break;
			case 3:
				if (sche.wed[i] != 0) //만약 데이터가 있다면
				{
					fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
					return except;
				}
				sche.wed[i] = lec.index;
				break;
			case 4:
				if (sche.thu[i] != 0) //만약 데이터가 있다면
				{
					fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
					return except;
				}
				sche.thu[i] = lec.index;
				break;
			case 5:
				if (sche.fri[i] != 0) //만약 데이터가 있다면
				{
					fprintf(stderr, "[WARNING] 이미 안에 데이터가 있습니다\n");
					return except;
				}
				sche.fri[i] = lec.index;
				break;
			default:
				break;
			}
		}

		
	}
	
	return sche;
}

void sche_print(Schedule sche)
{
	printf("\n");
	printf("[MON]: ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.mon[i]); printf("\n");
	printf("[TUS]: ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.tus[i]); printf("\n");
	printf("[WED]: ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.wed[i]); printf("\n");
	printf("[TUS]: ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.thu[i]); printf("\n");
	printf("[FRI]: ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.fri[i]); printf("\n");
	printf("\n");
}