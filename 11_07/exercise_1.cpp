#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<iostream>
using namespace std;

class MyPoint{
    private:
        double  x;
        double y;
    public:
        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        double distance(MyPoint & other){
            return sqrt((other.getX()-x)*(other.getX()-x)+(other.getY()-y)*(other.getY()-y));
        }
    MyPoint(){
        x = 0.0;
        y = 0.0;
    }
    MyPoint(double _x, double _y){
        x = _x;
        y = _y;
    } 
};

class ThreeDPoint:public MyPoint{
    private:
        double z;
    public:
        double getZ(){
            return z;
        }
        double distance(ThreeDPoint & other){
            double _x = this->getX();
            double _y = this->getY();
            return sqrt((other.getX()-_x)*(other.getX()-_x)+(other.getY()-_y)*(other.getY()-_y)+(other.getZ()-z)*(other.getZ()-z));
        }
    ThreeDPoint(double _x, double  _y, double _z):MyPoint(_x, _y){
        z = _z;
    }
    ThreeDPoint():MyPoint(){
        z = 0;
    }
};

int main(){
    ThreeDPoint point_1(0, 0, 0);
    ThreeDPoint point_2(10, 30, 25.5);
    cout << point_2.distance(point_1) << endl;
    return 0;
}
