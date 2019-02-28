#include<cstdio>
#include<iostream>
#define maxn 1005
using namespace std;

int arr[maxn];

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
    }
    int min=arr[0], max=arr[0], key=0;
    for(int i=0;i<n;i++){
        if(arr[i] < min){
            min = arr[i];
        }
        if(arr[i] > max){
            max = arr[i];
        }
    }
    for(int i=0;i<n;i++){
        if(arr[i]<max && arr[i]>min){
            key = i;
            break;
        }
    }
    printf("%d", arr[key]);
    return 0;
}
