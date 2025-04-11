#include <iostream>
#include <queue>
using namespace std;
class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node(int v):val(v),left(nullptr),right(nullptr){}
};
void level(Node* head){
    if (head!=nullptr){
        queue<Node*> q;
        q.push(head);                   //先压入根节点  
        while(!q.empty()){
            head = q.front();
            q.pop();
            cout<<head->val<<" ";       //打印根节点
            if (head->left!=nullptr){   //有左子树就先压左子树
                q.push(head->left);
            }
            if (head->right!=nullptr){  //有右子树就压右子树
                q.push(head->right);
            }
        }
    }
}