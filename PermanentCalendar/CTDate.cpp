#include "CTDate.h"

CTDate CTDate::operator+(int d)
{
	if (d < 0)
	{
		return *this - (0 - d);
	}

	CTDate temp(*this);

	temp.m_day += d;

	while (temp.m_day >  DaysInMonth(temp.m_year,temp.m_month ))
	{
		temp.m_day -= DaysInMonth(temp.m_year, temp.m_month);

		if (temp.m_month == 12)
		{
			temp.m_month = 1;
			temp.m_year++;
		}
		else
		{
			temp.m_month++;
		}
	}
	return temp;
}

CTDate CTDate::operator-(int d)
{
	if (d < 0)
	{
		return *this + (0 - d);
	}

	CTDate temp(*this);

	temp.m_day -= d;

	while (temp.m_day <= 0)
	{
		if (temp.m_month == 1)
		{
			temp.m_month = 12;
			temp.m_year--;
		}
		else
		{
			temp.m_month--;
		}

		temp.m_day += DaysInMonth(temp.m_year, temp.m_month);
	}
	return temp;
}

int CTDate::operator -(const CTDate &d)   //¼ÆËãÁ©ÈÕÆÚÖ®¼äµÄÌìÊý
{
	CTDate Max(*this);
	CTDate Min(d);
	int count = 0;

	if (Min > Max)
	{
		Min = *this;
		Max = d;
	}

	while (Min < Max)
	{
		count++;
		Min++;
	}

	return count;
}

CTDate& CTDate::operator=(const CTDate &d)
{
	if (this != &d)
	{
		m_year = d.m_year;
		m_month = d.m_month;
		m_day = d.m_day;
	}
	return *this;
}

CTDate&  CTDate::operator++() //Ç°ÖÃ++
{
	(*this) = (*this) + 1;
	return *this;
}

CTDate CTDate::operator++(int) //ºóÖÃ++
{
	CTDate temp(*this);

	(*this) = (*this) + 1;
	return temp;
}

CTDate& CTDate::operator--() //Ç°ÖÃ--
{
	(*this) = (*this) - 1;
	return *this;
}

CTDate CTDate::operator--(int) //ºóÖÃ--
{
	CTDate temp(*this);

	(*this) = (*this) - 1;
	return temp;
}

bool CTDate::operator > (const CTDate &d)
{
	if (m_year > d.m_year)
	{
		return true;
	}
	else if ((m_year == d.m_year) && (m_month > d.m_month))
	{
		return true;
	}
	else if ((m_year == d.m_year) &&
		(m_month == d.m_month) &&
		(m_day > d.m_day))
	{
		return true;
	}

	return false;
}

bool CTDate::operator == (const CTDate &d)
{
	return ((m_year == d.m_year) && (m_month == d.m_month) && (m_day == d.m_day));
}

bool CTDate::operator <(const CTDate &d)
{
	return  !((*this > d) || (*this == d));
}

ostream& operator <<(ostream &_cout, const CTDate &d)
{
	_cout << d.m_year << "-" << d.m_month << "-" << d.m_day;
	return _cout;
}

istream& operator >>(istream &_cin, CTDate &d)
{
	_cin >> d.m_year >> d.m_month >> d.m_day;
	return _cin;
}

void CTDate::Print(int year, int month)
{
	cout << "--------The calender of " << year << '/' << month << "------" << endl;

	CTDate MonthBeginDay(year, month, 1);
	CTDate NewYearDay(year, 1, 1);

	cout << setw(4) << "SUN" << setw(4) << "MON" << 
		    setw(4) << "TUE" << setw(4) << "WED" <<
			setw(4) << "THU" << setw(4) << "FRI" <<
			setw(4) << "SAT"   << endl;
	int blank = 0;
	int iBegin = 0;
	int S = 0;

	int X = year - 1;
	int C = (MonthBeginDay - NewYearDay) + 1;
	S = X + X / 4 - X / 100 + X / 400 + C;

	blank = S % 7;  //year-month-1¸
	for (iBegin = 0; iBegin < blank; iBegin++)
	{
		cout.width(4);
		cout << " ";
	}
	for (iBegin = 1; iBegin <= DaysInMonth(year, month); ++iBegin)
	{
		if (S % 7 == 6)
		{
			cout << setw(2) << resetiosflags(ios::right) << setw(4) << iBegin  << endl; 
		}
		else
		{
			cout << setw(2) << resetiosflags(ios::right) << setw(4) << iBegin;
		}
		++S;
	}
	cout << endl;
	cout << "-------------------------------------" << endl;
}

void CTDate::PrintYear(int y)  
{
	for (int month = 1; month < 13; month++) 
	{
		cout << "             " <<month << " month"<<"                      " << endl;
		Print(y, month);
		cout << endl;
	}
}


