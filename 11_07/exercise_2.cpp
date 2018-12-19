#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<iostream>
#include<algorithm>
// you can add more const number here...
#define PI 3.1415926

using namespace std;

// if you want to add a new class
// string Type = "Name you want print"
string R = "Rectangle";
string C = "Circle";
string T = "Triangle";

class Shape{
    public:
        string name;
        string Name(){
            return name;
        }
        virtual double getArea() {}
        void display(){
            cout << name << " " << getArea() << endl;
        }
    Shape(string name = string("Default")){
        this->name = name;
    }
};

bool operator<(Shape &x, Shape &y)
{
    return x.getArea() < y.getArea();
}

/* if you want to add a new class:
class NewClass: public Shape{
    private:
       a lot of attributes
    public:
        double getArea(){
            return the area;
        }
    NewClass():Shape(Type you define at first);
}*/

class Triangle: public Shape{
    private:
        int a;
        int b;
        int c;
    public:
        double getArea(){
            double p = (a+b+c)*1.0 / 2;
            return sqrt(p*(p-a)*(p-b)*(p-c));
        }
    Triangle(int a,int b,int c):Shape(T){
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

class Circle: public Shape{
    private:
        int r;
    public:
        double getArea(){
            return PI*r*r;
        }
    Circle(int r):Shape(C){
        this->r = r;
    }
};

class Rectangle: public Shape{
    private:
        int w;
        int h;
    public:
        double getArea(){
            return w*h*1.0;
        }
    Rectangle(int w, int h):Shape(R){
        this->w = w;
        this->h = h;
    }
};

Shape * array[105];

int main(){
    int n, w, h, r, a, b, c;
    char type;
    cin >> n;
    for(int i=1;i<=n;i++){
        getchar();
        scanf("%c\n", &type);
        Shape * obj = new Shape;
        switch (type){
            case 'R' :{
                cin >> w >> h;
                Rectangle re(w, h);
                obj = &re;
            }
            case 'C' :{
                cin >> r;
                Circle ci(r);
                obj = &ci;
            }
            case 'T' :{
                cin >> a >> b >> c;
                Triangle tr(a, b, c);
                obj = &tr;
            }
            default:
                array[i] = obj;
        }
    }
    sort(array+1,array+n+1);
    for(int i=1;i<=n;i++)
        array[i]->display();
    return 0;
}