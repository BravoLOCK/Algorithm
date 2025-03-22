#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
int maxBit(int* arr,int n){
    int max = INT_MIN;
    for (int i = 0;i<n;++i){
        max = max>arr[i]?max:arr[i];
    }
    int res = 0;
    while(max!=0){
        res++;
        max/=10;
    }
    return res;
}
int getDigit(int x,int d){
    return x/(int)pow(10,d-1)%10;
}
void radixSort(int* arr,int L,int R,int digit){
    const int radix = 10;
    int i = 0,j = 0;
    int* help = new int[R-L+1];
    for (int d = 1;d<=digit;++d){
        int count[radix] = {0}; 
        //统计每个基数的个数
        for (int i = L;i<=R;++i){
            j = getDigit(arr[i],d);
            count[j]++;
        }
        for (int i = 1;i<radix;++i){
            count[i] = count[i]+count[i-1];//统计小于等于当前数的数的个数
        }
        //count[j]表示小于等于j的数的个数,表示的是在help中的位置
        //从右往左遍历，保证排序稳定性
        for (int i = R;i>=L;--i){
            j = getDigit(arr[i],d);
            help[count[j]-1] = arr[i];  //count[j]-1表示的是在help中的位置
            count[j]--;                 //--之后，更新索引
        }
        for (int i = L;i<=R;++i){
            arr[i] = help[i-L];
        }
    }
}