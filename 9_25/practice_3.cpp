#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

class Ctriangle{
    private:
        int s[3];
    public:
        int sum(){
            return s[0]+s[1]+s[2];
        }
        double size(){
            double p=(s[0]+s[1]+s[2])/2;
            double res=sqrt(p*(p-s[0])*(p-s[1])*(p-s[2]));
            return res;
        }
    Ctriangle(int a,int b,int c){
        s[0]=a;
        s[1]=b;
        s[2]=c;
    }
    Ctriangle(){
        s[0]=0;
        s[1]=0;
        s[2]=0;
    }
};

int main(){
    int a,b,c;
    printf("please input 3 number: ");
    scanf("%d %d %d",&a,&b,&c);
    Ctriangle C=Ctriangle(a,b,c);
    if(C.size() > 0){
        printf("Sum: %d\n",C.sum());
        printf("Size: %.3lf\n",C.size());
    }
    else{
        printf("Data Error: please input the real data!\n");
    }
    return 0;
}