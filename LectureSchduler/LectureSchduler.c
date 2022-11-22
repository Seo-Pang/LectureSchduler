//"교과목.txt에 있는 2022년 2학기 수업 1341개를 세팅 및 추천하는 프로그램.
// 주의 : 메모장 저장 시 인코딩을 ANSI로 해야 한글이 안깨집니다.

#include "schedule.h"
#include "lecture.h"
#include "Algorithm.h"


int main()
{
	Schedule sche = { {0,}, {0,}, {0,}, {0,}, {0,} };
	Lecture lec;
	int lec_index_array[MAX_LECTURE] = { 0, }; //구조체의 인덱스 번호만 있는 array,
	int idx = 0;
	

	for (int i = 0; i < MAX_LECTURE; i++)
	{
		lec = lec_search(i); //원하는 인덱스를 삽입

		printf("%5d ", i); //실행중인지 확인

		if (strstr(lec.department, "게임전공") != NULL)
		{
			lec_index_array[idx] = i;
			idx++;
		}

		if (!strcmp(lec.name, "공간에대한인문학적이해"))
		{
			lec_index_array[idx] = i;
			idx++;
		}
	}
	
	printf("%d개를 탐색\n\n", idx);

	for (int i = 0; i < idx; i++)
	{
		lec = lec_search(lec_index_array[i]); //원하는 인덱스를 삽입
		
		lec_print(lec);
	}

	lec = lec_search(lec_index_array[0]);
	sche = push_lec(lec, sche);
	lec = lec_search(lec_index_array[1]);
	sche = push_lec(lec, sche);

	lec = lec_search(604);

	lec_print(lec);
	sche = push_lec(lec, sche);

	sche_print(sche);

	sche = delete_lec(lec_index_array[0], sche);
	
	sche_print(sche);

	printf("\n\n");
	printf("lec size : %d\n", (int)sizeof(Lecture));
	printf("sche size : %d\n", (int)sizeof(Schedule));
	return 0;
}


//나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
