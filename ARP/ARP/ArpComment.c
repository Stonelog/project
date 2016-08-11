
#include "ArpComment.h"

void doReadArp(FILE *read, ARP *arp)
{
	assert(read);
	assert(arp);

	doBlank(read);
	arp->Hard_Type = doTwoByte(read);  //��ȡHard_Type

	doBlank(read);
	arp->Protocol_Type = doTwoByte(read);  //��ȡProtocol_Type

	doBlank(read);
	arp->Hard_Length = doOneByte(read);  //��ȡHard_Length

	doBlank(read);
	arp->Protocol_Length = doOneByte(read);  //��ȡProtocol_Length

	doBlank(read);
	arp->Oper = doTwoByte(read);  //��ȡOper

	unsigned char ch[2];
	doBlank(read);
	for (int i = 0; i < 6; i++)   //��ȡSrc_MAC
	{
		fread(ch, 2, 1, read);
		arp->Src_MAC[i] = CharToNumber(ch[0], ch[1]);
	}

	doBlank(read);
	arp->Src_Ip.Ip = doIp(read);  //��ȡSrc_Ip

	doBlank(read);
	for (int i = 0; i < 6; i++)   //��ȡDest_MAC
	{
		fread(ch, 2, 1, read);
		arp->Dest_MAC[i] = CharToNumber(ch[0], ch[1]);
	}

	doBlank(read);
	arp->Dest_Ip.Ip = doIp(read);  //��ȡDest_Ip
}

void doWriteArp(FILE *write, ARP *arp)
{
	fprintf(write, "Hard_Type: 0x");
	fprintf(write, "%04x ", arp->Hard_Type);
	JustHard_Type(write, arp->Hard_Type);
	fprintf(write, "\n");

	fprintf(write, "Protocol_Type : 0x");
	fprintf(write, "%04x ", arp->Protocol_Type);
	JustProtocol_Type(write, arp->Protocol_Type);
	fprintf(write, "\n");

	fprintf(write, "Hard_Length : 0x");
	fprintf(write, "%02x ", arp->Hard_Length);
	fprintf(write, "\n");

	fprintf(write, "Protocol_Length : 0x");
	fprintf(write, "%02x ", arp->Protocol_Length);
	fprintf(write, "\n");

	fprintf(write, "Oper : 0x");
	fprintf(write, "%04x ", arp->Oper);
	if (arp->Oper == 1)
	{
		fprintf(write, " (Request) ");
	}
	if (arp->Oper == 2)
	{
		fprintf(write, " (Reply) ");
	}
	fprintf(write, "\n");

	fprintf(write, "Src_MAC : 0x");
	for (int i = 0; i < 6; i++)
	{
		fprintf(write, "%02x", arp->Src_MAC[i]);
	}
	fprintf(write, " ( 6 Byte )");
	fprintf(write, "\n");

	fprintf(write, "Src_Ip :  0x");
	fprintf(write, "%x", arp->Src_Ip);
	fprintf(write, "  ( %d.%d.%d.%d )", arp->Src_Ip.Ip1, arp->Src_Ip.Ip2, arp->Src_Ip.Ip3, arp->Src_Ip.Ip4);
	fprintf(write, "\n");

	fprintf(write, "Dest_MAC: 0x");
	for (int i = 0; i < 6; i++)
	{
		fprintf(write, "%02x", arp->Dest_MAC[i]);
	}
	fprintf(write, " ( 6 Byte )");
	fprintf(write, "\n");

	fprintf(write, "Dest_Ip : 0x");
	fprintf(write, "%x", arp->Dest_Ip);
	fprintf(write, "  ( %d.%d.%d.%d )", arp->Dest_Ip.Ip1, arp->Dest_Ip.Ip2, arp->Dest_Ip.Ip3, arp->Dest_Ip.Ip4);
	fprintf(write, "\n");
}

void doArpComment(FILE * read, FILE *write)
{
	ARP arp;

	doReadArp(read, &arp);

	doWriteArp(write, &arp);
}
