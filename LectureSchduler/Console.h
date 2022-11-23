#pragma once

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

#include "schedule.h"
#include "lecture.h"
#include "Algorithm.h"

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

static void create_timetable(Schedule* sche) {

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