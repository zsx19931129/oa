// Question 2) Implement insert and delete in a tri-nary tree. A tri-nary tree is much like a binary
// tree but with three child nodes for each parent instead of two -- with the left node being values
// less than the parent, the right node values greater than the parent, and the middle nodes values
// equal to the parent.
// For example, suppose I added the following nodes to the tree in this order: 5, 4, 9, 5, 7, 2, 2.
// The resulting tree would look like this:
//     5
//   / | \
// 4  5  9
// /     /
// 2   7
// |
// 2

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

class Node{
public:
    Node(int v):val(v){}
    int val;
    Node *left=NULL;
    Node *mid=NULL;
    Node *right=NULL;
};

class Tree{
public:
    /* 
     * Please complete this method.
     * Inserts val into the tree..
     */
    void insertNode(int val){
        if(!root){
            root = new Node(val);
            return ;
        }
        Node *cur = root, *parent=NULL;
        int status = 0; //-1 left 0 mid 1 right
        while(cur){
            parent = cur;
            if(cur->val == val){
                cur = cur->mid;
                status = 0;
            }else if(cur->val < val){
                cur = cur->right;
                status = 1;
            }else{
                cur = cur->left;
                status = -1;
            }
        }
        if(status == 1){
            parent->right = new Node(val);
        }else if(status == -1){
            parent->left = new Node(val);
        }else{
            parent->mid = new Node(val);
        }
    }
    
    
    void deleteNodeIterate(int val){
        Node *cur = root, *parent = NULL, *del=NULL;
        while(cur){
            parent = cur;
            if(val > cur->val){
                cur = cur->right;
            }else if(val < cur->val){
                cur = cur->left;
            }else{
                del = cur;
                Node *newSubRoot = NULL;
                if(cur->mid){
                    newSubRoot = cur->mid;
                }else if(cur->right){
                    Node *iter = cur->right, *subParent = cur;
                    while(iter->left){
                        subParent = iter;
                        iter = iter->left;
                    }
                    newSubRoot = iter;
                    if(subParent->val > iter->val){
                        subParent->left = iter->right;
                    }else{
                        subParent->right = iter->right;
                    }
                }
                if(!parent){
                    root = newSubRoot;
                }
                newSubRoot->left = cur->left;
                newSubRoot->right = cur->right;
                break;
            }
        }
        if(del){
            delete del;
        }
    }
    Node* deleteNodeRecursive(Node* rt, int val){
        if(rt == NULL){
            return rt;
        }
        if(rt->val < val){
            return deleteNodeRecursive(rt->left, val);
        }else if(rt->val > val){
            return deleteNodeRecursive(rt->right, val);
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
                rt = rt->left;
            }
        }
        return rt;
    }
    /*
     * Please complete this method.
     * Deletes only one instance of val from the tree.
     * If val does not exist in the tree, do nothing.
     */
    void deleteNode(int val){
        //root = deleteNodeRecursive(root, val);
        deleteNodeIterate(val);
    }
private:
    Node *root=NULL;
};

int main(){
    
    return 0;
}