//
// Created by song-ruyang on 18-11-21.
//

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

class Complex{
    private:
        double a;
        double b;
    public:
        Complex add(Complex & other){
            Complex rv(a+other.a, b+other.b);
            return rv;
        }
        Complex subtract(Complex & other){
            Complex rv(a-other.a, b-other.b);
            return rv;
        }
        Complex multiply(Complex & other){
            Complex rv(a*other.a-b*other.b, b*other.a+a*other.b);
            return rv;
        }
        Complex divide(Complex & other){
            double C = other.a*other.a+other.b*other.b;
            Complex rv((a*other.a+b*other.b)/C, (b*other.a-a*other.b)/C);
            return rv;
        }
        string toString(){
            if(abs(b) < 1e-6){
                return to_string(a);
            }
            return to_string(a)+string(" + ")+to_string(b)+string("i");
        }
        Complex operator + (Complex & other){
            return add(other);
        }
        Complex operator - (Complex & other){
            return subtract(other);
        }
        Complex operator * (Complex & other){
            return multiply(other);
        }
        Complex operator / (Complex & other){
            return divide(other);
        }
        Complex operator + (){
            return add(*this);
        }
        Complex operator - (){
            return subtract(*this);
        }
        Complex operator * (){
            return multiply(*this);
        }
        void operator += (Complex & other);
        void operator -= (Complex & other);
        double operator [] (int pos);
        Complex &operator ++ ();
        Complex &operator -- ();
        Complex operator ++ (int);
        Complex operator -- (int);
        Complex operator << (int num);
        Complex operator >> (int num);
    Complex(double a, double b){
        this->a = a;
        this->b = b;
    }
    Complex(double a){
        this->a = a;
        this->b = 0.0;
    }
    Complex(){
        this->a = 0.0;
        this->b = 0.0;
    }
};

void Complex::operator+=(Complex &other){
    this->a += other.a;
    this->b += other.b;
}
void Complex::operator-=(Complex &other){
    this->a -= other.a;
    this->b -= other.b;
}
double Complex::operator[](int pos){
    if(pos) return b;
    return a;
}
Complex& Complex::operator++(){
    this->a += 1;
    return *this;
}
Complex Complex::operator++(int){
    ++(*this);
    return *this;
}
Complex& Complex::operator--(){
    this->a -= 1;
    return *this;
}
Complex Complex::operator--(int){
    --(*this);
    return *this;
}
Complex Complex::operator<<(int num){
    this->a = double(int(this->a) << num);
    return *this;
}
Complex Complex::operator>>(int num){
    this->a = double(int(this->a) >> num);
    return *this;
}

int main(){
    Complex a(1,2);
    Complex b(3);
    Complex c();
    cout << a.toString() << endl;
    a++;
    cout << a.toString() << endl;
    ++a;
    cout << a.toString() << endl;
    a+=b;
    cout << a.toString() << endl;
    a=a*a;
    cout << a.toString() << endl;
    a=+a;
    cout << a.toString() << endl;
    return 0;
}