#pragma once

#include "schedule.h"
#include "lecture.h"

#pragma warning(disable:6031)

#define MAX_CREDIT 21 //�ִ�����
#define MAX_DP 10 //DP�� �Ի��� ���� ��


//���� �ε���, ����, ����ġ�� ������ ����
typedef struct LecArray
{
	int index;		//���� �ε���
	int credit;		//����
	int weight;		// ����ġ
}LecArray;

//���� ���빰�� �����ϱ� ���� ��Ʈ����: ���Կ� index list
typedef struct KnapsackArray
{
	int weight;
	int index[MAX_CREDIT];	//�ִ� ���� �̻��� ������ ������ ������ ������ ����
	int knapsackCount;		//���濡 �� ���� ������ ����ִ��� count�ϴ� �뵵
}KnapsackArray;

typedef char Preference;	//��ȣ ������ Ű���带 ���� �迭�� Ʋ

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
	la.credit = lec.credit;

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
	la.credit = lec.credit;

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

//����ġ�� �ִ� ��� ���ǵ��� DP�� �̿��� sche�� ��ȯ
Schedule DynamicProgrammingScheduling(LecArray lecture[MAX_LECTURE])
{
	
	// DP�� ������ ����ġ �迭[����(����)][���� ����(����)] {}
	KnapsackArray DP[MAX_LECTURE+1][MAX_CREDIT + 1] = { 0, };
	Schedule sche = { {0,}, {0,}, {0,}, {0,}, {0,} };
	Lecture lec;

	KnapsackArray beforeKnapsack = { 0, };
	KnapsackArray newKnapsack = { 0 , };
	int a = 0;
	for (int i = 1; i < MAX_DP+1; i++)
	{
		for (int DLC = 1; DLC < MAX_CREDIT+1; DLC++) //�ӽ� ���� ���Կ��� �ִ� ���� ���Ա��� for���� ���� ������ ����, Dynamic Limit Credit
		{
			beforeKnapsack = DP[i - 1][DLC]; //���� ���� ���ϰ� �ִ� ����
			newKnapsack.weight = DP[i - 1][DLC - lecture[i].credit].weight + lecture[i].weight; //���� ���� �� ����ġ
			if (DLC < lecture[i].credit) //������ ���� �� ���� ��
				newKnapsack.knapsackCount = DP[i - 1][0].knapsackCount;
			else
				newKnapsack.knapsackCount = DP[i - 1][DLC - lecture[i].credit].knapsackCount;
			
			

			for (int i = 0; i < newKnapsack.knapsackCount; i++)
			{
				printf("index : %d\t", newKnapsack.index[i]);
			}
			printf("count: %d\n", newKnapsack.knapsackCount);

			if (lecture[i].credit > DLC) //������ ũ�Ⱑ �ӽ� ũ�⺸�� ũ�ٸ�
			{
				//���Ǹ� ���� ����
				DP[i][DLC] = beforeKnapsack;
			}
			else
			{
				if (can_insert(lec_search(lecture[i].index), sche)) // ���Ǹ� ���� �� ������
				{
					if (beforeKnapsack.weight >= newKnapsack.weight) //���Ǹ� �ִ°ͺ��� ���� ������ �̵��̸�
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
					//���Ǹ� ���� ����
					DP[i][DLC] = beforeKnapsack;
				}
			}


			for (int j = 0; j < 10; j++)
			{
				for (int k = 0; k < MAX_CREDIT + 1; k++)
				{
					printf("[%d]", DP[j][k].weight);
				}
				printf("\n");
			}
		}

		printf("==============a: %d\n", a++);
	}

	int count = DP[MAX_DP][MAX_CREDIT].knapsackCount;
	int weight = DP[MAX_DP][MAX_CREDIT].weight;
	printf("count %d\n:" , count);
	printf("weight %d\n:", weight);

	for (int i = 0; i < DP[MAX_DP][MAX_CREDIT].knapsackCount; i++)
	{
		printf("index : %d\t", DP[MAX_DP][MAX_CREDIT].index[i]);
	}
	printf("\n");

	for (int i = 0; i < count; i++)
	{
		lec = lec_search(DP[MAX_DP][MAX_CREDIT].index[i]);
		sche = push_lec(lec, sche);
	}

	return sche;

}

