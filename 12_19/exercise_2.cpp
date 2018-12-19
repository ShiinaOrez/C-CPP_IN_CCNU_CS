#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

int tot = 0;
map<string, int> English;
string stop_word[] = {"a", "an", "in", "about", "for", "be", "is", "am", "are", "etc"};
set<string> StopWord(stop_word, stop_word + sizeof(stop_word)/ sizeof(*stop_word));

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
    for(int i=0;i<English_vec.size() && i<20;i++){
        cout << i << ".| " << English_vec[i].first << " " << ((double)English_vec[i].second)/tot << endl;
    }
    return ;
}

string endwith(string s){
    if (!(s[s.size()-1] <= 'Z' && s[s.size()-1] >= 'A') && !(s[s.size()-1] <= 'z' && s[s.size()-1] >= 'a') ){
        return s.substr(0, s.size()-1);
    }
    return s;
}

int main(int argc, char * argv[]){
    string ss;
    vector<string> Input;
    for(int i=1;i<argc;i++){
        string filename(argv[i]);
        ifstream infile;
        infile.open(filename, ios::in);
        while(infile >> ss){
            ss = endwith(ss);
            transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
            if(StopWord.find(ss) != StopWord.end())
                continue;
            Input.push_back(ss);
            tot ++;
        }
        infile.close();
    }
    count(Input);
    return 0;
}
