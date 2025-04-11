#include<iostream>
#include<queue>
#include<stack>
#include <string>
using namespace std;
class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node(int v):val(v),left(nullptr),right(nullptr){}
};
//先序  序列化
queue<string>* preSerial(Node* head){
    queue<string>* q = new queue<string>();
    if (head!=nullptr){
        pres(head,q);
    }
    return q;
}
void pres(Node* head,queue<string>* q){
    if (head==nullptr){
        q->push("#");
    }
    else{
        q->push(to_string(head->val));
        pres(head->left,q);
        pres(head->right,q);
    }
}
//先序   反序列化
Node* preRebuild(queue<string>* q){
    if (q->empty()){
        return nullptr;
    }
    return preb(q);
}
Node* preb(queue<string>* q){
    string str = q->front();
    q->pop();
    if (str=="#"){
        return nullptr;
    }
    Node* head = new Node(stoi(str));
    head->left = preb(q);
    head->right = preb(q);  
    return head;
}
//后序 序列化
queue<string>* posSerial(Node* head){
    queue<string>* q = new queue<string>();
    if (head!=nullptr){
        pos(head,q);
    }
    return q;
}
void pos(Node* head,queue<string>* q){
    if (head==nullptr){
        q->push("#");
    }
    else{
        pos(head->left,q);
        pos(head->right,q);
        q->push(to_string(head->val));
    }
}
//后序  反序列化
Node* posRebuild(queue<string>* q){
    if (q->empty()){
        return nullptr;
    }
    stack<string> s;
    while(!q->empty()){
        s.push(q->front());
        q->pop();
    }
    return posb(&s);
}
Node* posb(stack<string>* stk){
    string str = stk->top();
    stk->pop();
    if (str=="#"){
        return nullptr;
    }
    Node* head = new Node(stoi(str));
    head->right = posb(stk);
    head->left = posb(stk);
    return head;
}
//层次 序列化
queue<string>* levelSerial(Node* head){
    queue<string>* q = new queue<string>();
    if (head == nullptr){
        q->push("#");
    }
    else{
        queue<Node*>* q1 = new queue<Node*>();
        q1->push(head);
        q->push(to_string(head->val));
        while(!q1->empty()){
            head = q1->front();
            q1->pop();
            if (head->left!=nullptr){
                q1->push(head->left);
                q->push(to_string(head->left->val));
            }
            else{
                q->push("#");
            }
            if (head->right!=nullptr){
                q1->push(head->right);
                q->push(to_string(head->right->val));
            }
            else{
                q->push("#");
            }
        }
    }
    return q;
}
//层次  反序列化
Node* levelRebuild(queue<string>* q){
    if (q->empty()){
        return nullptr;
    }
    //创建一个队列来存储节点
    queue<Node*>* q1 = new queue<Node*>();
    //创建一个头节点
    Node* head = generateNode(q);
    //头节点入队
    q1->push(head);
    Node* node = nullptr;
    //当队列不为空时
    
    while(!q1->empty()){
        node = q1->front(); //取出队头节点
        q1->pop();
        node->left = generateNode(q);   //生成左节点
        node->right = generateNode(q);  //生成右节点
        if (node->left!=nullptr){       //如果左节点不为空，就入队
            q1->push(node->left);
        }
        if (node->right!=nullptr){      //如果右节点不为空，就入队
            q1->push(node->right);
        }
    }
    return head;
}
Node* generateNode(queue<string>* q){
    string str = q->front();
    q->pop();
    if (str=="#"){
        return nullptr;
    }
    Node* head = new Node(stoi(str));
    return head;
}