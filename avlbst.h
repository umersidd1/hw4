#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* insertHelper(AVLNode<Key, Value>* current, const std::pair<const Key, Value>& newItem, AVLNode<Key,Value>* parent);
    void removeFix(AVLNode<Key,Value>* node, int difference);
    void insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node); 
    void rotateRight(AVLNode<Key,Value>* node); 
    void rotateLeft(AVLNode<Key,Value>* node); 


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
 
template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* node){
  //if the node is null or the left child is null then the operation can't happen
    if(node == nullptr or node->getLeft() == nullptr){
        return; 
    }
    
    //get the child, parent, and the right node of the child values 
    AVLNode<Key,Value>* child = node->getLeft();
    AVLNode<Key,Value>* changeNode = child->getRight();
    AVLNode<Key,Value>* parent = node->getParent();

    //set the childs parent as the parent node
    child->setParent(parent);
    //set the rotated node's parent as the child 
    node->setParent(child);

    //set the nodes left pointer to the changenode
    node->setLeft(changeNode);
    //and if the change node is not null, have its parent be the node 
    if(changeNode != nullptr) {
        changeNode->setParent(node);
    }

    //have the child set their right child as the node 
    child->setRight(node);

    //if parent is null, then the child is now the root of the tree
    if(parent == nullptr){
        this->root_ = child;
    }
    //otherwise change the parent to have child as either its left or right pointer 
    else{
        if(parent->getLeft() == node){
            parent->setLeft(child);
        }
        else{
            parent->setRight(child);
        }
    }
}


template<class Key, class Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* node){
  //if the node is null or the right child is null then the operation can't happen
    if(node == nullptr or node->getRight() == nullptr){
        return; 
    }
    //get the child, parent, and the left node of the child values 
    AVLNode<Key,Value>* child = node->getRight();
    AVLNode<Key,Value>* changeNode = child->getLeft();
    AVLNode<Key,Value>* parent = node->getParent();

    //set the childs parent as the parent node
    child->setParent(parent);
    //set the rotated node's parent as the child
    node->setParent(child);

    //set the nodes right pointer to the changenode
    node->setRight(changeNode);
    //and if the change node is not null, have its parent be the node 
    if(changeNode != nullptr){
      changeNode->setParent(node);
    }

    //set the childs left node to the rotated node
    child->setLeft(node);

    //if the parent is null
    if(parent == nullptr){
      //set child to the root
      this->root_ = child;
    }
    //otherwise appropriately assign the child to the parent 
    else{
      if(parent->getLeft() == node){
        parent->setLeft(child);
      }
      else{
        parent->setRight(child);
      }
    }
}


template<class Key, class Value>
void AVLTree<Key,Value>::removeFix(AVLNode<Key,Value>* node, int difference) {
  //if node is null then return 
  if(node == nullptr){
    return;
  }
  //acquire the parent node 
  AVLNode<Key,Value>* parent = node->getParent(); 
  //alter next diff appropriately
  int nextdiff = 0; 
  if(parent!=nullptr){
    if(parent->getLeft() == node){
      nextdiff = 1;
    }
    else{
      nextdiff = -1;
    }
  }

  //if the difference is -1, it is the left subtree 
  if(difference == -1){
    //alter the balances of the nodes and rotate accordingly given the balance values of the node 
    //case 1, balance + diff = -1
    if(node->getBalance() + difference == -1){
      node->setBalance(-1);
    }
    //case 2, balance + diff = 0
    else if(node->getBalance() + difference == 0){
      node->setBalance(0);
      removeFix(parent, nextdiff);
    }
    //case 3, balance + diff = -2
    else if(node->getBalance() + difference == -2){
      //set the child to the nodes left child
      AVLNode<Key,Value>* child = node->getLeft();
      //case 3a
      if(child->getBalance() == -1){
        rotateRight(node);
        node->setBalance(0);
        child->setBalance(0);
        removeFix(parent, nextdiff);
      }
      //case 3b
      else if(child->getBalance() == 0){
        rotateRight(node);
        node->setBalance(-1);
        child->setBalance(1);
      }
      //case 3c
      else if(child->getBalance() == 1){
        //set grandchild as the child's right pointer 
        AVLNode<Key,Value>* grandchild = child->getRight(); 
        //proper rotations 
        rotateLeft(child);
        rotateRight(node);
        //case 3c1
        if(grandchild->getBalance() == 1){
          node->setBalance(0);
          child->setBalance(-1);
          grandchild->setBalance(0);
        }
        //3c2
        else if(grandchild->getBalance() == 0){
          node->setBalance(0);
          child->setBalance(0);
          grandchild->setBalance(0);
        }
        //3c3
        else if(grandchild->getBalance() == -1){
          node->setBalance(1);
          child->setBalance(0);
          grandchild->setBalance(0);
        }
        removeFix(parent, nextdiff);
      }
    }
  }

  //same thing if difference is 1, but instead, check if the values are 0,1,2 rather than 0,-1,-2 for the main cases
  //perform correct rotations and update balances accordingly 
  else if(difference == 1){
    if(node->getBalance() + difference == 1){
      node->setBalance(1);
    }
    else if(node->getBalance() + difference == 0){
      node->setBalance(0);
      removeFix(parent, nextdiff);
    }
    else if(node->getBalance() + difference == 2){
      AVLNode<Key,Value>* child = node->getRight();
      if(child->getBalance() == 1){
        rotateLeft(node);
        node->setBalance(0);
        child->setBalance(0);
        removeFix(parent, nextdiff);
      }
      else if(child->getBalance() == 0){
        rotateLeft(node);
        node->setBalance(1);
        child->setBalance(-1);
      }
      else if(child->getBalance() == -1){
        AVLNode<Key,Value>* grandchild = child->getLeft(); 
        rotateRight(child);
        rotateLeft(node);
        if(grandchild->getBalance() == -1){
          node->setBalance(0);
          child->setBalance(1);
          grandchild->setBalance(0);
        }
        else if(grandchild->getBalance() == 0){
          node->setBalance(0);
          child->setBalance(0);
          grandchild->setBalance(0);
        }
        else if(grandchild->getBalance() == 1){
          node->setBalance(-1);
          child->setBalance(0);
          grandchild->setBalance(0);
        }
        removeFix(parent, nextdiff);
      }
    }
  }

}

template<class Key, class Value>
void AVLTree<Key,Value>::insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node){
  //get the parent node of the parent 
  AVLNode<Key,Value>* grandparent = parent->getParent();
  //return if either of them are null  
  if(grandparent == nullptr or parent == nullptr){
    return; 
  }
  //check if left child 
  if(grandparent->getLeft() == parent){
    //add -1 to grandparents balance 
    grandparent->updateBalance(-1);
    //nothing to change 
    if(grandparent->getBalance() == 0){
      return;
    }
    //recursive insertfix call
    else if(grandparent->getBalance() == -1){
      insertFix(grandparent, parent);
    }
    //if unbalanced 
    else if(grandparent->getBalance() == -2){
      //perform zig zig and update balances 
      if(parent->getLeft() == node){
        rotateRight(grandparent);
        parent->setBalance(0);
        grandparent->setBalance(0);
      }
      //perform zig zag and update balances 
      else if(parent->getRight() == node){
        rotateLeft(parent);
        rotateRight(grandparent);
        if(node->getBalance() == -1){
          node->setBalance(0);
          parent->setBalance(0);
          grandparent->setBalance(1);
        }
        else if(node->getBalance() == 0){
          node->setBalance(0),parent->setBalance(0),grandparent->setBalance(0);
        }
        else if(node->getBalance() == 1){
          node->setBalance(0),parent->setBalance(-1),grandparent->setBalance(0);
        }
      }
    }
  }
  //check if right child
  else if(grandparent->getRight() == parent){
    //update grandparent balance by 1
    grandparent->updateBalance(1);
    //follow same logic as the left child 
    if(grandparent->getBalance() == 0){
      return; 
    }
    else if(grandparent->getBalance() == 1){
      insertFix(grandparent, parent);
    }
    else if(grandparent->getBalance() == 2){
      //zig zig case 
      if(parent->getRight() == node){
        rotateLeft(grandparent);
        parent->setBalance(0), grandparent->setBalance(0);
      }
      //zig zag case 
      else if(parent->getLeft() == node){
        rotateRight(parent);
        rotateLeft(grandparent);
        if(node->getBalance() == -1){
          node->setBalance(0);
          parent->setBalance(1);
          grandparent->setBalance(0);
        }
        else if(node->getBalance() == 0){
          node->setBalance(0),parent->setBalance(0),grandparent->setBalance(0);
        }
        else if(node->getBalance() == 1){
          node->setBalance(0),parent->setBalance(0),grandparent->setBalance(-1);
        }
      }
    }
  }
}

//same insertHelper as BST 
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::insertHelper(AVLNode<Key, Value>* current, const std::pair<const Key, Value>& newItem, AVLNode<Key,Value>* parent) {
  if(current == nullptr){
    AVLNode<Key,Value>* newNode = new AVLNode<Key,Value>(newItem.first, newItem.second, parent);
    newNode->setBalance(0);
    return newNode;
  }
  if(newItem.first < current->getKey()){
    current->setLeft(insertHelper(current->getLeft(), newItem, current));
  }
  else if(newItem.first > current->getKey()){
    current->setRight(insertHelper(current->getRight(), newItem, current));
  }
  else if(newItem.first == current->getKey()){
    current->setValue(newItem.second);
  }

 return current;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    //static cast the root to an AVLnode
    AVLNode<Key,Value>* tempRoot = static_cast<AVLNode<Key,Value>*>(this->root_);
    tempRoot = this->insertHelper(tempRoot, new_item, nullptr);

    //set the root to the avl node temproot
    this->root_ = tempRoot;
    //find the key that was inserted 
    AVLNode<Key,Value>* insertedNode = static_cast<AVLNode<Key,Value>*>(this->internalFind(new_item.first)); 
    //if null then return 
    if(insertedNode == nullptr){
      return; 
    }
    //get the parent node 
    AVLNode<Key,Value>* parent = insertedNode->getParent(); 

    if(parent == nullptr){
      return; 
    }
    //update the balances according to the parent<->insertedNode relationship
    if(parent->getBalance() == 1 or parent->getBalance() == -1){
      if(parent->getRight() == insertedNode){
        parent->updateBalance(1);
      }
      else{
        parent->updateBalance(-1);
      }
      return; 
    }

    if(parent->getBalance() == 0) {
      if(parent->getLeft() == insertedNode){
        parent->updateBalance(-1);
      }
      else{
        parent->updateBalance(1);
      }
      //call insertFix if the parent balance was initially 0
      insertFix(parent, insertedNode);
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    //find the node to remove 
    AVLNode<Key,Value>* removeNode = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    //if it doesnt exist, then return 
    if(removeNode == nullptr){
      return; 
    }

    //same implementation as BST remove but static cast to an avl node 
    AVLNode<Key,Value>* pred = nullptr;
    if(removeNode->getLeft() != nullptr and removeNode->getRight() != nullptr){
      pred = static_cast<AVLNode<Key,Value>*>(this->predecessor(removeNode));
      if(pred!=nullptr){
        nodeSwap(removeNode, pred);
      }
    }
    //set difference to 0
    int diff = 0; 

    //get the parent of the removeNode 
    AVLNode<Key,Value>* parent = removeNode->getParent(); 
    //if the parent is not null, diff = 1 if removeNode is left child and -1 if it is right child 
    if(parent != nullptr){
      if(parent->getLeft() == removeNode){
        diff = 1; 
      }
      else{
        diff = -1; 
      } 
    }

    
    //same implementation as BST remove for if there is 0 or 1 children 
    if (removeNode->getLeft() == nullptr and removeNode->getRight() == nullptr){
        if(removeNode->getParent() != nullptr) {
            if(removeNode->getParent()->getRight() == removeNode){
                removeNode->getParent()->setRight(nullptr); 
            }
            else{
                removeNode->getParent()->setLeft(nullptr); 
            }
        }
        else {
            this->root_ = nullptr;
        }
    }
    else {
        if (removeNode == this->root_) {
            AVLNode<Key, Value>* child = nullptr;
            if (removeNode->getRight() != nullptr and removeNode->getLeft() == nullptr) {
                child = removeNode->getRight();
            }
            if (removeNode->getRight() == nullptr and removeNode->getLeft() != nullptr) {
                child = removeNode->getLeft();
            }
            this->root_ = child;
            if(child != nullptr) {
                child->setParent(nullptr);
            }
        } 
        else {
            AVLNode<Key, Value>* child = nullptr; 
            bool leftBool = (parent->getLeft() == removeNode);

            if (removeNode->getLeft() != nullptr) {
                child = removeNode->getLeft(); 
            }
            else if (removeNode->getRight() != nullptr) {
                child = removeNode->getRight();
            }
          
            if (parent != nullptr) {
              if (leftBool){
                parent->setLeft(child); 
                child->setParent(parent); 
              }
              else{
                parent->setRight(child); 
                child->setParent(parent);
              }
            }
            else {
                this->root_ = child; 
                if (child != nullptr){
                    child->setParent(nullptr); 
                }
            }
        } 
    }

    //delete the node 
    delete removeNode; 
    //call removeFix on the parent and difference value 
    removeFix(parent, diff);
    //return
    return; 
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
