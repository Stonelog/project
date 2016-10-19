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

	char *d[7] = { "日", "一", "二", "三", "四", "五", "六" };
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
			//输入你所想查询该年的12个月份 (向屏幕打印该年的月份)
			cout << "Please input the year of calender you want to know :";
			cin >> year; 
			date.PrintYear(year);
			break;
		case 2:
			//输入你所想查询年的年份和具体的月份(向屏幕打印该年，具体月的月份)
			cout << "Please input the year and month you want to know :";
			cin >> year; cin >> month;
			date.Print(year, month);
			break;
		case 3:
			//输入你所想查询年的年份和月的月份以及具体的一天(判断是否为公历节日，输出星期几)
			cout << "Please input the year ,month and day you want to know :";
			cin >> date;
			if (date.IsFes())
			{
				cout << date << "是公历节日!距离今天" << date - now << "天!" << setw(4);
			}
			else
			{
				cout << date << "不是公历节日!距离今天" << date - now << "天!" << setw(4);
			}
			cout << "星期" << d[date.wh_day()] << endl;
			break;
		case 4:
		{
			system("CLS");
			//更改while循环的位置，使得可以不断输出刷新的日期节点
			CTDate dt(timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
			while (1)
			{
				system("CLS");
				cout << "今天是 " << dt << " 星期"<<d[dt.wh_day()] << endl;
				dt.Print(dt.GetYear(), dt.GetMonth());

				creation();

				int ch = 0;
				ch = _getch();
				switch (ch)
				{
				case UP:
					printf("你按下的是上键，1秒后更改....\n");
					Sleep(1000);
					dt++;
					break;
				case DOWN:
					printf("你按下的是下键，1秒后更改....\n");
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
				cout << "按 ESC 返回 " << endl;
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
