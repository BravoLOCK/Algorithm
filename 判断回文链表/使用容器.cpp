#include <iostream>
#include <stack>
using namespace std;
class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};
bool isPalinDrome(ListNode* head){
    stack<ListNode*> s;
    ListNode* cur = head;
    while(cur != nullptr){
        s.push(cur);
        cur = cur->next;
    }
    cur = head;
    while(cur!=nullptr){
        if (cur->val!=s.top()->val){
            return false;
        }
        s.pop();
        cur = cur->next;
    }
    return true;
}