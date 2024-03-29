#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <algorithm>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int depthLength(Node* root); 
bool equalCheck(Node* root, int length, int goalLength);


bool equalPaths(Node * root)
{
    // Add your code below
    if (root == nullptr){
        return true; 
    }

    int maxDepth = depthLength(root);

    return equalCheck(root, 1, maxDepth);

}

int depthLength(Node* root) {
    if (root == nullptr) {
        return 0; 
    }
    int leftTree = depthLength(root->left);
    int rightTree = depthLength(root->right);

    return 1 + max(leftTree, rightTree);
}

bool equalCheck(Node* root, int length, int goalLength) {
    if (root == nullptr) {
        return true; 
    }
    if (root->left == nullptr and root->right == nullptr) {
        if (length != goalLength) {
            return false;
        }
        else {
            return true; 
        }
    }

    bool leftTreeEqual = equalCheck(root->left, length + 1, goalLength);
    bool rightTreeEqual = equalCheck(root->right, length + 1, goalLength);

    return (leftTreeEqual and rightTreeEqual);
}




 