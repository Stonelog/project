#pragma once

#include <iostream>
using namespace std;
#include <stack>
#include <queue>
#include <vector>
#include <assert.h>
#include <stdlib.h>

int LenMax  = 0;

template <typename T>
struct BinaryTreeNode
{
	typedef BinaryTreeNode<T> Node;

	T  _value;
	Node *_left;
	Node *_right;

	BinaryTreeNode(const T & value)
		: _value(value)
		, _left (NULL)
		, _right(NULL)
	{ }
};

template <typename T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{ }

	void Insert(const T &x)
	{
		if(NULL == _root)
		{
			_root = new Node(x);
			return ;
		}
		
		Node *parent = NULL;
		Node *cur = _root;
		while(cur)
		{
			parent = cur;
			if(cur->_value < x)
			{
				cur = cur->_right;
			}
			else if(cur->_value > x)
			{
				cur = cur->_left;
			}
			else
			{
				return ;
			}
		}

		Node *node = new Node(x);
		if(parent->_value < x)
		{
			parent->_right = node;
		}
		if(parent->_value > x)
		{
			parent->_left = node;
		}
	}

	void InOrder()
	{
		if(NULL == _root)
			return ;

		stack<Node*> sa;
		sa.push(_root);

		Node *cur = _root->_left;
		while(!sa.empty() || cur)
		{
			while(cur)
			{
				sa.push(cur);
				cur = cur->_left;
			}

			Node *top = sa.top();
			sa.pop();
			std::cout << top->_value << " ";
			cur = top->_right;
		}
		std::cout << std::endl;
	}

	int KLevelNodes(int k)
	{
		if(k <= 0 || _root == NULL)
		{
			return 0;
		}
		return _KLevelNodes(_root, k);
	}
	
	int _KLevelNodes(Node *root , int k)
	{
		if(NULL == root)
			return 0;
		if(k == 1)
		{
			return 1;
		}

		return _KLevelNodes(root->_left,k-1) + _KLevelNodes(root->_right,k-1);
	}

	int High()
	{
		if(NULL == _root)
			return 0;

		return _High(_root);
	}

	int _High(Node *root)
	{
		if(NULL == root)
		{
			return 0;
		}
		int left = _High(root->_left);
		int right = _High(root->_right);

		return left > right ? 1+left : 1+right;
	}

	void  Max()
	{
		if(NULL == _root)
		{
			return ;
		}
		maxLen(_root);
	}

	//O(N)
	int maxLen(Node *root)
	{
		if(NULL == root)
		{
			return 0;
		}

		int left = maxLen(root->_left);
		int right = maxLen(root->_right);

		if(left+right > LenMax)
		{
			LenMax = left + right;
		}
		return left > right ? 1+left : 1+right;
	}

	Node* GetCommNode(Node *node1, Node *node2)
	{
		assert(node1 && node2);
		
		vector<Node*> path1;
		GetPath(_root, node1, path1);
		size_t size1 = path1.size();

		vector<Node*> path2;
		GetPath(_root, node2, path2);
		size_t size2 = path2.size();
	
		int index1 = 0;
		int index2 = 0;
		Node *ret = NULL;

		while(index1 < size1 && index2 < size2)
		{
			if(path1[index1] == path2[index2])
			{
				ret = path1[index1];
			}
			++index1;
			++index2;
		}
		return ret;
	}

	//O(N)
	bool GetPath(Node *root, Node *FindNode, vector<Node*> &path)
	{
		assert(FindNode);
		if(NULL == root)
		{
			return false;
		}

		path.push_back(root);
		if(root == FindNode)
		{
			return true;
		}
		if(GetPath(root->_left,FindNode,path))
		{
			return true;
		}
		if(GetPath(root->_right,FindNode,path))
		{
			return true;
		}

		path.pop_back();
		return false;
	}

	Node* toList()
	{
		if(_root == NULL)
			return NULL;
	
		Node *head = _root;
		while(head->_left)
		{
			head = head->_left;
		}

		Node *prev = NULL;
		_toList(_root,prev);

		return head;
	}

	void _toList(Node *root, Node *&prev)
	{
		if(NULL  == root)
		{
			return ;
		}

		_toList(root->_left,prev);

		root->_left = prev;
		if(prev)
		{
			prev->_right = root;
		}
		prev = root;

		_toList(root->_right,prev);
	}

	bool IsEntireBinaryTree()
	{
		if(NULL == _root)
		{
			return false;
		}
		
		bool flag = true;
		queue<Node*> qu;
		qu.push(_root);

		while(!qu.empty())
		{
			Node *front = qu.front();
			qu.pop();
	
			if(front->_left)
			{
				if(flag == false)
				{
					return false;
				}
				qu.push(front->_left);
			}
			else
			{
				flag = false;
			}

			if(front->_right)
			{
				if(flag == false)
				{
					return false;
				}
				qu.push(front->_right);
			}
			else 
			{
				flag = false;
			}
		}
		return true;
	}

	Node* Find(const T& x)
	{
		if(NULL == _root)
		{
			return NULL;
		}

		Node *cur = _root;

		while(cur)
		{
			if(cur->_value > x)
			{
				cur = cur->_left;
			}
			else if(cur->_value < x)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return NULL;	
	}

//	bool IsAVLTree()
//	{
//		if(NULL == _root)
//		{
//			return true;
//		}
//
//		return _IsAVLTree(_root);
//	}
//
//	bool _IsAVLTree(Node *root)
//	{
//		if(NULL == root)
//		{
//			return true;
//		}
//
//		int left = _High(root->_left);
//		int right = _High (root->_right);
//
//		if((right - left) != root->bf)
//		{
//			return false;
//		}
//
//		return (abs(right-left) < 2) && _IsAVLTree(root->_left) && _IsAVLTree(root->_right);
//	}
//
//	bool IsRBTree()
//	{
//		if(NULL == _root)
//		{
//			return true;
//		}
//
//		Node *parent = NULL;
//		int num = 0;
//
//		int count = 0;
//		Node *node = _root;
//
//		while(node)
//		{
//		
//			if(node->_color == BLANK)
//			{
//				++count;
//			}
//			node = node->_left;
//		}
//
//		return _IsRBTree(_root,parent,count,num);
//	}
//
//	bool _IsRBTree(NOde *root, Node *&parent, const int &count,int num)
//	{
//		if(NULL == root)
//			return true;
//
//		if(parent && parent->_color == RED && root->_color == RED)
//			return false;
//
//		if(root->_color == BLANK)
//			++num;
//		if(root->_left == NULL && root->_right == NULL)
//		{
//			if(num != count)
//			{
//				return false;
//			}
//			return true;
//		}
//
//		parent = root;
//		return _IsRBTree(root->_left ,parent,count,num) &&  _IsRBTree(root->_right ,parent,count,num);
//	}

protected:
	Node * _root;
};

typedef BinaryTreeNode<char> Node;

Node* create(char *&prev, char *in1, char *in2)
{
	assert(prev && in1 && in2);

	Node *root = new Node(*prev);
	
	char *pos = in1;
	while(*pos != *prev)
	{
		++pos;
	}

	if(in1 < pos)
	{
		root->_left = create(++prev,in1, pos-1);
	}
	if(pos < in2)
	{
		root->_right = create(++prev,pos+1,in2);
	}

	return root;
}

void TestPre(Node *root)
{
	if(NULL == root)
		return ;

	stack<Node*> sa;
	sa.push(root);

	while(!sa.empty())
	{
		Node *top = sa.top();
		sa.pop();

		std::cout << top->_value << " ";
		if(top->_right)
		{
			sa.push(top->_right);
		}
		if(top->_left)
		{
			sa.push(top->_left);
		}
	}
	std::cout << std::endl;
}

void TestIn(Node *root)
{
	if(NULL == root)
	{
		return ;
	}

	stack<Node*> sa;
	sa.push(root);
	Node *cur = root->_left;
	
	while(!sa.empty() || cur)
	{
		while(cur)
		{
			sa.push(cur);
			cur = cur->_left;
		}
		Node *top = sa.top();
		sa.pop();
		std::cout << top->_value << "  ";
		cur =  top->_right;
	}
	std::cout << std::endl;
}

void Test()
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 1, 6, 0, 9 };
	BinaryTree<int> tree;
				
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
		tree.Insert(arr[i]);
	}
//	tree.InOrder();

//	BinaryTreeNode<int> *node = tree.toList();
//	while(node)
//	{
//		std::cout << node->_value << " ";
//		node = node->_right;
//	}
//	std::cout << std::endl;


//	BinaryTreeNode<int> *node1 = tree.Find(4);
//	BinaryTreeNode<int> *node2 = tree.Find(2);
//
//	BinaryTreeNode<int> *LastCommParent = tree.GetCommNode(node1, node2);
//	std::cout << LastCommParent->_value << std::endl;


//  利用前序，中序构造二叉树
//	char *prev = "12473568";
//	char *in = "47215386";
//	BinaryTreeNode<char>* root = create(prev, in, in + 7);
//				
//	TestPre(root);
//	TestIn(root);

//	tree.Max();
//	std::cout << "LenMax : " << LenMax << std::endl;

	int nodes = tree.KLevelNodes(3);
	std::cout << "3 level nodes : " << nodes << std::endl;

	nodes = tree.KLevelNodes(4);
	std::cout << "4 level nodes : " << nodes << std::endl;
}



