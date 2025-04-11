#include <iostream>
#include <list>
using namespace std;
class TreeNode{
public:
    int val;
    list<TreeNode*> children;
    TreeNode(int v, list<TreeNode*> c):val(v),children(c){}
};
class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node(int v):val(v),left(nullptr),right(nullptr){}
};
Node* encode(TreeNode* root){
    if (root == nullptr){
        return nullptr;
    }
    Node* head = new Node(root->val);
    head->left = en(root->children);
}
Node* en(list<TreeNode*> children){
    Node* first = nullptr;
Node* cur = nullptr;            //cur指向前一个节点
    for (auto child:children){  //遍历孩子列表，递归出口
        Node* node = new Node(child->val);  //创建孩子对应的二叉树节点
        if (first == nullptr){       //如果是第一个孩子，则标识一下
            first = node;
        }
        else{
            cur->right = node;   //将cur的右孩子指向node
                                //此时cur指向node的前一个节点，和node错开
                                //因为循环是for循环，所以这里必须在cur值更新前连接
        }
        cur = node;
        cur->left = en(child->children);    //递归入口，将孩子的孩子列表转化为二叉树
    }
    return first;   //返回第一个孩子
}
TreeNode* decode(Node* root){
    if (root == nullptr){
        return nullptr;
    }
    return new TreeNode(root->val,de(root->left));
}
list<TreeNode*> de(Node* head){
    list<TreeNode*> children;           //行为：创建一个空的孩子列表
    while(head!=nullptr){               //递归出口
        TreeNode* child = new TreeNode(head->val,de(head->left));   //递归入口//行为：创建孩子节点
        children.push_back(child);              //行为：将孩子节点加入孩子列表
        head = head->right;         //行为：遍历孩子节点
    }
    return children;
}

