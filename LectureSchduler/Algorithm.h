#pragma once

#include "schedule.h"
#include "lecture.h"

#define MAX_QUESTION

typedef int UserInfo;

/*
이 헤더파일에 구현해야 할 것은 0 - 1 배낭문제
0-1 배낭문제를 쓰기 위해서는 Dynamic Programming을 사용해야 한다.
그러기 위해서는 표가 필요하다.

학과 학년을 입력하면 이에 맞는 전공을 배정해주는 알고리즘.
질문을 받고 강의를 추려내는 알고리즘, 혹은 가중치를 설정하는 알고리즘이 필요 //개설학과를 찾아 관련 분야를 제외
원하는 공강을 설정하면 그 공강에 따라 가중치를 변화하게 하는 알고리즘이 필요 //공강에 해당하는 수업은 가중치 0

그 가중치에 따라 강의를 Schedule 구조체에 넣어 DP를 실행하는 알고리즘이 필요

DP를 실행하기 위해 새로운 DP 표를 만들어야 한다.
*/


//질문에 따라 리스트를 만들어 반환하고, 이를 가중치 설정에 사용함.
UserInfo *ask_basic()
{
	UserInfo list[10] = { 0, };

	printf("수강해야 할 기초 교양을 입력해주세요.\n");
	scanf("%d", &list[0]);

	printf("수강해야 할 균형 교양 분야를 입력해주세요.\n");
	scanf("%d", &list[1]);

	printf("수강해야 할 핵심 교양 분야 를 입력해주세요.\n");
	scanf("%d", &list[2]);

	//여기부터는 일반교양 추천 선호도 조사
	printf("질문을 합니다[1~9].\n");
	scanf("%d", &list[3]);

	printf("질문을 합니다[1~9].\n");
	scanf("%d", &list[4]);

	printf("질문을 합니다[1~9].\n");
	scanf("%d", &list[5]);

	printf("질문을 합니다[1~9].\n");
	scanf("%d", &list[6]);

	printf("질문을 합니다[1~9].\n");
	scanf("%d", &list[7]);

	printf("질문을 합니다[1~9].\n");
	scanf("%d", &list[8]);

	printf("질문을 합니다[1~9].\n");
	scanf("%d", &list[9]);

	return list;
}



//Lecture을 넣어서, 이를 인덱스와 가중치를 가진 LecArray로 반환함.
LecArray weight_setting_basic(Lecture lec, UserInfo user)
{
	LecArray la = { 0, };

	la.index = lec.index;
	if (strstr(lec.cmp_clf, "교필") != NULL)
	{
		la.weight = 9;
	}
	
	
	return la;
}

