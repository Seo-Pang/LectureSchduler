// 주의 : 메모장 저장 시 인코딩을 ANSI로 해야 한글이 안깨집니다.

#include "schedule.h"
#include "lecture.h"


int main()
{
	Schedule sche = { {0,}, {0,}, {0,}, {0,}, {0,} };
	Lecture lec;
	int lec_index[MAX_LECTURE] = { 0, };
	int idx = 0;

	
	for (int i = 0; i < MAX_LECTURE; i++)
	{
		lec = lec_search(i); //원하는 인덱스를 삽입

		printf("%d ", i); //실행중인지 확인

		if (!strcmp(lec.name, "교육통계"))
		{
			lec_index[idx] = i;
			idx++;
		}
	}
	
	printf("%d개를 탐색\n\n", idx);

	for (int i = 0; i < idx; i++)
	{
		lec = lec_search(lec_index[i]); //원하는 인덱스를 삽입
		
		lec_print(lec);
	}

	lec = lec_search(lec_index[0]);
	sche = push_lec(lec, sche);
	lec_print(lec);

	sche_print(sche);


	
	printf("\n\n");
	printf("lec size : %d\n", (int)sizeof(Lecture));
	printf("sche size : %d\n", (int)sizeof(Schedule));
	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
