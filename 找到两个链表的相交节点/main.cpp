#include <iostream>
#include <cmath>
using namespace std;
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};
//找到链表第一个入环节点，如果无环，返回nullptr
ListNode* getLoopNode(ListNode* head){
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr){
        return nullptr;
    }
    ListNode* slow = head->next;
    ListNode* fast = head->next->next;
    while(slow!=fast){
        //快指针走到尽头，无环
        if (fast->next == nullptr || fast->next->next == nullptr){
            return nullptr;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    //两个指针相遇
    //快指针回到头节点，慢指针不动
    fast = head;
    while(slow!=fast){  //两个指针相遇的位置就是入环节点
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
//两个无环链表的相交节点
ListNode* noLoop(ListNode* head1,ListNode* head2){
    if (head1 == nullptr || head2 == nullptr){
        return nullptr;
    }
    ListNode* cur1 = head1;
    ListNode* cur2 = head2;
    int n = 0;  //记录两个链表的长度差
    while(cur1->next!=nullptr){
        n++;
        cur1 = cur1->next;
    }
    while(cur2->next!=nullptr){
        n--;
        cur2 = cur2->next;
    }
    if (cur1!=cur2){
        return nullptr;
    }
    cur1 = n>0?head1:head2; //cur1指向长链表
    cur2 = cur1==head1?head2:head1; //cur2指向短链表
    n = abs(n);
    while(n!=0){
        n--;
        cur1 = cur1->next;
    }
    while(cur1!=cur2){
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return cur1;
}
ListNode* bothLoop(ListNode* head1,ListNode* head2,ListNode* loop1,ListNode* loop2){
    ListNode* cur1 = nullptr;
    ListNode* cur2 = nullptr;
    if (loop1 == loop2){
        cur1 = head1;
        cur2 = head2;
        int n = 0;
        while(cur1!=loop1){
            n++;
            cur1 = cur1->next;
        }
        while(cur2!=loop2){
            n--;
            cur2 = cur2->next;
        }
        cur1 = n>0?head1:head2;
        cur2 = cur1==head1?head2:head1;
        n = abs(n);
        while(n!=0){
            n--;
            cur1 = cur1->next;
        }
        while(cur1!=cur2){
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return cur1;
    }
    else{
        cur1 = loop1->next; //从loop1的下一个节点开始
        while (cur1!=loop1){//循环一圈，如果遇到loop2，返回loop1
            if (cur1 == loop2){
                return loop1;   //返回任意一个入环节点
            }
            cur1 = cur1->next;
        }
        return nullptr;
    }
}
ListNode* getIntersectNode(ListNode* head1,ListNode* head2){
    if (head1 == nullptr||head2 == nullptr){
        return nullptr;
    }
    ListNode* loop1 = getLoopNode(head1);
    ListNode* loop2 = getLoopNode(head2);
    if (loop1 == nullptr && loop2 == nullptr){
        return noLoop(head1,head2);
    }
    if (loop1 != nullptr && loop2 != nullptr){
        return bothLoop(head1,head2,loop1,loop2);
    }
    return nullptr;
}