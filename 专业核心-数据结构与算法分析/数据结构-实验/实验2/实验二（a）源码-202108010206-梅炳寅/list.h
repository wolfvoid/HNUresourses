#ifndef LIST
#define LIST
template  <typename  E>  class  List  {  //  List  ADT
private:
        void  operator  =(const  List&)  {}            //  Protect  assignment
        List(const  List&)  {}                      //  Protect  copy  constructor
public:
        List()  {}                    //  Default  constructor
        virtual  ~List()  {}  //  Base  destructor
        virtual  void  insert(const  E&  item)  =  0;
        virtual  void  moveToStart()  =  0;
        virtual  void  prev()  =  0;
        virtual  void  next()  =  0;
        virtual  int  length()  const  =  0;
        virtual  void  moveToPos(int  pos)  =  0;
        virtual  const  E&  getValue()  const  =  0;
};
#endif
