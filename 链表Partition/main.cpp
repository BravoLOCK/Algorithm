#include <iostream>
using namespace std;
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};
ListNode* ListPartition(ListNode* head,int pivot){
    ListNode* sh = nullptr;
    ListNode* st = nullptr;
    ListNode* eh = nullptr;
    ListNode* et = nullptr;
    ListNode* bh = nullptr;
    ListNode* bt = nullptr;
    ListNode* next = nullptr;   //保存下一个节点,初始化为nullptr
    while(head!=nullptr){
        next = head->next;
        head->next = nullptr;//将原链表中的节点断开
        if(head->val<pivot){
            if (sh == nullptr){
                sh = head;
                st = head;
            }
            else{
                st->next = head;
                st = head;
            }
        }
        else if (head->val == pivot){
            if (eh == nullptr){
                eh = head;
                et = head;
            }
            else{
                et->next = head;
                et = head;
            }
        }
        else{
            if (bh == nullptr){
                bh = head;
                bt = head;
            }
            else{
                bt->next = head;
                bt = head;
            }
        }
        head = next;
    }
    //将三个链表连接起来
    if (st !=nullptr){
        st->next = eh;  
        et = et == nullptr ? st : et;   //没有小于区域，让st代替et去连接大于区域
    }
    if (et != nullptr){ //et在等于区域不为空时为et，为空时为st，只
        et->next = bh;  //有小于区域为空等于区域也为空时et才为空
    }
    return sh != nullptr ? sh :(eh!=nullptr?eh:bh);
}