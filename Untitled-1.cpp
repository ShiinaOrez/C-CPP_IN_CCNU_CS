#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    string x;
    int flag;
    multimap<string,int> words;
    cin >> x;
    while(x != "0")
    {
        words.insert(pair<string,int>(x,1));
        cin >> x;
    }
    multimap<string,int>::iterator it;
    map<string,int> store;
    map<string,int>::iterator iter;
    map<string,int>::iterator it1;
    for(it=words.begin();it!=words.end();it++)
    {
        flag=0;
        for(iter=store.begin();iter!=store.end();iter++)
        {
            if(it->first==iter->first)
            {
                iter->second++;
                flag=1;
            }
        }
        if(flag!=1)
        store.insert(pair<string,int>(it->first,it->second));
    }
    map<string,int>::iterator it2;
    map<string,int>::iterator it3;
    map<string,int>::iterator max;
    for(it2=store.begin();it2!=store.end();it2++)
    {
        max=it2;
        for(it3=store.begin();it3!=store.end();it3++)
        {
            if(max->second<it3->second)
            max=it3;
        }
        if(max->second!=0)
        cout << max->first << " " << max->second <<endl;
        max->second=0;
    }
}