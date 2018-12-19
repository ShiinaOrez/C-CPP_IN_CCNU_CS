#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

/*
 * TEST Successful!
 * TEST Environment: Liunx/ Ubuntu 18.01 G++
 *
 * -----* TESTing Command *--------*

 * ~bash: g++ domain.cpp
 * ~bash: ./a.out
 * ~bash: Add one.ccnu.edu.cn 127.0.0.1
 * ~bash:                                  |>>> one.ccnu.edu.cn Add Successful
 * ~bash: Add spoc.ccnu.edu.cn 127.0.0.2
 * ~bash:                                  |>>> spoc.ccnu.edu.cn Add Successful
 * ~bash: ShowAll
 * ~bash:                                  |>>>:) one.ccnu.edu.cn 127.0.0.1
 * ~bash:                                  |>>>:) spoc.ccnu.edu.cn 127.0.0.2
 * ~bash: Find work.muxixyz.com
 * ~bash:                                  |>>>False
 * ~bash: Find one.ccnu.edu.cn
 * ~bash:                                  |>>>True 127.0.0.1
 * ~bash: Del spoc.ccnu.edu.cn
 * ~bash: ShowAll
 * ~bash:                                  |>>>:) one.ccnu.edu.cn 127.0.0.1
 * ~bash: Find spoc.ccnu.edu.cn
 * ~bash:                                  |>>>False
*/

struct DomainNode{
    DomainNode * preSubdomain;
    string content;
    vector<DomainNode*> next;
    int nodeCount;
    string host;
}Top;

string doc = ".";

class Domain{
private:
    string originDomain;
public:
    string getOriginDomain(){
        return originDomain;
    }
    stack <string> split(){
        stack <string> subdomain;
        subdomain.push(doc);
        string domain = this->originDomain;
        if (domain[0] == '.')
            domain = domain.substr(1, domain.size()-1);
        if (domain[domain.size()-1] == '.')
            domain = domain.substr(0, domain.size()-1);
        this->originDomain = domain;
        domain = domain + ".";
        do{
            int index = domain.find(".");
            string slice = domain.substr(0, index);
            subdomain.push(slice);
            domain = domain.substr(index+1, domain.size()-index+1);
        }while (domain.size() > 0 && domain.find(".") != domain.npos);
        return subdomain;
    }
    void update(Domain other){
        this->originDomain = other.getOriginDomain();
    }
    bool equal(Domain & other){
        stack <string> here = this->split();
        stack <string> there = other.split();
        if (here.size() != there.size())
            return false;
        while(!here.empty() && !there.empty()){
            if(here.top() != there.top())
                return false;
            here.pop();
            there.pop();
        }
        return true;
    }
    Domain(){
        this->originDomain = ".";
    }
    Domain(string domain){
        this->originDomain = domain;
    }
};

vector <Domain*> DomainList;

void AddDomainInTree(Domain * domain, string host){
    stack <string> List = domain->split();
    DomainNode * next, * now = &Top;
    while (!List.empty()){
        string subdomain = List.top();
        bool exist = false;
        for(int i=0;i<now->next.size();i++){
            if(now->next[i]->content == subdomain){
                exist = true;
                next = now->next[i];
                break;
            }
        }
        if(exist) {
            now->nodeCount++;
            now = next;
        }
        else{
            DomainNode * NewNode = new DomainNode;
            NewNode->content = subdomain;
            NewNode->preSubdomain = now;
            NewNode->nodeCount = 0;
            now->nodeCount++;
            now->next.push_back(NewNode);
            now = NewNode;
        }
        List.pop();
    }
    now->host = host;
    cout << domain->getOriginDomain() <<" Add Successful" << endl;
    return ;
}

void AddDomain(Domain domain, string host){
    for(int i=0;i<DomainList.size();i++){
        if(domain.equal(*DomainList[i]))
            return;
    }
    Domain * NewDomain = new Domain;
    NewDomain->update(domain);
    DomainList.push_back(NewDomain);
    AddDomainInTree(NewDomain, host);
    return;
}

string FindDomain(Domain domain){
    stack <string> List = domain.split();
    DomainNode * next, * now = &Top;
    while (!List.empty()){
//        cout << now->content <<now->nodeCount << " ";
        string subdomain = List.top();
        List.pop();
        bool exist = false;
        for(int i=0;i<now->next.size();i++){
            if(now->next[i]->content == subdomain){
                exist = true;
                next = now->next[i];
                break;
            }
        }
        if(exist){
            if(now->nodeCount == 0 && !List.empty())
                return doc;
            now = next;
        }
        else{
            return doc;
        }
    }
    return now->host;
}

void ShowAllDomain(){
    for(int i=0;i<DomainList.size();i++){
        if(FindDomain(*DomainList[i])!=doc) {
            cout << ":) " << DomainList[i]->getOriginDomain() << " " << FindDomain(*DomainList[i]) << endl;
        }
    }
    return ;
}

void DelDomain(Domain domain){

    stack <string> List = domain.split();
    stack <DomainNode*> delList;
    DomainNode * next, * now = &Top;
    delList.push(now);
    while (!List.empty()){
        string subdomain = List.top();
        bool exist = false;
        for(int i=0;i<now->next.size();i++){
            if(now->next[i]->content == subdomain){
                exist = true;
                next = now->next[i];
                break;
            }
        }
        if(exist){
            delList.push(next);
            now = next;
        }
        else
            return;
        List.pop();
    }
    while(!delList.empty()){
        DomainNode * now = delList.top();
        if(now->next.size() == 0||now->nodeCount == 0){
            DomainNode * pre = now->preSubdomain;
            for(int i=0;i<pre->next.size();i++){
                if(pre->next[i]->content == now->content)
                    pre->next[i]->content = doc;
            }
            pre->nodeCount--;
        }
        delList.pop();
    }
    return ;
}

int main(){
    Top.content = doc;
    string DomainString, type, host;
    while(1){
        cin >> type;
        if (type == "ShowAll"){
            ShowAllDomain();
            continue;
        }
        cin >> DomainString;
        Domain domain(DomainString);
        if (type == "Add"){
            cin >> host;
            AddDomain(domain, host);
        }
        if (type == "Del")
            DelDomain(domain);
        if (type == "Find")
            cout << (FindDomain(domain)!=doc?"True "+FindDomain(domain):"False") << endl;
    }
    return 0;
}
