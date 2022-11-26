#pragma once

#include "schedule.h"
#include "lecture.h"

#pragma warning(disable:6031)

#define MAX_QUESTION

typedef char Preference; //선호 교양의 키워드를 담을 배열의 틀

typedef struct UserInfo
{
	int year;
	char major[MAX_LEN];
}UserInfo;

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


/// <summary>
/// 교양으로 듣고싶은 키워드를 5개 설정하여 해당 문자열 5개의 배열을 리턴, MAXBUFFER : 20
/// </summary>
/// <returns></returns>
Preference* ask_basic()
{
	static Preference list[5][20];

	printf("교양으로 듣고 싶은 키워드를 5개 입력하세요. (중복 가능)\n");
	for (int i = 0; i < 5; i++)
	{
		printf("키워드 %d : ", i + 1);
		scanf("%s", list[i]);
		printf("%s\n", list[i]);
	}

	return (Preference*) list;
}


//학년과 이름을 물어보고 이를 가지고 있는 구조체를 반환함
UserInfo ask_major()
{
	UserInfo user = { 0, "" };
	printf("당신의 전공은 무엇입니까?\n");
	scanf("%s", user.major);
	printf("당신의 학년은 무엇입니까?\n");
	scanf("%d", &user.year);

	return user;
}

//(수정필요) 전공 Lecture를 넣어서, 학년, 전공에 맞는지 판단하고, 맞으면 가중치 10과 인덱스를 반환함.
LecArray weight_setting_major(Lecture lec, UserInfo user)
{
	LecArray la = { 0, };
	la.index = lec.index;

	if (strstr(lec.department, user.major) != NULL && lec.year == user.year)
		la.weight = 10;
	else
		la.weight = 0;

	return la;
}


/// <summary>
/// 입력받은 키워드를 바탕으로 교양강의의 가중치를 증가시킴
/// </summary>
/// <param name="lec"></param>
/// <param name="user"></param>
/// <returns></returns>
LecArray weight_setting_basic(Lecture lec, Preference (*user)[20])
{
	LecArray la = { 0, };

	la.index = lec.index;


	if (strstr(lec.cmp_clf, "교필") || strstr(lec.cmp_clf, "교선") != NULL)
	{
		//printf("caught : %s\n", lec.name);
		for (int i = 0; i < 5; i++)
		{
			if (strstr(lec.name, user[i]) != NULL)
				la.weight++;
		}
	}



	return la;
}

