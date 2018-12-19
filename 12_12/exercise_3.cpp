#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

set <int> s;
multiset <int> ms;

int main(){
    int n, num, tot;
    scanf("%d", &n);
    for (int i=0;i<n;i++){
        string command;
        cin >> command >> num;
        if(command == "add"){
            ms.insert(num);
            s.insert(num);
            cout << ms.count(num);
        }
        if(command == "del"){
            cout << ms.count(num);
            ms.erase(num);
        }
        if(command == "ask"){
            cout << (s.count(num) > 0 ? 1 : 0) << " " << ms.count(num);
        }
        cout << endl;
    }
    return 0;
}