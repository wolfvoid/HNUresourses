//BinaryTree-ADT.h
//������ADT�Ķ�������� 
#include<iostream>
using  namespace  std;

template<typename  E>
class  BinNode//�����
{
private:
        BinNode*lc;//����
        BinNode*rc;//�Һ���
        E  elem;
public:
        BinNode();//Ĭ�Ϲ��캯�����������Һ���Ϊ��
        BinNode(E  tmp,  BinNode*l=NULL,  BinNode*r=NULL);//���ι��캯��
        BinNode*left();//��������
        BinNode*right();//�����Һ���
        void  setLeft(BinNode*l);//��������
        void  setRight(BinNode*r);//�����Һ���
        void  setValue(E  tmp);//���õ�ǰ����ֵ
        E  getValue();//��õ�ǰ����ֵ
        bool  isLeaf();//�жϵ�ǰ����Ƿ�ΪҶ�ӽ��
};

template<typename  E>
class  BinTree//��������
{
private:
        BinNode<E>*root;//�����
        void  clear(BinNode<E>*r);//��ն�����
        void  preOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node));
//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ�������
//��visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
        void  inOrder(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node));
//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ�������
//��visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
        void  postOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node));
//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ�������
//��visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
        void  LevelOrderTranverse(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node));
//��α�����void(*visit)(BinNode<E>*node)Ϊһ������ָ�������
//��visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
        int  BinTreeDepth(BinNode<E>*tmp);//��ö����������
        int  BinTreeNodes(BinNode<E>*tmp);//��ö������Ľ����
        int  BinTreeHeight(BinNode<E>*tmp);//��ö������ĸ߶�
        int  BinTreeLeafs(BinNode<E>*tmp);//��ö�������Ҷ�ӽ����
        bool  find(BinNode<E>*tmp,  E  e);//���Ҷ��������Ƿ���ĳ����Ϊe�Ľ��
public:
        BinTree();//Ĭ�Ϲ��캯��
        ~BinTree();//��������
        bool  BinTreeEmpty();//�ж϶������Ƿ�Ϊ��
        BinNode<E>*getRoot();//��ø��ڵ�
        void  setRoot(BinNode<E>*r);//���ø��ڵ�
//����ĺ����Ƕ���ĺ����������ڲ�������һЩͬ���ĺ�����
//���ǲ����б�һ����ʵ�����ݵķ�װ���ⲿ�ĵ��ò����漰���ڲ������ݶ���
        void  clear();//��ն�����
        void  preOrder(void(*visit)(BinNode<E>*node));
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        void  inOrder(void(*visit)(BinNode<E>*node));
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        void  postOrder(void(*visit)(BinNode<E>*node));
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        void  LevelOrderTranverse(void(*visit)(BinNode<E>*node));
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        int  BinTreeDepth();//��ö��������
        int  BinTreeNodes();//��ö����������
        int  BinTreeHeight();//��ö������߶�
        int  BinTreeLeafs();//��ö�����Ҷ�ӽ����
        bool  find(E  e);//���Ҷ��������Ƿ������Ϊe�Ľ��
};




