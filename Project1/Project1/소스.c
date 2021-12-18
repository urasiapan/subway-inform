#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

struct subway {
	int number; //몇호선
	int arrival_time; //내가 있는 역에 도착하는데 걸리는 시간(분)
	char terminus[20]; //종착역
	double bustle; //붐비는 정도(%)
};

// 내가 있는 역의 실시간 이번 열차, 다음 열차, 다다음열차 구조체
struct subway first[4] = { { 1, 15, "청량리", 85.5 }, { 2, 10, "성수", 70 }, {3, 15, "동대입구", 20 } ,{4,13,"당고개역",60 } }; //이번 열차 정보
struct subway next[4] = { { 1, 30, "동묘앞", 50 }, { 2,30, "건대입구", 90 }, {3, 30, "동대입구", 10 }, {4, 20, "길음역", 50} }; //다음 열차 정보
struct subway next_next[4] = { { 1, 60, "광운대", 25 }, { 2, 45, "성수", 60 }, {3, 45, "잠원", 10 }, {4, 40, "남태령역", 30} }; //다다음 열차 정보

// //1~4호선 노선
char subway_hosun[4][30][15] = { { "서울역", "시청역", "종각역", "종로3가역", "종로5가역", "동대문역", "동묘앞역", "신설동역", "제기동역", "청량리역", "석계역", "광운대역","창동역","도봉산역","회룡역","소요산역" },
	{ "시청역", "을지로입구역", "을지로3가역", "을지로4가역", "동대문운동장역", "신당역", "상왕십리역", "왕십리역", "한양대역", "뚝섬역", "성수역", "건대입구역" },
	{"독립문역", "경복궁역","종로3가역", "을지로3가역","충무로역", "동대입구역" , "약수역", "금호역", "옥수역", "압구정역", "신사역", "잠원역"},
	{"당고개역","상계역","노원역","창동역","쌍문역","수유역","미아역","미아삼거리역","길음역","성신여대입구역","한성대입구역","혜화역","동대문역","동대문운동장역","충무로역","명동역","회현역","서울역","숙대입구역","삼각지역","신용산역","이촌역","동작역","총신대입구역","사당역","남태령역"} };


//1~4호선 역 사이의 시간 간격
int time_interval_hosun[4][30] = { { 2, 3, 1, 2, 2, 1, 2, 2, 2, 2, 2,1,2,2,2 },
	{ 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
	{2,2,2,2,1,2,2,1,2,2,3},
	{2,2,2,2,3,2,2,2,3,2,2,2,2,2,1,2,2,2,2,1,2,4,3,2,1} }; 

//알림 기능 함수
void alarm(int sec)
{
	Sleep(sec * 1000 * 60);
	printf("\a");
}

//지하철 안내 서비스 메인 기능 함수
void subway_inform(int use_hosun, char my_place[15]) 
{
	int number; //1~6 선택지
	char want_place[10]; //목적지
	int time_to_want = 0; //목적지까지 걸리는 시간
	int i, j;

	do {
		printf("1. 이번 열차의 내가 있는 역에 도착하는데 걸리는 시간\n");
		printf("2. 이번 열차의 종착역\n");
		printf("3. 이번 열차의 나의 목적지까지 걸리는 시간\n");
		printf("4. 이번 열차의 붐비는 정도\n");
		printf("5. 다음 열차와 다다음 열차의 정보 확인하기\n");
		printf("6. 종료\n");

		printf("번호를 입력하세요.\n");
		scanf("%d", &number);

		if (number == 1)
			printf("%d분\n", first[use_hosun - 1].arrival_time); 
		else if (number == 2)
			printf("%s\n", first[use_hosun - 1].terminus); 
		else if (number == 3) {
			printf("나의 목적지 역을 입력하세요.\n");//현재 역에서 목적지까지 가는데 걸리는 시간 계산
			scanf("%s", want_place);
			int w, m, t; //want_place인덱스, my_place인덱스, temporary
			for (i = 0; i < 30; i++)
			{
				if (strcmp(want_place, subway_hosun[use_hosun - 1][i]) == 0) 
					w = i;
				if (strcmp(my_place, subway_hosun[use_hosun - 1][i]) == 0) 
					m = i;
			}

			if (m > w) //my_place 인덱스가 더 큰 경우 둘이 바꾼다.
				t = m, m = w, w = t;

			for (i = m; i < w; i++)
				time_to_want += time_interval_hosun[use_hosun - 1][i]; 

			printf("%s에서 %s까지 %d분 걸립니다.\n", my_place, want_place, time_to_want);

		}
		else if (number == 4)
			printf("%.1f%%\n", first[use_hosun - 1].bustle);
		else if (number == 5) {
			printf("다음 열차: %d분 후 도착, 종착역은 %s, %.1f%%붐빔\n", next[use_hosun - 1].arrival_time, next[use_hosun - 1].terminus, next[use_hosun - 1].bustle); 
			printf("다다음 열차: %d분 후 도착, 종착역은 %s, %.1f%%붐빔\n", next_next[use_hosun - 1].arrival_time, next_next[use_hosun - 1].terminus, next_next[use_hosun - 1].bustle);
		}
		else if (number == 6)
			break;
		else
			printf("1에서 6까지의 숫자를 입력하세요.\n");
	} while (number != 6);

}




int main(void) {
	int ans;
	int use_hosun;
	char my_place[15];
	char check_place[10];
	int check = -1;

	printf("본인이 있는 지하철 역을 '(   )역' 형식으로 입력하세요\n");
	do{
		scanf("%s", &my_place);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 30; j++)
				{
					if (strcmp(subway_hosun[i][j], my_place) == 0) {
						check = 0;
						break;
					}
				}
		if (check == -1) {
			printf("본인이 있는 지하철 역을 '(   )역' 형식으로 올바르게 입력하세요\n");
		}
	}while (check == -1);

	printf("이용할 지하철이 몇 호선인지 숫자를 입력하세요.(1~4중 입력하세요)\n");
	while (1) {
		scanf("%d", &use_hosun);
		if (0<use_hosun && use_hosun<5)
			break;
		else
			printf("1~4호선 중 하나의 숫자를 입력하세요.\n");
	}


	while (1) {
		printf("지하철을 탑승 예정이면 1, 지하철을 탑승 중이면 2를 입력해주세요.\n");
		scanf("%d", &ans);

		//지하철 탑승 예정
		if (ans == 1) {
			subway_inform(use_hosun, my_place);
			break;
		}

		//지하철 탑승 중. //목적지역의 전역에서 시간 맞춰 알림 기능 제공
		else if (ans == 2) {
			int time_to_before_want = 0;
			char want_place[10];
			printf("나의 목적지 역을 입력하세요.\n");//현재 역과 목적지의 거리에 따른 시간 계산
			scanf("%s", want_place);
			int w, m, t; //want_place인덱스, my_place인덱스, temporary
			for (int i = 0; i < 30; i++)
			{
				if (strcmp(want_place, subway_hosun[use_hosun - 1][i]) == 0) 
					w = i;
				if (strcmp(my_place, subway_hosun[use_hosun - 1][i]) == 0) 
					m = i;
			}

			if (m > w) //my_place 인덱스가 더 큰 경우 둘이 바꾼다.
				t = m, m = w, w = t;

			for (int i = m; i < w - 1; i++)
				time_to_before_want += time_interval_hosun[use_hosun - 1][i]; 
			printf("%d분 후, %s 의 바로 전 역에 도착하면 알람이 울립니다.\n", time_to_before_want, want_place);
			alarm(time_to_before_want);

			break;
		}

		//1,2외 숫자 잘못 입력
		else
			printf("지하철을 탑승 예정이면 1, 지하철을 탑승 중이면 2를 입력해주세요.\n");
	}


	return 0;
}