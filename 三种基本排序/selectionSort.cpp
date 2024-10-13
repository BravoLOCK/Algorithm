#include <iostream>
template<class T>
class selectionSort{
public:
    void exchange(T& data1,T& data2){
        data1 = data1^data2;
        data2 = data1^data2;
        data1 = data1^data2;
    }
    void selectionsort(T* data,int size){
        for (int i = 0;i<size;++i){
            for (int j = i+1;j<size;++j){
                if (data[j]<data[i]){
                    exchange(data[i],data[j]);
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
    selectionSort<int> solve;
    solve.selectionsort(arr,10);
    solve.show(arr,10);
}