#include<cstdio>
#include<iostream>
#include<string.h>
#include<cmath>

using namespace std;

class MyString{
    private:
        char * content;
    public:
        char at(int index) const{
            return content[index];
        }
        int length() const {
            return strlen(content);
        }
        void clear(){
            strcpy(content, "");
        }
        bool empty() const{
            if (!strcmp(content, ""))
                return true;
            return false;
        }
        int compare(const MyString& s) const{
            int len = s.length();
            if (len != length())
                if(len > length()) return -1;
                else return 1;
            for(int i=0;i<length();i++){
                if(s.at(i) != content[i])
                    if(s.at(i) > content[i])
                        return -1;
                    else return 1;
            }
            return 0;
        }
        int compare(int index, int n, MyString s) const{
            int len = s.length();
            if(index >= len){
                cout << "Error: OutOfRange!" << endl;
                return -999;
            }
            char * copy, *res;
            copy = new char[len+1];
            if(index+n < len){
                copy[index+n] = '\0';
            }
            strcpy(res, copy+index);
            delete copy;
            return compare(MyString(res));
        }
        void copy(char s[], int index, int n){
            if(index >= length()){
                cout << "Error: OutOfRange!" << endl;
                return ;
            }
            char * copy;
            strcpy(copy, content);
            if(index+n < length()) copy[index+n] = '\0';
            strcpy(s, copy+index);
            return ;
        }
        char * data(){
            return content;
        }
        void display(){
            cout << content << endl;
        }
        int find(char ch) const {
            for(int i=0;i<length();i++){
                if(content[i] == ch)
                    return i;
            }
            return -1;
        }
        int find(char ch, int index) const {
            if(index >= length()) {
                cout << "Error: OutOfRange!";
                return -999;
            }
            for(int i=index;i<length();i++){
                if(content[i] == ch)
                    return i;
            }
            return -1;
        }
    MyString(){
        strcpy(content, "");
        return ;
    }
    MyString(const char * cString){
        int length = strlen(cString);
        content = new char[length+1];
        strcpy(content, cString);
    }
};

int main(){
    // you can also write unit test by yourself:
 /*   MyString a;
    MyString b("shiina_orez");
    a.display();
    b.display();
    cout << "index :6 at shiina_orez is :" << b.at(6) << endl;
    cout << "length of shiina_orez is :" << b.length() << endl;
    b.clear();
    cout << "After clear(), is b empty() now?" << b.empty() << endl;
    MyString c("abc");
    MyString d("ABC");
    MyString _c("abc");
    cout << "abc == abc ?: " << c.compare(_c) << endl;
    cout << "abc == ABC ?: " << c.compare(d) << endl;
    cout << "I want to compare start at 10: " << c.compare(10, 3, _c) << endl;
    char s[20] = "I am shiina.";
    c.copy(s, 0, 3);
    cout << "Copy abc to 'I am shiina': " << s << endl;
    cout << "find 'A' in ABC: " << d.find('A') << endl;*/
    return 0;
}