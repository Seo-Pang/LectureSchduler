#pragma once

#include "lecture.h"
#define LATEST_TIME 21

typedef int Day;
//��ȭ������� �ð��� ���� �ð�ǥ
typedef struct Schedule
{
	//0��° ���� 1���ÿ� �� ���� �ش��ϴ� ������ �ִٴ� ��
	Day mon[LATEST_TIME]; //mon[0]�� ������ 1����, fri[8]�� �ݿ��� 9����
	Day tus[LATEST_TIME];
	Day wed[LATEST_TIME];
	Day thu[LATEST_TIME];
	Day fri[LATEST_TIME];

}Schedule;


//sche�� �ð�ǥ�� �����Ͽ� lec�� �ְ� �ð�ǥ�� ����
Schedule push_lec(Lecture lec, Schedule sche)
{
	Schedule except = sche; //���ܰ� �Ͼ ��� ��� ��ȯ�� ������
	if (lec.week > 10) //������ �����Ͽ� ������ �ִ� ���
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
					if (sche.mon[i] != 0) //���� �����Ͱ� �ִٸ�
					{
						fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
						return except;
					}
					sche.mon[i] = lec.index;
					break;
				case 2:
					if (sche.tus[i] != 0) //���� �����Ͱ� �ִٸ�
					{
						fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
						return except;
					}
					sche.tus[i] = lec.index;
					break;
				case 3:
					if (sche.wed[i] != 0) //���� �����Ͱ� �ִٸ�
					{
						fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
						return except;
					}
					sche.wed[i] = lec.index;
					break;
				case 4:
					if (sche.thu[i] != 0) //���� �����Ͱ� �ִٸ�
					{
						fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
						return except;
					}
					sche.thu[i] = lec.index;
					break;
				case 5:
					if (sche.fri[i] != 0) //���� �����Ͱ� �ִٸ�
					{
						fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
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
		int lec_start_time = lec.start_time / 100 - 1; //300 => 3���� =>day[2]
		int lec_end_time = lec.end_time / 100 - 1; //500 => 5���� => day[4]
		int lec_hours = lec.end_time - lec.start_time + 1; //���� �ð�
		
		for (int i = lec_start_time; i <= lec_end_time; i++)
		{
			switch (lec.week)
			{
			case 1:
				if (sche.mon[i] != 0) //���� �����Ͱ� �ִٸ�
				{
					fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
					return except;
				}
				sche.mon[i] = lec.index;
				break;
			case 2:
				if (sche.tus[i] != 0) //���� �����Ͱ� �ִٸ�
				{
					fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
					return except;
				}
				sche.tus[i] = lec.index;
				break;
			case 3:
				if (sche.wed[i] != 0) //���� �����Ͱ� �ִٸ�
				{
					fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
					return except;
				}
				sche.wed[i] = lec.index;
				break;
			case 4:
				if (sche.thu[i] != 0) //���� �����Ͱ� �ִٸ�
				{
					fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
					return except;
				}
				sche.thu[i] = lec.index;
				break;
			case 5:
				if (sche.fri[i] != 0) //���� �����Ͱ� �ִٸ�
				{
					fprintf(stderr, "[WARNING] �̹� �ȿ� �����Ͱ� �ֽ��ϴ�\n");
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

//�ð�ǥ�� �����˻� �Ͽ�, index�� �ش��ϴ� ������ ������ �����ϰ� �ð�ǥ�� ����
Schedule delete_lec(int index, Schedule sche)
{
	for (int i = 0; i < LATEST_TIME; i++)
	{
		if (sche.mon[i] == index)
		{
			sche.mon[i] = 0;
		}

		if (sche.tus[i] == index)
		{
			sche.tus[i] = 0;
		}

		if (sche.wed[i] == index)
		{
			sche.wed[i] = 0;
		}

		if (sche.thu[i] == index)
		{
			sche.thu[i] = 0;
		}

		if (sche.fri[i] = index)
		{
			sche.fri[i] = 0;
		}
	}
	return sche;
}
//����: sche = delete_lec(lec_array[0].index, sche);


//�ð�ǥ ���
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