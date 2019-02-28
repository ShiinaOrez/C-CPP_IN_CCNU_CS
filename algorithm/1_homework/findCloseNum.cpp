#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#define maxn 1005
using namespace std;

int arr[maxn];

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    sort(arr, arr+n);
    int close = arr[n-1]-arr[0], left=0, right=n-1;
    for(int i=0;i<n-1;i++){
        if(arr[i+1]-arr[i] < close){
            close = arr[i+1]-arr[i];
            left = i;
            right = i+1;
        }
    }
    cout << "Num1:" << arr[left] << " & Num2:" << arr[right] << " are most close!" <<endl;
    return 0;
}
