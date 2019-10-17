#include <cstdio>
#include <iostream>

using namespace std;

void print_varints(int num) {
    bool buffer[32] = {false};
    for (int i=31; i>=0; i--) {
        buffer[i] = num&1;
        num >>= 1;
    }
    for (int i=0; i<32; i++) {
        cout << buffer[i]?1:0;
    }
    cout << endl;

    int flag = 0;
    while(!buffer[flag]) flag++;
    int index = 32, byte_num=0;
    while(index > flag) {
        index -= 7;
        byte_num += 1;
    }
    bool new_buffer[40], is_last = true;
    int pointer = 0;
    for (; byte_num>=1; byte_num--) {
        new_buffer[pointer] = !is_last;
        pointer++;
        if (is_last) is_last = false;

        for (int i=1; i<=7; i++) {
            new_buffer[pointer] = buffer[index];
            index++; pointer++;
        }
    }
    // cout << "[pointer]: " << pointer << endl;
    for (int i=1; i<=pointer/8; i++) {
        for (int j=pointer-8*i; j<pointer-8*(i-1); j++) {
            cout << new_buffer[j]?1:0;
        }
        if (i != pointer/8) {
            cout << "_";
        }
    }
    cout << endl;
}

int main() {
    int num1;
    cout << "Please input the number: ";
    cin >> num1;
    print_varints(num1);
    return 0;
}