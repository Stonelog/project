
#include "ArpFrame.h"

void doFrameHead(FILE * read, FILE *write)
{
	Ethernet_Frame_Head frame;

	unsigned char ch[2];

	for (int i = 0; i < 6; i++)   //¶ÁÈ¡Dest_MAC
	{
		fread(ch, 2, 1, read);
		frame.Dest_MAC[i] = CharToNumber(ch[0], ch[1]);
	}

	doBlank(read);
	for (int i = 0; i < 6; i++)    //¶ÁÈ¡Src_MAC
	{
		fread(ch, 2, 1, read);
		frame.Src_MAC[i] = CharToNumber(ch[0], ch[1]);
	}

	doBlank(read);
	frame.Protocol_Type = doTwoByte(read);  //¶ÁÈ¡Protocol_Type

	fprintf(write, "Dest_MAC: 0x");
	for (int i = 0; i < 6; i++)
	{
		fprintf(write, "%02x", frame.Dest_MAC[i]);
	}
	fprintf(write, " ( 6 Byte )");
	fprintf(write, "\n");

	fprintf(write, "Src_MAC : 0x");
	for (int i = 0; i < 6; i++)
	{
		fprintf(write, "%02x", frame.Src_MAC[i]);
	}
	fprintf(write, " ( 6 Byte )");
	fprintf(write, "\n");

	fprintf(write, "Protocol_Type : 0x");
	fprintf(write, "%04x ", frame.Protocol_Type);
	JustProtocol_Type(write, frame.Protocol_Type);
	fprintf(write, "\n");
}

void doAnalysisWork(FILE * read, FILE *write)
{
	doFrameHead(read, write);

	doArpComment(read, write);
}

void ConmmentAnalysis()
{
	FILE *write = NULL;
	FILE *read = fopen("log.txt", "rb");
	if (NULL == read)
	{
		printf("Can not for read");
		exit(EXIT_FAILURE);
	}

	write = fopen("analysis.txt", "w");
	if (NULL == write)
	{
		fclose(read);
		printf("Can not for write");
		exit(EXIT_FAILURE);
	}
	doAnalysisWork(read, write);

	fclose(read);
	fclose(write);
}

