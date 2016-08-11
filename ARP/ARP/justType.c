
#include "justType.h"

void JustHard_Type(FILE *write, unsigned short num)
{
	if (NULL == write || num <= 0 || num > 7)
	{
		return;
	}

	switch (num)
	{
	case 0x0001:
		fprintf(write, " (10Mb Ethernet)  ");  //��̫��
		break;
	case 0x0002:
		fprintf(write, " ( Experimental Ethernet )  "); //ʵ������̫��
		break;
	case 0x0003:
		fprintf(write, " ( Amateur Radio AX.25 )  "); //ҵ�����ߵ�AX.25
		break;
	case 0x0004:
		fprintf(write, " ( Proteon ProNET )  ");  //���ƻ�
		break;
	case 0x0005:
		fprintf(write, " ( Chaos )  ");  //������
		break;
	case 0x0006:
		fprintf(write, " ( IEEE 802.X )  ");
		break;
	case 0x0007:
		fprintf(write, " ( ARCNET )  "); //ARC����
		break;
	default:
		break;
	}
}

void JustProtocol_Type(FILE *write, unsigned short num)
{
	if (NULL == write)
	{
		return;
	}

	switch (num)
	{
	case 0x0800:
		fprintf(write, " ( IP Protocol )  ");  //IPЭ��
		break;
	case 0x0806:
		fprintf(write, " ( ARP Protocol)  "); //ARPЭ��
		break;
	case 0x8035:
		fprintf(write, " ( RARP Protocol)  "); //RARPЭ��
		break;
	default:
		break;
	}
}