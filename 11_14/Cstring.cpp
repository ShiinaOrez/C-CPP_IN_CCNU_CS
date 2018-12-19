#include<cstdio>
#include<iostream>
#include<string.h>
#include<cmath>

using namespace std;

class Cstring{
    private:
        char * content;
    public:
        int size(){
            return strlen(content);
        }
        char * getChars(){
            return content;
        }
        void display(){
            cout << content << endl;
        }
        int find(char r){
            for(int i=0;i<size();i++){
                if(content[i] == r)
                    return i;
            }
            return -1;
        }
        int find(Cstring & other){
            char * re;
            strcpy(re, other.getChars());
            return strcmp(content, re);
        }
        int count(char r){
            int tot = 0;
            for(int i=0;i<size();i++){
                if(content[i] == r)
                    tot++;
            }
            return tot;
        }
        Cstring operator+ (Cstring other){
            char * inside;
            strcpy(inside, this->content);
            strcat(inside, other.getChars());
            Cstring obj(inside);
            return obj;
        }
        Cstring operator* (int number){
            char * copy;
            const char * res = "";
            strcpy(copy, this->content);
            for(int i=1;i<=number;i++)
                strcat((char *)res, copy);
            Cstring obj((char *)res);
            return obj;
        }
    Cstring(){
        strcpy(content, "");
        return ;
    }
    Cstring(Cstring & other){
        int length = other.size();
        content = new char[length];
        strcpy(content, other.getChars());
    }
    Cstring(char * other){
        int length = strlen(other);
        content = new char[length];
        strcpy(content, other);
    }
    Cstring(const char * other){
        int length = strlen(other);
        content = new char[length];
        strcpy(content, other);
    }
    ~Cstring(){
    }
};

int main(){
    Cstring s1("abc");
    Cstring s2(s1);
    const char * ss = "def";
    Cstring s3(ss);
    s1.display();
    s2.display();
    s3.display();
    Cstring s4;
    s4 = s2 + s3;
    s4.display();
    cout << s2.find(s1) << endl;
    cout << s2.find('b') << endl;
}