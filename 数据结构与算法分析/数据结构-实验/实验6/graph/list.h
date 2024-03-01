#ifndef LIST
#define LIST
template <typename E> class List { // List ADT
private:
  void operator =(const List&) {}      // Protect assignment   
  List(const List&) {}           // Protect copy constructor 
public:
  List() {}          // 默认构造函数 
  virtual ~List() {} // 基本的析构函数 

  // 从列表中清除内容,让它空着
  virtual void clear() = 0;

  // 在当前位置插入一个元素
  // item: 要插入的元素
  virtual void insert(const E& item) = 0;

  // 在列表的最后添加一个元素 
  // item: 要添加的元素 
  virtual void append(const E& item) = 0;

  // 删除和返回当前元素 
  // Return: 要删除的元素 
  virtual E remove() = 0;

  // 将当前位置设置为列表的开始
  virtual void moveToStart() = 0;

  // 将当前位置设置为列表的末尾 
  virtual void moveToEnd() = 0;

  // 将当前位置左移一步，如果当前位置在首位就不变 
  virtual void prev() = 0;

  // 将当前位置右移一步，如果当前位置在末尾就不变 
  virtual void next() = 0;

  // 返回列表当前元素个数 
  virtual int length() const = 0;

  // 返回当前位置 
  virtual int currPos() const = 0;

  // 设置当前位置 
  // pos: 要设置的当前位置 
  virtual void moveToPos(int pos) = 0;

  // Return: 当前位置的元素 
  virtual const E& getValue() const = 0;
};
#endif


