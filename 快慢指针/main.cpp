#include <iostream>
using namespace std;
/*
        这类题目要先找slow指针停在哪，再根据fast指针走两步的原理来确定循环条件*/
// 链表节点定义
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

// 返回链表的中点
// 如果链表长度为奇数，返回正中间的节点
// 如果链表长度为偶数，返回上中点（即中间两个节点中的前一个）
ListNode* midNode1(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;  // 空链表或只有一个节点，直接返回头节点
    }
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // fast指针每次走两步，slow指针每次走一步
    // 当fast到达末尾时，slow刚好在中间位置
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;  // slow指向中点或上中点
}

// 返回链表的中点
// 如果链表长度为奇数，返回正中间的节点
// 如果链表长度为偶数，返回下中点（即中间两个节点中的后一个）
ListNode* midNode2(ListNode* head){
    // 处理边界情况
    // 如果链表为空或只有一个节点，直接返回头节点
    if (head == nullptr || head->next == nullptr){
        return head;
    }
    
    // 初始化快慢指针，都从头节点开始
    ListNode* slow = head;
    ListNode* fast = head;
    
    // 快指针每次走两步，慢指针每次走一步
    // 循环直到快指针到达链表末尾
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;        // 慢指针前进一步
        fast = fast->next->next;  // 快指针前进两步
    }
    
    // 循环结束时，对于奇数长度链表，slow指向正中间节点
    // 对于偶数长度链表，slow指向下中点（中间两个节点中的后一个）
    return slow;
}

// 返回链表的特定节点
// 如果链表长度为奇数，返回中点前一个节点
// 如果链表长度为偶数，返回上中点前一个节点（即第一个四等分点）
ListNode* midNode3(ListNode* head){
    // 处理特殊情况
    if (head == nullptr){
        return nullptr;  // 空链表，返回空
    }
    if (head->next == nullptr){
        return nullptr;  // 只有一个节点，中点前一个不存在，返回空
    }
    if (head->next->next == nullptr){
        return nullptr;  // 只有两个节点，中点前一个不存在，返回空
    }
    
    // 初始化快慢指针
    ListNode* fast = head;
    ListNode* slow = head;
    
    // 快指针检查未来的4个节点，每次移动2个节点
    // 慢指针每次移动1个节点
    while(fast->next->next->next != nullptr && fast->next->next->next->next != nullptr){
        slow = slow->next;       // 慢指针前进一步
        fast = fast->next->next; // 快指针前进两步
    }
    
    // 循环结束时：
    // 对于奇数长度链表，slow指向中点的前一个节点
    // 对于偶数长度链表，slow指向上中点的前一个节点
    return slow;
}

// 返回链表的特定节点
// 如果链表长度为奇数，返回中点前一个节点
// 如果链表长度为偶数，返回下中点前一个节点
ListNode* midNode4(ListNode* head){
    // 处理空链表的情况
    if (head == nullptr){
        return head;  // 返回空
    }
    // 处理只有一个节点的情况
    if (head->next == nullptr){
        return nullptr;  // 只有一个节点时，无
    }
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast->next->next!=nullptr&&fast->next->next->next!=nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

