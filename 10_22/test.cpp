#include<cstdio>
#include<iostream>

using namespace std;

class human{
    private:
        int a;
        int b;
    public:
        int A(){
            return a;
        }
        int B(){
            return b;
        }
    human(int x,int y){
        this->a=x;
        this->b=y;
    }
};

class me: public human{
    private:
        int age;
    public:
        int getAge(){
            return age;
        }
    me(int age,int x,int y):human(x,y){
        this->age=age;
    }
};

int main(){
    me i(3,1,2);
    cout << i.getAge() << endl;
}
