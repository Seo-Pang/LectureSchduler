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
	printf("                         ==========     ==========     공강 Builder     ==========      ==========\n");
	printf("\n");
	printf("\n");
	printf("                                                 프로그램이 종료됩니다...\n");
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
	printf("                         ==========     ==========     강의  리스트     ==========      ==========\n");
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
	printf("                                             <- 이전 | ESC 돌아가기 | 다음 ->                     \n");
	printf("\n");
	printf("                         ==========     ==========      %3d 페이지      ==========      ==========\n", (keyNum + 1));
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
	printf("                         ==========     ==========        시간표        ==========      ==========\n");
	printf("\n                            [요일] ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", i + 1);
	printf("\n                             [월]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.mon[i]);
	printf("\n                             [화]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.tus[i]);
	printf("\n                             [수]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.wed[i]);
	printf("\n                             [목]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.thu[i]);
	printf("\n                             [금]  ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", sche.fri[i]);
	printf("\n\n");
	printf("                         ==========     ==========      강의  정보      ==========      ==========\n\n");
	for (int i = 0; i < 9; i++) {
		if (use_lec_index[i] >= 0) {
			lec = lec_search(use_lec_index[i]);
			lec_printList(lec);
		}
		else {
			printf("\n");
		}
	}
	printf("\n                         ==========     ==========     ESC 돌아가기     ==========      ==========\n");
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
		printf("                         ==========     ==========     공강 Builder     ==========      ==========\n");
		printf("\n");
		printf("                                        강의 리스트 확인하기                 : 1번\n");
		printf("                                        원하는 시간표 짜러가기               : 2번\n");
		printf("                                        짜둔 시간표 확인하기                 : 3번\n");
		printf("                                        프로그램 종료하기                    : 4번\n");
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		printf("\n                         원하는 번호를 선택해 주세요. >>> ");

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