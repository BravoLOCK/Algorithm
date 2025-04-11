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
int maxWidth(Node* root){
    if (root == nullptr){
        return 0;
    }
    queue<Node*> q; //使用队列实现按层遍历
    q.push(root);   //将根节点入队，初始化
    Node* curEnd = root;    //当前层的最后一个节点
    Node* nextEnd = nullptr;    //下一层的最后一个节点
    int maxWidth = 0;
    int curWidth = 0;
    while(!q.empty()){
        Node* node = q.front();
        q.pop();
        curWidth++; //当前层节点数加一
        if (node->left!=nullptr){   //如果有左孩子，入队
            q.push(node->left);
            nextEnd = node->left;   //更新下一层的最后一个节点
        }
        if (node->right!=nullptr){  //如果有右孩子，入队
            q.push(node->right);
            nextEnd = node->right;  //更新下一层的最后一个节点
        }
        if (node == curEnd){        //如果当前节点是当前层的最后一个节点
            maxWidth = max(maxWidth,curWidth);  //更新最大宽度
            curWidth = 0;       //当前层节点数清零  
            curEnd = nextEnd;   //更新当前层的最后一个节点
        }   
    } 
    return maxWidth;
}