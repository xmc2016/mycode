//递归版本二插树的遍历
#pragma once 
#include<iostream>
#include<assert.h>
#include<queue>
using namespace std;
template< class T>
struct  BinaryTreeNode  //二叉树的节点
{
	BinaryTreeNode(const T data = T())
	:_data(data)
	, _left(NULL)
	, _right(NULL){}

	T _data;
	BinaryTreeNode*_left;
	BinaryTreeNode* _right;
};
template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T>  Node;
public:
	BinaryTree() : _root(NULL){}
	BinaryTree(T*arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreateTree(arr,size,index,invalid);
	}
	BinaryTree(const BinaryTree<T>& s)
	{
		_root = _Copy(s._root);
	}
	//BinaryTree<T>& operator =(const BinaryTree<T>& bt) //传统写法
	//{
	//	if (this != &bt) // 防止自赋值
	//	{
	//		Node* root = _Capy(bt.root);
	//		delete _root;
	//		_root = root;
	//	}
	//	return *this;
	//}
	BinaryTree<T>& operator=(BinaryTree<T> bt) // 现代写法
	{
		if (this != &bt)
		{
			std::swap(_root, bt._root);
		}		
		return *this;

	}
	~BinaryTree()
	{
		_Destroy(_root);
	}
public:
	void PrevOrder() //先序遍历
	{
		_PreVOrder(_root);
		cout << endl;
	}
	void InOrder() // 中序遍历
	{
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder() // 后序遍历
	{
		_PostOrder(_root);
		cout << endl;
	} 
	void LevelOrder()// 层次遍历
	{
		_LevelOrder(_root);
		cout << endl;
	}
	size_t Size()// 求二叉树的总节点数
	{
		size_t size = _Size(_root);
		return size;
	}
	size_t Depth()  //求树的深度
	{
		size_t depth = _Depth(_root);
		return depth;
	}
	size_t GetLevel(int level) // level层的所有节点的个数
	{
		size_t count = _GetKLevel(_root, level);
		return count;
	}
	size_t  LeafSize() // 子树的大小
	{  

		size_t count = _LeafSize(_root);
		return count;
	}
	void  IsCompleteBinaryTree()
	{
		bool tmp = _IsCompleteBinaryTree(_root);
		if ( tmp==true)
		{
			cout << "是完全二叉树" << endl;
		}
		else
		{
			cout << "不是完全二叉树" << endl;
		}
	}
protected:
	void  _PreVOrder(Node*root) // 前序遍历
	{ 
		Node* cur = root;
		if (cur)
		{
			cout << cur->_data << " ";
			_PreVOrder(cur->_left);
			_PreVOrder(cur->_right);
		}
	}

	void _InOrder(Node*root)// 中序遍历
	{
		 Node* cur = root;
		 if (cur)
		 {
			
			 _InOrder(cur->_left);
			 cout << cur->_data << " ";
			 _InOrder(cur->_right);
		 }
		 
	}
	 void _PostOrder(Node*root) // 后序遍历
	 {
		 Node* cur = root;
		 if (cur)
		 {
			 _PostOrder(cur->_left);
			 _PostOrder(cur->_right);
			 cout << cur->_data << " ";
		 }
	 }
	 void _LevelOrder(Node* root)  //层次遍历
	 {
		 queue<Node*> q;
		 Node* cur = root;
		 q.push(cur);
		 while (!q.empty())
		 {
			 Node* t = q.front()
			 cout << t->_data << " ";
			 if (t->_left != NULL)
			 {
				 q.push(t->_left);
			 }
			 if (t->_right!= NULL)
			 {
				 q.push(t->_right);

			 }
			 q.pop()
		 }
	 }
	 size_t _Size(Node* root)//求树的总节点个数
	 {
		 if (root == NULL)
		 {
			 return 0; // 空数
		 }
		 return 1 + _Size(root->_left) + _Size(root->_right);
	 }

	 size_t _Depth(Node* root) //求树的深度
	 {
		 Node* cur = root;
		 if (cur == NULL)
		 {
			 return 0;
		 }
		
	 return  1 + (_Depth(cur->_left)>_Depth(cur->_right)?
				 _Depth(cur->_left) :
				 _Depth(cur->_right));
	 }
	 size_t  _GetKLevel(Node* root, size_t level) //求第k层节点个数
	 {
		 size_t count = 0;
		 Node* cur = root;
		 if (cur == NULL)
		 {
			 return 0;
		 }
		 if (level == 1)
		 {
			 return 1;
		 }
		 else{
			 count += _GetKLevel(cur->_left, level - 1);
			 count += _GetKLevel(cur->_right, level - 1);
		 }
		 return count;
	 }
	 size_t _LeafSize(Node* root) //求子树的节点个数
	 {
		 if (root == NULL)
		 {
			 return 0;
		 }
		 else if (root->_left == NULL&&root->_right == NULL)
		 {
			 // 叶子节点没有左子树也没有右子数
			 return 1;
		 }
		 else
			 return _LeafSize(root->_left) + _LeafSize(root->_right);
	 }
	Node* _CreateTree(T* arr, size_t size,size_t& index, const T& invalid) // 创造二叉树
	{
		 assert(arr);
		  Node* root = NULL;
		if (index<size && arr[index]!= invalid)
		{
  			root = new Node(arr[index]);
			root->_left = _CreateTree(arr,size,++index, invalid);
			root->_right = _CreateTree(arr, size,++index, invalid);
		}
	
		return root;
	}
	Node* _Copy(Node* root)
	{
		Node* cur = root;
		Node* proot = NULL;
		if (cur)
		{
			proot = new Node(cur->_data);
			proot->_left= _Copy(cur->_left);
			proot->_right = _Copy(cur->_right);
		}
		return proot;
	}
	void _Destroy(Node* root)
	{
		Node* cur = root;
		if (cur)
		{
			_Destroy(cur->_left);
			_Destroy(cur->_right);
			delete cur;
			cur = NULL;
		}
	}
	bool _IsCompleteBinaryTree(Node* root)  //判断一课树是完全二叉树
	{
		if (root == NULL)
		{
			return false;
		}
		queue<Node* > q;

		q.push(root);
		int flag = 0;
		while (!q.empty())
		{
			Node* cur = q.front();
			q.pop();
			if (cur->_left != NULL)
			{
				if (flag)
				{
					return false;
				}
				q.push(cur->_left);
			}
			else
			{
				if (flag == 0)
				{
					flag = 1;
				}
			}
			
			if (cur->_right != NULL)
			{
				if (flag)
				{
					return false;
				}
				q.push(cur->_right);
			}
			else
			{
				if (flag == 0)
					flag = 1;
			}
		}
		return true;
	}

protected:
	Node* _root;
};
