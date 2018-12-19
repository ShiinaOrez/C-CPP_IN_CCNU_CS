#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

int main(){
    int n;
    printf("please input the width: ");
    scanf("%d",&n);
    int m[50][50];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&m[j][n-i-1]);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    return 0;
}