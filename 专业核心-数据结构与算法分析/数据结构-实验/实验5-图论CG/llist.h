#include "list.h"
#include<assert.h>

// This is the declaration for LList. It is split into two parts
// because it is too big to fit on one book page
// Linked list implementation
using namespace std;
template <typename E> class LList: public List<E> {
private:
  Link<E>* head;       // 指向链表头结点 
  Link<E>* tail;       // 指向链表最后一个结点 
  Link<E>* curr;       // 指向当前元素 
  int cnt;    	       // 当前列表大小 

  void init() {        // 初始化
    curr = tail = head = new Link<E>;
    cnt = 0;
  }

  void removeall() {   // Return link nodes to free store 
    while(head != NULL) {
      curr = head;
      head = head->next;
      delete curr;
    }
  }

public:
  LList(int size=100) { init(); }    // 构造函数 
  ~LList() { removeall(); }                   // 析构函数
  void print() const;                // 打印列表内容
  void clear() { removeall(); init(); }       // 清空列表

  // 在当前位置插入“it”
  void insert(const E& it) {
    curr->next = new Link<E>(it, curr->next);  
    if (tail == curr) tail = curr->next;  //新的尾指针 
    cnt++;
  }

  void append(const E& it) { // 追加“it”到列表中
    tail = tail->next = new Link<E>(it, NULL);
    cnt++;
  }

  // 删除并返回当前元素
  E remove() {
    assert(curr->next != NULL);//"No element"
    E it = curr->next->element;      // 保存元素值
    Link<E>* ltemp = curr->next;     // 保存指针域信息 
    if (tail == curr->next) tail = curr; // 重置尾指针
    curr->next = curr->next->next;   // 从列表中删除 
    delete ltemp;                    //回收空间
    cnt--;			     // 当前列表大小减一
    return it;
  }

  void moveToStart() // 将curr设置在列表头部
    { curr = head; }

  void moveToEnd()   // 将curr设置在列表尾部
    { curr = tail; }

  // 将curr指针往前（左）移一步；如果已经指向头部了就不需要改变 
  void prev() {
    if (curr == head) return;       // 之前没有元素 
    Link<E>* temp = head;
    // March down list until we find the previous element
    while (temp->next!=curr) temp=temp->next;
    curr = temp;
  }

  // 将curr指针往后（右）移一步；如果已经指向尾部了就不需要改变 
  void next()
    { if (curr != tail) curr = curr->next; }

  int length() const  { return cnt; } // 返回当前列表大小

  // 返回当前元素的位置
  int currPos() const {
    Link<E>* temp = head;
    int i;
    for (i=0; curr != temp; i++)
      temp = temp->next;
    return i;
  }

  // 向下移动到列表“pos”位置
  void moveToPos(int pos) {
    assert ((pos>=0)&&(pos<=cnt));//"Position out of range"
    curr = head;
    for(int i=0; i<pos; i++) curr = curr->next;
  }

  const E& getValue() const { // 返回当前元素
    assert(curr->next != NULL);//"No value"
    return curr->next->element;
  }
};

