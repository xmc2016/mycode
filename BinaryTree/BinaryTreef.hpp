//非递归
#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<assert.h>
using namespace std;
template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data = T())
	:_data(data){}
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
};
template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree() :_root(NULL){}
	BinaryTree(T* arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTree(arr, size, index, invalid);
	}
	BinaryTree(const BinaryTree<T>& bt)
	{
		_root = _Copy(bt._root);
	}
	 /*BinaryTree<T>& operator =(const BinaryTree<T>& bt)
	{
		 if (this != &bt)
		 {
			 Node* root = _Copy(bt._root);
			 delete _root;
			 _root = root;
		 }
		 return *this;
	}*/
	BinaryTree<T>&operator =(const BinaryTree<T>& bt)
	{
		if (this != &bt)
		{
			Node* root = _Copy(bt._root);
		std::swap(_root, root);
		}
		return*this;
	}
	~BinaryTree()
	{
			_Destroy(_root);
	}
	void PrevOrder() //前序遍历
	{
		_PrevOrder(_root);
		
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	void PostOrder()
	{
		_PostOrder(_root);
	}
	void LevelOrder()
	{
		_LevelOrder(_root);
	}
	size_t Depth()// 求树的深度
	{
		size_t depth= _Depth(_root);
		return depth;
	}
protected:
	Node* _Copy(Node* root)
	{
		Node* cur = root;
		Node* proot = NULL;
		if (cur != NULL)
		{
			proot = new Node(cur->_data);
			proot->_left = _Copy(cur->_left);
			proot->_right = _Copy(cur->_right);
		}
		return proot;
	}
	Node* _CreateTree(T* arr, size_t size, size_t& index,  const T& invalid) //创建二叉树
	{
		assert(arr);
		Node* root = NULL;
		if (index < size&& arr[index] != invalid)
		{
			root = new Node(arr[index]);
			root->_left = _CreateTree(arr, size, ++index, invalid);
			root->_right = _CreateTree(arr, size, ++index, invalid);
		}
		return root;
	}
	void _Destroy(Node* root)
	{
		Node* cur = root;
		if (cur != NULL)
		{
			_Destroy(cur->_left);
			_Destroy(cur->_right);
			delete cur;
			cur = NULL;
		}
	}
	void _PrevOrder(Node* root) //前序遍历
	{
		stack<Node*> s;
		Node* cur = root;
		while (cur != NULL || !s.empty())
		{
			while (cur)
			{	
				s.push(cur);
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			Node* t = s.top();
			s.pop();
			cur = t->_right;
		}
		cout << endl;
	}
	void _InOrder(Node* root) // 中序遍历
	{
		stack<Node*> s;
		Node* cur = root;
		while (cur != NULL || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* t = s.top();
			cout <<t->_data <<" ";
			s.pop();
			cur = t->_right;
		}
		cout <<endl;
	}
	void _PostOrder(Node* root) // 后序遍历
	{
		stack<Node*> s;
		Node* cur = root;
		Node* prev = NULL;
		while (cur != NULL || !s.empty())
		{	
			while (cur) //一直向左遍历直到左为空时跳出
			{ 
				s.push(cur);
				cur = cur->_left;
			}
			cur = s.top();
			if (cur->_right == NULL || cur->_right == prev)
			{
				cout << cur->_data <<" ";
				prev = cur;
				s.pop();
				cur = NULL;
			}
			else
			{
				cur = cur->_right;
			}
		}
		cout <<endl;
 	}
	void _LevelOrder(Node* root) //层次遍历
	{
		Node* cur = root;
		queue<Node*> q;
		q.push(cur);
		while (!q.empty())
		{
			Node* front = q.front();
			cout << front->_data << " ";
			if (front->_left != NULL)
			{
				q.push(front->_left);
			}
			if (front->_right != NULL)
			{
				q.push(front->_right);
			}
			q.pop();

		}
		
	}
	size_t _Depth(Node* root)
	{
		Node* cur = root;
		if (cur == NULL)
		{
			return 0;
		}
		return 1 + (_Depth(cur->_left) > _Depth(cur->_right) ? 
			       _Depth(cur->_left) : _Depth(cur->_right));
	}
protected:
	Node* _root;
};




