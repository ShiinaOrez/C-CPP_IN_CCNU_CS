#include <algorithm>
#include <iostream>
using namespace std;

bool comp(int &x, int &y)
{
    return x > y ? true: false;
}

int main(){
    int a[8] = {6, 5, 14, 23, 2, 9, 87, 10};
    sort(a+1, a+7, comp);
    for(int i=0; i<8; ++i){
        cout << a[i] << ",";
    }
    return 0;
}
