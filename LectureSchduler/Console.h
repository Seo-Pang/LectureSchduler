#pragma once

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

#include "Algorithm.h"

static void getError() {
	system("cls");
	for (int i = 0; i < 11; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========     ���� Builder     ==========      ==========\n");
	printf("\n");
	printf("\n");
	printf("                                                Error! �߸� �Է��ϼ̽��ϴ�.\n");
	printf("\n");
	printf("\n");
	printf("                         ==========     ==========     ============     ==========      ==========\n");
	Sleep(2000);
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

UserInfo get_UserInfo_Console() {
	UserInfo user = { 0, "", 0 };
	int checkNum = 0;
	int getYear = 0;
	char getMajor[] = "";
	int getCredit = 0;
	while (checkNum <= 3) {
		system("cls");
		for (int i = 0; i < 9; i++) {
			printf("\n");
		}
		printf("                         ==========     ==========     �����  ����     ==========      ==========\n");
		printf("\n");
		if (user.year >= 1 && user.year <= 4) {
			printf("                                        ������� �г�                       %d �г�\n", user.year);
		}
		else {
			printf("                                        ������� �г�                     ���� ����\n");
		}
		printf("\n");
		if (user.major != "") {
			printf("                                        ������� ����           %20s\n", user.major);
		}
		else {
			printf("                                        ������� ����                     ���� ����\n");
		}
		printf("\n");
		printf("                                        �̹� �б� �ִ� ����                 %2d ����\n", user.credit);
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		if (checkNum == 0) {
			printf("\n                       ����� �г��� �Է��� �ּ���. 0�� �Է��ϸ� ��ҵ˴ϴ�. >>> ");
			scanf("%d", &getYear);
			if (getYear < 0 || getYear > 4) {
				getError();
			}
			else if (getYear == 0) {
				break;
			}
			else {
				user.year = getYear;
				checkNum++;
			}
		}
		else if (checkNum == 1) {
			printf("\n                       ����� ������ �Է��� �ּ���. >>> ");
			scanf("%s", &getMajor);
			strcmp(user.major, getMajor);
			checkNum++;
		}
		else if (checkNum == 2) {
			printf("\n                       ����� �̹� �б� �ִ� ���� ���� ������ �Է��� �ּ���. >>> ");
			scanf("%d", &getCredit);
			user.credit = getCredit;
			checkNum++;
		}
		else if (checkNum == 3) {
			printf("\n                       ������� ������ �Է��ϰ� �ֽ��ϴ�... ��ٷ� �ּ���...");
			Sleep(3000);
			return user;
		}
	}
}

static void get_Basic_Console(Preference* list) {
	for (int a = 0; a < 5; a++) {
		system("cls");
		for (int i = 0; i < 11; i++) {
			printf("\n");
		}
		printf("                         ==========     ==========     ����  Ű����     ==========      ==========\n");
		printf("\n");
		for (int i = 0; i < 5; i++) {
			if (list[i] == NULL)
				printf("                                        [ %d ]                          Ű���� ����\n", i + 1);
			else
				printf("                                        [ %d ]                  %20s\n", i + 1, list[i]);
		}
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		printf("                         �������� ��� ���� Ű���带 �Է����ּ���. (���� %d��) >>> ", a + 1);
		scanf("%s", list[a]);
	}
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
						view_lecture(keyNum);
					}
					else {
						return 0;
					}
					break;
				case 77:
					keyNum++;
					if (keyNum <= 134) {
						view_lecture(keyNum);
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

static int* create_timetable(Schedule* sche) {
	FILE* data = fopen("������.txt", "r"); //���� �о����
	Lecture lec;
	LecArray lec_array[MAX_LECTURE] = { 0, }; //����ü�� �ε��� ��ȣ�� ����ġ �ִ� array,
	LecArray major_insert[MAX_LECTURE] = { 0, }; //����ü�� �ε��� ��ȣ�� ����ġ �ִ� array,
	LecArray basic_insert[MAX_LECTURE] = { 0, }; //���� ���Կ� �ʿ��� ���
	Preference(*user_preference)[20];
	int use_lec_index[MAX_LECTURE];
	int idx = 0;

	UserInfo user_info;
	user_info = get_UserInfo();
	int canUseCredit = user_info.credit;

	/*
	for (int i = 0; i < MAX_LECTURE; i++) {
		lec = lec_search(i);
		if (strstr(lec.cmp_clf, "��") != NULL)	//������ ���,
			lec_array[idx] = weight_setting_major(lec, user_info);
		else									//������ ���,
			lec_array[idx] = weight_setting_basic(lec, user_preference);
		idx++;
	}

	for (int i = 0, j = 0; i < idx; i++)
	{
		if (lec_array[i].weight > 0)
		{
			basic_insert[j].index = lec_array[i].index; //���ϴ� �ε����� ����

			lec = lec_search(lec_array[i].index);

			j++;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		lec = lec_search(basic_insert[i].index);
		if(canUseCredit >= lec.credit){
			*sche = push_lec(lec, *sche);
			canUseCredit -= lec.credit;

		}
	}
	*/
}

static int view_timetable(Schedule sche, int use_lec_index[], int* idx) {
	Lecture lec;
	int getKey = 0;

	system("cls");
	for (int i = 0; i < 4; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========        �ð�ǥ        ==========      ==========\n");
	printf("\n                            [����] ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", i + 1);
	printf("\n                             [��]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.mon[i]);
	printf("\n                             [ȭ]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.tus[i]);
	printf("\n                             [��]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.wed[i]);
	printf("\n                             [��]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.thu[i]);
	printf("\n                             [��]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.fri[i]);
	printf("\n\n");
	printf("                         ==========     ==========      ����  ����      ==========      ==========\n\n");
	for (int i = 0; i < 9; i++) {
		if (use_lec_index[i] >= 0) {
			lec = lec_search(use_lec_index[i]);
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
				return 0;
			}
		}
	}
}

static void main_menu(Schedule* sche, int use_lec_index[], int* idx) {

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
			//create_timetable();
		}
		else if (select_menu == 3) {
			view_timetable(*sche, use_lec_index, idx);
		}
		else if (select_menu == 4) {
			end_program();
		}
	}
}