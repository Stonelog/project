#pragma once  

#include "Heap.h"

template <typename T>
struct HuffmanTreeNode
{
	T  _weight;
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;

	HuffmanTreeNode(const T& weight)
		:_weight(weight)
		, _left(NULL)
		, _right(NULL)
	{	}
};

template <typename T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;

public:
	HuffmanTree(const T* a, size_t n, const T& invalid)
		:_root(NULL)
	{
		struct  Compare
		{
			bool operator ()(const Node* left, const Node* right)
			{
				return left->_weight < right->_weight;
			}
		};

		Heap<Node*, Compare> minHeap;

		for (size_t i = 0; i < n; ++i)
		{
			if (a[i] != invalid)
			{
				Node *temp = new Node(a[i]);
				minHeap.Push(temp);
			}
		}

		while (minHeap.Size() > 1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;

			minHeap.Push(parent);
		}

		_root = minHeap.Top();
	}

	Node* GetRoot()
	{
		return _root;
	}

private:

	Node*  _root;
};

void Test()
{
	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	HuffmanTree<int>  huf(a, 10,'#');
}