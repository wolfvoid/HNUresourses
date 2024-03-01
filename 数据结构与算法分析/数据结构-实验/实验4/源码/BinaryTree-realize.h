//BinaryTree-realize.h
//二叉树ADT的实现
#include"BinaryTree-ADT.h"
#include<iostream>
#include"string"
#include<queue>

//BinaryTreeNode二叉树的节点的实现 
template<typename  E>
BinNode<E>::BinNode()//默认构造函数，设置左右孩子为空
    {                
        setLeft(NULL);
        setRight(NULL);
    }

template<typename  E>   
BinNode<E>::BinNode(E  tmp,  BinNode*l,  BinNode*r)//带参构造函数
//模板函数的默认参数似乎必须在第一次声明的时候给出,也就是说，这里不能有两个=NULL 
//详情参见https://blog.csdn.net/u013457310/article/details/89510406
    {          
		elem=tmp;
		lc=l;
		rc=r;
    }

template<typename  E>   
BinNode<E>* BinNode<E>::left()//返回左孩子
    {
        return lc;
    }

template<typename  E>  
BinNode<E>* BinNode<E>::right()//返回右孩子
    {            
		return rc;
    }

template<typename  E>  
void  BinNode<E>::setLeft(BinNode*l)//设置左孩子
    {
        lc=l;
    }

template<typename  E>  
void  BinNode<E>::setRight(BinNode*r)//设置右孩子
    {             
		rc=r;
    }
  
template<typename  E>       
void  BinNode<E>::setValue(E  tmp)//设置当前结点的值
    {
        elem=tmp;
	}

template<typename  E>    
E  BinNode<E>::getValue()//获得当前结点的值
    {
        return elem;
    }

template<typename  E>   
bool  BinNode<E>::isLeaf()//判断当前结点是否为叶子结点
    {
        return (lc==NULL && rc==NULL);
    }



//BinaryTree二叉树的实现 

template<typename E>
BinNode<E>* BinTree<E>::find(BinNode<E>* tmp, E e)
{
if (tmp == NULL)return NULL;
	else if (tmp->getValue() == e)return tmp;
	else
	{
		BinNode<E>* tmp1 = find(tmp->left(), e);
		if (tmp1)return tmp1;
		else
		{
			BinNode<E>* tmp2 = find(tmp->right(), e);
			if (tmp2)return tmp2;

		}
	}
	return NULL; 
}

template<typename  E>
BinTree<E>::BinTree()//默认构造函数
    {
        root=new  BinNode<E>;
    }

template<typename  E>        
BinTree<E>::~BinTree()//析构函数
    {
        clear(root);
    }

template<typename  E>
bool  BinTree<E>::BinTreeEmpty()//判断二叉树是否为空
    {
        if  (root  ==  NULL) return  true;
        else return  false;
    }
    
template<typename  E>        
BinNode<E>* BinTree<E>::getRoot()//获得根节点
    {
        return  root;
    }

template<typename  E>        
void  BinTree<E>::setRoot(BinNode<E>*r)//设置根节点
    {
        root  =  r;
    }
//下面的函数是对外的函数，所以内部还会有一些同名的函数，但是参数列表不一样，
//实现数据的封装，外部的调用不会涉及到内部的数据对象


//类外函数 
template<typename E>
BinNode<E>* creatBinaryTree(string s[], int& x, int n)
{
	if (s[x] == "#")
		return NULL;
	else
	{
		BinNode<E>* node = new BinNode<E>(s[x]);
		x = x + 1;
		if (x < n)
		node->setLeft(creatBinaryTree<E>(s, x, n));
		x = x + 1;
		if (x < n)
		node->setRight(creatBinaryTree<E>(s, x, n));
		return node;
	}
}

void creatBinaryTree(BinTree<string>* BT)
{
	int n = 0;
	string te;
	cin >> te;
	n = te.size();
	string* s = new string[n];
	for (int i = 0; i < n; i++)
	{
		s[i] = te[i];
	}
	int now = 0;
	BT->setRoot(creatBinaryTree<string>(s, now, n));
}

template<typename E>
void preOrder1(BinNode<E>* tmp, vector< string>& ve)
{
	if (tmp == NULL)
	{
		ve.push_back("#");
		return ;
	}
	ve.push_back(tmp->getValue());
	preOrder1(tmp->left(),ve);
	preOrder1(tmp->right(),ve);

}

bool compare(BinNode<string>* s, BinNode<string>* s1)
{
	vector<string> ve,ve1;
	preOrder1(s, ve);
	preOrder1(s1, ve1);
	if (ve.size() != ve1.size())return 0;
	else
	{
		for (int i = 0; i < ve.size(); i++)
		{
			if (ve[i] != ve1[i])return 0;
		}
	}
	return 1;
}
