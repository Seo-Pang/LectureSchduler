#pragma once

#include "schedule.h"
#include "lecture.h"

#define MAX_QUESTION

typedef int Preference; //������ �����, �� ������ ���� ���� int ��

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


//(�����ʿ�) ������ ���� ����Ʈ�� ����� ��ȯ�ϰ�, �̸� ����ġ ������ �����. 
Preference *ask_basic()
{
	Preference list[10] = { 0, };

	printf("�����ؾ� �� ���� ������ �Է����ּ���.\n");
	scanf("%d", &list[0]);

	/* 
	//�����ؼ� weight_setting_basic() �Լ��� ȣȯ�ǰ� �ؾ���

	printf("�����ؾ� �� ���� ���� �о߸� �Է����ּ���.\n");
	scanf("%d", &list[1]);

	printf("�����ؾ� �� �ٽ� ���� �о� �� �Է����ּ���.\n");
	scanf("%d", &list[2]);

	//������ʹ� �Ϲݱ��� ��õ ��ȣ�� ����
	printf("������ �մϴ�[1~9].\n");
	scanf("%d", &list[3]);

	printf("������ �մϴ�[1~9].\n");
	scanf("%d", &list[4]);

	printf("������ �մϴ�[1~9].\n");
	scanf("%d", &list[5]);

	printf("������ �մϴ�[1~9].\n");
	scanf("%d", &list[6]);

	printf("������ �մϴ�[1~9].\n");
	scanf("%d", &list[7]);

	printf("������ �մϴ�[1~9].\n");
	scanf("%d", &list[8]);

	printf("������ �մϴ�[1~9].\n");
	scanf("%d", &list[9]);
	*/
	return list;
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


//(���� �ʿ�) ���� Lecture�� �־, �̸� �ε����� ����ġ�� ���� LecArray�� ��ȯ��.
LecArray weight_setting_basic(Lecture lec, Preference *user)
{
	LecArray la = { 0, };

	la.index = lec.index;
	if (strstr(lec.cmp_clf, "����") != NULL)
	{
		la.weight = 7;
	}
	return la;
}

