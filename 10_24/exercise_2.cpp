#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

bool isPrime(int n);
int lcm(int a, int b);
int gcd(int a, int b);

class Rational{
    private:
        int numerrator;
        int denominator;
    public:
        int getNumerrator(){
            return numerrator;
        }
        int getDenominator(){
            return denominator;
        }
        Rational add(Rational * sr){
            int sr_n = sr->getNumerrator();
            int sr_d = sr->getDenominator();
            int n = this->numerrator;
            int d = this->denominator;
            int l = lcm(sr_d,d);
            int v = n*(l/d)+sr_n*(l/sr_d);
            return Rational(v,l);
        }
        Rational subtract(Rational * sr){
            int sr_n = sr->getNumerrator();
            int sr_d = sr->getDenominator();
            int l = lcm(sr_d,this->denominator);
            return Rational(numerrator*(l/denominator)-sr_n*(l/sr_d),l);
        }
        Rational multiply(Rational * sr){
            int sr_n = sr->getNumerrator();
            int sr_d = sr->getDenominator();
            return Rational(sr_n*numerrator,sr_d*denominator);
        }
        Rational divide(Rational * sr){
            int sr_n = sr->getNumerrator();
            int sr_d = sr->getDenominator();
            return Rational(sr_d*numerrator,sr_n*denominator);
        }
        int compareTo(Rational * sr){
            int sr_n = sr->getNumerrator();
            int sr_d = sr->getDenominator();
            if(numerrator == sr_n && denominator == sr_d){
                return 0;
            }
            double sr_v = (sr_n*1.0)/(sr_d*1.0);
            double this_v = (numerrator*1.0)/(denominator*1.0);
            return (this_v < sr_v)?-1:1;
        }
        bool equals(Rational * sr){
            return !this->compareTo(sr);
        }
        int intValue(){
            return numerrator/denominator;
        }
        double doubleValue(){
            return (numerrator*1.0)/(denominator*1.0);
        }
        string toString(){
            if(denominator == 1) return to_string(numerrator);
            return to_string(numerrator)+string("/")+to_string(denominator);
        }
        Rational operator + (Rational sr);
        Rational operator - (Rational sr);
        Rational operator * (Rational sr);
        Rational operator / (Rational sr);
        int operator [] (int index);
    Rational(){
        numerrator = 0;
        denominator = 1;
    }
    Rational(int n,int d){
        numerrator = n;
        denominator = d;
        int mini = min(n,d);
        for(int i=2;i<=mini;i++){
            if(isPrime(i)){
                if(numerrator%i == 0 && denominator%i == 0){
                    numerrator/=i;
                    denominator/=i;
                    mini = min(numerrator, denominator);
                    i=1;
                }
            }
        }
    }

};

Rational Rational:: operator + (Rational sr){
    return this->add(&sr);
}

Rational Rational:: operator - (Rational sr){
    return this->subtract(&sr);
}

Rational Rational:: operator * (Rational sr){
    return this->multiply(&sr);
}

Rational Rational:: operator / (Rational sr){
    return this->divide(&sr);
}

int Rational:: operator [] (int index){
    if(index) return this->denominator;
    return this->numerrator;
}

bool isPrime(int n){
    if(n<=1) return false;
    for(int i=2;i<=(int)sqrt(n);i++){
        if(n%i == 0) return false;
    }
    return true;
}

int gcd(int a, int b){
    if(a<b) swap(a,b);
    if(b == 0) return a;
    else return gcd(b, a%b);
}

int lcm(int a, int b){
    return a*b/gcd(a, b);
}

int main(){
    Rational num_1(23,46);
    Rational num_2(12,36);
    cout << "first  number:" << num_1.toString() << endl;
    cout << "second number:" << num_2.toString() << endl;
    cout << "number 1 + number 2: " << (num_1+num_2).toString() << endl;
    cout << "number 1 - number 2: " << (num_1-num_2).toString() << endl;
    cout << "number 1 * number 2: " << (num_1.multiply(&num_2)).toString() << endl;
    cout << "number 1 / number 2: " << (num_1.divide(&num_2)).toString() << endl;
    cout << "number 1[0]? : "<< num_1[0] << endl;
    cout << "number 1[1]? : "<< num_1[1] << endl;
    return 0;
}