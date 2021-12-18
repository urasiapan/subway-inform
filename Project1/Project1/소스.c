#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

struct subway {
	int number; //��ȣ��
	int arrival_time; //���� �ִ� ���� �����ϴµ� �ɸ��� �ð�(��)
	char terminus[20]; //������
	double bustle; //�պ�� ����(%)
};

// ���� �ִ� ���� �ǽð� �̹� ����, ���� ����, �ٴ������� ����ü
struct subway first[4] = { { 1, 15, "û����", 85.5 }, { 2, 10, "����", 70 }, {3, 15, "�����Ա�", 20 } ,{4,13,"�����",60 } }; //�̹� ���� ����
struct subway next[4] = { { 1, 30, "������", 50 }, { 2,30, "�Ǵ��Ա�", 90 }, {3, 30, "�����Ա�", 10 }, {4, 20, "������", 50} }; //���� ���� ����
struct subway next_next[4] = { { 1, 60, "�����", 25 }, { 2, 45, "����", 60 }, {3, 45, "���", 10 }, {4, 40, "���·ɿ�", 30} }; //�ٴ��� ���� ����

// //1~4ȣ�� �뼱
char subway_hosun[4][30][15] = { { "���￪", "��û��", "������", "����3����", "����5����", "���빮��", "�����տ�", "�ż�����", "���⵿��", "û������", "���迪", "����뿪","â����","�����꿪","ȸ�濪","�ҿ�꿪" },
	{ "��û��", "�������Ա���", "������3����", "������4����", "���빮��忪", "�Ŵ翪", "��սʸ���", "�սʸ���", "�Ѿ�뿪", "�Ҽ���", "������", "�Ǵ��Ա���" },
	{"��������", "�溹�ÿ�","����3����", "������3����","�湫�ο�", "�����Ա���" , "�����", "��ȣ��", "������", "�б�����", "�Ż翪", "�����"},
	{"�����","��迪","�����","â����","�ֹ���","������","�̾ƿ�","�̾ƻ�Ÿ���","������","���ſ����Ա���","�Ѽ����Ա���","��ȭ��","���빮��","���빮��忪","�湫�ο�","����","ȸ����","���￪","�����Ա���","�ﰢ����","�ſ�꿪","���̿�","���ۿ�","�ѽŴ��Ա���","��翪","���·ɿ�"} };


//1~4ȣ�� �� ������ �ð� ����
int time_interval_hosun[4][30] = { { 2, 3, 1, 2, 2, 1, 2, 2, 2, 2, 2,1,2,2,2 },
	{ 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
	{2,2,2,2,1,2,2,1,2,2,3},
	{2,2,2,2,3,2,2,2,3,2,2,2,2,2,1,2,2,2,2,1,2,4,3,2,1} }; 

//�˸� ��� �Լ�
void alarm(int sec)
{
	Sleep(sec * 1000 * 60);
	printf("\a");
}

//����ö �ȳ� ���� ���� ��� �Լ�
void subway_inform(int use_hosun, char my_place[15]) 
{
	int number; //1~6 ������
	char want_place[10]; //������
	int time_to_want = 0; //���������� �ɸ��� �ð�
	int i, j;

	do {
		printf("1. �̹� ������ ���� �ִ� ���� �����ϴµ� �ɸ��� �ð�\n");
		printf("2. �̹� ������ ������\n");
		printf("3. �̹� ������ ���� ���������� �ɸ��� �ð�\n");
		printf("4. �̹� ������ �պ�� ����\n");
		printf("5. ���� ������ �ٴ��� ������ ���� Ȯ���ϱ�\n");
		printf("6. ����\n");

		printf("��ȣ�� �Է��ϼ���.\n");
		scanf("%d", &number);

		if (number == 1)
			printf("%d��\n", first[use_hosun - 1].arrival_time); 
		else if (number == 2)
			printf("%s\n", first[use_hosun - 1].terminus); 
		else if (number == 3) {
			printf("���� ������ ���� �Է��ϼ���.\n");//���� ������ ���������� ���µ� �ɸ��� �ð� ���
			scanf("%s", want_place);
			int w, m, t; //want_place�ε���, my_place�ε���, temporary
			for (i = 0; i < 30; i++)
			{
				if (strcmp(want_place, subway_hosun[use_hosun - 1][i]) == 0) 
					w = i;
				if (strcmp(my_place, subway_hosun[use_hosun - 1][i]) == 0) 
					m = i;
			}

			if (m > w) //my_place �ε����� �� ū ��� ���� �ٲ۴�.
				t = m, m = w, w = t;

			for (i = m; i < w; i++)
				time_to_want += time_interval_hosun[use_hosun - 1][i]; 

			printf("%s���� %s���� %d�� �ɸ��ϴ�.\n", my_place, want_place, time_to_want);

		}
		else if (number == 4)
			printf("%.1f%%\n", first[use_hosun - 1].bustle);
		else if (number == 5) {
			printf("���� ����: %d�� �� ����, �������� %s, %.1f%%�պ�\n", next[use_hosun - 1].arrival_time, next[use_hosun - 1].terminus, next[use_hosun - 1].bustle); 
			printf("�ٴ��� ����: %d�� �� ����, �������� %s, %.1f%%�պ�\n", next_next[use_hosun - 1].arrival_time, next_next[use_hosun - 1].terminus, next_next[use_hosun - 1].bustle);
		}
		else if (number == 6)
			break;
		else
			printf("1���� 6������ ���ڸ� �Է��ϼ���.\n");
	} while (number != 6);

}




int main(void) {
	int ans;
	int use_hosun;
	char my_place[15];
	char check_place[10];
	int check = -1;

	printf("������ �ִ� ����ö ���� '(   )��' �������� �Է��ϼ���\n");
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
			printf("������ �ִ� ����ö ���� '(   )��' �������� �ùٸ��� �Է��ϼ���\n");
		}
	}while (check == -1);

	printf("�̿��� ����ö�� �� ȣ������ ���ڸ� �Է��ϼ���.(1~4�� �Է��ϼ���)\n");
	while (1) {
		scanf("%d", &use_hosun);
		if (0<use_hosun && use_hosun<5)
			break;
		else
			printf("1~4ȣ�� �� �ϳ��� ���ڸ� �Է��ϼ���.\n");
	}


	while (1) {
		printf("����ö�� ž�� �����̸� 1, ����ö�� ž�� ���̸� 2�� �Է����ּ���.\n");
		scanf("%d", &ans);

		//����ö ž�� ����
		if (ans == 1) {
			subway_inform(use_hosun, my_place);
			break;
		}

		//����ö ž�� ��. //���������� �������� �ð� ���� �˸� ��� ����
		else if (ans == 2) {
			int time_to_before_want = 0;
			char want_place[10];
			printf("���� ������ ���� �Է��ϼ���.\n");//���� ���� �������� �Ÿ��� ���� �ð� ���
			scanf("%s", want_place);
			int w, m, t; //want_place�ε���, my_place�ε���, temporary
			for (int i = 0; i < 30; i++)
			{
				if (strcmp(want_place, subway_hosun[use_hosun - 1][i]) == 0) 
					w = i;
				if (strcmp(my_place, subway_hosun[use_hosun - 1][i]) == 0) 
					m = i;
			}

			if (m > w) //my_place �ε����� �� ū ��� ���� �ٲ۴�.
				t = m, m = w, w = t;

			for (int i = m; i < w - 1; i++)
				time_to_before_want += time_interval_hosun[use_hosun - 1][i]; 
			printf("%d�� ��, %s �� �ٷ� �� ���� �����ϸ� �˶��� �︳�ϴ�.\n", time_to_before_want, want_place);
			alarm(time_to_before_want);

			break;
		}

		//1,2�� ���� �߸� �Է�
		else
			printf("����ö�� ž�� �����̸� 1, ����ö�� ž�� ���̸� 2�� �Է����ּ���.\n");
	}


	return 0;
}