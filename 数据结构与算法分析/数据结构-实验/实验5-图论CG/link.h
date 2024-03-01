#include <iostream> 
template <typename E> class Link {
public:
  E element;      // 结点值 
  Link *next;        // 结点指针：在链表中指向下一结点
  // 构造函数
  Link(const E& elemval, Link* nextval =NULL)
    { element = elemval;  next = nextval; }
  Link(Link* nextval =NULL) { next = nextval; }
};



