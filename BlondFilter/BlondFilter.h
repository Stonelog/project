#pragma once
#include "MapBit.h"
#include "HashTable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

template <typename K>
struct _HashFunc1
{
public:
	size_t operator ()(const K& key)
	{
		return SDBMHash(key.c_str());
	}
protected:
	size_t SDBMHash(const char *str)
	{
		    register size_t hash = 0;
		    while (size_t ch = (size_t)*str++)
		    {
			        hash = 65599 * hash + ch;
		         //hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		    }
		    return hash;
	}
};

template <typename K>
struct _HashFunc2
{
public:
	size_t operator ()(const K& key)
	{
		return ELFHash(key.c_str());
	}

protected:
	size_t ELFHash(const char *str)
	{
		static const size_t TotalBits = sizeof(size_t)* 8;
		static const size_t ThreeQuarters = (TotalBits * 3) / 4;
		static const size_t OneEighth = TotalBits / 8;
		static const size_t HighBits = ((size_t)-1) << (TotalBits - OneEighth);
		register size_t hash = 0;
		size_t magic = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = (hash << OneEighth) + ch;
			if ((magic = hash & HighBits) != 0)
			{
				hash ^= (magic >> ThreeQuarters);
				hash &= ~magic;
			}
			return hash;
		}
	}
};

template<typename K>
struct _HashFunc3
{
public:
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}

protected:
	size_t BKDRHash(const char * str)
	{

		unsigned int seed = 131; // 31 131 1313 13131 131313 
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}
};

template<typename K>
struct _HashFunc4
{
public:
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}

protected:
	size_t RSHash(const char * str)
	{
		size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

template<typename K>
struct _HashFunc5
{
public:
	size_t operator()(const string& key)
	{
		return APHash(key.c_str());
	}

protected:
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

template<typename K>
struct _HashFunc6
{
public:
	size_t operator()(const string& key)
	{
		return JSHash(key.c_str());
	}

protected:
	size_t JSHash(const char* str)
	{
		if (!*str)
		{
			return 0;
		}
		size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
};

template<typename K = string, 
class HashFunc1 = _HashFunc1<K> ,
class HashFunc2 = _HashFunc2<K> ,
class HashFunc3 = _HashFunc3<K> ,
class HashFunc4 = _HashFunc4<K> ,
class HashFunc5 = _HashFunc5<K> >
class BondFilter
{
public:
	BondFilter(size_t capacity)
		: _bitMap(capacity)
		,_capacity(capacity)
	{ }

	void Set(const K& key)
	{
		size_t hash1 = HashFunc1()(key);
		_bitMap.Set(hash1%_capacity);

		size_t hash2 = HashFunc2()(key);
		_bitMap.Set(hash2%_capacity);

		size_t hash3 = HashFunc3()(key);
		_bitMap.Set(hash3%_capacity);

		size_t hash4 = HashFunc4()(key);
		_bitMap.Set(hash4%_capacity);

		size_t hash5 = HashFunc5()(key);
		_bitMap.Set(hash5%_capacity);
	}

	bool Test(const K& key)
	{
		size_t hash1 = HashFunc1()(key);
		bool h1 = _bitMap.Test(hash1%_capacity);
		if (!h1)
		{
			return false;
		}

		size_t hash2 = HashFunc2()(key);
		bool h2 = _bitMap.Test(hash2%_capacity);
		if (!h2)
		{
			return false;
		}

		size_t hash3 = HashFunc3()(key);
		bool h3 = _bitMap.Test(hash3%_capacity);
		if (!h3)
		{
			return false;
		}

		size_t hash4 = HashFunc4()(key);
		bool h4 = _bitMap.Test(hash4%_capacity);
		if (!h4)
		{
			return false;
		}

		size_t hash5 = HashFunc5()(key);
		bool h5 = _bitMap.Test(hash5%_capacity);
		if (!h5)
		{
			return false;
		}

		return true;
	}

private:
	BitMap		_bitMap;
	size_t		_capacity;
};

#define _SIZE_ 1024

void BolndFilterTest()
{
	BondFilter <string>			bf(_SIZE_);
	HashTable <string,string>	ht(_SIZE_);

	FILE *fp = NULL;
	char buf[_SIZE_];
	memset(buf, 0, sizeof(buf));
	int index = 0;
	char ch = 0;

	if ((fp = fopen("log.txt", "r")) == NULL)
	{
		printf("Can not open this file");
		system("pause");
	}

	//while (!feof(fp))
	//{
	//	ch = fgetc(fp);
	//	buf[index++] = ch;
	//	if (ch == '\n' && index != 0)
	//	{
	//		buf[index - 1] = '\0';
	//		bf.Set(buf);

	//		cout << buf << endl;
	//		memset(buf, 0, sizeof(buf));
	//		index = 0;
	//	}
	//	//fputc(ch, fh);
	//	//putchar(ch);
	//}
	char line[_SIZE_];
	char *pTail = NULL;
	char *pValue = NULL;

	while (fgets(line, _SIZE_, fp))
	{
		if ((pValue = strchr(line, '&'))) { *(pValue++) = '\0'; }
		if ((pTail = strchr(line, '\r'))) { *pTail = '\0'; }
		if ((pTail = strchr(line, '\n'))) { *pTail = '\0'; }

		ht.Insert(line, pValue);
		bf.Set(line);
		cout << line << "  "<<pValue;
	}
	fclose(fp);

	bool flag = true;

	while (flag)
	{
		memset(line, 0, sizeof(line));
		cin >> line;
		if (!bf.Test(line))
		{
			cout << "In file log.txt no find this world !" << endl;
		}
		else
		{
			HashTableNode<string, string> *ret = ht.Find(line);
			cout << ret->_key << " : " << ret->_value << endl;
		}
	}
}


