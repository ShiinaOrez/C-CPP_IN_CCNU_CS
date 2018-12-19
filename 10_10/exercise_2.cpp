#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define maxn 1005
using namespace std;

const double pi=3.1415926;
class Circle{
    private:
        double r;
        double size;
    public:
        double getSize(){
            return size;
        }
    Circle(double r){
        this->r=r;
        size=pi*r*r;
    }
    Circle(){
        r=0.00;
        size=0.00;
    }
};

Circle * ca[maxn];

double sum(Circle * circleArray[],int size){
    double ans=0;
    for(int i=0;i<size;i++){
        ans+=circleArray[i]->getSize();
    }
    return ans;
}

int main(){
    int n;
    printf("please input the number=");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        double r;
        printf("please input the %d circle's r:",i);
        scanf("%lf",&r);
        Circle c(r);
        ca[i]=&c;
    }
    printf("%.5lf",sum(ca,n));
    return 0;
}
