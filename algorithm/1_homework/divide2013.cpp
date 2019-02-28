#include<iostream>
#include<algorithm>
using namespace std;
int mod(string a,int b)
{
    int d=0;
    for(int i=0;i<a.size();i++)  d=(d*10+(a[i]-'0'))%b;
    return d;
}
int main()
{
    string a="11111";
    int b=2013, n=5;
    while(mod(a, b) != 0)
    {
        a = a+"1";
        n += 1;
    }
    cout << a << endl << "N:" << n << endl;;
    return 0;
}

