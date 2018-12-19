#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<string>
#include<vector>
#include<time.h>

using namespace std;

struct date{
    int year;
    int month;
    int day;
};

struct CustData{
    string name;
    int age;
    date birthday;
    int grade;
    bool isMember;
};

struct DragData{
    string name;
    double value;
    int size;
    int restNumber;
    double price;
};

struct SellData{
    int dragID;
    string dragName;
    int total;
    double singlePrice;
    double allPrice;
    double discountPrice;
    double returnPrice;
    double getPrice;
    bool isMember;
    int memberID;
    int memberGrade;
};

struct EmplData{
    string name;
    int id;
    string job;
    int todayMashineID;
};

struct RecordData{
    int id;
    int casherID;
    int mashineID;
    date time;
    vector <SellData> sellData;
};

struct SelectData{
    int drag_id;
    int number;
};

int Month[13]={0,1,-2,1,0,1,0,1,1,0,1,0,1};
date TODAY=date{2018,10,8};
int REPO=10000;
double MONEY=100000;
int SECERT_KEY=314159;

void _abort(string e){
    cout << e ;
    return ;
}

class Cust{
    private:
        string name;
        int age;
        date birthday;
        int grade;
        bool isMember;
    public:
        CustData getInfo(){
            CustData data=CustData{name,age,birthday,grade,isMember};
            return data;
        }
        bool updateGrade(int num){
            if(!isMember){
                _abort("CustError: ");
                cout << "custom " << name << ", isn's a member."<< endl;
                return false;
            }
            if(num<0 && abs(num)>grade){
                _abort("CustError: ");
                cout << "custom "<< name <<"'s grade is not enough." << endl ;
                return false;
            }
            grade+=num;
            cout << "Custom " << name << "'s grade rest: " << grade << "." <<endl;
            return true;
        }
        bool beMember(){
            if(isMember){
                _abort("CustError: ");
                cout << "custom " << name <<" already be a member." << endl;
                return false;
            }
            isMember=true;
            grade=0;
            cout << "custom " << name << " is a member now!" << endl;
            return true;
        }
        bool changeName(string newName){
            if(name == newName){
                _abort("CustError ");
                printf("please input a different name.\n");
                return false;
            }
            name=newName;
            return true;
        }
        int checkAge(){
            int baseAge=TODAY.year-birthday.year-1;
            if(TODAY.month<birthday.month) 
                baseAge+=1;
            else if(TODAY.month==birthday.month && TODAY.day<=birthday.day){
                baseAge+=1;
            }
            if(age>baseAge){
                _abort("CustError: ");
                printf("Something wrong as your age!\n");
                return 0; // false
            }
            cout << "Custom " << name << "'s age is: " << age << "." << endl;
            age=baseAge;
            return age; 
        }
        bool isBirthday(){
            if(TODAY.month==birthday.month && TODAY.day==birthday.day)
                return true;
            return false;
        }
    Cust(CustData data){
        name=data.name;
        age=data.age;
        birthday=data.birthday;
        grade=data.grade;
        isMember=data.isMember;
    }
};

class Empl{
    private:
        string name;
        int id;
        string job;
        int todayMashineID;
    public:
        bool changeMashine(int mID){
            if(mID==todayMashineID)
                return false;
            todayMashineID=mID;
            return true;
        }
        EmplData getInfo(){
            EmplData data={name,id,job,todayMashineID};
            return data;
        }
    Empl(string Name,int ID,string Job){
        name=Name;
        id=ID;
        job=Job;
    }
};

class Drag{
    private:
        string name;
        double value;
        double price;
        int size;
        int restNumber;
    public:
        DragData getInfo(){
            DragData data=DragData{name = name,
                                   value = value,
                                   size = size,
                                   restNumber = restNumber};
            return data;
        }
        bool tryAddDrag(int number){
            if(REPO<size*number)
                return false;
            return true;
        }
        bool addDrag(int number){
            if(REPO<size*number){
                _abort("DragError: ");
                printf("reposity has no rest space.\n");
                return false;
            }
            if(MONEY<value*number){
                _abort("DragError: ");
                printf("your money isn't enough to add drag.\n");
                return false;
            }
            if(number>=0)
                MONEY-=(value*number);
            restNumber+=number;
            REPO-=(size*number);
            cout << "Add drag " << name << "'s for " << number << " successful." << endl;
            return true;
        }
        bool returnDrag(){
            if(restNumber<=0){
                _abort("DragError: ");
                cout << "drag " << name << "'s rest number already is 0." << endl;
                return false;
            }
            MONEY+=(restNumber*value);
            REPO+=(restNumber*size);
            restNumber=0;
            cout << "Return drag " << name << " successful." << endl;
            return true;
        }
    Drag(DragData data){
        name=data.name;
        value=data.value;
        price=data.price;
        size=data.size;
        restNumber=0;
    }
};

vector <Drag> Drags;
vector <Cust> Custs;

class ShoppingCart{
    private:
        vector <SelectData> Datas;
    public:
        double getTotal(){
            double response=0;
            for(int i=0;i<Datas.size();i++){
               Drag * drag=&Drags[Datas[i].drag_id-1];
               response+=Datas[i].number*drag->getInfo().price;
            }
            return response; 
        }
        bool ClearShoppingCart(int CustID){
            printf("---------------------------------------------\n");
            printf("Your drags count: %.3lf, are you ready to pay?\n",getTotal());
            printf("Pay Or NOT (P/N): ");
            char type;
            scanf("%c",&type);
            if(type=='n'||type=='N'){
                printf("...Kiding me?...But OK.\n");
                return false;
            }
            printf("OK, cash or Alipay? (C/A): ");
            scanf("%c",&type);
            printf("OK.\n");
            MONEY+=getTotal();
            if(Custs[CustID-1].getInfo().isMember){
                Cust * cust = &Custs[CustID-1];
                cust->updateGrade((int)getTotal());
                printf("Your Grade Now: %d.\n",cust->getInfo().grade);
            }
            Drag * now;
            for(int i=0;i<Datas.size();i++){
                now=&Drags[Datas[i].drag_id-1];
                now->addDrag(-1*Datas[i].number);
            }

            printf("Clear Finished! --over--.\n");
        }
    ShoppingCart(vector <SelectData> * origin){
        for(int i=0;i<origin->size();i++){
            this->Datas.push_back((*origin)[i]);
        }
        return ;
    }
};

class Record{
    private:
        int id;
        int casherID;
        int mashineID;
        date time;
        vector <SellData> sellData;
    public:
        bool postRecordData(vector <SellData> data){
            sellData=data;
            return true;
        }
        RecordData getInfo(){
            RecordData data={id,casherID,mashineID,time,sellData};
            return data;
        }
    Record(int rID,int cID,int mID){
        id=rID;
        casherID=cID;
        mashineID=mID;
        time=TODAY;
    }
};

void ShowDragTable(){
    int size=Drags.size();
    DragData data;
    printf("| id |   name   |  price   |   rest   |");
    for(int i=0;i<size;i++){
        data=Drags[i].getInfo();
        printf("|%4d|%10s| %10.5lf| %10d|",i+1,data.name,data.price,data.restNumber);
    }
    printf("----------------------------------");
    printf("count: %d",size);
    return ;
}

void AddNewDrag(){
    char quit;
    DragData data;
    printf("You want add a new Drag now?\nIf not, please input N/n to quit.\n");
    printf("Or input Y/y to continue.\n");
    scanf("%c",&quit);
    if(quit == 'N'|| quit == 'n') return ;
    printf("Please input new Drag name: ");
    scanf("%s",data.name);
    printf("Please input new Drag value: ");
    scanf("%lf",&data.value);
    printf("Please input new Drag price: ");
    scanf("%lf",&data.price);
    printf("Please input new Drag size: ");
    scanf("%d",&data.size);
    data.restNumber=0;
    Drag d(data);
    Drags.push_back(d);
    printf("Add a new Drag %s successful, id: %d.\n",data.name,(int)Drags.size());
    return ;
}

void DragPurchase(){
    char quit;
    int id,num;
    DragData data;
    printf("You want purchase now?\nIf not, please input N/n to quit.\n");
    printf("Or input Y/y to continue.\n");
    scanf("%c",&quit);
    if(quit == 'N'|| quit == 'n') return ;
    printf("Please input the Drag ID: ");
    scanf("%d",&id);
    data=Drags[id-1].getInfo();
    printf("You choose the %s.\n",data.name);
    printf("Your rest Money: %.3lf.\n",MONEY);
    printf("Your rest space is: %d.\n",REPO);
    printf("Drag: %s, rest: %d\n",data.name,data.restNumber);
    printf("Please input the number you want to purchase: ");
    bool response=false;
    do{
        scanf("%d",&num);
        Drags[id-1].tryAddDrag(num);
        if(response){
            response=Drags[id-1].addDrag(num);
            if(response){
                data=Drags[id-1].getInfo();
                printf("Purchase successfully!\n");
            }
        }
        else{
            printf("ValueError: Your want number is too big.\n");
            printf("Please input it again.\n");
        }
    }while(!response);
    return ;
}

void ReturnDrags(){
    char quit;
    int id;
    DragData data;
    printf("You want return a kind of drag now?\nIf not, please input N/n to quit.\n");
    printf("Or input Y/y to continue.\n");
    scanf("%c",&quit);
    if(quit == 'N'|| quit == 'n') return ;
    printf("Please input the id of you want to return: ");
    scanf("%d",&id);
    data=Drags[id-1].getInfo();
    printf("If you return %s, you will get %.3lf money, and %d space.\n",data.name,
                                                                        data.restNumber*data.value,
                                                                        data.restNumber*data.size);
    printf("Make sure you want to return it.\n");
    printf("(Y/N)");
    scanf("%c",&quit);
    if(quit == 'N'|| quit == 'n'){
        printf("Quit! Stop to return %s.\n",data.name);
        return ;
    }
    bool response=Drags[id-1].returnDrag();
    if(!response){
        printf("Quit! Stop to return %s.\n",data.name);
        return ;
    }
    printf("Return drag successfully!\n");
    return ;
}

void NextDay(){
    TODAY.day++;
    if(Month[TODAY.month]+1==TODAY.day && TODAY.month!=2){
        TODAY.month++;
        TODAY.day=1;
    }
    else if(Month[TODAY.month]+(TODAY.year%4==0)+1==TODAY.day && TODAY.month==2){
        TODAY.month++;
        TODAY.day=1;
    }

    if(TODAY.month==13){
        TODAY.year++;
        TODAY.month=1;
    }
    return ;
}

int Register(){
    CustData data;
    char type;
    printf("Now you are registing, please input your informatioin.\n");
    printf("Your Name: ");scanf("%s",data.name);
    printf("Your Age Now: ");scanf("%d",&data.age);
    printf("Your Birthday(Y M D): ");scanf("%d %d %d",&data.birthday.year,&data.birthday.month,&data.birthday.day);

    printf("Now your base information input over.\nDo you want to be member?(Y/N)\n");
    scanf("%c",&type);
    if(!(type=='n'||type=='N')){
        printf("The cost of member is 100, are you willing to give SM 100?(Y/N)\n");
        char willing;
        scanf("%c",&willing);
        if(!(willing=='n'||willing=='N')){
            printf("Cash Or Alipay?(C/A)\n");
            char way;
            scanf("%c",&way);
            MONEY+=100;
            data.isMember=true;
            data.grade=100;
            printf("You a member now!\n");
        }
        else{
            printf("Sorry, you can't be member QAQ.\n");
        }
    }
    else{
        printf("OK.\n");
    }

    Custs.push_back(data);
    int id=Custs.size();
    printf("Your Account: %s, ID: %d.\n",data.name,id);
    return id;
}

int Login(int id){
    if(id>Custs.size()||id<=0){
        _abort("Login Error: ");
        printf("Account ID not exist!\n");
        return 'e';
    }
    id--;
    Cust * cust=&Custs[id];
    printf("Login Successful!\n");
    return id^SECERT_KEY;
}

void ShowCustInfo(int cookie){
    int id=cookie^SECERT_KEY;
    Cust * cust=&Custs[id-1];
    CustData data=cust->getInfo();
    if(data.isMember)
        printf("******INFORMATION******\n");
    else    
        printf("------INFORMATION------\n");
    printf("|Name |%2s\n",data.name);
    printf("|Age  |%2d\n",data.age);
    printf("|Grade|%2d\n",data.grade);
    printf("-----------------------\n");
    return ;
}

double SelectDrags(int cookie){
    double count=0;
    vector <SelectData> shopping_cart;
    printf("Now it's time to select drags you want.\n");
    printf("Please see the format:\n");
    printf("Drag ID|Number (A drag single line.ID:-1 to over)");
    printf("Now, Start.\n");
    int drag_id,number;
    SelectData data;
    do{
        scanf("%d|%d",&drag_id,&number);
        if(drag_id==-1) break;

        Drag * drag=& (Drags[drag_id-1]);
        if(number>drag->getInfo().restNumber){
            _abort("DragError: ");
            printf("You want too much!\n");
            continue;
        }
        else{
            count+=drag->getInfo().price*number;
            data.drag_id=drag_id;
            data.number=number;
            shopping_cart.push_back(data);
        }
    }while(drag_id!=-1);

    ShoppingCart sc(&shopping_cart);
    printf("You will clear your shopping cart.\n");
    bool response=sc.ClearShoppingCart(cookie^SECERT_KEY);
    if(!response){
        _abort("ShoppingError: ");
        printf("Pay failed!\n");
        return 0.02;
    }
    else{
        printf("You clear shopping cart! Now return to table.\n");
        return count;
    }
}

void BuySomething(){
    int id;
    char quit;
    printf("You want buy something now?\nIf not, please input N/n to quit.\n");
    printf("Or input Y/y to continue.\n");
    scanf("%c",&quit);
    if(quit == 'N'|| quit == 'n') return ;

    printf("Now Login, If You Want To Registe, input 0.\nplease input your ID: ");
    scanf("%d",&id);
    if(!id){
        id=Register();
    }
    int cookie=Login(id);
    while(cookie=='e'){
        printf("Please input ID again(-1 To Exit): ");
        scanf("%d",&id);
        if(id==-1) break;
        cookie=Login(id);
    }
    if(cookie=='e'){
        _abort("Login Error: ");
        printf("Exit Login. Return to Table\n");
        return ;
    }
    ShowCustInfo(cookie);
    system("pause");
    ShowDragTable();
    double count=SelectDrags(cookie);

    printf("Welcome~\n");
    return ;
}

char word[50][50]={ "Show drags table",
                    "Add new kind of drags",
                    "Drags purchase",
                    "Return drags",
                    "To Next Day",
                    "Be A Custom And Buy Something",
                    "quit"};

void printBoard(){
    printf("REPO SIZE: %d\nMONEY REST: %.3lf\n",REPO,MONEY);
    printf("Input the number you want:\n");
    for(int i=0;;i++){
        if(word[i][0]=='_'){
            break;
        }
        printf("    %d: %s",i+1,word[i]);
    }
    printf("Please: ");
    return ;
}

int main(){
    int type;
    while(MONEY>=0){
        printBoard();
        scanf("%d",&type);
        if(type==0){
            ShowDragTable();
        }
        if(type==1){
            AddNewDrag();
        }
        if(type==2){
            DragPurchase();
        }
        if(type==3){
            ReturnDrags();
        }
        if(type==4){
            NextDay();
        }
        if(type==5){
            BuySomething();
        }
        if(type==6){
            break;
        }
    }
    printf("You quit the game, or your money is zero!\n");
    return 0;
}