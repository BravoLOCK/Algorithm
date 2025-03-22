#include <iostream>
#include <string>
using namespace std;
class TrieNode1{
public:
    int pass;
    int end;
    TrieNode1** next;
    TrieNode1():pass(0),end(0),next(new TrieNode1*[26]){}
    ~TrieNode1(){
        delete []next;
    }
};
class Trie{
public:
    TrieNode1 root;
    void insert(string str){
        if (str == ""){
            return ;
        }
        TrieNode1* node = &root;
        node->pass++;
        const char* chs = str.c_str();
        for (int i = 0;i<str.length();++i){
            int path = chs[i]-'a';
            if (node->next[path] == nullptr){
                node->next[path] = new TrieNode1();
            }
            node = node->next[path];
            node->pass++;
        }
        node->end++;
    }
    int search(string str){
        if (str == ""){
            return 0;
        }
        TrieNode1* node = &root;
        const char* chs = str.c_str();
        for (int i = 0;i<str.length();++i){
            int path = chs[i]-'a';
            if (node->next[path] == nullptr){
                return 0;
            }
            node = node->next[path];
        }
        return node->end;
    }
    int prefixnum(string str){
        if (str == ""){
            return 0;
        }
        TrieNode1* node = &root;
        const char* chs = str.c_str();
        for (int i = 0;i<str.length();++i){
            int path = chs[i]-'a';
            if (node->next[path] == nullptr){
                return 0;
            }
            node = node->next[path];
        }
        return node->pass;
    }
    void deleteNode(string str){
        if (str == ""){
            return;
        }
        if (search(str)!=0){
            TrieNode1* node = &root;
            vector<TrieNode1*> nodes;
            vector<int> indice;
            const char* chs = str.c_str();
            int index = 0;
            for (int i = 0;i<str.length();++i){
                nodes.push_back(node);
                index = chs[i]-'a';
                indice.push_back(index);
                node->pass--;
                node = node->next[index];
            }
            node->end--;
            nodes.push_back(node);
            for (int i = nodes.size()-1;i>0;--i){
                if (nodes[i]->pass == 0){
                    int idx = indice[i-1];
                    nodes[i-1]->next[idx] = nullptr;
                    delete nodes[i];
                }
                else{break;}
            }
        }
    }
    
};