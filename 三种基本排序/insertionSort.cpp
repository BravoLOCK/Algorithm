#include <iostream>
template<class T>
class insertionSort{
public:
    void exchange(T& data1,T&data2){
        data1 = data1^data2;
        data2 = data1^data2;
        data1 = data1^data2;
    }
    void insertionsort(T* data,int size){
        for (int i = 0;i<size;++i){
            for (int j = size-1;j>i;--j){
                if (data[j]<data[j-1]){
                    exchange(data[j],data[j-1]);
                }
            }
        }
    }
    void show(T* data,int size){
        for (int i = 0;i<size;++i){
            std::cout<<data[i];
        }
    }
};
int main (void){
    int* arr = new int[10]{4,3,8,9,1,2,7,6,0,5};
    insertionSort<int> solve;
    solve.insertionsort(arr,10);
    solve.show(arr,10);
}
