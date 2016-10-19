#pragma once

#include<stdio.h>

void menu()
{
	cout << endl;
	cout << "*******************************************************" << endl;
	cout << "*	1 . 查询该年的12个月份                              " << endl;
	cout << "*	2 . 查询年的年份和具体的月份                        " << endl;
	cout << "*	3 . 判断一个日期是否为公历节日并输出星期几	        " << endl;
	cout << "*	4 . 按上下键更换日期	                            " << endl;
	cout << "*	5 . 显示时间	                                    " << endl;
	cout << "*	0 . 退出	                                        " << endl;
	cout << "*******************************************************" << endl << endl;
	//printf("1.日历显示->\n");
	//printf("2.日历查询->\n");
	//printf("3.修改日期->\n");
	//printf("4.日期备忘录->\n");
	//printf("5.退出\n");
}

void menu1()
{
	printf("显示日期时间\n");
	printf("显示本月日历表\n");
	printf("返回主菜单\n");
}

void menu2()
{
	printf("显示当前日期\n");
	printf("查询N天后日期\n");
	printf("查询N天前日期\n");
	printf("查看距离某日期的天数\n");
	printf("返回主菜单\n");
}

void week()
{
	printf("  SUN  MON  TUES  WED THUR  FRI  SAT  \n");
}

void creation()
{
	printf("\n");
	printf("按下PageDown可以看下一个月的日历         ");
	printf("按下PageUp可以看上一个月的日历\n");
	//printf("上键昨天       ");
	//printf("下键明天\n");
	printf("按 ESC 键退出\n");
}