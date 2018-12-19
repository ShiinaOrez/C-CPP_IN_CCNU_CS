#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;

class StackOfInteger{
    private:
        int elements[100];
        int size;
    public:
        bool empty(){
            return (size==0);
        }
        int peek(){
            return elements[size-1];
        }
        int push(int value){
            if(size == 100){
                printf("StackError: Stack is full!\n");
                return size;
            }
            elements[size]=value;
            size++;
            return size;
        }
        int pop(){
            if(empty()){
                printf("StackError: Stack is empty!\n");
                return 12138;
            }
            int ans=elements[size-1];
            size--;
            return ans;
        }
        int getSize(){
            return size;
        }
    StackOfInteger(){
        for(int i=0;i<=99;i++) elements[i]=0;
        size=0;
    }
};

void print(bool response){
    if(response) printf("Stack is empty\n");
    else printf("Stack is not empty");
    return ;
}

int main(){
    StackOfInteger stack;
    for(int i=1;i<=50;i++){
        int len=stack.push(i);
        printf("Now stack have %d elements\n",len);
    }
    for(int i=1;i<=51;i++){
        int ele=stack.pop();
        if(ele == 12138) break;
        else{
            printf("Pop successful!\n");
        }
    }
    print(stack.empty());
    for(int i=1;i<=10;i++){
        int len=stack.push(i);
        printf("Now stack have %d elements\n",len);
    }
    printf("%d",stack.peek());
    return 0;
}