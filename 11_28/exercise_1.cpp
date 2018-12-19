#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

template <class T>
bool is_sorted(T array[], int len){
    bool flag = true;
    bool compare = false;
    if(len >= 2)
        if(array[0] > array [1]) compare = true;
    for(int i=0;i<len-1;i++){
        if((array[i] > array[i+1]) == compare)
            continue;
        else{
            flag = false;
            break;
        }
    }
    return flag;
}

int main(){
    int test_int[6] = {1,2,5,4,5};
    double test_double[6] = {5.5, 4.4, 3.3, 2.2, 1.1};
    cout << is_sorted((int *)test_int, 5) << endl;
    cout << is_sorted((double *)test_double, 5) << endl;
    return 0;
}