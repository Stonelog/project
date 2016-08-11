#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include <stdlib.h>

#include "CharToNumber.h"
#include "justType.h"

#include "ArpComment.h"

typedef struct Ethernet_Frame_Head
{
	unsigned char Dest_MAC[6];    //6×Ö½Ú
	unsigned char Src_MAC[6];     //6×Ö½Ú
	unsigned short Protocol_Type; //2×Ö½Ú

}Ethernet_Frame_Head;

void doFrameHead(FILE * read, FILE *write);

void doAnalysisWork(FILE * read, FILE *write);

void ConmmentAnalysis();