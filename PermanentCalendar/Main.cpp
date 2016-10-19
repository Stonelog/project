#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "CTDate.h"
#include  <time.h>
#include "menu.h"
#include <conio.h>
#include <Windows.h>

////////////////////////////////////////
#define UP			72
#define DOWN		80
#define PAGEUP		73
#define PAGEDOWN	81
#define S			115

int main()
{
	time_t nowtime;
	struct tm *timeinfo = NULL;

	time(&nowtime);
	timeinfo = localtime(&nowtime);

	CTDate now(timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	CTDate date;

	char *d[7] = { "��", "һ", "��", "��", "��", "��", "��" };
	int year = 0;
	int month = 0;

	while (true)
	{
		system("CLS");
		menu();

		cout << "Please Enter Your Choice :";
		int choice = 0;
		cin >> choice;

		switch (choice)
		{
		case 1:
			//�����������ѯ�����12���·� (����Ļ��ӡ������·�)
			cout << "Please input the year of calender you want to know :";
			cin >> year; 
			date.PrintYear(year);
			break;
		case 2:
			//�����������ѯ�����ݺ;�����·�(����Ļ��ӡ���꣬�����µ��·�)
			cout << "Please input the year and month you want to know :";
			cin >> year; cin >> month;
			date.Print(year, month);
			break;
		case 3:
			//�����������ѯ�����ݺ��µ��·��Լ������һ��(�ж��Ƿ�Ϊ�������գ�������ڼ�)
			cout << "Please input the year ,month and day you want to know :";
			cin >> date;
			if (date.IsFes())
			{
				cout << date << "�ǹ�������!�������" << date - now << "��!" << setw(4);
			}
			else
			{
				cout << date << "���ǹ�������!�������" << date - now << "��!" << setw(4);
			}
			cout << "����" << d[date.wh_day()] << endl;
			break;
		case 4:
		{
			system("CLS");
			//����whileѭ����λ�ã�ʹ�ÿ��Բ������ˢ�µ����ڽڵ�
			CTDate dt(timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
			while (1)
			{
				system("CLS");
				cout << "������ " << dt << " ����"<<d[dt.wh_day()] << endl;
				dt.Print(dt.GetYear(), dt.GetMonth());

				creation();

				int ch = 0;
				ch = _getch();
				switch (ch)
				{
				case UP:
					printf("�㰴�µ����ϼ���1������....\n");
					Sleep(1000);
					dt++;
					break;
				case DOWN:
					printf("�㰴�µ����¼���1������....\n");
					Sleep(1000);
					dt--;
					break;
				default:
					break;
				}
				if (ch == 27)
				{
					break;
				}
			}
			break;
		}
		case 5:
		{
			char ch = 0;
			while (ch != 27)
			{
				system("CLS");
				cout << "�� ESC ���� " << endl;
				time(&nowtime);
			    timeinfo = localtime(&nowtime);

			    printf("%d-%d-%d %d:%d:%d \n", \
				timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
				timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

				if (_kbhit())
				{
				   ch = _getch();
			    }
			}
			break;
		}
		case 0:
			return 0;
			break;
		default:
			break;
		}

		cout << endl;
		system("pause");
	}

	return 0;
}
