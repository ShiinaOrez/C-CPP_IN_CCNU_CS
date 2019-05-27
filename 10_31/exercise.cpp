#include<cstdio>
#include<iostream>
using namespace std;

class Shape{
    public:
        virtual void Show();
        virtual double GetArea();
    Shape(){}
};

class Rectangle: public Shape{
    private:
        int x,y;
    public:
        double GetArea(){
            return 1.0 * this->x * this->y;
        }
        void Show(){
            printf("[Rectangle]: (0, 0) - (%d, %d)\n", this->x, this->y);
            return;
        }
        void Set(int newX=-1, int newY=-1){
            if(newX >= 0)
                this->x = newX;
            if(newY >= 0)
                this->y = newY;
            return;
        }
        Rectangle():Shape(){
            this->x = 0;
            this->y = 0;
        }
        Rectangle(int x=0, int y=0):Shape(){
            this->x = x;
            this->y = y;
        }
};

class Circle: public Shape{
    public:
        int x;
        int y;
        double r;
    public:
        double GetArea(){
            return 3.1415926*r*r;
        }
        void Show(){
            printf("[Circle]: (%d, %d) - r: %.2f\n", this->x, this->y, this->r);
            return;
        }
        void Set(int x=-1, int y=-1, double r=-1.0){
            if(x>=0)
                this->x = x;
            if(y>=0)
                this->y = y;
            if(r>=0)
                this->r = r;
        }
    Circle():Shape(){
        this->x=0;
        this->y=0;
        this->r=0;
        return ;
    }
    Circle(int x=0, int y=0, double r=0.0):Shape(){
        this->x = x;
        this->y = y;
        this->r = r;
    }
};

class Triangle: public Shape{
    private:
        int ax;
        int bx;
        int cx;
        int ay;
        int by;
        int cy;
    public:
        double GetArea(){
            double a = sqrt((ax-bx)*(ax-bx)*1.0 + (ay-by)*(ay-by)*1.0));
            double b = sqrt((bx-cx)*(bx-cx)*1.0 + (by-cy)*(by-cy)*1.0);
            double c = sqrt((cx-ax)*(cx-ax)*1.0 + (cy-ay)*(cy-ay)*1.0);
            double p = (a+b+c)/2;
            return sqrt(p*(p-a)*(p-b)*(p-c));
        }
        void Show(){
            printf("[Triangle]: (%d, %d) - (%d, %d) - (%d, %d)\n", ax, ay, bx, by, cx, cy);
            return;
        }
        void Set(int ax, int ay, int bx, int by, int cx, int cy){
            this->ax = ax;
            this->bx = bx;
            this->cx = cx;
            this->ay = ay;
            this->by = by;
            this->cy = cy;
        }
        Triangle():Shape(){
            this->ax = 0;
            this->bx = 0;
            this->cx = 0;
            this->ay = 0;
            this->by = 0;
            this->cy = 0;
        }
        Triangle(int ax, int ay, int bx, int by, int cx, int cy):Shape(){
            this->ax = ax;
            this->bx = bx;
            this->cx = cx;
            this->ay = ay;
            this->by = by;
            this->cy = cy;
        }
}

int main(){
    // do it by yourself
}
