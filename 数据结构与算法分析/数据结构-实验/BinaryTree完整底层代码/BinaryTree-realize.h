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
template<typename  E>
void  BinTree<E>::clear(BinNode<E>*r)//清空二叉树
    {       
	if (r==NULL) return;
	if (r->left()) clear(r->left());
	if (r->right()) clear(r->right());
	delete r;
    }

template<typename  E>
void  BinTree<E>::preOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node))
//先序遍历，void(*visit)(BinNode<E>*node)为一个函数指针参数，
//用visit代替传进来的函数，在遍历函数中使用传进来的函数功能
    {               
	if (tmp==NULL) return;
	visit(tmp);
	preOrder(tmp->left(),visit);
	preOrder(tmp->right(),visit);
	}

template<typename  E>       
void  BinTree<E>::inOrder(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node))
//中序遍历，void(*visit)(BinNode<E>*node)为一个函数指针参数，
//用visit代替传进来的函数，在遍历函数中使用传进来的函数功能
    {              
		if (tmp==NULL) return;
		inOrder(tmp->left(),visit);
		visit(tmp);
		inOrder(tmp->right(),visit);
    }

template<typename  E>    
void  BinTree<E>::postOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node))
//后序遍历，void(*visit)(BinNode<E>*node)为一个函数指针参数，
//用visit代替传进来的函数，在遍历函数中使用传进来的函数功能
    {   
		if (tmp==NULL) return;
		postOrder(tmp->left(),visit);
		postOrder(tmp->right(),visit);
		visit(tmp);
    }

template<typename  E>    
void  BinTree<E>::LevelOrderTranverse(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node))
//层次遍历，void(*visit)(BinNode<E>*node)为一个函数指针参数，
//用visit代替传进来的函数，在遍历函数中使用传进来的函数功能
    {
    	if (tmp==NULL) return;
		queue<BinNode<E>*> q;
		q.push(tmp);
		BinNode<E>* b;
		while (!q.empty())
		{
			b=q.front();
			visit(b);
			q.pop();
			if (b->left()) q.push(b->left());
			if (b->right()) q.push(b->right());
		}
    }

template<typename  E>   
int  BinTree<E>::BinTreeDepth(BinNode<E>*tmp)//获得二叉树的深度
    {
        if (BinTreeHeight(tmp)>0) return (BinTreeHeight(tmp)-1);
		else return 0;
    }

template<typename  E>    
int  BinTree<E>::BinTreeNodes(BinNode<E>*tmp)//获得二叉树的结点数
    {               
		if (tmp==NULL) return 0;
		return BinTreeNodes(tmp->left())+BinTreeNodes(tmp->right())+1;
    }

template<typename  E>   
int  BinTree<E>::BinTreeHeight(BinNode<E>*tmp)//获得二叉树的高度
    {
        if (tmp==NULL) return 0;
		if (tmp->isLeaf()) return 1;
		int lh=BinTreeHeight(tmp->left());
		int rh=BinTreeHeight(tmp->right());
		return 1+( lh>rh ? lh : rh) ;
    }

template<typename  E>        
int  BinTree<E>::BinTreeLeafs(BinNode<E>*tmp)//获得二叉树的叶子结点数
    {
        if (tmp==NULL) return 0;
		if (tmp->isLeaf()) return 1;
		return BinTreeLeafs(tmp->left())+BinTreeLeafs(tmp->right());
    }

template<typename  E>        
bool  BinTree<E>::find(BinNode<E>*tmp,  E  e)//查找二叉树中是否含有某个名为e的结点
    {           
		if (tmp==NULL) return 0;
		if (tmp->getValue()==e) return 1;
		return find(tmp->left(),e) || find(tmp->right(),e);
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

template<typename  E>
void  BinTree<E>::clear()//清空二叉树
    {
        clear(root);
        root  =  NULL;
    }

template<typename  E>  
void  BinTree<E>::preOrder(void(*visit)(BinNode<E>*node))
//先序遍历，传入相对应的访问函数即可对该当前结点实现不同功能的访问（本程序为输出）
    {
        preOrder(root,visit);
    }

template<typename  E>
void  BinTree<E>::inOrder(void(*visit)(BinNode<E>*node))  
//先序遍历，传入相对应的访问函数即可对该当前结点实现不同功能的访问（本程序为输出）
    {
        inOrder(root,visit);
    }

template<typename  E>     
void  BinTree<E>::postOrder(void(*visit)(BinNode<E>*node))
//先序遍历，传入相对应的访问函数即可对该当前结点实现不同功能的访问（本程序为输出）
    {
        postOrder(root,visit);
    }

template<typename  E>    
void  BinTree<E>::LevelOrderTranverse(void(*visit)(BinNode<E>*node))
//先序遍历，传入相对应的访问函数即可对该当前结点实现不同功能的访问（本程序为输出）
    {
        LevelOrderTranverse(root,visit);
    }

template<typename  E>       
int  BinTree<E>::BinTreeDepth()//获得二叉树深度
    {
        return  BinTreeDepth(root);
    }

template<typename  E>       
int  BinTree<E>::BinTreeNodes()//获得二叉树结点数
    {
        return  BinTreeNodes(root);
    }

template<typename  E>       
int  BinTree<E>::BinTreeHeight()//获得二叉树高度
    {
        return  BinTreeHeight(root);
    }
   
template<typename  E>     
int  BinTree<E>::BinTreeLeafs()//获得二叉树叶子结点数
    {
        return  BinTreeLeafs(root);
    }

template<typename  E>
bool  BinTree<E>::find(E  e)//查找二叉树中是否存在名为e的结点
    {
        return  find(root,  e);
    }

//类外函数 
template<typename  E>
void  printNode(BinNode<E>*tmp)//打印结点的值的函数
{
        cout  <<  tmp->getValue()  <<  "  ";
}

template<typename  E>
BinNode<E>*  creatBinaryTree(string  s[],  int  &x,int  n)
//构建二叉树的主函数，根据先序遍历，采用递归思想构建
{
        if  (s[x]  =="/")
                return  NULL;
        else
        {
                BinNode<E>*node  =  new  BinNode<E>(s[x]);
                x  =  x  +  1;
                if  (x  <  n);
                node->setLeft(creatBinaryTree<E>(s,  x,n));
                x  =  x  +  1;
                if  (x  <  n);
                node->setRight(creatBinaryTree<E>(s,  x,n));
                return  node;
        }
}

void  creatBinaryTree(BinTree<string>*BT)
//构建二叉树的函数，包含了上面的构建二叉树的主函数，仅仅起到了在主函数中简洁一些的作用
{
        //cout  <<  "现在进入构建二叉树程序......"  <<  endl;
        //cout  <<  "请输入二叉树有多少个结点(空结点也计算其中)"  <<  endl;
        int  n  =  0;
        cin  >>  n;
        //cout  <<  "请按preorder顺序输入，遇到NULL请输入'/',用空格隔开或者回车隔开均可以"  <<  endl;
        string*s  =  new  string[n];
        for  (int  i  =  0;  i  <  n;  i++)
        {
                cin  >>  s[i];
        }
        int  now  =  0;
        BT->setRoot(creatBinaryTree<string>(s,  now,  n));
}
