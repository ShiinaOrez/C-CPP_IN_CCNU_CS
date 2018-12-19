#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;

class MyInteger{
    private:
        int value;
    public:
        int getValue(){
            return value;
        }
        bool isEven(){
            if(value%2==0) return true;
            else return false;
        }
        bool isPrime(){
            if(value<=1){
                return false;
            }
            else{
                for(int i=2;i<=(int)sqrt(value);i++){
                    if(value%i==0){
                        return false;
                    }
                }
                return true;
            }
        }
        bool equals(int x){
            return (x==value);
        }
        bool equals(MyInteger & OtherInteger){
            return (value==OtherInteger.getValue());
        }
    MyInteger(){
        value=0;
    }
    MyInteger(int x){
        value=x;
    }
};

void print(bool response){
    if(response) printf("True\n");
    else printf("False\n");
}

int main(){
    MyInteger first(5);
    print(first.isEven());
    print(first.isPrime());
    print(first.equals(3)); 
    print(first.equals(5));
    MyInteger second(6);
    print(first.equals(second));
    return 0;
}
