#include<cstdio>
#include<iostream>
using namespace std;

class Shape{
    private:
        double area;
    public:
        double getA(){
            return this->area;
        }
    Shape(){
        this->area = 0;
    }
    Shape(double a){
        this->area = a;
    }
};

class Rectangle: public Shape{
    private:
        int x,y;
    public:
        double area(){
            return getA();
        }
    Rectangle():Shape(){
        x=0;
        y=0;
    }
    Rectangle(int x,int y):Shape(1.0*x*y){
        this->x = x;
        this->y = y;
    }
};

class Circle: public Shape{
    public:
        int r;
    public:
        double area(){
            return getA();
        }
    Circle():Shape(){
        r=0;
        return ;
    }
    Circle(int r):Shape(3.1415926*r*r){
        this->r = r;
    }
};

int main(){
    Rectangle a(2,4);
    Circle c(3);
    cout << a.area() << " " << c.area() << endl;
}