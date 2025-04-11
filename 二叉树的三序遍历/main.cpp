#include <iostream>
#include <stack>
using namespace std;
class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node(int v):val(v),left(nullptr),right(nullptr){}
};
void pre1(Node* head){  //这样的写法是不能够改写中序和后序遍历的，它没有用栈来模拟递归的向下和返回的向上
    if (head!= nullptr){    //它只是利用了栈的后进先出的特性，对树的节点进行了一个深度优先的遍历
        stack<Node*> s;     //这样的算法不能模拟出遍历完成这一过程，对于中序和后序就无法在正确时机打印根节点
        s.push(head);
        while(!s.empty()){
            head = s.top();
            s.pop();
            cout<<head->val<<" ";
            if (head->right!=nullptr){  //先压右再压左
                s.push(head->right);
            }
            if (head->left!=nullptr){
                s.push(head->left);
            }
        }
    }
}
void pre2(Node* head){
    if (head!=nullptr){
        stack<Node*> s;
        while(!s.empty()||head!=nullptr){   //递归函数结束大条件：栈为空且head为空，说明整棵树遍历完了
            if (head!=nullptr){             //模拟递归出口：head为空
                cout<<head->val<<" ";       //模拟行为
                s.push(head);               //模拟递归深度
                head = head->left;          //模拟递归入口
            }
            else{
                head = s.top();             //top的时候就说明左子树已经遍历完了
                head = head->right;         //模拟递归入口
                s.pop();                    //模拟递归深度
            }
        }
    }
}
void in(Node* head){
    if (head!=nullptr){
        stack<Node*> s;
        while(!s.empty()||head!=nullptr){   //递归函数结束大条件：栈为空且head为空，说明整棵树遍历完了
            if (head!=nullptr){             //模拟递归出口：head为空
                s.push(head);               //模拟递归深度    
                head = head->left;          //模拟递归入口
            }
            else{                           //触发递归出口时，深度向上
                head = s.top();             //top的时候就说明左子树已经遍历完了
                cout<<head->val<<" ";       //左子树遍历完了，打印根节点
                s.pop();
                head = head->right;         //模拟递归入口，类似尾递归
            }
        }
    }
}
