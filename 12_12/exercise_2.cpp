#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point{
    int x;
    int y;
};

class Rule1{
public:
    bool operator() (int & x, int & y){
        if (x%10 == y%10)
            return x > y ? true : false;
        return x%10 < y%10 ? true : false;
    }
};

class Rule2{
public:
    bool operator() (Point & x, Point & y){
        if ((x.x*x.x + x.y*x.y)==(y.x*y.x + y.y*y.y)){
            if (x.x == y.x)
                return x.y < y.y ? true : false;
            return x.x < y.x ? true : false;
        }
        return (x.x*x.x + x.y*x.y) < (y.x*y.x + y.y*y.y) ? true : false;
    }
};

int main(){
    int a[8] = {6, 5, 55, 23, 3, 9, 87, 10};
    sort(a, a+8, Rule1());
    for (int i=0; i<8; ++i){
        cout << a[i] << ",";
    }
    cout << endl;
    Point ps[8] = {{1,0}, {0,1}, {0,-1}, {-1,0}, {1,-1}, {1,1}, {2,0}, {-2,0}};
    sort(ps, ps+8, Rule2());
    for (int i=0; i<8; ++i){
        cout << "(" << ps[i].x << "," << ps[i].y << ") ";
    }
    return 0;
}