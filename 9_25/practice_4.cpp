#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

class Point{
    private:
        double x,y;
    public:
        double distance(Point& p){
            double a=abs(x-p.x);
            double b=abs(y-p.y);
            return sqrt(a*a+b*b);
        }
    Point(double a,double b){
        x=a;
        y=b;
    }
    Point(){
        x=0;
        y=0;
    }
};

int main(){
    double a,b;
    printf("please input the first point: ");
    scanf("%lf %lf",&a,&b);
    Point p1=Point(a,b);
    printf("please input the second point: ");
    scanf("%lf %lf",&a,&b);
    Point p2=Point(a,b);
    printf("The distance: %.3lf",p1.distance(p2));
    return 0;
}