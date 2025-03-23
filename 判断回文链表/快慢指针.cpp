#include <iostream>
using namespace std;
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};
bool isPalindrome(ListNode* head){
    if (head == nullptr||head->next == nullptr){
        return true;
    }
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast->next!=nullptr&&fast->next->next!=nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    slow->next = nullptr;
    ListNode* pre = slow;
    ListNode* cur = slow->next;
    ListNode* next = nullptr;
    //本质上只有pre和cur两个指针在移动，next只是用来记录cur的下一个节点，
    //所以循环条件要看cur指针的移动情况，看cur在哪儿停下来就是循环条件
    while(cur!=nullptr){
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    next = pre; //next指向反转后的链表的头节点
    cur = head;
    bool res = true;
    while(cur!=nullptr&&pre!=nullptr){
        if (cur->val!=pre->val){
            res = false;
            break;  //不能直接return false，因为要把链表恢复原状
        }
        cur = cur->next;
        pre = pre->next;
    }
    //恢复链表
    pre = next->next;
    next->next = nullptr;
    //本质上只有pre和next两个指针在移动，cur只是用来记录pre的下一个节点，
    //所以循环条件要看pre指针的移动情况,看pre在哪儿停下来就是循环条件
    while(pre!=nullptr){
        cur = pre->next;
        pre->next = next;
        next = pre;
        pre = cur;
    }
    return res;
}