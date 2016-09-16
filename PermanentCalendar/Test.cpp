#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "CTDate.h"
#include  <time.h>
#include  <string>

int main()
{
	time_t nowtime;
	struct tm *timeinfo;
	time(&nowtime);
	timeinfo = localtime(&nowtime);

	CTDate now(timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
	CTDate date;

	string d[7] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
	int sum = 0;
	int year = 0;
	int month = 0;

	while (true)
	{
		cout << endl;
		cout << "****************************************************** " << endl;
		cout << "*	1 . The year of calender " <<endl;
		cout << "*	2 . The year and month of calender  "  << endl;
		cout << "*	3 . The date where is the week " << endl;
		cout << "******************************************************"  << endl << endl;

		int choice = 0;
		cout << "Please Enter Your Choice :";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Please input the year of calender you want to know :";
			cin >> year;
			cout << endl;
			cout << "--------The calender of " << year << "--------" << endl;
			date.PrintYear(year);
			break;
		case 2:
			cout << "Please input the year and month you want to know :";
			cin >> year; 
			cin >> month;
			date.Print(year, month);
			break;
		case 3:
			cout << "Please input the year ,month and day you want to know :";
			cin >> date;
			sum = date - now;
			if (date.IsFes())
			{
				cout << date << " is Festive  " << sum << " days !" << setw(4);
			}
			else
			{
				cout << date << "  not is Festive " << sum << " days !" << setw(4);
			}
			cout <<  d[date.wh_day()] << endl;
			break;
		default:
			break;
		}

		cout << endl;
	}

	return 0;
}
