#ifndef LIST
#define LIST
template <typename E> class List { // List ADT
private:
  void operator =(const List&) {}      // Protect assignment   
  List(const List&) {}           // Protect copy constructor 
public:
  List() {}          // Ĭ�Ϲ��캯�� 
  virtual ~List() {} // �������������� 

  // ���б����������,��������
  virtual void clear() = 0;

  // �ڵ�ǰλ�ò���һ��Ԫ��
  // item: Ҫ�����Ԫ��
  virtual void insert(const E& item) = 0;

  // ���б��������һ��Ԫ�� 
  // item: Ҫ��ӵ�Ԫ�� 
  virtual void append(const E& item) = 0;

  // ɾ���ͷ��ص�ǰԪ�� 
  // Return: Ҫɾ����Ԫ�� 
  virtual E remove() = 0;

  // ����ǰλ������Ϊ�б�Ŀ�ʼ
  virtual void moveToStart() = 0;

  // ����ǰλ������Ϊ�б��ĩβ 
  virtual void moveToEnd() = 0;

  // ����ǰλ������һ���������ǰλ������λ�Ͳ��� 
  virtual void prev() = 0;

  // ����ǰλ������һ���������ǰλ����ĩβ�Ͳ��� 
  virtual void next() = 0;

  // �����б�ǰԪ�ظ��� 
  virtual int length() const = 0;

  // ���ص�ǰλ�� 
  virtual int currPos() const = 0;

  // ���õ�ǰλ�� 
  // pos: Ҫ���õĵ�ǰλ�� 
  virtual void moveToPos(int pos) = 0;

  // Return: ��ǰλ�õ�Ԫ�� 
  virtual const E& getValue() const = 0;
};
#endif


