#include <bits/stdc++.h>
#include "list.h"
#include "alist.h"
using namespace std;

int main()
{
	LList <char>mylist;
	bool flag=true;
	string str;
	cin>>str;
	int len=str.length();
	int n=len/2;
	mylist.moveToStart();
    for(int i=0;i<len;i++)
        {
        	mylist.insert(str[i]);
		}
//	cout<<"input alright"<<endl;
//	cout<<"mylist.length()="<<mylist.length();
	for (int i=0;i<=n;i++)
	{
		mylist.moveToPos(i); char left=mylist.getValue();
		mylist.moveToPos(mylist.length()-1-i); char right=mylist.getValue();
//		cout<<"left="<<left<<" "<<"right="<<right<<endl;
		if (left!=right)
		{
			flag=false;
			break;
		}
	}
	if (flag) cout<<"yes"<<endl; else cout<<"no"<<endl;
//	mylist.moveToStart();
//	for(int i=0;i<len;i++)
//        {
//        	cout<<mylist.currPos()<<":"<<mylist.getValue()<<endl;
//        	mylist.next();
//        	
//		}
}
