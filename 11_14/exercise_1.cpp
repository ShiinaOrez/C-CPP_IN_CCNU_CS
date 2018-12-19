#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

bool map[130] = {false};

string commonChars(const string& s1, const string& s2){
    string ss;
    for(int i=0;i<s1.length();i++){
        char c = s1[i];
        if(map[c] == true) continue;
        else map[c] = true;
        if(s2.find(c)>=0 && s2.find(c) <s2.length()){
            ss += c;
        }
    }
    return ss;
}

int main(){
    string a,b;
    printf("enter a string s1: ");
    cin >> a;
    printf("enter a string s2: ");
    cin >> b;
    cout << "the common characters are: " << commonChars(string(a),string(b)) << endl;
}