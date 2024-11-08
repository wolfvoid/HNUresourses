#include "list.h"
#include <assert.h>

using namespace std;

//断言工具函数：如果val为假则输出s然后中断程序
void  Assert(bool  val,string  s){
        if(!val){
                cout<<"断言失败："<<s<<endl;
        }
}

//  Singly  linked  list  node
template  <typename  E>  class  Link  {
public:
        E  element;            //  Value  for  this  node
        Link  *next;                //  Pointer  to  next  node  in  list
        //  Constructors
        Link(const  E&  elemval,  Link*  nextval  =NULL)  {
        	element=elemval;
        	next=nextval;
        }
        Link(Link*  nextval  =NULL)  {      
			next=nextval;
        }
};

template  <typename  E>  class  LList:  public  List<E>  {
private:
        Link<E>*  head;              //  Pointer  to  list  header
        Link<E>*  tail;              //  Pointer  to  last  element
        Link<E>*  curr;              //  Access  to  current  element
        int  cnt;                              //  Size  of  list

        void  init()  {                //  Intialization  helper  method      
			curr=tail=head=new Link<E>;
			cnt=0;
        }

public:
        LList(int  size=100)  {
                init();        //  Constructor
        }
        ~LList()  {
                removeall();        //  Destructor
        }

        void  removeall()  {      
			while (head!=NULL)
			{			
				curr=head;
				head=head->next;
				delete curr;
			}
        }
        
        void  insert(const  E&  it)  {
			curr->next=new Link<E>(it,curr->next);
			if (tail==curr) tail=curr->next;
			cnt++;
        }

        void  moveToStart()  {      
			curr=head;
        }

        void  prev()  { 
			if (curr==head) return;
			Link<E>* temp=head;
			while (temp->next!=curr) temp=temp->next;
			curr=temp;
        }

        void  next()  {
			if ( curr != tail ) curr=curr->next;
        }

        int  length()  const    {       
			return cnt;
        }

        void  moveToPos(int  pos)  {
                Assert((pos>=0)&&(pos<=cnt),"Position  out  of  range");
                curr=head;
				for (int i=0;i<pos;i++) curr=curr->next;
        }

        const  E&  getValue()  const  {
                Assert(curr->next  !=  NULL,  "No  value");
                return curr->next->element;
        }
};
