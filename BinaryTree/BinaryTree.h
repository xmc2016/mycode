//求二叉树中最远的两个节点的距离
#pragma once
#include<queue>
#include<iostream>
using namespace std; 
template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& data = T())    
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL){}
	bool Insert(const T& x)
	{
		if (_root == NULL)
			_root = new Node(x);
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (x > cur->_data)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (x < cur->_data)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}
		if (x < parent->_data)
		{
			parent->_left = new Node(x);
		}
		else
		{
			parent->_right = new Node(x);
		}
		return true;
	}
	void Display()
	{
		_Display(_root);
		cout << endl;
	}
	int  GetMaxDistance()
	{
       int MaxLen = 0;
	   _GetMaxDistance(_root,MaxLen);
	   return MaxLen;
	}
	//将二叉搜索树转化成双向链表
	void  TreeToList()
	{
		Node* prev = NULL; //定义一个当前节点的前一个节点
		_TreeToNode(_root, prev);
	}
	void PrintList(Node* root)
	{
		if (root==NULL)
		{
			return;
		}
		while (root->_right!=NULL)
		{
			cout << root->_data << "->";
			root = root->_right;
		}
		cout << root->_data << endl;
		while (root->_left != NULL)
		{
			cout << root->_data << "->";
			root = root->_left;
		}
		cout << root->_data << endl;
	}
	void LeastCommonParent(const T& x, const T& y)
	{
		Node* cur = _LeastCommonParent(_root, x, y);
		Node* cur = _CommonParent(_root, x, y);
		if (cur)
		{
			cout << "最近公共节点为：" << cur->_data << endl;
		}
	}
protected:

	Node* _CommonParent(Node* root, const T& x, const T& y)
	{
		if (root == NULL)
		{
			return NULL;
		}
		Node* cur = root;
		while (cur)
		{
			if (cur->_data<x&&cur->_data<y) //两个节点的值大于cur，则最近公共祖先在cur的右边
			{
				cur = cur->_right;
			}
			else if (cur->_data>x&&cur->_data>y)//两个节点的值小于cur，则最近公共祖先在cur的左边
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}
	Node*  _LeastCommonParent(Node* root, const T& x, const T& y)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->_data == x || root->_data == y)
		{
			return root;
		}
		Node* left = _LeastCommonParent(root->_left, x, y);
		Node* right = _LeastCommonParent(root->_right, x, y);
		if (left&&right)
		{
			return root;
		}
		return left ?left:right;
	}
	void _TreeToNode(Node* root, Node* prev)
	{
		Node* Head = NULL;
		
		if (root == NULL)
		{
			return;
		}
		queue<Node* >  q;
		_InOrder(root, q);
		root = q.front();
		root->_left = prev;
		prev = root;
		Head = root;
		q.pop();
		while (!q.empty())
		{
			Node* cur = q.front();
			q.pop();
			prev->_right = cur;
			cur->_left = prev;
			prev = cur;	
		}
		
		PrintList(Head);
	}

	void _InOrder(Node* root, queue<Node* >&q)
	{
		if (root == NULL)
			return;
		Node* cur = root;
		_InOrder(cur->_left, q);
		q.push(cur);
		_InOrder(cur->_right, q);
	}
	int _GetMaxDistance(Node*root,int& maxlen)
	 {
 
		Node* cur = root;
		if (cur == NULL)
		{
			return 0;
		}
		int leftDepth = _GetMaxDistance(cur->_left,maxlen);
		int rightDepth = _GetMaxDistance(cur->_right,maxlen);
        if (leftDepth + rightDepth > maxlen)
        {
	    maxlen = leftDepth + rightDepth;
        }
		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}

	void _Display(Node* root)
	{
		if (root == NULL)
			return;
		_Display(root->_left);
		cout << root->_data << " ";
		_Display(root->_right);
	}
protected:
	Node* _root;
};

//方法2 求最远节点的距离
//template<class T>
//struct BinaryTreeNode
//{
//	T _data;
//	BinaryTreeNode<T>* _left;
//	BinaryTreeNode<T>* _right;
//	T _maxLeft;
//	T _maxRight;
//	BinaryTreeNode(const T& data = T())
//		:_data(data)
//		, _left(NULL)
//		, _right(NULL)
//		, _maxLeft(0) //左边最远距离
//		, _maxRight(0) //右边最远距离
//	{}
//};

//template<class T>
//class BinaryTree
//{
//	typedef BinaryTreeNode<T> Node;
//public:
//	BinaryTree()
//		:_root(NULL){}
//	bool Insert(const T& x)
//	{
//		if (_root == NULL)
//			_root = new Node(x);
//		Node* cur = _root;
//		Node* parent = NULL;
//		while (cur)
//		{
//			if (x > cur->_data)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (x < cur->_data)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//				return false;
//		}
//		if (x < parent->_data)
//		{
//			parent->_left = new Node(x);
//		}
//		else
//		{
//			parent->_right = new Node(x);
//		}
//		return true;
//	}
//	void FindMax()
//	{
//		int maxLen = 0;
//		_FindMax(_root, maxLen);
//		cout << maxLen << endl;
//	}
//		void Display()
//		{
//			_Display(_root);
//			cout << endl;
//		}
//protected:
//		void _Display(Node* root)
//		{
//			if (root == NULL)
//				return;
//			_Display(root->_left);
//			cout << root->_data << " ";
//			_Display(root->_right);
//		}
//	void _FindMax(Node* root, int& maxLen)
//	{
//		if (root == NULL)
//		{
//			return;
//		}
//
//		if (root->_left == NULL)
//		{
//			root->_maxLeft = 0;
//		}
//		else
//		{
//			_FindMax(root->_left, maxLen); //递归走左子树
//		}
//
//		if (root->_right == NULL)
//		{
//			root->_maxRight = 0;
//		}
//		else
//		{
//			_FindMax(root->_right, maxLen);//递归走右子树
//		}
//
//		if (root->_left != NULL)
//		{
//			int tmp = 0; 
//			if (root->_left->_maxLeft > root->_left->_maxRight) //root节点的_maxleft等于root->_left节点距离最远节点的距离+1
//			{
//				tmp = root->_left->_maxLeft;
//			}
//			else
//			{
//				tmp = root->_left->_maxRight;
//			}
//		     root->_maxLeft = tmp + 1;  
//		}
//		if (root->_right != NULL)  //root节点的_maxRight等于root->_right节点距离最远节点的距离+1
//		{
//			int tmp = 0;
//			if (root->_right->_maxLeft > root->_right->_maxRight)
//			{
//				tmp = root->_right->_maxLeft;
//			}
//			else
//			{
//				tmp = root->_right->_maxRight;
//			}
//			root->_maxRight = tmp + 1; 
//		}
//
//		if (root->_maxLeft + root->_maxRight> maxLen)  //更新最远距离
//		{
//			maxLen = root->_maxLeft + root->_maxRight;
//		}
//	}
//protected:
//	Node* _root;
//};





