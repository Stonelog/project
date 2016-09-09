#pragma once 
#include <vector>
#include <string>

template <typename K,typename V>
struct HashTableNode
{
	K						_key;
	V						_value;
	HashTableNode<K, V>*	_next;

	HashTableNode(const K& key, const V& value)
		: _key(key)
		, _value(value)
		, _next(NULL)
	{ }
};

template <typename K>
class __HashFunc
{
public:
	size_t operator()(const K& key)
	{
		return key;
	}
};

template <>
class __HashFunc<string>
{
public:
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}

protected:
	static size_t BKDRHash(const char * str)
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

template <typename K, typename V, class _HashFunc = __HashFunc<K> >
class  HashTable
{
	typedef HashTableNode<K, V> Node;

public:
	HashTable(size_t capacity)
		:_size(0)
	{
		_tables.resize(GetCapacity(capacity));
	};

	HashTable(const HashTable<K ,V , _HashFunc>& ht )
		: _size(ht._size)
	{
		_tables.resize(ht._tables.size());
		
		for (size_t i = 0; i < ht._tables.size(); ++i)
		{
			if (ht._tables[i] != NULL)
			{
				Node* cur = ht._tables[i];
				Node* NewNode = new Node(ht._tables[i]->_key, ht._tables[i]->_value);
				Node* TailNode = NewNode;

				_tables[i] = NewNode;
				cur = cur->_next;

				while (cur)
				{
					Node* Node1 = new Node(cur->_key, cur->_value);
					TailNode->_next = Node1;
					TailNode = TailNode->_next;

					cur = cur->_next;
				}
			}
		}
	};

	HashTable<K, V, _HashFunc> operator = (const HashTable<K, V, _HashFunc>& ht)
	{
		if (this != &ht)
		{
			HashTable<K, V, _HashFunc> temp(ht);

			_tables.swap(temp._tables);
			swap(_size, temp._size);
		}
		return *this;
	}

	void Insert(const K& key ,const V& value)
	{
		CheckCapacity();

		size_t index = HashFunc(key, _tables.size());
		Node* cur = _tables[index];

		while (cur)
		{
			if (cur->_key == key)
			{
				return;
			}
			cur = cur->_next;
		}

		Node* NewNode = new Node(key, value);
		NewNode->_next = _tables[index];
		_tables[index] = NewNode;

		_size++;
	}

	Node* Find(const K& key)
	{
		size_t index = HashFunc(key, _tables.size());

		Node* cur = _tables[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next;
		}

		return NULL;
	}

	bool Remove(const K& key)
	{
		size_t index = HashFunc(key ,_tables.size());
		Node* cur = _tables[index];
		if (cur == NULL)
		{
			return false;
		}

		if (cur->_key == key)
		{
			_tables[index] = cur->_next;
			delete cur;
			cur = NULL;

			return true;
		}

		Node* prev = cur;
		while (cur)
		{
			if (cur->_key == key)
			{
				prev->_next = cur->_next;
				delete cur;
				cur = NULL;

				return true;
			}

			prev = cur;
			cur = cur->_next;
		}

		return false;
	}

	~HashTable()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			if (_tables[i] != NULL)
			{
				Destory(&_tables[i]);
			}
		}
	}

protected:

	void Destory(Node** head)
	{
		Node* cur = *head;
		Node* next = NULL;

		while (cur)
		{
			next = cur->_next;
			delete cur;
			cur = next;
		}
	}

	size_t GetCapacity(const size_t& capacity)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		size_t i = 0;
		for (i = 0; i < 28; ++i)
		{
			if (capacity < _PrimeList[i])
			{
				return _PrimeList[i];
			}
		}

		if (capacity == _PrimeList[i - 1])
		{
			return _PrimeList[i - 1];
		}
	}

	void CheckCapacity()
	{
		if (_size == _tables.size())
		{
			size_t capacity = GetCapacity(_tables.size());
			HashTable<K, V> temp(capacity);

			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				size_t index = temp.HashFunc(cur->_key, capacity);

				temp._tables[index] = cur;
			}
			_tables.swap(temp._tables);
		}
	}

	size_t HashFunc(const K& key, const size_t& capacity)
	{
		//_HashFunc ha;
		//return ha(key) % capacity;
		return _HashFunc()(key) % capacity;
	}

private:
	vector<Node*>   _tables;
	size_t			_size;
};


