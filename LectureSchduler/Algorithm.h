#pragma once

#include "schedule.h"
#include "lecture.h"

#pragma warning(disable:6031)

#define MAX_CREDIT 21 //최대 학점 (21학점)
#define MAX_DP 10 //DP에 게산할 물건 수


//강의 인덱스, 학점, 가중치를 가지고 있음
typedef struct LecArray
{
	int index;		//강의 인덱스
	int credit;		//학점
	int weight;		// 가중치
}LecArray;

//가방 내용물을 구현하기 위한 스트럭쳐: 무게와 index list
typedef struct KnapsackArray
{
	int weight;
	int index[MAX_CREDIT];	//최대 학점 이상의 수업을 넣으면 가방은 무조건 터짐
	int knapsackCount;		//가방에 몇 개의 수업이 들어있는지 count하는 용도
}KnapsackArray;

typedef char Preference;	//선호 교양의 키워드를 담을 배열의 틀

typedef struct UserInfo
{
	int year;
	char major[MAX_LEN];
	int maxCredit;
}UserInfo;

int getCredit(UserInfo user) //유저의 최대학점 입력받아서 값 return
{
	return user.maxCredit;
}

UserInfo ask_major_console();

Preference* ask_basic_console();

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
	return ask_basic_console();
}


//학년과 이름을 물어보고 이를 가지고 있는 구조체를 반환함
UserInfo ask_major()
{
	return ask_major_console();
}

//(수정필요) 전공 Lecture를 넣어서, 학년, 전공에 맞는지 판단하고, 맞으면 가중치 10과 인덱스를 반환함.
LecArray weight_setting_major(Lecture lec, UserInfo user)
{
	LecArray la = { 0, };
	la.index = lec.index;
	la.credit = lec.credit;

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
LecArray weight_setting_basic(Lecture lec, Preference(*user)[20])
{
	LecArray la = { 0, };

	la.index = lec.index;
	la.credit = lec.credit;

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

//가중치가 있는 모든 강의들을 DP를 이용해 sche를 반환
Schedule DynamicProgrammingScheduling(LecArray lecture[MAX_LECTURE], UserInfo user)
{

	// DP에 서용할 가중치 배열[강의(물건)][강의 학점(무게)] {}
	int maxCredit;
	if (user.maxCredit < MAX_CREDIT) {
		maxCredit = user.maxCredit;
	}
	else {
		maxCredit = MAX_CREDIT;
	}
	KnapsackArray DP[MAX_LECTURE + 1][MAX_CREDIT + 1] = { 0, };
	Schedule sche = { {0,}, {0,}, {0,}, {0,}, {0,} };
	Lecture lec;

	KnapsackArray beforeKnapsack = { 0, };
	KnapsackArray newKnapsack = { 0 , };
	int a = 0;
	for (int i = 1; i < MAX_DP + 1; i++)
	{
		for (int DLC = 1; DLC < maxCredit + 1; DLC++) //임시 가방 무게에서 최대 가방 무게까지 for문에 의해 설정된 변수, Dynamic Limit Credit
		{
			beforeKnapsack = DP[i - 1][DLC]; //이전 값을 지니고 있는 가방
			newKnapsack.weight = DP[i - 1][DLC - lecture[i].credit].weight + lecture[i].weight; //새로 담을 때 가중치
			if (DLC < lecture[i].credit) //학점을 넣을 수 없을 
				newKnapsack.knapsackCount = DP[i - 1][0].knapsackCount;
			else
				newKnapsack.knapsackCount = DP[i - 1][DLC - lecture[i].credit].knapsackCount;



			for (int i = 0; i < newKnapsack.knapsackCount; i++)
			{
				printf("index : %d\t", newKnapsack.index[i]);
			}
			printf("count: %d\n", newKnapsack.knapsackCount);

			if (lecture[i].credit > DLC) //강의의 크기가 임시 크기보다 크다면
			{
				//강의를 넣지 않음
				DP[i][DLC] = beforeKnapsack;
			}
			else
			{
				if (can_insert(lec_search(lecture[i].index), sche)) // 강의를 넣을 수 있으면
				{
					if (beforeKnapsack.weight >= newKnapsack.weight) //강의를 넣는것보다 넣지 않은게 이득이면
					{
						DP[i][DLC] = beforeKnapsack;
					}
					else
					{
						newKnapsack.index[newKnapsack.knapsackCount] = lecture[i].index;
						newKnapsack.knapsackCount++;
						DP[i][DLC] = newKnapsack;
						//DP[i][DLC].weight = newKnapsack.weight;
						//DP[i][DLC].index[DP[i][DLC].knapsackCount++] = lecture[i].index;
						printf("index ; %d\n", lecture[i].index);
					}
				}
				else
				{
					//강의를 넣지 않음
					DP[i][DLC] = beforeKnapsack;
				}
			}


			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < maxCredit + 1; k++)
				{
					printf("[%d]", DP[j][k].weight);
				}
				printf("\n");
			}
		}

		printf("==============a: %d\n", a++);
	}

	int count = DP[MAX_DP][maxCredit].knapsackCount;
	int weight = DP[MAX_DP][maxCredit].weight;
	printf("count %d\n:", count);
	printf("weight %d\n:", weight);

	for (int i = 0; i < DP[MAX_DP][maxCredit].knapsackCount; i++)
	{
		printf("index : %d\t", DP[MAX_DP][maxCredit].index[i]);
	}
	printf("\n");

	for (int i = 0; i < count; i++)
	{
		lec = lec_search(DP[MAX_DP][maxCredit].index[i]);
		sche = push_lec(lec, sche);
	}

	return sche;

}

