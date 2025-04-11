#include <iostream>
using namespace std;
class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
    Node(int v):val(v),left(nullptr),right(nullptr),parent(nullptr){}
};
Node* getSuccessor(Node* head){
    if (head == nullptr){
        return nullptr;
    }
    //如果有右子树，则返回右子树的最左节点
    if (head->right != nullptr){    
        return getLeftMost(head->right);
    }
    Node* parent = head->parent;
    //如果没有右子树，则向上遍历，直到找到一个节点是其父节点的左孩子或者是根节点
    //如果是左孩子，则返回父节点
    //如果是根节点，则返回nullptr
    while(parent!=nullptr&&parent->right==head){
        head = parent;
        parent = parent->parent;
    }
    return parent;

}
//获取节点node的最左节点
Node* getLeftMost(Node* node){
    if (node == nullptr){
        return nullptr;
    }
    //遍历左子树，直到找到最左节点
    while(node->left!=nullptr){
        node = node->left;
    }
    return node;
}
