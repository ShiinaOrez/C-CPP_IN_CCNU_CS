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

bool isPrime(int k){
    for(int i=2;i<=(int)sqrt(k);i++){
        if(k%i==0) return false;
    }
    return true;
}

int NextPrime(int k){
    while(!isPrime(++k));
    return k;
}

int main(){
    StackOfInteger stack;
    int x;
    printf("Please input a positive number: ");
    scanf("%d",&x);
    int k=2;
    while(1){
        printf("k=%d, n=%d\n",k,x);
        if(k==x){
            stack.push(k);
            break;
        }
        if(k<x&&x%k==0){
            stack.push(k);
            x/=k;
            continue;
        }
        k=NextPrime(k);
    }
    while(!stack.empty()){
        printf("%d ",stack.pop());
    }
    printf("\n");
    return 0;
}