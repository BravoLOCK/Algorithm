#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
using namespace std;
//不优化的实时抽奖
class Customer{
public:
    int id;
    int buy;
    int enterTime;
    Customer(int id,int buy,int enterTime):id(id),buy(buy),enterTime(enterTime){}
};
list<int> getCurAns(vector<Customer>& daddy){
    list<int> ans;
    for (int i = 0;i<daddy.size();++i){
        ans.push_back(daddy[i].id);
    }
    return ans;
}
bool contains(vector<Customer>& vec,int id){
    for(int i = 0;i<vec.size();++i){
        if (vec[i].id == id){
            return true;
        }
    }
    return false;
}
void cleanZeroBuy(vector<Customer>& daddy){
    for (int i = 0;i<daddy.size();++i){
        if (daddy[i].buy == 0){
            daddy.erase(daddy.begin()+i);
            i--;
        }
    }
}
bool candidatesComparator(Customer& c1,Customer& c2){
    return c1.buy!=c2.buy?(c1.buy>c2.buy):(c1.enterTime<c2.enterTime);
    //buy不同，buy大的在前；buy相同，enterTime小的在前
}
bool daddyComparator(Customer& c1,Customer& c2){
    return c1.buy!=c2.buy?(c1.buy<c2.buy):(c1.enterTime<c2.enterTime);
    //buy不同，buy小的在前；buy相同，enterTime小的在前,方便后面pop
}
void move(vector<Customer>cands,vector<Customer>& daddy,int k,int time){
    if (cands.size()==0){
        return ;            //没有候选人(daddy未满，或者cleanZeroBuy后),直接返回
    }
    if(daddy.size()<k){
        Customer c = cands[0];
        c.enterTime = time;
        daddy.push_back(c);
        cands.erase(cands.begin());
    }
    else{
        if (cands[0].buy>daddy[0].buy){
            Customer oldDaddy = daddy[0];
            daddy.erase(daddy.begin());
            Customer newDaddy = cands[0];
            cands.erase(cands.begin());
            newDaddy.enterTime = time;
            oldDaddy.enterTime = time;
            daddy.push_back(newDaddy);
            cands.push_back(oldDaddy);
            //一次行动只会发生一次move，所以move之后，不需要额外排序重新调整
        }
    }
}
list<list<int>> compare(int arr[],bool op[],int n,int k){
    unordered_map<int,Customer> map;
    vector<Customer> candidates;
    vector<Customer> daddy;
    list<list<int>> ans;    //存放每次抽奖的结果
    for (int i = 0;i<n;++i){
        int id = arr[i];
        bool buyOrRefund = op[i];
        if (!buyOrRefund&&map.find(id)==map.end()){ //退票且不存在
            ans.push_back(getCurAns(daddy));
            continue;
        }
        if (map.find(id)==map.end()){   //买票且不存在
            map.insert({id,Customer(id,0,0)});//初始化
        }
        Customer& c = map[id];

        //调整buy值
        if (buyOrRefund){
            c.buy++;
        }
        else{
            c.buy--;
        }
        //如果buy为0，先将它从map中删除
        if (c.buy == 0){
            map.erase(id);
        }
        //如果候选队列和daddy队列中都没有这个人，说明这个人是新来的
        if(!contains(candidates,id)&&!contains(daddy,id)){
            //准备入队
            if (daddy.size()<k){
                c.enterTime = i;//入队时才记录时间
                daddy.push_back(c);
            }
            else{
                c.enterTime = i;
                candidates.push_back(c);
            }
        }
        //操作可能是买票，也可能是退票，所以可能会有人buy为0，要将他们清除
        cleanZeroBuy(daddy);
        cleanZeroBuy(candidates);
        //清除完后要按比较器重新排序，方便后面的move
        sort(candidates.begin(),candidates.end(),candidatesComparator);
        sort(daddy.begin(),daddy.end(),daddyComparator);
        move(candidates,daddy,k,i);
        ans.push_back(getCurAns(daddy));
    }
    return ans;
}