#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<list>
#include<queue>
using namespace std;
list<int> * array[10005];
int n;

void _new(int num){
    list<int> * new_list;
    new_list = new list<int>;
    array[num] = new_list;
    return ;
}
void _add(int num, int value){
    list<int> * list_now;
    list_now = array[num];
    list_now->push_back(value);
    return ;
}
void _merge(int num1, int num2){
    array[num1]->sort();
    array[num2]->sort();
    array[num1]->merge(*array[num2]);
    array[num2]->clear();
    return ;
}
void _unique(int num){
    array[num]->unique();
    return ;
}
void _out(int num){
    array[num]->sort();
    list<int>::iterator it;
    for(it = array[num]->begin();it!=array[num]->end();it++){
        cout << *it << " ";
    }
    return ;
}
int main(){
    int num1,num2;
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        string order;
        cin >> order;
        if(order == "new"){
            cin >> num1;
            _new(num1);
        }
        if(order == "add"){
            cin >> num1 >> num2;
            _add(num1, num2);
        }
        if(order == "merge"){
            cin >> num1 >> num2;
            _merge(num1, num2);
        }
        if(order == "unique"){
            cin >> num1;
            _unique(num1);
        }
        if(order == "out"){
            cin >> num1;
            _out(num1);
        }
    }
    return 0;
}
