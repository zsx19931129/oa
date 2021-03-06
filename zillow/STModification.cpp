#include <iostream>
using namespace std;

struct Node{
    int val;
    Node *left, *mid, *right;
    Node(int val):left(0),mid(0),right(0),val(val){}
};

class Tree{
public:
    Tree();
    void insert(int val);
    void remove(int val);
    Node *getRoot();
protected:
    Node *root;
};

Node* Tree::getRoot(){
    return root;
}

/*
 * Implement the methods below
 */
Tree::Tree(){
    root = NULL;
}

void Tree::insert(int val){
    if(!root){
        root = new Node(val);
        return ;
    }
    Node *cur = root, *parent=NULL;
    while(cur){
        parent = cur;
        if(cur->val == val){
            cur = cur->mid;
        }else if(cur->val < val){
            cur = cur->right;
        }else{
            cur = cur->left;
        }
    }
    if(parent->val < val){
        parent->right = new Node(val);
    }else if(parent->val > val){
        parent->left = new Node(val);
    }else{
        parent->mid = new Node(val);
    }
}

Node* deleteNodeRecursive(Node* rt, int val){
    if(rt == NULL){
        return rt;
    }
    if(rt->val > val){
        rt->left = deleteNodeRecursive(rt->left, val);
    }else if(rt->val < val){
        rt->right = deleteNodeRecursive(rt->right, val);
    }else{
        if(rt->mid){
            rt->mid = deleteNodeRecursive(rt->mid, val);
        }else if(rt->right){
            Node *iter = rt->right;
            while(iter->left){
                iter = iter->left;
            }
            int minval = iter->val;
            rt->val = minval;
            rt->mid = iter->mid;
            iter->mid = NULL;
            rt->right = deleteNodeRecursive(rt->right, minval);
        }else{
            Node *del = rt;
            rt = rt->left;
            delete del;
        }
    }
    return rt;
}

// 1.recursive
void Tree::remove(int val){
    root = deleteNodeRecursive(root, val);
}

// 2.iterate
//void Tree::remove(int val){
//    Node *cur = root, *parent = NULL, *del=NULL;
//    while(cur){
//        if(val > cur->val){
//            parent = cur;
//            cur = cur->right;
//        }else if(val < cur->val){
//            parent = cur;
//            cur = cur->left;
//        }else{
//            del = cur;
//            Node *newSubRoot = NULL;
//            bool last = false;
//            if(cur->mid){
//                newSubRoot = cur->mid;
//            }else if(cur->right){
//                Node *iter = cur->right, *subParent = cur;
//                while(iter->left){
//                    subParent = iter;
//                    iter = iter->left;
//                }
//                newSubRoot = iter;
//                if(subParent->val > iter->val){
//                    subParent->left = iter->right;
//                }else{
//                    subParent->right = iter->right;
//                }
//            }else{
//                last = true;
//                newSubRoot = cur->left;
//            }
//            if(!parent){
//                root = newSubRoot;
//            }else{
//                if(parent->val > cur->val){
//                    parent->left = newSubRoot;
//                }else{
//                    parent->right = newSubRoot;
//                }
//            }
//            if(!last){
//                newSubRoot->left = cur->left;
//                newSubRoot->right = cur->right;
//            }
//            break;
//        }
//    }
//    if(del){
//        delete del;
//    }
//}