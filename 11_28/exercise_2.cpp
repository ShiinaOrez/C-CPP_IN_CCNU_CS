#include <iostream>
#include <string>
using namespace std;

template <class T>
T ArraySum(T* start, T* end){
    T sum = *start;
    T* now;
    for(int i = 1;&start[i] != end;i++){
//        cout << now << " " << sum << endl;
        now = &start[i];
        sum += start[i];
    }
    return sum;
}

int main(){
    string array[4] = {"Tomy", "Jacy", "Mary", "John"};
    cout << ArraySum(array, array+4) << endl;
    int a[4] = {1,2,3,4};
    cout << ArraySum(a, a+4) << endl;
    return 0;
}
