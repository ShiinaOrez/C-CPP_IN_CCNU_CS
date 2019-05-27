#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main()
{
    fstream input;
    input.open("word.txt");
    string each;
    map<string,int> store;
    while(getline(input,each))
    {
        string::size_type start=0;
        string::size_type end=each.find_first_of(" ");
        while(end!=string::npos)
        {
            string content=each.substr(start,end-start);
            map<string,int>::iterator it=store.find(content);
            if(it==store.end())
            {
                store.insert(pair<string,int>(content,1));
            }
            else
            it->second++;
            start=end+1;
            end=each.find_first_of(" ",start);
        }
    }
    multimap<int,string,greater<int> words;
    for(map<int,string>)
}