#pragma once

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

#include "schedule.h"
#include "lecture.h"
#include "Algorithm.h"

void check_search(int a) {
	system("cls");
	for (int i = 0; i < 11; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========     ���� Builder     ==========      ==========\n");
	printf("\n");
	printf("\n");
	printf("                                        ���� ����Ʈ �˻���         [ %4d / %4d ]\n", a, MAX_LECTURE);
	printf("\n");
	printf("\n");
	printf("                         ==========     ==========     ============     ==========      ==========\n");
}

UserInfo ask_major_console() {

	UserInfo user = { 0, "", 0 };
	int inputNum = 0;

	while (inputNum < 3) {

		system("cls");
		for (int i = 0; i < 9; i++) {
			printf("\n");
		}
		printf("                         ==========     ==========     ���� Builder     ==========      ==========\n");
		printf("\n");
		printf("                                        ������� ���� %28s\n", user.major);
		printf("                                        ������� �г�                      %2d �г�\n", user.year);
		printf("                                        �ִ� �������� ����                 %2d ����\n", user.maxCredit);
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		if (inputNum == 0) {
			printf("\n                         ������� ������ �Է��� �ּ��� >>> ");
			scanf("%s", user.major);
			inputNum++;
		}
		else if (inputNum == 1) {
			printf("\n                         ������� �г��� �Է��� �ּ��� >>> ");
			scanf("%d", &user.year);
			inputNum++;
		}
		else if (inputNum == 2) {
			printf("\n                         �������� ������ �Է��� �ּ��� >>> ");
			scanf("%d", &user.maxCredit);
			inputNum++;
		}
	}

	system("cls");
	for (int i = 0; i < 9; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========     ���� Builder     ==========      ==========\n");
	printf("\n");
	printf("                                        ������� ���� %28s\n", user.major);
	printf("                                        ������� �г�                      %2d �г�\n", user.year);
	printf("                                        �ִ� �������� ����                 %2d ����\n", user.maxCredit);
	printf("\n");
	printf("                         ==========     ==========     ============     ==========      ==========\n");
	printf("\n                                             ������� ������ �Է� ���Դϴ�...");
	Sleep(2000);
	return user;

}

Preference* ask_basic_console() {

	static Preference list[5][20];

	int inputNum = 0;

	while (inputNum < 5) {

		system("cls");
		for (int i = 0; i < 10; i++) {
			printf("\n");
		}
		printf("                         ==========     ==========     ���� Builder     ==========      ==========\n");
		printf("\n");
		printf("                                                    ���� Ű���� ����Ʈ\n\n");
		for (int i = 0; i < inputNum; i++) {
			printf("                                        [%d]           %28s\n", (i + 1), list[i]);
		}
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		printf("\n                         �������� ���� ������ Ű���带 �Է��� �ּ���. (�ߺ� ����) >>> ");
		scanf("%s", list[inputNum]);
		inputNum++;
	}

	system("cls");
	for (int i = 0; i < 10; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========     ���� Builder     ==========      ==========\n");
	printf("\n");
	printf("                                                    ���� Ű���� ����Ʈ\n\n");
	for (int i = 0; i < inputNum; i++) {
		printf("                                        [%d]           %28s\n", (i + 1), list[i]);
	}
	printf("\n");
	printf("                         ==========     ==========     ============     ==========      ==========\n");
	printf("\n                                              ���� ����Ʈ�� �Է� ���Դϴ�...");
	Sleep(2000);
	return (Preference*)list;
}
static void end_program() {
	system("cls");
	for (int i = 0; i < 11; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========     ���� Builder     ==========      ==========\n");
	printf("\n");
	printf("\n");
	printf("                                                 ���α׷��� ����˴ϴ�...\n");
	printf("\n");
	printf("\n");
	printf("                         ==========     ==========     ============     ==========      ==========\n");
	Sleep(2000);
	system("cls");
	exit(0);
}

static int view_lecture(int a) {
	Lecture lec;

	int keyNum = a;
	int getKey = 0;
	int idx = 0;
	system("cls");
	for (int i = 0; i < 6; i++) {
		printf("\n");
	}
	printf("\n");
	printf("                         ==========     ==========     ����  ����Ʈ     ==========      ==========\n");
	printf("\n");
	for (int j = 0; j < 10; j++) {
		idx = (keyNum * 10) + j;
		if (idx < MAX_LECTURE) {
			lec = lec_search(idx);
			lec_printList(lec);
		}
		else {
			printf("\n");
		}
	}
	printf("\n");
	printf("                                             <- ���� | ESC ���ư��� | ���� ->                     \n");
	printf("\n");
	printf("                         ==========     ==========      %3d ������      ==========      ==========\n", (keyNum + 1));
	while (1) {
		if (kbhit()) {
			getKey = getch();
			if (getKey == 224) {
				getKey = getch();
				switch (getKey) {
				case 75:
					keyNum--;
					if (keyNum >= 0) {
						return view_lecture(keyNum);
					}
					else {
						return 0;
					}
					break;
				case 77:
					keyNum++;
					if (keyNum <= 134) {
						return view_lecture(keyNum);
					}
					else {
						return 0;
					}
					break;
				}
			}
			else if (getKey == 27) {
				keyNum = -1;
				return 0;
			}
		}
	}
}

static void view_timetable(Schedule sche) {
	Lecture lec;
	int lecture_idx[10] = { 0, };
	int count_lecture = 0;

	int getKey;

	system("cls");
	for (int i = 0; i < 4; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========        �ð�ǥ        ==========      ==========\n");
	printf("\n                            [����] ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", i + 1);
	printf("\n                             [��]  ");
	for (int i = 0; i < LATEST_TIME; i++) {
		printf("%4d", sche.mon[i]);
		if (sche.mon[i] != 0) {
			for (int j = 0; j < 10; j++) {
				if (sche.mon[i] != lecture_idx[j] && lecture_idx[j] == 0) {
					lecture_idx[j] = sche.mon[i];
					count_lecture++;
					break;
				}
				if (sche.mon[i] == lecture_idx[j]) {
					break;
				}
			}
		}
	}
	printf("\n                             [ȭ]  ");
	for (int i = 0; i < LATEST_TIME; i++) {
		printf("%4d", sche.tus[i]);
		if (sche.tus[i] != 0) {
			for (int j = 0; j < 10; j++) {
				if (sche.tus[i] != lecture_idx[j] && lecture_idx[j] == 0) {
					lecture_idx[j] = sche.tus[i];
					count_lecture++;
					break;
				}
				if (sche.tus[i] == lecture_idx[j]) {
					break;
				}
			}
		}
	}
	printf("\n                             [��]  ");
	for (int i = 0; i < LATEST_TIME; i++) {
		printf("%4d", sche.wed[i]);
		if (sche.wed[i] != 0) {
			for (int j = 0; j < 10; j++) {
				if (sche.wed[i] != lecture_idx[j] && lecture_idx[j] == 0) {
					lecture_idx[j] = sche.wed[i];
					count_lecture++;
					break;
				}
				if (sche.wed[i] == lecture_idx[j]) {
					break;
				}
			}
		}
	}
	printf("\n                             [��]  ");
	for (int i = 0; i < LATEST_TIME; i++) {
		printf("%4d", sche.thu[i]);
		if (sche.thu[i] != 0) {
			for (int j = 0; j < 10; j++) {
				if (sche.thu[i] != lecture_idx[j] && lecture_idx[j] == 0) {
					lecture_idx[j] = sche.thu[i];
					count_lecture++;
					break;
				}
				if (sche.thu[i] == lecture_idx[j]) {
					break;
				}
			}
		}
	}
	printf("\n                             [��]  ");
	for (int i = 0; i < LATEST_TIME; i++) {
		printf("%4d", sche.fri[i]);
		if (sche.fri[i] != 0) {
			for (int j = 0; j < 10; j++) {
				if (sche.fri[i] != lecture_idx[j] && lecture_idx[j] == 0) {
					lecture_idx[j] = sche.fri[i];
					count_lecture++;
					break;
				}
				if (sche.fri[i] == lecture_idx[j]) {
					break;
				}
			}
		}
	}
	printf("\n\n");
	printf("                         ==========     ==========      ����  ����      ==========      ==========\n\n");
	for (int i = 0; i < count_lecture; i++) {
		if (lecture_idx[i] >= 0) {
			lec = lec_search(lecture_idx[i]);
			lec_printList(lec);
		}
		else {
			printf("\n");
		}
	}
	printf("\n                         ==========     ==========     ESC ���ư���     ==========      ==========\n");
	while (1) {
		if (kbhit()) {
			getKey = getch();
			if (getKey == 27) {
				return;
			}
		}
	}
}

static Schedule create_timetable(Schedule sche)
{
	FILE* data = fopen("������.txt", "r");
	Lecture lec;
	LecArray lec_array[MAX_LECTURE] = { 0, }; //����ü�� �ε��� ��ȣ�� ����ġ �ִ� array,
	LecArray major_insert[MAX_LECTURE] = { 0, }; //����ü�� �ε��� ��ȣ�� ����ġ �ִ� array,
	LecArray basic_insert[MAX_LECTURE] = { 0, }; //���� ���Կ� �ʿ��� ���
	Preference(*user_preference)[20];
	UserInfo user_info;
	int use_lec_index[MAX_LECTURE];
	int idx = 0;
	char string[MAX_LEN] = "";
	int input = 0;

	user_info = ask_major();

	user_preference = (void*)ask_basic();

	//��� �ε����� Ž���ϸ鼭 ��� ������ ����ġ�� ���
	for (int i = 0; i < MAX_LECTURE; i++)
	{
		lec = lec_search(i); //���ϴ� �ε����� ����

		check_search(i); //���������� Ȯ��

		if (strstr(lec.cmp_clf, "��") != NULL)	//������ ���,
			lec_array[idx] = weight_setting_major(lec, user_info);
		else									//������ ���,
			lec_array[idx] = weight_setting_basic(lec, user_preference);
		idx++;
	}
	printf("\n%d���� Ž��\n\n", idx);


	//(�����ʿ�) ����ġ ����ϴ� �κ�
	for (int i = 0, j = 0; i < idx; i++)
	{
		if (lec_array[i].weight > 0) //����ġ�� ���� ��쿡�� ����
		{
			basic_insert[j].index = lec_array[i].index; //���ϴ� �ε����� ����
			basic_insert[j].credit = lec_array[i].credit;
			basic_insert[j].weight = lec_array[i].weight;

			lec = lec_search(lec_array[i].index);
			lec_print(lec);

			j++;
		}
	}

	sche = DynamicProgrammingScheduling(basic_insert, user_info);

	view_timetable(sche);

	return sche;
}

void main_menu()
{
	Schedule sche = { {0,}, {0,}, {0,}, {0,}, {0,} };
	int select_menu = 0;

	while (1) {
		system("cls");
		for (int i = 0; i < 9; i++) {
			printf("\n");
		}
		printf("                         ==========     ==========     ���� Builder     ==========      ==========\n");
		printf("\n");
		printf("                                        ���� ����Ʈ Ȯ���ϱ�                 : 1��\n");
		printf("                                        ���ϴ� �ð�ǥ ¥������               : 2��\n");
		printf("                                        ¥�� �ð�ǥ Ȯ���ϱ�                 : 3��\n");
		printf("                                        ���α׷� �����ϱ�                    : 4��\n");
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		printf("\n                         ���ϴ� ��ȣ�� ������ �ּ���. >>> ");

		scanf("%d", &select_menu);

		if (select_menu == 1) {
			select_menu = view_lecture(0);
		}
		else if (select_menu == 2) {
			sche = create_timetable(sche);
		}
		else if (select_menu == 3) {
			view_timetable(sche);
		}
		else if (select_menu == 4) {
			end_program();
		}
	}
}