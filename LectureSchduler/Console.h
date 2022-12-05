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
	printf("                         ==========     ==========     공강 Builder     ==========      ==========\n");
	printf("\n");
	printf("\n");
	printf("                                        강의 리스트 검색중         [ %4d / %4d ]\n", a, MAX_LECTURE);
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
		printf("                         ==========     ==========     공강 Builder     ==========      ==========\n");
		printf("\n");
		printf("                                        사용자의 전공 %28s\n", user.major);
		printf("                                        사용자의 학년                      %2d 학년\n", user.year);
		printf("                                        최대 수강가능 학점                 %2d 학점\n", user.maxCredit);
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		if (inputNum == 0) {
			printf("\n                         사용자의 전공을 입력해 주세요 >>> ");
			scanf("%s", user.major);
			inputNum++;
		}
		else if (inputNum == 1) {
			printf("\n                         사용자의 학년을 입력해 주세요 >>> ");
			scanf("%d", &user.year);
			inputNum++;
		}
		else if (inputNum == 2) {
			printf("\n                         수강가능 학점을 입력해 주세요 >>> ");
			scanf("%d", &user.maxCredit);
			inputNum++;
		}
	}

	system("cls");
	for (int i = 0; i < 9; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========     공강 Builder     ==========      ==========\n");
	printf("\n");
	printf("                                        사용자의 전공 %28s\n", user.major);
	printf("                                        사용자의 학년                      %2d 학년\n", user.year);
	printf("                                        최대 수강가능 학점                 %2d 학점\n", user.maxCredit);
	printf("\n");
	printf("                         ==========     ==========     ============     ==========      ==========\n");
	printf("\n                                             사용자의 정보를 입력 중입니다...");
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
		printf("                         ==========     ==========     공강 Builder     ==========      ==========\n");
		printf("\n");
		printf("                                                    교양 키워드 리스트\n\n");
		for (int i = 0; i < inputNum; i++) {
			printf("                                        [%d]           %28s\n", (i + 1), list[i]);
		}
		printf("\n");
		printf("                         ==========     ==========     ============     ==========      ==========\n");
		printf("\n                         교양으로 들을 강의의 키워드를 입력해 주세요. (중복 가능) >>> ");
		scanf("%s", list[inputNum]);
		inputNum++;
	}

	system("cls");
	for (int i = 0; i < 10; i++) {
		printf("\n");
	}
	printf("                         ==========     ==========     공강 Builder     ==========      ==========\n");
	printf("\n");
	printf("                                                    교양 키워드 리스트\n\n");
	for (int i = 0; i < inputNum; i++) {
		printf("                                        [%d]           %28s\n", (i + 1), list[i]);
	}
	printf("\n");
	printf("                         ==========     ==========     ============     ==========      ==========\n");
	printf("\n                                              교양 리스트를 입력 중입니다...");
	Sleep(2000);
	return (Preference*)list;
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
	printf("                         ==========     ==========        시간표        ==========      ==========\n");
	printf("\n                            [요일] ");
	for (int i = 0; i < LATEST_TIME; i++) printf("%4d", i + 1);
	printf("\n                             [월]  ");
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
	printf("\n                             [화]  ");
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
	printf("\n                             [수]  ");
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
	printf("\n                             [목]  ");
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
	printf("\n                             [금]  ");
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
	printf("                         ==========     ==========      강의  정보      ==========      ==========\n\n");
	for (int i = 0; i < count_lecture; i++) {
		if (lecture_idx[i] >= 0) {
			lec = lec_search(lecture_idx[i]);
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
				return;
			}
		}
	}
}

static Schedule create_timetable(Schedule sche)
{
	FILE* data = fopen("교과목.txt", "r");
	Lecture lec;
	LecArray lec_array[MAX_LECTURE] = { 0, }; //구조체의 인덱스 번호랑 가중치 있는 array,
	LecArray major_insert[MAX_LECTURE] = { 0, }; //구조체의 인덱스 번호랑 가중치 있는 array,
	LecArray basic_insert[MAX_LECTURE] = { 0, }; //교양 삽입에 필요한 어레이
	Preference(*user_preference)[20];
	UserInfo user_info;
	int use_lec_index[MAX_LECTURE];
	int idx = 0;
	char string[MAX_LEN] = "";
	int input = 0;

	user_info = ask_major();

	user_preference = (void*)ask_basic();

	//모든 인덱스를 탐색하면서 모든 강의의 가중치를 계산
	for (int i = 0; i < MAX_LECTURE; i++)
	{
		lec = lec_search(i); //원하는 인덱스를 삽입

		check_search(i); //실행중인지 확인

		if (strstr(lec.cmp_clf, "전") != NULL)	//전공일 경우,
			lec_array[idx] = weight_setting_major(lec, user_info);
		else									//교양일 경우,
			lec_array[idx] = weight_setting_basic(lec, user_preference);
		idx++;
	}
	printf("\n%d개를 탐색\n\n", idx);


	//(수정필요) 가중치 계산하는 부분
	for (int i = 0, j = 0; i < idx; i++)
	{
		if (lec_array[i].weight > 0) //가중치가 있을 경우에만 실행
		{
			basic_insert[j].index = lec_array[i].index; //원하는 인덱스를 삽입
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