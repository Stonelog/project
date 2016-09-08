#pragma once
#include "MapBit.h"
#include <string>

template <typename K>
struct _HashFunc1
{
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

	size_t operator ()(const K& key)
	{
		return SDBMHash(key.c_str());
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

template<typename K = string, class HashFunc1 = _HashFunc1<K>, class HashFunc2 = _HashFunc2<K> >
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
	
		return true;
	}

private:
	BitMap _bitMap;
	size_t _capacity;
};

void BolndFilterTest()
{
	BondFilter<string> bf(100);
	bf.Set("www.baidu.com");
	bf.Set("name");
//	bf.Set("happy");

	cout << bf.Test("www.baidu.com") << " ";
	cout << bf.Test("name") << " ";
	cout << bf.Test("happy") << endl;
}


