#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<string>
using namespace std;

class str{
    private:
        string origin;
    public:
        string append(char end){
            origin = origin + end;
        }
    str(){
        origin = "test";
    }
    str(string from){
        origin = from;
    }
};

class screen{
    private:
        str include;
        str readonly;
    public:
        str append(char ends){
            include = include.append(ends);
            return include;
        }
        str add(str tail = readonly){
            include = include + tail;
            tail = tail.append('$');
            return include;
        }
        void print_readonly(){
            printf("readonly: %s \n",readonly);
        }
        void show(){
            printf("screen: %s\n",include);
        }
    screen(){
        include = readonly;
    }
    screen(str inc){
        include = inc;
    }
};

int main(){
    str a("hello,world");
    screen s();
    screen c(a);
    s.print_readonly();
    c.print_readonly();
    s.append('!');
    c.append('!');
    s.add();
    s.show();
    s.print_readonly();
    s.add("!");
    s.show();
    s.print_readonly();
    s.add();
    s.show();
    s.print_readonly();
    return 0;
}
