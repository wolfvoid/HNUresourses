#include <bits/stdc++.h>
using namespace std;
int main()
{
        stack <char> s;
        stack <char> s1;
        string str;
        cin>>str;
        int len=str.length();
        for(int i=0;i<len;i++)
        {
            if(str[i]=='<'||str[i]=='('||str[i]=='['||str[i]=='{')
            {
                s.push(str[i]);
            }
            else if(str[i]=='>')
            {
                if(!s.empty()&&s.top()=='<')
                {
                    s.pop();
                }
                else
                {
                    s1.push(str[i]);
                }
            }
            else if(str[i]==')')
            {
                if(!s.empty()&&s.top()=='(')
                {
                    s.pop();
                }
                else
                {
                    s1.push(str[i]);
                }
            }
            else if(str[i]==']')
            {
                if(!s.empty()&&s.top()=='[')
                {
                    s.pop();
                }
                else
                {
                    s1.push(str[i]);
                }
            }
            else if(str[i]=='}')
            {
                if(!s.empty()&&s.top()=='{')
                {
                    s.pop();
                }
                else
                {
                    s1.push(str[i]);
                }
            }
        }
        bool bools=s.empty(),bools1=s1.empty();
        if(bools&&bools1) {cout<<"yes"<<endl;}
        else {cout<<"no"<<endl;}
    return 0;
}

