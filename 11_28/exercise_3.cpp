#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

template <class T>
class Stack{
    private:
        T elements[100];
        int size;
    public:
        bool empty(){
            return (!size);
        }
        T peek(){
            return elements[size-1];
        }
        void push(T value){
            if(size >= 100){
                cout << "StackError: " << "Stack is FULL!" << endl;
                return ; 
            }
            elements[size] = value;
            size ++;
            return ;
        }
        T pop(){
            if(empty()){
                cout << "StackError: " << "Stack is EMPTY!" << endl;
            }
            size --;
            return elements[size];
        }
        int getSize(){
            return size;
        }
    Stack(){
        size = 0;
    }
};

int main(){
    Stack <double> stack_double;
    Stack <int> stack_int;
    for(int i=0;i<=6;i++){
        stack_double.push(i*2.3);
        stack_int.push(i);
    }
    for(int i=0;i<=6;i++){
        cout << stack_double.pop() <<  " " << stack_int.pop() << endl;
    }
    return 0;
}