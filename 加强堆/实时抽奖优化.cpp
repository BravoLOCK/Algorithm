#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
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
    list<T> getAllElement(){
        list <T> ans;
        for (auto c:heap){
            ans.push_back(c);
        }
        return ans;
    }
};
class Customer{
public:
    int id;
    int buy;
    int enterTime;
    Customer(int id,int buy,int enterTime):id(id),buy(buy),enterTime(enterTime){}
};
bool candidatesComparator(Customer& c1,Customer& c2){
    return c1.buy!=c2.buy?(c1.buy>c2.buy):(c1.enterTime<c2.enterTime);
    //buy不同，buy大的在前；buy相同，enterTime小的在前
}
bool daddyComparator(Customer& c1,Customer& c2){
    return c1.buy!=c2.buy?(c1.buy<c2.buy):(c1.enterTime<c2.enterTime);
    //buy不同，buy小的在前；buy相同，enterTime小的在前,方便后面pop
}
class WhosYourDaddy{
public:
    unordered_map<int,Customer> customers;
    Greaterheap<Customer> candHeap;
    Greaterheap<Customer> daddyHeap;
    int daddyLimit;
    WhosYourDaddy(int limit):candHeap(candidatesComparator),daddyHeap(daddyComparator){}
    list<int> getDaddies(){
        list<Customer> cust = daddyHeap.getAllElement();
        list<int> ans;
        for (auto c:cust){
            ans.push_back(c.id);
        }
        return ans;
    }
    void operate(int time,int id,bool buyOrRefund){
        //用户如果第一次加进来并且操作为退货，直接忽略
        if (!buyOrRefund&&customers.find(id) == customers.end()){
            return;
        }
        //用户第一次加进来，写入哈希表中，时间在进堆时再改，购买/退货操作在下面单独处理。
        if (customers.find(id) == customers.end()){
            customers.insert({id,Customer(id,0,0)});
        }
        //用户操作
        Customer c = customers[id];
        if (buyOrRefund){
            c.buy++;
        }
        else{
            c.buy--;
        }
        //操作完后，可能会出现用户的数量为0的情况，这时既要将他从堆中删除，也要从表中删除
        //先从表中删除
        if (c.buy == 0){
            customers.erase(id);
        }
        //检查两个堆，如果用户都不在其中，说明用户第一次购买
        if (!candHeap.contains(c)&&!daddyHeap.contains(c)){
            //得讲未满直接加入得奖区
            if (daddyHeap.size()<daddyLimit){
                c.enterTime = time;
                daddyHeap.push(c);
            }
            else{
                c.enterTime = time;
                candHeap.push(c);
            }
        }
        //如果用户在其中一个之中，说明用户之前购买过，先检查这次操作是否将它从堆中删除
        else if (candHeap.contains(c)){
            if (c.buy==0){
                candHeap.remove(c);
            }
            else{
                candHeap.resign(c);
            }
        }
        else{
            if (c.buy == 0){
                daddyHeap.remove(c);
            }
            else{
                daddyHeap.resign(c);
            }
        }
        //操作完后检查两个堆是否要互倒
        daddyMove(time);
    }
    void daddyMove(int time){
        //如果候选区为空，说明不需要操作，为空不需要倒
        if (candHeap.isEmpty()){
            return;
        }
        //如果操作导致有人buy为0，跌出得奖区，此时候选区不为空，得奖区不满
        //操作完后候选区不为空当且仅当得奖区满员
        //操作过程中不一定如此
        if (daddyHeap.size()<daddyLimit){
            Customer p = candHeap.pop();
            p.enterTime = time;
            daddyHeap.push(p);
        }
        else{
            if (candHeap.peek().buy>daddyHeap.peek().buy){
                Customer olddaddy = daddyHeap.pop();
                Customer newdaddy = candHeap.pop();
                olddaddy.enterTime = time;
                newdaddy.enterTime = time;
                daddyHeap.push(newdaddy);
                candHeap.push(olddaddy);
            }
        }
    }
};
list<list<int> > topK(int* arr,bool* op,int k,int n){
    list<list<int> > ans;
    WhosYourDaddy* whoDaddies = new WhosYourDaddy(k);
    for (int i = 0;i<n;++i){
       whoDaddies->operate(i,arr[i],op[i]);
       ans.push_back(whoDaddies->getDaddies()); 
    }
    return ans;
}