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
template<typename  E>
void  BinTree<E>::clear(BinNode<E>*r)//��ն�����
    {       
	if (r==NULL) return;
	if (r->left()) clear(r->left());
	if (r->right()) clear(r->right());
	delete r;
    }

template<typename  E>
void  BinTree<E>::preOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node))
//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ�������
//��visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
    {               
	if (tmp==NULL) return;
	visit(tmp);
	preOrder(tmp->left(),visit);
	preOrder(tmp->right(),visit);
	}

template<typename  E>       
void  BinTree<E>::inOrder(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node))
//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ�������
//��visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
    {              
		if (tmp==NULL) return;
		inOrder(tmp->left(),visit);
		visit(tmp);
		inOrder(tmp->right(),visit);
    }

template<typename  E>    
void  BinTree<E>::postOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node))
//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ�������
//��visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
    {   
		if (tmp==NULL) return;
		postOrder(tmp->left(),visit);
		postOrder(tmp->right(),visit);
		visit(tmp);
    }

template<typename  E>    
void  BinTree<E>::LevelOrderTranverse(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node))
//��α�����void(*visit)(BinNode<E>*node)Ϊһ������ָ�������
//��visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
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
int  BinTree<E>::BinTreeDepth(BinNode<E>*tmp)//��ö����������
    {
        if (BinTreeHeight(tmp)>0) return (BinTreeHeight(tmp)-1);
		else return 0;
    }

template<typename  E>    
int  BinTree<E>::BinTreeNodes(BinNode<E>*tmp)//��ö������Ľ����
    {               
		if (tmp==NULL) return 0;
		return BinTreeNodes(tmp->left())+BinTreeNodes(tmp->right())+1;
    }

template<typename  E>   
int  BinTree<E>::BinTreeHeight(BinNode<E>*tmp)//��ö������ĸ߶�
    {
        if (tmp==NULL) return 0;
		if (tmp->isLeaf()) return 1;
		int lh=BinTreeHeight(tmp->left());
		int rh=BinTreeHeight(tmp->right());
		return 1+( lh>rh ? lh : rh) ;
    }

template<typename  E>        
int  BinTree<E>::BinTreeLeafs(BinNode<E>*tmp)//��ö�������Ҷ�ӽ����
    {
        if (tmp==NULL) return 0;
		if (tmp->isLeaf()) return 1;
		return BinTreeLeafs(tmp->left())+BinTreeLeafs(tmp->right());
    }

template<typename  E>        
bool  BinTree<E>::find(BinNode<E>*tmp,  E  e)//���Ҷ��������Ƿ���ĳ����Ϊe�Ľ��
    {           
		if (tmp==NULL) return 0;
		if (tmp->getValue()==e) return 1;
		return find(tmp->left(),e) || find(tmp->right(),e);
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

template<typename  E>
void  BinTree<E>::clear()//��ն�����
    {
        clear(root);
        root  =  NULL;
    }

template<typename  E>  
void  BinTree<E>::preOrder(void(*visit)(BinNode<E>*node))
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
    {
        preOrder(root,visit);
    }

template<typename  E>
void  BinTree<E>::inOrder(void(*visit)(BinNode<E>*node))  
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
    {
        inOrder(root,visit);
    }

template<typename  E>     
void  BinTree<E>::postOrder(void(*visit)(BinNode<E>*node))
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
    {
        postOrder(root,visit);
    }

template<typename  E>    
void  BinTree<E>::LevelOrderTranverse(void(*visit)(BinNode<E>*node))
//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
    {
        LevelOrderTranverse(root,visit);
    }

template<typename  E>       
int  BinTree<E>::BinTreeDepth()//��ö��������
    {
        return  BinTreeDepth(root);
    }

template<typename  E>       
int  BinTree<E>::BinTreeNodes()//��ö����������
    {
        return  BinTreeNodes(root);
    }

template<typename  E>       
int  BinTree<E>::BinTreeHeight()//��ö������߶�
    {
        return  BinTreeHeight(root);
    }
   
template<typename  E>     
int  BinTree<E>::BinTreeLeafs()//��ö�����Ҷ�ӽ����
    {
        return  BinTreeLeafs(root);
    }

template<typename  E>
bool  BinTree<E>::find(E  e)//���Ҷ��������Ƿ������Ϊe�Ľ��
    {
        return  find(root,  e);
    }

//���⺯�� 
template<typename  E>
void  printNode(BinNode<E>*tmp)//��ӡ����ֵ�ĺ���
{
        cout  <<  tmp->getValue()  <<  "  ";
}

template<typename  E>
BinNode<E>*  creatBinaryTree(string  s[],  int  &x,int  n)
//������������������������������������õݹ�˼�빹��
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
//�����������ĺ���������������Ĺ������������������������������������м��һЩ������
{
        //cout  <<  "���ڽ��빹������������......"  <<  endl;
        //cout  <<  "������������ж��ٸ����(�ս��Ҳ��������)"  <<  endl;
        int  n  =  0;
        cin  >>  n;
        //cout  <<  "�밴preorder˳�����룬����NULL������'/',�ÿո�������߻س�����������"  <<  endl;
        string*s  =  new  string[n];
        for  (int  i  =  0;  i  <  n;  i++)
        {
                cin  >>  s[i];
        }
        int  now  =  0;
        BT->setRoot(creatBinaryTree<string>(s,  now,  n));
}
