#pragma once

#include <iostream>
using namespace std;
#include <iomanip>

class CTDate
{
	friend ostream& operator <<(ostream &_cout, const CTDate &d);
	friend istream& operator >>(istream &_cin, CTDate &d);

public:

	CTDate(int year = 1900, int month = 1, int day = 1)
		: m_year(year)
		, m_month(month)
		, m_day(day)
	{
		if ((year < 1900) ||
			(month <= 0 || month > 12) ||
			day < 0 && day > DaysInMonth(year, month))
		{
			m_year = 1900;
			m_month = 1;
			m_day = 1;
		}
	}

	CTDate(const CTDate &d)
		: m_year(d.m_year)
		, m_month(d.m_month)
		, m_day(d.m_day)
	{  }

	int wh_day()
	{
		//�����κ�һ��Ϊ���ڼ��Ĺ�ʽ: S=X+(X/4)-(X/100)+(X/400)+C;   X--��Ԫ��-1��C--����Ԫ�������յ�����
		CTDate NewYearDay(m_year, 1, 1);
		int X = m_year - 1;
		int C = (*this) - NewYearDay + 1;
		int S = X + X / 4 - X / 100 + X / 400 + C;

		return	S % 7;
	}

	//�ж�Month��Day���Ƿ��ǹ������գ��Ƿ���1,���򷵻�0
	int IsFes()
	{
		if (m_day == 1)
		{
			if (m_month == 1 || m_month == 4 ||
				m_month == 5 || m_month == 6 ||
				m_month == 7 || m_month == 8 || m_month == 10)
				return 1;
		}
		if ((m_month == 3 && m_day == 12) ||
			(m_month == 2 && m_day == 14) ||
			(m_month == 5 && m_day == 4) ||
			(m_month == 9 && m_day == 10) ||
			(m_month == 12 && m_day == 25))
		{
			return 1;
		}
		return 0;
	}

	void Print(int y, int m);

	void PrintYear(int y);

	CTDate operator+(int d);

	CTDate operator-(int d);

	int operator -(const CTDate &d);

	CTDate& operator=(const CTDate &d);

	CTDate& operator++(); //ǰ��	

	CTDate operator++(int);//����

	CTDate& operator--(); //ǰ��

	CTDate operator--(int); //����

	bool operator > (const CTDate &d);

	bool operator == (const CTDate &d);

	bool operator <(const CTDate &d);

	int GetYear() { return m_year; };
	int GetMonth() { return m_month;  };
	int GetDay() {  return m_day; };

private:

	bool IsLeap(int year)
	{
		return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	int DaysInMonth(int year, int month)
	{
		int day[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		if (IsLeap(year) && month == 2)
		{
			day[month]++;
		}

		return day[month];
	}

private:
	int m_year;
	int m_month;
	int m_day;
};
