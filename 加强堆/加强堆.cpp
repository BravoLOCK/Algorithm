//没有规定小根堆就一定是>比较器，按喜好来
//但是小根堆用<，大根堆用>，非常清晰方便
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
template<class T>
class Greaterheap{
public:
    vector<T> heap; //动态数组用于存放数据
    unordered_map<T,int> indexMap;  //哈希表用于构建反向索引表，可以根据元素查位置
    int heapsize;                   //堆的大小
    bool (*comparator)(T& op1,T& op2);  //比较器
    Greaterheap(bool (*comp)(T& op1,T& op2)):heapsize(0),comparator(comp){}
    bool isEmpty(){
        return heapsize == 0;
    }
    int size(){
        return heapsize;
    }
    bool contains(T obj){
        if (indexMap.find(obj)!=indexMap.end()){
            return true;
        }
        else return false;
    }
    T peek(){   //peek方法不用检查堆是否为空，这个错误应由用户承担
        return heap[0];
    }
    void push(T obj){
        heap.push_back(obj);
        indexMap.insert({obj,heapsize});
        heapInsert(heapsize++);
    }
    void heapInsert(int index){
        while (comparator(heap[index],heap[(index-1)/2])){ 
            //小根堆比较器为<，那么子节点<父节点时，要交换，同时不会出现index = 0时的矛盾问题
            swap(index,(index-1)/2);    //交换索引表在swap中实现
            index = (index-1)/2;
        }
    }
    T pop(){
        T ans = heap[0];
        swap(0,heapsize-1);
        indexMap.erase(ans);
        heap.pop_back();
        heapsize--;
        heapify(0);
        return ans;
    }
    void resign(T obj){
        heapInsert(indexMap[obj]);
        heapify(indexMap[obj]); //两个操作都是O(logN)的复杂度,只会执行一个
    }
    void remove(T obj){         //删除借用了最后一个元素，所以要判断是否相同
        T replace = heap[heapsize-1];
        int index = indexMap[obj];
        indexMap.erase(obj);
        heap.erase(heap.begin()+(--heapsize));  //这里有待商榷，在实际使用时erase出现了问题
        if (obj!=replace){      //交换时一定要判断是否相同，不然会出现错误
            heap[index] = replace;
            indexMap[replace] = index;
            resign(replace);    //可能是大根堆，也可能是小根堆
        }
    }
    void heapify(int index){
        int left = index*2 +1;
        while(left<heapsize){
            int best = left+1<heapsize&&comparator(heap[left+1],heap[left])?left+1:left;
            //小根堆比较器为<，left+1<left时，选left+1
            best = comparator(heap[index],heap[best])?index:best;
            //index<best时，选index
            if (best == index)break;
            swap(index,best);
            index = best;
            left = index*2+1;
        }
    }
    void swap(int i,int j){ //交换两个元素时，不仅要交换堆中的元素，还要更新哈希表中的索引
        T o1 = heap[i];
        T o2 = heap[j];
        heap[i] = o2;
        heap[j] = o1;
        indexMap[o1] = j;
        indexMap[o2] = i;
    }
};