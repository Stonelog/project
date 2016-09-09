#pragma once
#include <vector>

class BitMap
{
public:
	BitMap(size_t capacity)
		: _size(0)
	{ 
		_tables.resize((capacity >> 5) + 1);
	};

	bool Set(const size_t& key)
	{
		size_t index = key >> 5;
		size_t num = key % 32;

		if ( ( (_tables[index]) & (1 << num) ) == 0)
		{
			_tables[index] |= (1 << num);
			++_size;
			return true;
		}
		return false;
	}

	bool ReSet(const size_t& key)
	{
		size_t index = key >> 5;
		size_t num = key % 32;

		if (((_tables[index]) & (1 << num)) != 0)
		{
			_tables[index] &= (~(1 << num));
			--_size;
			return true;
		}
		return false;
	}

	bool Test(const size_t& key)
	{
		size_t index = key >> 5;
		size_t num = key % 32;

		size_t ret = ((_tables[index]) & (1 << num));
		if (ret == 0)
		{
			return false;
		}
		return true;
	}

	size_t Size()
	{
		return _size;
	}

	//~BitMap();

private:
	vector<size_t> _tables;
	size_t _size;
};


