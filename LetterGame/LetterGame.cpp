// LetterGame.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <graphics.h>
#include  <conio.h>
#include  <time.h>

void welcome()
{
	initgraph(640, 480);
	setcolor(YELLOW);
	settextstyle(64, 0, L"����");
	outtextxy(160, 50, L"��ĸ�����");

	int nColor = 255;
	while (!_kbhit())
	{
		setcolor(RGB(nColor, 0, 0));
		outtextxy(160, 250, L"�밴�����");
		nColor = nColor - 10;
		Sleep(20);
	}
}

void gamebegin()
{
	srand(time(nullptr));

	int nX = 250, nY = 0;
	int score = 0, miss = 0;
	int nSpeed = 1;

	wchar_t target = 0;
	wchar_t inputch = 0;
	wchar_t sz_score[MAXBYTE];
	wchar_t sz_miss[MAXBYTE];

	settextstyle(20, 0, L"����");
	setcolor(WHITE);
	setfillcolor(BLACK);

	while (true)
	{
		target = 'A' + rand() % 26;
		nX = rand() % 620;
		for (nY = 0; nY < 480; nY += (10 + nSpeed))
		{
			outtextxy(nX, nY, target);
			if (_kbhit())
			{
				inputch = _getch();//��ȡ��������ݣ�
				if (inputch == target || inputch == (target + 32))
				{
					bar(nX, nY, nX + 100, nY + 100);
					score++;
					if (score % 10 == 0)
					{
						nSpeed += 20;;
					}
					break;
				}
				else if (inputch == 27)
				{
					break;
				}
			}
			Sleep(40);
			bar(nX, nY, nX + 100, nY + 100);
			//left top right bottom
			swprintf_s(sz_score, L"��ǰ���� ��%d ", score);
			outtextxy(10, 10, sz_score);

			swprintf_s(sz_miss, L"��ǰmiss ��%d ", miss);
			outtextxy(10, 30, sz_miss);
		}
		if (nY >= 480)
		{
			miss++;
		}
		if (inputch == 27)
		{
			break;
		}
	}
}

void gameover()
{
	settextstyle(64, 0, L"����");
	setcolor(YELLOW);
	outtextxy(160, 250, L"Game Over !");
}

int _tmain(int argc, _TCHAR* argv[])
{
	welcome();

	cleardevice();
	gamebegin();

	cleardevice();
	gameover();

	system("pause");
	return 0;
}