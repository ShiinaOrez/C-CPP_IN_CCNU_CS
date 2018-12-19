#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
class Num{
    private:
        int value;
    public:
        int add(int number){
            return value+number;
        }
        int sub(int number){
            return value-number;
        }
        int mul(int number){
            return value*number;
        }
        int div(int number){
            if(!number){
                printf("ValueError: DivNumber can not be 0!\n");
                return -1;
            }
            return value/number;
        }
    Num(int number){
       value=number;
    }
};

int Integer(char * str){
    int length=strlen(str);
    int re=1,result=0;
    for(int i=length-1;i>=0;i--){
       result=result+re*(str[i]-'0');
        re*=10;
    }
    return result;
}

int main(int argc,char * argv[]){
    if(argc<4||argc>4){
        printf("CommandError: Excepting 3 arguments!\n");
        return 0;
    }
    int result;
    int number_1=Integer(argv[1]);
    int number_2=Integer(argv[2]);
    Num N=Num(number_1);
    switch(argv[3][0]){
        case '+':
            result=N.add(number_2);
            break;
        case '-':
            result=N.sub(number_2);
            break;
        case 'x':
            result=N.mul(number_2);
            break;
        case '/':{
            result=N.div(number_2);
            if(result==-1) return 0;
            break;
        }
        default:{
            printf("CommandError: Useless Operator!\n");
            return 0;
        }
    }
    printf("Result of %s %s %s is: %d\n",argv[1],argv[3],argv[2],result);
    return 0;
}
