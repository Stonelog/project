#pragma once 
#include <iostream>
using namespace std;
#include <vector>
#include <assert.h>

template <typename T>
struct Less
{
	bool operator () (const T& left, const T& right)
	{
		return left < right;
	}
};

template <typename T>
struct Greate
{
	bool operator () (const T& left, const T& right)
	{
		return left > right;
	}
};

template <typename T,class Compare = Less<T>>
class Heap
{
public:
	Heap()
	{
		_a.resize(0);
	}

	Heap(const T* a , int size)
	{
		assert(a);

		for (int i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		
		for (int i = (size - 2) / 2; i >= 0; --i)
		{
			AdjustDown(i,size);
		}
	}

	void Push(const T& x)
	{
		_a.push_back(x);
		Adjustup(_a.size() - 1);
	}

	void Pop()
	{
		int size = _a.size();
		if (size == 0)
		{
			return;
		}

		swap(_a[0], _a[size -1]);
		_a.pop_back();

		AdjustDown(0, _a.size());
	}

	const T& Top()
	{
		if (_a.size() == 0)
		{
			throw;
		}
		return _a[0];
	}
	 
	size_t Size()
	{
		return _a.size();
	}

	void Display()
	{
		int size = _a.size();
		for (int i = 0; i <size; i++)
		{
			cout << _a[i] << "  ";
		}
		cout << endl;
	}

protected:

	void Adjustup(int child)
	{
		int parent = (child - 1) / 2;

		Compare com;
		while (child > 0)
		{
			if (com(_a[child], _a[parent]))
			{
				swap(_a[parent], _a[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void AdjustDown(int parent,int size)
	{
		int child = 2 * parent + 1;

		Compare com;

		while (child < size)
		{
			if ((child +1 ) < size && com(_a[child + 1] ,_a[child]))
			{
				child++;
			}
			if (com(_a[child], _a[parent]))
			{
				swap(_a[parent], _a[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				break;
			}
		}
	}

private:
	vector<T> _a;
};

void HeapTest()
{
	int arr[] = { 49, 38, 65, 97, 76, 13, 27 };

	Heap<int, Greate<int>> hp(arr, sizeof(arr) / sizeof(arr[0]));
	hp.Display();

	hp.Push(100);
	hp.Display();

	hp.Pop();
	hp.Display();

	getchar();
}

template <typename T >
class PriorityQueue
{
public:
	void Push(const T& x)
	{
		hp.Push(x);
	}

	void Pop()
	{
		hp.Pop();
	}

	const T& Top()
	{
		return hp.Top();
	}

private:
	Heap<T, Greate<T>> hp;
};

void AdjustDown(int *a, int size,int parent)
{
	assert(a);
	int child = 2 * parent + 1;

	while (child < size)
	{
		if ( (child + 1) < size && a[child+1] > a[child] )
		{
			child++;
		}

		if (a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}

}

void HeapSort(int *a , int size)
{
	if (NULL == a || size <= 0)
	{
		assert(a);
		return;
	}

	for (int i = (size - 2) / 2; i >= 0; --i)
	{
		AdjustDown(a, size, i);
	}

	for (int end = size - 1; end > 0; --end)
	{
		swap(a[end],a[0]);
		AdjustDown(a, end, 0);
	}
}

void HeapSortTest()
{
	int arr[] = { 49, 38, 65, 97, 76, 13, 27 };

	HeapSort(arr, sizeof(arr) / sizeof(arr[0]));

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;

	getchar();
}