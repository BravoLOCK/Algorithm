#include <iostream>
#include <unordered_map>
using namespace std;
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode* rand;
    ListNode(int v) : val(v), next(nullptr),rand(nullptr) {}
};
//使用哈希表
ListNode* copyListWithRand(ListNode* head){
    unordered_map<ListNode*,ListNode*> map;//原节点和复制节点的映射
    ListNode* cur = head;
    while(cur!=nullptr){
        map[cur] = new ListNode(cur->val);
        cur = cur->next;
    }
    cur = head;
    while(cur!=nullptr){
        map[cur]->next = map[cur->next];//一一对应拷贝
        map[cur]->rand = map[cur->rand];
        cur = cur->next;
    }
    return map[head];
}