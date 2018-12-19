#include <queue>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
 * TEST Successful!
 * TEST Environment: Liunx/ Ubuntu 18.01 G++
 *
 * -----* TESTing Command *--------*
At the start you have 10 customs in defualt.

NextOne
    David: 12$
    Tom: 9$
    Frame: 3$
NextOne
    David: 6$
    Tom: 9$
    Frame: 9$
NextDay
    David: 18$
    Tom: 18$
    Frame: 42$
    Today we got: 78$.
    How many customs you want generate next day?: 3
NextOne
    David: No One To Serve. Poor guy.
    Tom: 12$
    Frame: 3$
NextOne
    David: No One To Serve. Poor guy.
    Tom: No One To Serve. Poor guy.
    Frame: 8$
    All barber is available now!
NextDay
    David: 0$
    Tom: 12$
    Frame: 11$
    Today we got: 23$.
    How many customs you want generate next day?: 100000
NextDay
    David: 435054$
    Tom: 323781$
    Frame: 216252$
    Today we got: 975087$.
    How many customs you want generate next day?: 999999
NextDay
    David: 4.34236e+06$
    Tom: 3.24754e+06$
    Frame: 2.16135e+06$
    Today we got: 9.75124e+06$.
Exit
    Bye~
*/

int _LEVEL[4] = {0, 20, 15, 10};
double _COMMENT[5] = {0, 0.9, 0.8, 0.6, 0.3};
int LENGTH;

class Custom{
private:
    bool alive;
public:
    int comment;
    int index;
    Custom(){
        alive = true;
        comment = (rand()%4) + 1;
        index = rand()%LENGTH;
    }
};

class Barber{
private:
    string name;
    int level;
    double profit;
    queue<Custom*> customs;
public:
    int nextCustom(bool silence){
        if (customs.empty()) {
            if (!silence)
                cout << this->name << ": No One To Serve. Poor guy." << endl;
            return 0;
        }
        int comment = customs.front()->comment;
        delete customs.front();
        this->customs.pop();
        this->profit += _LEVEL[this->level]*_COMMENT[comment];
        if (!silence)
            cout << this->name << ": " << _LEVEL[this->level]*_COMMENT[comment] << "$" << endl;
        return this->customs.size();
    }
    string Name(){
        return this->name;
    }
    double nextDay(){
        while(!this->customs.empty()){
            int re = this->nextCustom(true);
        }
        double pf = this->profit;
        this->profit = 0.0;
        cout << this->name << ": " << pf << "$" << endl;
        return pf;
    }
    void addCustom(Custom * newCustom){
        this->customs.push(newCustom);
        return;
    }
    Barber(){
        this->name = "";
        this->level = 3; //last level
        this->profit = 0.0;
    }
    Barber(string name, int level){
        this->name = name;
        this->level = level;
        this->profit = 0.0;
    }
};

vector <Barber*> BarberList;

int main() {
    cout << "At the start you have 10 customs in defualt." << endl << endl;
    srand(time(NULL));
    Barber *David = new Barber("David", 1);
    Barber *Tom = new Barber("Tom", 2);
    Barber *Frame = new Barber("Frame", 3);
    BarberList.push_back(David);
    BarberList.push_back(Tom);
    BarberList.push_back(Frame);
    LENGTH = BarberList.size();
    for (int i = 1; i <= 10; i++) {
        Custom *now = new Custom;
        BarberList[now->index]->addCustom(now);
    }
    string command;
    while (1) {
        cin >> command;
        if (command == "NextOne") {
            int num = 0;
            for (int i = 0; i < BarberList.size(); i++)
                num += BarberList[i]->nextCustom(false);
            if (!num) {
                cout << "All barber is available now!" << endl;
            }

        }
        if (command == "NextDay") {
            double pf = 0.0;
            for (int i = 0; i < BarberList.size(); i++)
                pf += BarberList[i]->nextDay();
            cout << "Today we got: " << pf << "$." << endl;
            cout << "How many customs you want generate next day?: ";
            int n;
            cin >> n;
            LENGTH = BarberList.size();
            for (int i = 1; i <= n; i++) {
                Custom *now = new Custom;
                BarberList[now->index]->addCustom(now);
            }
        }
        if (command == "Exit")
            break;
    }
    cout << "Bye~" << endl;
}