#include<cstdio>
#include<string>
#include<algorithm>
#include<iostream>

using namespace std;

struct node{
    int num;
    node * next;
};

class proxy{
    private:
        int num;
    public:
        int * address;
        void operator = (int value);
        int operator & ();
        int getNum(){
            return num;
        }
    proxy(){
        return ;
    }
    proxy(int n){
        this->num = n;
    }
};

class CArray{
    private:
        node head;
        int l;
    public:
        int length(){
            return this->l;
        }
        int push_back(int value){
            node * now = &this->head;
            while(now->next != &this->head){
                now = now->next;
            }
            node * n = new node;
            n->num = value;
            n->next = now->next;
            now->next = n;
//            cout << now << " " << now->num << " " << now->next << endl;
//            cout << now->next << " " << now->next->num << " " << now->next->next << endl;
            this->l+=1;
        }
        int * getItem(int index){
            node * now = &head;
            for(int i=0;i<=index;i++){
                now = now->next;
            }
            return &(now->num);
        }
        node getHead(){
            return head;
        }
        proxy operator [] (int index);
    CArray(CArray & a){
        this->head = a.getHead();
        this->l = a.length();
    }
    CArray(){
        node h;
        this->head = h;
        this->head.next = &this->head;
        this->head.num = 0;
        this->l = 0;
        printf("New Array Build Successful!\n");
    }
};

proxy CArray:: operator [] (int index){
    if(index>this->length()-1){
        printf("IndexError: Out of limit.\n");
        return 0;
    }
    int * value = this->getItem(index);
    proxy p(*value);
    p.address = value;
    return p;
}

void proxy:: operator = (int value){
    *(this->address) = value;
    return ;
}

int proxy:: operator & (){
    return this->getNum();
}

ostream& operator<<(ostream& out, const proxy& p){
    out << *(p.address);
    return out;
}
int main(){
    CArray a;
    for(int i=0;i<5;i++)
        a.push_back(i);
    CArray a2,a3;
    a2=a;
    for(int i=0;i<a2.length();i++)
        cout << a2[i] << " ";
    cout << endl;
    a2=a3;
    for(int i=0;i<a2.length();i++)
        cout << a2[i] << " ";
    a[3]=100;
    CArray a4 = a;
    for(int i=0;i<a4.length();i++)
        cout << a4[i] << " ";  
    cout << endl;
    return 0;
}
