#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class F{
    private:
        double a;
        double b;
        double c;
    public:
        int judgeType(){
            double d=b*b-4*a*c;
            if(abs(d)<0.000001) return 0;
            if(d<0) return 2;
            if(d>0) return 1;
        }
        void display(){
            int type=judgeType();
            if(type==0){
                double ans=(-1*b+sqrt(b*b-4*a*c))/(2*a);
                printf("x1=x2=%.5lf\n",ans);
            }
            if(type==1){
                double x1=(-1*b+sqrt(b*b-4*a*c))/(2*a);
                double x2=(-1*b+sqrt(b*b-4*a*c))/(2*a);
                printf("x1=%.5lf;x2=%.5lf;\n",x1,x2);
            }
            if(type==2){
                double s=(-1*b)/(2*a);
                double x=sqrt(4*a*c-b*b)/(2*a);
                printf("x1=%.5lf+%.5lfi;x2=%.5lf+%.5lfi;",s,x,s,x);
            }
        }
    F(double a,double b,double c){
        this->a=a;
        this->b=b;
        this->c=c;
    }
};

int main(){
    double a,b,c;
    printf("please input 3 numbers:");
    scanf("%lf %lf %lf",&a,&b,&c);
    F f(a,b,c);
    f.display();
    return 0;
}
