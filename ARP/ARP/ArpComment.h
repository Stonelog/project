#pragma once

#include "CharToNumber.h"
#include "justType.h"

#include <assert.h>


typedef  union  ip  // 4�ֽ�
{
	int Ip;
	struct
	{
		unsigned char Ip4;
		unsigned char Ip3;
		unsigned char Ip2;
		unsigned char Ip1;
	};
}ip;

typedef struct ARP
{
	unsigned short Hard_Type;			//2�ֽ�
	unsigned short Protocol_Type;		//2�ֽ�
	unsigned char Hard_Length;			//1�ֽ�
	unsigned char Protocol_Length;		//1�ֽ�
	unsigned short Oper;                 //2�ֽ�
	unsigned char Src_MAC[6];   //6�ֽ�
	ip Src_Ip;                  //4�ֽ�
	unsigned char Dest_MAC[6];  //6�ֽ�
	ip Dest_Ip;                 //4�ֽ�

}ARP;

void doReadArp(FILE *read, ARP *arp);

void doWriteArp(FILE *write, ARP *arp);

void doArpComment(FILE * read, FILE *write);