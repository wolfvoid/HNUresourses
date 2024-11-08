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
public:
        BinTree();//Ĭ�Ϲ��캯��
        ~BinTree();//��������
        bool  BinTreeEmpty();//�ж϶������Ƿ�Ϊ��
        BinNode<E>*getRoot();//��ø��ڵ�
        void  setRoot(BinNode<E>*r);//���ø��ڵ�
//����ĺ����Ƕ���ĺ����������ڲ�������һЩͬ���ĺ�����
//���ǲ����б�һ����ʵ�����ݵķ�װ���ⲿ�ĵ��ò����漰���ڲ������ݶ���
        void  preOrder(void(*visit)(BinNode<E>*node));
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        BinNode<E>* find(BinNode<E>* tmp, E e);//���Ҷ��������Ƿ���ĳ����Ϊe�Ľ��
};




