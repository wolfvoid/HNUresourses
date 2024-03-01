//BinaryTree-realize.h
//������ADT��ʵ��
#include"BinaryTree-ADT.h"
#include<iostream>
#include"string"
#include<queue>

//BinaryTreeNode�������Ľڵ��ʵ�� 
template<typename  E>
BinNode<E>::BinNode()//Ĭ�Ϲ��캯�����������Һ���Ϊ��
    {                
        setLeft(NULL);
        setRight(NULL);
    }

template<typename  E>   
BinNode<E>::BinNode(E  tmp,  BinNode*l,  BinNode*r)//���ι��캯��
//ģ�庯����Ĭ�ϲ����ƺ������ڵ�һ��������ʱ�����,Ҳ����˵�����ﲻ��������=NULL 
//����μ�https://blog.csdn.net/u013457310/article/details/89510406
    {          
		elem=tmp;
		lc=l;
		rc=r;
    }

template<typename  E>   
BinNode<E>* BinNode<E>::left()//��������
    {
        return lc;
    }

template<typename  E>  
BinNode<E>* BinNode<E>::right()//�����Һ���
    {            
		return rc;
    }

template<typename  E>  
void  BinNode<E>::setLeft(BinNode*l)//��������
    {
        lc=l;
    }

template<typename  E>  
void  BinNode<E>::setRight(BinNode*r)//�����Һ���
    {             
		rc=r;
    }
  
template<typename  E>       
void  BinNode<E>::setValue(E  tmp)//���õ�ǰ����ֵ
    {
        elem=tmp;
	}

template<typename  E>    
E  BinNode<E>::getValue()//��õ�ǰ����ֵ
    {
        return elem;
    }

template<typename  E>   
bool  BinNode<E>::isLeaf()//�жϵ�ǰ����Ƿ�ΪҶ�ӽ��
    {
        return (lc==NULL && rc==NULL);
    }



//BinaryTree��������ʵ�� 

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
BinTree<E>::BinTree()//Ĭ�Ϲ��캯��
    {
        root=new  BinNode<E>;
    }

template<typename  E>        
BinTree<E>::~BinTree()//��������
    {
        clear(root);
    }

template<typename  E>
bool  BinTree<E>::BinTreeEmpty()//�ж϶������Ƿ�Ϊ��
    {
        if  (root  ==  NULL) return  true;
        else return  false;
    }
    
template<typename  E>        
BinNode<E>* BinTree<E>::getRoot()//��ø��ڵ�
    {
        return  root;
    }

template<typename  E>        
void  BinTree<E>::setRoot(BinNode<E>*r)//���ø��ڵ�
    {
        root  =  r;
    }
//����ĺ����Ƕ���ĺ����������ڲ�������һЩͬ���ĺ��������ǲ����б�һ����
//ʵ�����ݵķ�װ���ⲿ�ĵ��ò����漰���ڲ������ݶ���


//���⺯�� 
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
