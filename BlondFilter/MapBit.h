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


void BitMapTest()
{
	BitMap  bm(100);
	bm.Set(13);
	bm.Set(54);
	bm.Set(64);

	cout << bm.Test(13) << " ";
	cout << bm.Test(54) << " ";
	cout << bm.Test(64) << endl;

	bm.ReSet(54);
	cout << bm.Test(13) << " ";
	cout << bm.Test(54) << " ";
	cout << bm.Test(64) << endl;

	cout << bm.Size() << endl;
}



