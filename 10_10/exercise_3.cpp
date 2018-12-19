#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;

class Child{
    private:
        int id;
        Child * preChild;
        Child * nextChild;
    public:
        int getID(){
            return id;
        }
        int changePre(Child& pChild){
            preChild=&(pChild);
            return pChild.getID();
        }
        int changeNext(Child& pChild){
            nextChild=&(pChild);
            return pChild.getID();
        }
        Child * getPre(){
            return preChild;
        }
        Child * getNext(){
            return nextChild;
        }
    Child(int id){
        this->id=id;
    }
    Child(){
        return;
    }
};

class Circle{
    private:
        Child * nowChild;
        int w;
        int s;
        int count;
    public:
        int makeIt(){
            Child * removeChild;
            removeChild=nowChild->getNext();
            for(int i=1;i<s;i++){
                removeChild=removeChild->getNext();
            }
            Child * preChild=removeChild->getPre();
            Child * nextChild=removeChild->getNext();
            preChild->changeNext(*nextChild);
            nextChild->changePre(*preChild);
            printf("Sorry the id: %d boy has been removed.\n",removeChild->getID());
            nowChild=nextChild;
            count-=1;
            return count;
        }
    Circle(int n,Child& pChild){
        count=n;
        this->nowChild=&(pChild);
    }
};

Child children[1005];

int main(){
    int n,w,s;
    printf("please input the n,w,s:");
    scanf("%d %d %d",&n,&w,&s);
    Circle * c;
    Child preBoy(1);
    children[1]=preBoy;
    Child * firstBoy=&children[1];
    Child * lastBoy;
    printf("1");
    for(int i=2;i<=n;i++){
        Child nowBoy(i);
        children[i]=nowBoy;
        preBoy.changeNext(children[i]);
        children[i].changePre(preBoy);
        if(i==w){
            Circle C(n,children[i]);
            c=&C;
        }
        if(i==n)
            lastBoy=&children[i];
        preBoy=children[i];
    }
    firstBoy->changePre(*lastBoy);
    lastBoy->changeNext(*firstBoy);
    for(int i=1;i<=n;i++){
        c->makeIt();
    }
    return 0;
}