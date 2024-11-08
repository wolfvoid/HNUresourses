//
//BinNodeTree�ײ����ʵ�� 
//
//��������ʽ��
//��һ�У�����������ܽڵ���n�����սڵ�Ҳ�������ڣ�
//�ڶ��У��Կո�ָ��Ľڵ����ݣ�string���ͣ������� / ��ʾ�ýڵ�Ϊ�գ���������Ϊ�ýڵ㱣�����Ϣ
//�����У����ڶ������в�ѯ��ֵ
//�������ʽ��
//����������ṩ�Ĵ���Ϊ׼
//���������롿
//11
//A B / / C D / / E / /
//C
//�����������
//0:�ж��Ƿ�Ϊ��������
//1:ǰ�����:A B C D E
//2:�������:B A D C E
//3:�������:B D E C A
//4:��α���:A B C D E
//5:��¼�������:2
//6:��¼���ĸ߶�:3
//7:ͳ�ƽ��:5
//8:ͳ��Ҷ�ӽ��:3
//9:����C:����
//10:�Ƿ����:�����
//5:��¼�������:0
//6:��¼���ĸ߶�:0
//7:ͳ�ƽ��:0
//8:ͳ��Ҷ�ӽ��:0

#include<iostream>
#include"string"
#include<queue>

using  namespace  std;

template<typename  E>
class  BinNode//�����
{
private:
        BinNode*lc;//����
        BinNode*rc;//�Һ���
        E  elem;
public:
        BinNode()//Ĭ�Ϲ��캯�����������Һ���Ϊ��
        {
                
setLeft(NULL);
setRight(NULL);

        }
        BinNode(E  tmp,  BinNode*l=NULL,  BinNode*r=NULL)//���ι��캯��
        {
                
elem=tmp;
lc=l;
rc=r;
        
        }
        BinNode*left()//��������
        {
                
return lc;
        
        }
        BinNode*right()//�����Һ���
        {
                
return rc;

        }
        void  setLeft(BinNode*l)//��������
        {
                
lc=l;

        }
        void  setRight(BinNode*r)//�����Һ���
        {
                
rc=r;

        }
        void  setValue(E  tmp)//���õ�ǰ����ֵ
        {
                
elem=tmp;

        }
        E  getValue()//��õ�ǰ����ֵ
        {
                
return elem;

        }
        bool  isLeaf()//�жϵ�ǰ����Ƿ�ΪҶ�ӽ��
        {
                
return (lc==NULL && rc==NULL);

        }
};

template<typename  E>
class  BinTree//��������
{
private:
        BinNode<E>*root;//�����
        void  clear(BinNode<E>*r)//��ն�����
        {
                
if (r==NULL) return;
if (r->left()) clear(r->left());
if (r->right()) clear(r->right());
delete r;

        }
        void  preOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node))//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ���������visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
        {
                
if (tmp==NULL) return;
visit(tmp);
preOrder(tmp->left(),visit);
preOrder(tmp->right(),visit);

        }
        void  inOrder(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node))//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ���������visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
        {
                
if (tmp==NULL) return;
inOrder(tmp->left(),visit);
visit(tmp);
inOrder(tmp->right(),visit);

        }
        void  postOrder(BinNode<E>*tmp,void(*visit)(BinNode<E>*node))//���������void(*visit)(BinNode<E>*node)Ϊһ������ָ���������visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
        {
                
if (tmp==NULL) return;
postOrder(tmp->left(),visit);
postOrder(tmp->right(),visit);
visit(tmp);

        }
        void  LevelOrderTranverse(  BinNode<E>*tmp,void(*visit)(BinNode<E>*node))//��α�����void(*visit)(BinNode<E>*node)Ϊһ������ָ���������visit���洫�����ĺ������ڱ���������ʹ�ô������ĺ�������
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
        int  BinTreeDepth(BinNode<E>*tmp)//��ö����������
        {
                
if (BinTreeHeight(tmp)>0) return (BinTreeHeight(tmp)-1);
else return 0;

        }
        int  BinTreeNodes(BinNode<E>*tmp)//��ö������Ľ����
        {
                
if (tmp==NULL) return 0;
return BinTreeNodes(tmp->left())+BinTreeNodes(tmp->right())+1;

        }
        int  BinTreeHeight(BinNode<E>*tmp)//��ö������ĸ߶�
        {
                
if (tmp==NULL) return 0;
if (tmp->isLeaf()) return 1;
int lh=BinTreeHeight(tmp->left());
int rh=BinTreeHeight(tmp->right());
return 1+( lh>rh ? lh : rh) ;

        }
        int  BinTreeLeafs(BinNode<E>*tmp)//��ö�������Ҷ�ӽ����
        {
                
if (tmp==NULL) return 0;
if (tmp->isLeaf()) return 1;
return BinTreeLeafs(tmp->left())+BinTreeLeafs(tmp->right());

        }
        bool  find(BinNode<E>*tmp,  E  e)//���Ҷ��������Ƿ���ĳ����Ϊe�Ľ��
        {
                
if (tmp==NULL) return 0;
if (tmp->getValue()==e) return 1;
return find(tmp->left(),e) || find(tmp->right(),e);

        }
public:
        BinTree()//Ĭ�Ϲ��캯��
        {
                root=new  BinNode<E>;
        }
        ~BinTree()//��������
        {
                clear(root);
        }
        bool  BinTreeEmpty()//�ж϶������Ƿ�Ϊ��
        {
                if  (root  ==  NULL)
                        return  true;
                else
                        return  false;
        }
        BinNode<E>*getRoot()//��ø��ڵ�
        {
                return  root;
        }
        void  setRoot(BinNode<E>*r)//���ø��ڵ�
        {
                root  =  r;
        }
        //����ĺ����Ƕ���ĺ����������ڲ�������һЩͬ���ĺ��������ǲ����б�һ����ʵ�����ݵķ�װ���ⲿ�ĵ��ò����漰���ڲ������ݶ���
        void  clear()//��ն�����
        {
                clear(root);
                root  =  NULL;
        }
        void  preOrder(void(*visit)(BinNode<E>*node))//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        {
                preOrder(root,visit);
        }
        void  inOrder(void(*visit)(BinNode<E>*node))  //����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        {
                inOrder(root,visit);
        }
        void  postOrder(void(*visit)(BinNode<E>*node))//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        {
                postOrder(root,visit);
        }
        void  LevelOrderTranverse(void(*visit)(BinNode<E>*node))//����������������Ӧ�ķ��ʺ������ɶԸõ�ǰ���ʵ�ֲ�ͬ���ܵķ��ʣ�������Ϊ�����
        {
                LevelOrderTranverse(root,visit);
        }
        int  BinTreeDepth()//��ö��������
        {
                return  BinTreeDepth(root);
        }
        int  BinTreeNodes()//��ö����������
        {
                return  BinTreeNodes(root);
        }
        int  BinTreeHeight()//��ö������߶�
        {
                return  BinTreeHeight(root);
        }
        int  BinTreeLeafs()//��ö�����Ҷ�ӽ����
        {
                return  BinTreeLeafs(root);
        }
        bool  find(E  e)//���Ҷ��������Ƿ������Ϊe�Ľ��
        {
                return  find(root,  e);
        }
};



template<typename  E>
void  printNode(BinNode<E>*tmp)//��ӡ����ֵ�ĺ���
{
        cout  <<  tmp->getValue()  <<  "  ";
}

template<typename  E>
BinNode<E>*  creatBinaryTree(string  s[],  int  &x,int  n)//������������������������������������õݹ�˼�빹��
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

void  creatBinaryTree(BinTree<string>*BT)//�����������ĺ���������������Ĺ������������������������������������м��һЩ������
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

int  main()
{
        //������Ķ�������һ��ģ���࣬����ı�Ϊ������ͣ���������صĵط��ڡ�<>�����޸���ز���,������Ĭ��Ϊ������ձ��Ե�string
        BinTree<string>*BT  =  new  BinTree<string>;
        creatBinaryTree(BT);
        string  strfind;
        cin>>strfind;
        //������Ѿ���������һ�ö�����
        //�����Ƕ������Ļ�������������չʾ

        cout  <<  "0:�ж��Ƿ�Ϊ������";
        if  (BT->BinTreeEmpty()  ==  true)
                cout  <<  "��"  <<  endl;
        else
                cout  <<  "��"  <<  endl;
        cout  <<  "1:ǰ�����:";
        BT->preOrder(printNode);
        cout  <<  endl;
        cout  <<  "2:�������:";
        BT->inOrder(printNode);
        cout  <<  endl;
        cout  <<  "3:�������:";
        BT->postOrder(printNode);
        cout  <<  endl;
        cout  <<  "4:��α���:";
        BT->LevelOrderTranverse(printNode);
        cout  <<  endl;
        cout  <<  "5:��¼�������:";
        cout  <<  BT->BinTreeDepth()  <<  endl;
        cout  <<  "6:��¼���ĸ߶�:";
        cout  <<  BT->BinTreeHeight()  <<  endl;
        cout  <<  "7:ͳ�ƽ��:";
        cout  <<  BT->BinTreeNodes()  <<  endl;
        cout  <<  "8:ͳ��Ҷ�ӽ��:";
        cout  <<  BT->BinTreeLeafs()  <<  endl;
        cout  <<  "9:����"<<strfind<<":";
        if  (BT->find(strfind)  ==  true)
                cout  <<  "����"  <<  endl;
        else
                cout  <<  "������"  <<  endl;
        cout  <<  "10:�Ƿ����:";
        BT->clear();
        cout  <<  "�����"  <<  endl;
        cout  <<  "5:��¼�������:";
        cout  <<  BT->BinTreeDepth()  <<  endl;
        cout  <<  "6:��¼���ĸ߶�:";
        cout  <<  BT->BinTreeHeight()  <<  endl;
        cout  <<  "7:ͳ�ƽ��:";
        cout  <<  BT->BinTreeNodes()  <<  endl;
        cout  <<  "8:ͳ��Ҷ�ӽ��:";
        cout  <<  BT->BinTreeLeafs()  <<  endl;
        return  0;
}
