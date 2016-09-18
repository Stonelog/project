#define  _CRT_SECURE_NO_WARNINGS 0
//实现一个通讯录：
//通讯录最多可以保存1000个人的信息（通讯录的总大小动态增长）。
//每个人的信息包括：
//姓名、性别、年龄、电话、住址
//提供方法：
//1>	添加联系人信息
//2>	删除指定联系人信息
//3>	查找指定联系人信息
//4>	修改指定联系人信息
//5>	显示所有联系人信息
//6>	清空所有联系人
//7>	按照名字排序联系人的信息。
//8>	当退出程序时将刚刚添加的人的信息保存在文件，下次打开程序的时候要可找到保存好的信息。
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <string.h>

#define INITSIZE  100
int length = 4;			//通讯录中已有4人
int size = 0;			//当前能存放多少人

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
	printf("姓名\t性别\t年龄\t电话\t\t地址 \n");
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
		printf("该人不存在! \n");
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
		printf("该人不存在 ！\n");
	}
	else
	{
		printf("请输入要修改的姓名>:");
		scanf("%s", (book + num - 1)->name);
		printf("请输入要修改的性别>:");
		scanf("%s", (book + num - 1)->sex);
		printf("请输入要修改的年龄>:");
		scanf("%d", &(book + num - 1)->age);
		printf("请输入要修改的电话>:");
		scanf("%s", (book + num - 1)->tele);
		printf("请输入要修改的地址>:");
		scanf("%s", (book + num - 1)->addr);
	}
}

void print(addr_book *book)
{
	assert(book);

	title();
	if (length <= 0)
	{
		printf("无联系人!\n");
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
		printf("该人不存在! \n");
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
	printf("清空成功!\n");
}

int cmp(const void* elem1, const void* elem2) //字符串的比较
{
	//return  strcmp((char *)*(int *)elem1 , (char *)*(int *)elem2 );
	//先对elem1强制转化为int *,在解引用取出四个字节的内容，也就是字符串首元素的地址，强制转化为 char *
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
	printf("\t*****************通讯录*******************\n");
	printf("\t******* 1>  添加联系人信息          ******\n");
	printf("\t******* 2>  删除指定联系人信息      ******\n");
	printf("\t******* 3>  查找指定联系人信息      ******\n");
	printf("\t******* 4>  修改指定联系人信息      ******\n");
	printf("\t******* 5>  显示所有联系人信息      ******\n");
	printf("\t******* 6>  清空所有联系人          ******\n");
	printf("\t******* 7>  按照名字排序联系人的信息******\n");
	printf("\t******* 0>  退出                    ******\n");
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
		printf("请选择>: ");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("请输入姓名>:");
			scanf("%s", name1);
			printf("请输入性别>:");
			scanf("%s", sex1);
			printf("请输入年龄>:");
			scanf("%d", &age1);
			printf("请输入电话>:");
			scanf("%s", tele1);
			printf("请输入地址>:");
			scanf("%s", addr1);
			insert(book, name1, sex1, age1, tele1, addr1);
			break;
		case 2:
			printf("请输入你要删除第几个人的信息>:");
			scanf("%d", &num);
			delete(book, num);
			break;
		case 3:
			printf("请输入你要查找第几个人的信息>:");
			scanf("%d", &num);
			find(book, num);
			break;
		case 4:
			printf("请输入你要修改第几个人的信息>:");
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
	writefile(book);//程序结束，保存信息到文件

	destory(&book);

	system("pause");
	return 0;
}

