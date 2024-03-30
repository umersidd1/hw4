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

    //if the root is a nullptr then it is already balanced
    if (root == nullptr){
        return true; 
    }

    //calculate the max depth with the depthLength helper function
    int maxDepth = depthLength(root);

    //check to see if the tree reaches the maxDepth 
    return equalCheck(root, 1, maxDepth);

}


int depthLength(Node* root) {
  //if there is only the root return 0
    if (root == nullptr) {
        return 0; 
    }
    //get the height of the left and right subtrees recursively
    int leftTree = depthLength(root->left);
    int rightTree = depthLength(root->right);

    //get the final height of whatever is the longest root->leaf node path 
    return 1 + max(leftTree, rightTree);
}

bool equalCheck(Node* root, int length, int goalLength) {
    if (root == nullptr) {
        return true; 
    }
    //check if you are at a leaf node
    if (root->left == nullptr and root->right == nullptr) {
      //if the lenght is not the same as the goal length, it is not balanced
        if (length != goalLength) {
            return false;
        }
        else {
            return true; 
        }
    }

    //check if the left node or right node are balanced. increment the overall length by 1
    bool leftTreeEqual = equalCheck(root->left, length + 1, goalLength);
    bool rightTreeEqual = equalCheck(root->right, length + 1, goalLength);

    //see if both trees have equal heights 
    return (leftTreeEqual and rightTreeEqual);
}




 