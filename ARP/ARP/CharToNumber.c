
#include "CharToNumber.h"

int ChToNu(unsigned char ch)
{
	int num1 = 0;
	switch (ch)
	{
	case '0':
		num1 = 0;
		break;
	case '1':
		num1 = 1;
		break;
	case '2':
		num1 = 2;
		break;
	case '3':
		num1 = 3;
		break;
	case '4':
		num1 = 4;
		break;
	case '5':
		num1 = 5;
		break;
	case '6':
		num1 = 6;
		break;
	case '7':
		num1 = 7;
		break;
	case '8':
		num1 = 8;
		break;
	case '9':
		num1 = 9;
		break;
	case 'A':
	case 'a':
		num1 = 10;
		break;
	case 'B':
	case 'b':
		num1 = 11;
		break;
	case 'C':
	case 'c':
		num1 = 12;
		break;
	case 'D':
	case 'd':
		num1 = 13;
		break;
	case 'E':
	case 'e':
		num1 = 14;
		break;
	case 'F':
	case 'f':
		num1 = 15;
		break;
	default:
		break;
	}
	return num1;
}

unsigned int CharToNumber(unsigned char ch1, unsigned char ch2)
{
	int num1 = 0;
	int num2 = 0;

	num1 = ChToNu(ch1);
	num2 = ChToNu(ch2);

	return num1 * 16 + num2;
}

long pow(int num, int N)
{
	if (N == 0)
	{
		return 1;
	}
	return num *  pow(num, N - 1);
}

long doTwoByte(FILE * fp)
{
	long num = 0;
	long ret = 0;
	char ch = 0;

	for (int i = 3; i >= 0; i--)
	{
		fread(&ch, 1, 1, fp);
		num = ChToNu(ch);
		ret += num * pow(16, i);
	}
	return ret;
}

long doOneByte(FILE * fp)
{
	long num = 0;
	long ret = 0;
	char ch = 0;

	for (int i = 1; i >= 0; i--)
	{
		fread(&ch, 1, 1, fp);
		num = ChToNu(ch);
		ret += num * pow(16, i);
	}
	return ret;
}

void doBlank(FILE * fp)
{
	unsigned char ch1;
	fread(&ch1, 1, 1, fp);

	while (ch1 == ' ' || ch1 == '\n' || ch1 == '\r')
	{
		fread(&ch1, 1, 1, fp);
		NULL;
	}
	fseek(fp, -1, SEEK_CUR);
}

long doIp(FILE * fp)
{
	long num = 0;
	long ret = 0;
	char ch = 0;

	for (int i = 7; i >= 0; i--)
	{
		fread(&ch, 1, 1, fp);
		num = ChToNu(ch);
		ret += num * pow(16, i);
	}
	return ret;
}


