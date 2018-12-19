#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;

map<string, int> English;

bool comp_by_num(const pair<string, int>& ele1, const pair<string, int>& ele2){
    if (ele1.second == ele2.second){
        return ele1.first < ele2.first;
    }
    return ele1.second > ele2.second;
}

void count(vector<string> Input){
    for(int i=0;i<Input.size();i++){
        if(English.find(Input[i]) == English.end()){
            English.insert(pair<string, int>(Input[i], 1));
            continue;
        }
        else
            English[Input[i]]++;
    }
    vector<pair<string, int>> English_vec(English.begin(), English.end());
    sort(English_vec.begin(), English_vec.end(), comp_by_num);
    for(int i=0;i<English_vec.size();i++){
        cout << English_vec[i].first << " " << English_vec[i].second << endl;
    }
    return ;
}

int main(){
    string ss;
    vector<string> Input;
    for(int i=1;i<=10;i++){
        cin >> ss;
        Input.push_back(ss);
    }
    count(Input);
    return 0;
}
