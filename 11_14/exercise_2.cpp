#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;

bool isPalindrome(const string &s){
    for(int i=0;i<=s.length()/2;i++){
//        cout << s[i] << " " << s[s.length()-i-1] << endl;
        if(s[i] != s[s.length()-i-1]) return false;
    }
    return true;
}

int main(){
    string ss;
    cout << "enter a string:" ;
    cin >> ss;
    cout << isPalindrome(ss) << endl;
    return 0;
}