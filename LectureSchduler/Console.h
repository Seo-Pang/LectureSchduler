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
	printf("                         ==========     ==========     공강 Builder     ==========      ==========\n");
	printf("\n");
	printf("\n");
	printf("                                                Error! 잘못 입력하셨습니다.\n");
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
		printf("                         ==========     ==========     사용자  정보     ==========      ==========\n");
		printf("\n");
		if (user.year >= 1 && user.year <= 4) {
			printf("                                        사용자의 학년                       %d 학년\n", user.year);
		}
		else {
			printf("                                        사용자의 학년                     정보 없음\n");
		}
		printf("\n");
		if (user.major != "") {
			printf("                                        사용자의 전공           %20s\n", user.major);
		}
		else {
			printf("                                        사용자의 전공                     정보 없음\n");
		}
		printf("\n");
		printf("                                        이번 학기 최대 학점                 %2d 학점\n", user.credit);
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		if (checkNum == 0) {
			printf("\n                       당신의 학년을 입력해 주세요. 0을 입력하면 취소됩니다. >>> ");
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
			printf("\n                       당신의 전공을 입력해 주세요. >>> ");
			scanf("%s", &getMajor);
			strcmp(user.major, getMajor);
			checkNum++;
		}
		else if (checkNum == 2) {
			printf("\n                       당신의 이번 학기 최대 수강 가능 학점을 입력해 주세요. >>> ");
			scanf("%d", &getCredit);
			user.credit = getCredit;
			checkNum++;
		}
		else if (checkNum == 3) {
			printf("\n                       사용자의 정보를 입력하고 있습니다... 기다려 주세요...");
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
		printf("                         ==========     ==========     교양  키워드     ==========      ==========\n");
		printf("\n");
		for (int i = 0; i < 5; i++) {
			if (list[i] == NULL)
				printf("                                        [ %d ]                          키워드 없음\n", i + 1);
			else
				printf("                                        [ %d ]                  %20s\n", i + 1, list[i]);
		}
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		printf("                         교양으로 듣고 싶은 키워드를 입력해주세요. (현재 %d개) >>> ", a + 1);
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

static int* create_timetable(Schedule* sche) {
	FILE* data = fopen("교과목.txt", "r"); //파일 읽어오기
	Lecture lec;
	LecArray lec_array[MAX_LECTURE] = { 0, }; //구조체의 인덱스 번호랑 가중치 있는 array,
	LecArray major_insert[MAX_LECTURE] = { 0, }; //구조체의 인덱스 번호랑 가중치 있는 array,
	LecArray basic_insert[MAX_LECTURE] = { 0, }; //교양 삽입에 필요한 어레이
	Preference(*user_preference)[20];
	int use_lec_index[MAX_LECTURE];
	int idx = 0;

	UserInfo user_info;
	user_info = get_UserInfo();
	int canUseCredit = user_info.credit;

	/*
	for (int i = 0; i < MAX_LECTURE; i++) {
		lec = lec_search(i);
		if (strstr(lec.cmp_clf, "전") != NULL)	//전공일 경우,
			lec_array[idx] = weight_setting_major(lec, user_info);
		else									//교양일 경우,
			lec_array[idx] = weight_setting_basic(lec, user_preference);
		idx++;
	}

	for (int i = 0, j = 0; i < idx; i++)
	{
		if (lec_array[i].weight > 0)
		{
			basic_insert[j].index = lec_array[i].index; //원하는 인덱스를 삽입

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