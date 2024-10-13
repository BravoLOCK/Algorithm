#include <iostream>
#include <cstdlib>
#include <ctime>
class comparator{
public:
    int* getRandomArray(int size,int L,int R){
        int* randomArray = new int[size];
        srand(time(0));
        for (int i = 0;i<size;++i){
            randomArray[i] = rand()%(R-L+1)+L;
        }
        return randomArray;
    }
};
int main (void){
    comparator comp;
    int* arr = comp.getRandomArray(5,1,10);
    for (int i = 0;i<5;++i){
        std::cout<<arr[i];
    }
}