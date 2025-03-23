#include <iostream>
using namespace std;
class ListNode{
public:
    int val;
    ListNode* next;
    ListNode* rand;
    ListNode(int v):val(v),next(nullptr),rand(nullptr){}
};
ListNode* copyListNodeWithRand(ListNode* head){
    if (head == nullptr){
        return nullptr;
    }
    ListNode* cur = head;
    ListNode* next = nullptr;
    //将复制节点插入到原节点后面
    while(cur!=nullptr){
        next = cur->next;
        cur->next = new ListNode(cur->val);
        cur->next->next = next;
        cur = next;
    }
    cur = head;
    ListNode* copy = nullptr;
    //复制rand指针
    while(cur!=nullptr){
        next = cur->next->next;
        copy = cur->next;
        copy->rand = cur->rand!=nullptr?cur->rand->next:nullptr;
        cur = next;
    }
    //返回复制链表的头节点
    ListNode* res = head->next;
    cur = head;
    //分离复制链表
    while(cur!=nullptr){
        next = cur->next->next;//next为原链表的下一个节点
        copy = cur->next;//copy为复制链表的节点
        cur->next = next;//恢复原链表
        copy->next = next!=nullptr?next->next:nullptr;//注意这里的next可能为空
        cur = next;//分离复制链表
    }
    //必须三个while循环分开写，否则会出错，因为要从原节点找到复制节点
    return res;
}