#include<iostream>
template<class T>
class FindNum{
    int findNumInSortedArray(T* data,int size,T tar){
        int mid = L+((R-L)<<1);
        while(L<R)
        {
            if (data[mid]<tar){
                L = mid;
                mid = L+((R-L)<<1);
            }
            else if (data[mid]>tar){
                R = mid;
                mid = L +((R-L)<<1);
            }
            else{
                return mid;
            }
        }
        if (data[L] == tar){
            return L;
        }
        else{
            return -1;
        }
    }
};