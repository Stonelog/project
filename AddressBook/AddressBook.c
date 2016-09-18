#define  _CRT_SECURE_NO_WARNINGS 0
//ʵ��һ��ͨѶ¼��
//ͨѶ¼�����Ա���1000���˵���Ϣ��ͨѶ¼���ܴ�С��̬��������
//ÿ���˵���Ϣ������
//�������Ա����䡢�绰��סַ
//�ṩ������
//1>	�����ϵ����Ϣ
//2>	ɾ��ָ����ϵ����Ϣ
//3>	����ָ����ϵ����Ϣ
//4>	�޸�ָ����ϵ����Ϣ
//5>	��ʾ������ϵ����Ϣ
//6>	���������ϵ��
//7>	��������������ϵ�˵���Ϣ��
//8>	���˳�����ʱ���ո���ӵ��˵���Ϣ�������ļ����´δ򿪳����ʱ��Ҫ���ҵ�����õ���Ϣ��
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <string.h>

#define INITSIZE  100
int length = 4;			//ͨѶ¼������4��
int size = 0;			//��ǰ�ܴ�Ŷ�����

typedef struct addr_book
{
	char	name[30];
	char	sex[5];
	int		age;
	char	tele[13];
	char	addr[50];
}addr_book;

void title()
{
	printf("����\t�Ա�\t����\t�绰\t\t��ַ \n");
}

void init_book(addr_book **book)
{
	(*book) = (addr_book *)malloc(INITSIZE*(sizeof(addr_book)));
	size = INITSIZE;
}

void insert( addr_book *book, const char *name1, const char *sex1,
			 const int age1, const char *tele1, const char *addr1)
{
	assert(book);
	assert(name1);
	assert(sex1);
	assert(tele1);
	assert(addr1);

	if (size < 1000)
	{
		if (length > size)
		{
			book = (addr_book *)realloc(book, 100 * sizeof (addr_book));
			assert(book);
			size += 100;
		}

		strcpy((book + length)->name, name1);
		(book + length)->age = age1;
		strcpy((book + length)->sex, sex1);
		strcpy((book + length)->tele, tele1);
		strcpy((book + length)->addr, addr1);
		length++;
		printf("Insert  Succeed !\n");
	}
	else
	{
		printf("UP TO MAX !\n");
	}
}

void find(addr_book *book, int num)
{
	assert(book);

	if (num > length  && num > 0)
	{
		printf("���˲�����! \n");
	}
	else
	{
		title();
		printf("%s", (book + num - 1)->name);
		printf("\t%s", (book + num - 1)->sex);
		printf("\t%d", (book + num - 1)->age);
		printf("\t%s", (book + num - 1)->tele);
		printf("\t\t%s ", (book + num - 1)->addr);
	}
}

void update(addr_book *book, int num)
{
	assert(book);

	if (num > length  && num > 0)
	{
		printf("���˲����� ��\n");
	}
	else
	{
		printf("������Ҫ�޸ĵ�����>:");
		scanf("%s", (book + num - 1)->name);
		printf("������Ҫ�޸ĵ��Ա�>:");
		scanf("%s", (book + num - 1)->sex);
		printf("������Ҫ�޸ĵ�����>:");
		scanf("%d", &(book + num - 1)->age);
		printf("������Ҫ�޸ĵĵ绰>:");
		scanf("%s", (book + num - 1)->tele);
		printf("������Ҫ�޸ĵĵ�ַ>:");
		scanf("%s", (book + num - 1)->addr);
	}
}

void print(addr_book *book)
{
	assert(book);

	title();
	if (length <= 0)
	{
		printf("����ϵ��!\n");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			printf("%s", (book + i)->name);
			printf("\t%s", (book + i)->sex);
			printf("\t%d", (book + i)->age);
			printf("\t%s", (book + i)->tele);
			printf("\t\t%s  \n", (book + i)->addr);
		}
	}
}

void delete(addr_book *book, int num)
{
	assert(book);

	int npos = num - 1;
	int iBegin = 0;
	if (num > length && num > 0)
	{
		printf("���˲�����! \n");
	}
	else
	{
		for (iBegin = npos; iBegin < length; iBegin++)
		{
			strcpy((book + iBegin)->name, (book + iBegin + 1)->name);
			strcpy((book + iBegin)->sex, (book + iBegin + 1)->sex);
			(book + iBegin)->age = (book + iBegin + 1)->age;
			strcpy((book + iBegin)->tele, (book + iBegin + 1)->tele);
			strcpy((book + iBegin)->addr, (book + iBegin + 1)->addr);
		}
		length--;
		printf("Delete  Succeed !\n");
	}
}

void empty(addr_book *book)
{
	int iBegin = 0;
	for (iBegin = length - 1; iBegin >= 0; iBegin--)
	{
		delete(book, iBegin);
	}
	printf("��ճɹ�!\n");
}

int cmp(const void* elem1, const void* elem2) //�ַ����ıȽ�
{
	//return  strcmp((char *)*(int *)elem1 , (char *)*(int *)elem2 );
	//�ȶ�elem1ǿ��ת��Ϊint *,�ڽ�����ȡ���ĸ��ֽڵ����ݣ�Ҳ�����ַ�����Ԫ�صĵ�ַ��ǿ��ת��Ϊ char *
	return  strcmp((char *)elem1, (char *)elem2);
}

void swap(char  *p1, char *p2, size_t sz)
{
	size_t i = 0;
	for (i = 0; i < sz; i++)
	{
		char temp = *(p1 + i);
		*(p1 + i) = *(p2 + i);
		*(p2 + i) = temp;
	}
}

void bubble_sort(void *base, size_t num, size_t width, int(*cmp)(const void* elem1, const void* elem2))
{
	int flag = num;
	int k = 0;

	while (flag)
	{
		k = flag;
		flag = 0;
		for (int iBegin = 0; iBegin < k; ++iBegin)
		{
			if (cmp((char *)base + iBegin*width, (char *)base + (iBegin + 1)*width) >0)
			{
				flag = iBegin;
				swap((char *)base + iBegin*width, (char *)base + (iBegin + 1)*width, width);
			}
		}
	}

	//size_t i = 0;
	//size_t j = 0;
	//int flag = 1;
	//for (i = 1; i < num && flag ==1;i++)
	//{
	//	flag = 0;
	//	for (j = 0; j < num - i;j++)
	//	{
	//		if (cmp((char *)base + j*width, (char *)base + (j + 1)*width ) >0)
	//		{
	//			flag = 1;
	//			swap((char *)base + j*width, (char *)base + (j + 1)*width, width );
	//		}
	//	}
	//}
}

void book_sort(addr_book *book)
{
	bubble_sort(book, length, sizeof(addr_book), cmp);
	printf("Sort  Succeed ! \n");
}

void destory(addr_book **book)
{
	free(*book);
	(*book) = NULL;
}

void readerfile(addr_book *book)
{
	FILE *pf = fopen("AddressBook.txt", "r");
	if (pf == NULL)
	{
		printf("Can not the file !");
		return;
	}

	int i = 0;
	while (i < length)
	{
		fscanf(pf, "%s", (book + i)->name);
		fscanf(pf, "%s", (book + i)->sex);
		fscanf(pf, "%d", &(book + i)->age);
		fscanf(pf, "%s", (book + i)->tele);
		fscanf(pf, "%s\n", (book + i)->addr);
		i++;
	}

	fclose(pf);
}

void writefile(addr_book *book)
{
	FILE *pf = fopen("AddressBook.txt", "w");
	if (pf == NULL)
	{
		printf("Can not the file !");
		return;
	}

	int i = 0;
	while (i < length)
	{
		fprintf(pf, "%s  ", (book + i)->name);
		fprintf(pf, "%s  ", (book + i)->sex);
		fprintf(pf, "%d  ", (book + i)->age);
		fprintf(pf, "%s  ", (book + i)->tele);
		fprintf(pf, "%s\n", (book + i)->addr);
		i++;
	}

	fclose(pf);
}

void menu()
{
	printf("\t*****************ͨѶ¼*******************\n");
	printf("\t******* 1>  �����ϵ����Ϣ          ******\n");
	printf("\t******* 2>  ɾ��ָ����ϵ����Ϣ      ******\n");
	printf("\t******* 3>  ����ָ����ϵ����Ϣ      ******\n");
	printf("\t******* 4>  �޸�ָ����ϵ����Ϣ      ******\n");
	printf("\t******* 5>  ��ʾ������ϵ����Ϣ      ******\n");
	printf("\t******* 6>  ���������ϵ��          ******\n");
	printf("\t******* 7>  ��������������ϵ�˵���Ϣ******\n");
	printf("\t******* 0>  �˳�                    ******\n");
	printf("\t******************************************\n");
}

int main()
{
	int n = 0, num = 0;
	char name1[30];
	char sex1[5];
	int age1;
	char tele1[13];
	char addr1[50];
	addr_book *book = NULL;

	init_book(&book);
	readerfile(book);

	while (1)
	{
		menu();
		printf("��ѡ��>: ");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("����������>:");
			scanf("%s", name1);
			printf("�������Ա�>:");
			scanf("%s", sex1);
			printf("����������>:");
			scanf("%d", &age1);
			printf("������绰>:");
			scanf("%s", tele1);
			printf("�������ַ>:");
			scanf("%s", addr1);
			insert(book, name1, sex1, age1, tele1, addr1);
			break;
		case 2:
			printf("��������Ҫɾ���ڼ����˵���Ϣ>:");
			scanf("%d", &num);
			delete(book, num);
			break;
		case 3:
			printf("��������Ҫ���ҵڼ����˵���Ϣ>:");
			scanf("%d", &num);
			find(book, num);
			break;
		case 4:
			printf("��������Ҫ�޸ĵڼ����˵���Ϣ>:");
			scanf("%d", &num);
			update(book, num);
			break;
		case 5:
			print(book);
			break;
		case 6:
			empty(book);
			break;
		case 7:
			book_sort(book);
			break;
		case 0:
			break;
		default:
			printf("error !");;
		}
		if (_getch() == 27 || n == 0)
		{
			break;
		}
		system("CLS");
	}
	writefile(book);//���������������Ϣ���ļ�

	destory(&book);

	system("pause");
	return 0;
}

