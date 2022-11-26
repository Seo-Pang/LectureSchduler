#pragma once

#include "schedule.h"
#include "lecture.h"

#pragma warning(disable:6031)

#define MAX_QUESTION

typedef char Preference; //��ȣ ������ Ű���带 ���� �迭�� Ʋ

typedef struct UserInfo
{
	int year;
	char major[MAX_LEN];
}UserInfo;

/*
�� ������Ͽ� �����ؾ� �� ���� 0 - 1 �賶����
0-1 �賶������ ���� ���ؼ��� Dynamic Programming�� ����ؾ� �Ѵ�.
�׷��� ���ؼ��� ǥ�� �ʿ��ϴ�.

�а� �г��� �Է��ϸ� �̿� �´� ������ �������ִ� �˰���.
������ �ް� ���Ǹ� �߷����� �˰���, Ȥ�� ����ġ�� �����ϴ� �˰����� �ʿ� //�����а��� ã�� ���� �о߸� ����
���ϴ� ������ �����ϸ� �� ������ ���� ����ġ�� ��ȭ�ϰ� �ϴ� �˰����� �ʿ� //������ �ش��ϴ� ������ ����ġ 0

�� ����ġ�� ���� ���Ǹ� Schedule ����ü�� �־� DP�� �����ϴ� �˰����� �ʿ�

DP�� �����ϱ� ���� ���ο� DP ǥ�� ������ �Ѵ�.
*/


/// <summary>
/// �������� ������ Ű���带 5�� �����Ͽ� �ش� ���ڿ� 5���� �迭�� ����, MAXBUFFER : 20
/// </summary>
/// <returns></returns>
Preference* ask_basic()
{
	static Preference list[5][20];

	printf("�������� ��� ���� Ű���带 5�� �Է��ϼ���. (�ߺ� ����)\n");
	for (int i = 0; i < 5; i++)
	{
		printf("Ű���� %d : ", i + 1);
		scanf("%s", list[i]);
		printf("%s\n", list[i]);
	}

	return (Preference*) list;
}


//�г�� �̸��� ����� �̸� ������ �ִ� ����ü�� ��ȯ��
UserInfo ask_major()
{
	UserInfo user = { 0, "" };
	printf("����� ������ �����Դϱ�?\n");
	scanf("%s", user.major);
	printf("����� �г��� �����Դϱ�?\n");
	scanf("%d", &user.year);

	return user;
}

//(�����ʿ�) ���� Lecture�� �־, �г�, ������ �´��� �Ǵ��ϰ�, ������ ����ġ 10�� �ε����� ��ȯ��.
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
/// �Է¹��� Ű���带 �������� ���簭���� ����ġ�� ������Ŵ
/// </summary>
/// <param name="lec"></param>
/// <param name="user"></param>
/// <returns></returns>
LecArray weight_setting_basic(Lecture lec, Preference (*user)[20])
{
	LecArray la = { 0, };

	la.index = lec.index;


	if (strstr(lec.cmp_clf, "����") || strstr(lec.cmp_clf, "����") != NULL)
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

