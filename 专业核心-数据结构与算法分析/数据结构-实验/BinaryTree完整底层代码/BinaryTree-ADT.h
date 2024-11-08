//BinaryTree-ADT.h
//二叉树ADT的定义和声明 
#include<iostream>
using  namespace  std;

template<typename  E>
class  BinNode//结点类
{
private:
        BinNode*lc;//左孩子
        BinNode*rc;//右孩子
        E  elem;
public:
        BinNode();//默认构造函数，设置左右孩子为空
        BinNode(E  tmp,  BinNode*l=NULL,  BinNode*r=NULL);//带参构造函数
        BinNode*left();//返回左孩子
        BinNode*right();//返回右孩子
        void  setLeft(BinNode*l);//设置左孩子
        void  setRight(BinNode*r);//设置右孩子
        void  setValue(E  tmp);//设置当前结点的值
        E  getValue();//获得当前结点的值
        bool  isLeaf();//判断当前结点是否为叶子结点
};

template<typename  E>
class  BinTree//二叉树类
{
private:
        BinNode<E>*root;//根结点
        void  clear(BinNode<E>*r);//清空二叉树
        void  preOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node));
//先序遍历，void(*visit)(BinNode<E>*node)为一个函数指针参数，
//用visit代替传进来的函数，在遍历函数中使用传进来的函数功能
        void  inOrder(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node));
//中序遍历，void(*visit)(BinNode<E>*node)为一个函数指针参数，
//用visit代替传进来的函数，在遍历函数中使用传进来的函数功能
        void  postOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node));
//后序遍历，void(*visit)(BinNode<E>*node)为一个函数指针参数，
//用visit代替传进来的函数，在遍历函数中使用传进来的函数功能
        void  LevelOrderTranverse(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node));
//层次遍历，void(*visit)(BinNode<E>*node)为一个函数指针参数，
//用visit代替传进来的函数，在遍历函数中使用传进来的函数功能
        int  BinTreeDepth(BinNode<E>*tmp);//获得二叉树的深度
        int  BinTreeNodes(BinNode<E>*tmp);//获得二叉树的结点数
        int  BinTreeHeight(BinNode<E>*tmp);//获得二叉树的高度
        int  BinTreeLeafs(BinNode<E>*tmp);//获得二叉树的叶子结点数
        bool  find(BinNode<E>*tmp,  E  e);//查找二叉树中是否含有某个名为e的结点
public:
        BinTree();//默认构造函数
        ~BinTree();//析构函数
        bool  BinTreeEmpty();//判断二叉树是否为空
        BinNode<E>*getRoot();//获得根节点
        void  setRoot(BinNode<E>*r);//设置根节点
//下面的函数是对外的函数，所以内部还会有一些同名的函数，
//但是参数列表不一样，实现数据的封装，外部的调用不会涉及到内部的数据对象
        void  clear();//清空二叉树
        void  preOrder(void(*visit)(BinNode<E>*node));
//先序遍历，传入相对应的访问函数即可对该当前结点实现不同功能的访问（本程序为输出）
        void  inOrder(void(*visit)(BinNode<E>*node));
//先序遍历，传入相对应的访问函数即可对该当前结点实现不同功能的访问（本程序为输出）
        void  postOrder(void(*visit)(BinNode<E>*node));
//先序遍历，传入相对应的访问函数即可对该当前结点实现不同功能的访问（本程序为输出）
        void  LevelOrderTranverse(void(*visit)(BinNode<E>*node));
//先序遍历，传入相对应的访问函数即可对该当前结点实现不同功能的访问（本程序为输出）
        int  BinTreeDepth();//获得二叉树深度
        int  BinTreeNodes();//获得二叉树结点数
        int  BinTreeHeight();//获得二叉树高度
        int  BinTreeLeafs();//获得二叉树叶子结点数
        bool  find(E  e);//查找二叉树中是否存在名为e的结点
};




