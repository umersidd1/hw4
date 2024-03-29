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
    if(node == nullptr or node->getLeft() == nullptr){
        return; 
    }
    
    AVLNode<Key,Value>* child = node->getLeft();
    AVLNode<Key,Value>* changeNode = child->getRight();
    AVLNode<Key,Value>* parent = node->getParent();

  
    child->setParent(parent);
    node->setParent(child);


    node->setLeft(changeNode);
    if(changeNode != nullptr) {
        changeNode->setParent(node);
    }

    child->setRight(node);


    if(parent == nullptr){
        this->root_ = child;
    }
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
    if(node == nullptr or node->getRight() == nullptr){
        return; 
    }
    AVLNode<Key,Value>* child = node->getRight();
    AVLNode<Key,Value>* changeNode = child->getLeft();
    AVLNode<Key,Value>* parent = node->getParent();

    child->setParent(parent);
    node->setParent(child);

    node->setRight(changeNode);
    if(changeNode != nullptr){
      changeNode->setParent(node);
    }

    child->setLeft(node);

    if(parent == nullptr){
      this->root_ = child;
    }
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
  if(node == nullptr){
    return;
  }
  AVLNode<Key,Value>* parent = node->getParent(); 
  int nextdiff = 0; 
  if(parent!=nullptr){
    if(parent->getLeft() == node){
      nextdiff = 1;
    }
    else{
      nextdiff = -1;
    }
  }

  if(difference == -1){
    if(node->getBalance() + difference == -1){
      node->setBalance(-1);
    }
    else if(node->getBalance() + difference == 0){
      node->setBalance(0);
      removeFix(parent, nextdiff);
    }
    else if(node->getBalance() + difference == -2){
      AVLNode<Key,Value>* child = node->getLeft();
      if(child->getBalance() == -1){
        rotateRight(node);
        node->setBalance(0);
        child->setBalance(0);
        removeFix(parent, nextdiff);
      }
      else if(child->getBalance() == 0){
        rotateRight(node);
        node->setBalance(-1);
        child->setBalance(1);
      }
      else if(child->getBalance() == 1){
        AVLNode<Key,Value>* grandchild = child->getRight(); 
        if(grandchild == nullptr){
          removeFix(parent, nextdiff);
          return;
        }
        rotateLeft(child);
        rotateRight(node);
        if(grandchild->getBalance() == 1){
          node->setBalance(0);
          child->setBalance(-1);
          grandchild->setBalance(0);
        }
        else if(grandchild->getBalance() == 0){
          node->setBalance(0);
          child->setBalance(0);
          grandchild->setBalance(0);
        }
        else if(grandchild->getBalance() == -1){
          node->setBalance(1);
          child->setBalance(0);
          grandchild->setBalance(0);
        }
        removeFix(parent, nextdiff);
      }
    }
  }

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
        if(grandchild == nullptr){
          removeFix(parent, nextdiff);
          return;
        }
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
  AVLNode<Key,Value>* grandparent = parent->getParent(); 
  if(grandparent == nullptr or parent == nullptr){
    return; 
  }
  if(grandparent->getLeft() == parent){
    grandparent->updateBalance(-1);
    if(grandparent->getBalance() == 0){
      return;
    }
    else if(grandparent->getBalance() == -1){
      insertFix(grandparent, parent);
    }
    else if(grandparent->getBalance() == -2){
      if(parent->getLeft() == node){
        rotateRight(grandparent);
        parent->setBalance(0);
        grandparent->setBalance(0);
      }
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
  else if(grandparent->getRight() == parent){
    grandparent->updateBalance(1);
    if(grandparent->getBalance() == 0){
      return; 
    }
    else if(grandparent->getBalance() == 1){
      insertFix(grandparent, parent);
    }
    else if(grandparent->getBalance() == 2){
      if(parent->getRight() == node){
        rotateLeft(grandparent);
        parent->setBalance(0), grandparent->setBalance(0);
      }
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
  else{
    current->setValue(newItem.second);
  }

 return current;
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //PROBABLY CAN GET RID OF THIS STATIC CAST ROOT BECAUSE I USE RECURSION NOT 
    //IN HOUSE ITERATION 
    AVLNode<Key,Value>* tempRoot = static_cast<AVLNode<Key,Value>*>(this->root_);
    tempRoot = this->insertHelper(tempRoot, new_item, nullptr);

    this->root_ = tempRoot;

    AVLNode<Key,Value>* insertedNode = static_cast<AVLNode<Key,Value>*>(this->internalFind(new_item.first)); 
    insertedNode->setBalance(0); 

    if(insertedNode == nullptr){
      return; 
    }
    
    AVLNode<Key,Value>* parent = insertedNode->getParent(); 

    if(parent == nullptr){
      return; 
    }

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
    AVLNode<Key,Value>* removeNode = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    if(removeNode == nullptr){
      return; 
    }

    AVLNode<Key,Value>* pred = nullptr;
    if(removeNode->getLeft() != nullptr and removeNode->getRight() != nullptr){
      pred = static_cast<AVLNode<Key,Value>*>(this->predecessor(removeNode));
      //if(pred!=nullptr){
        nodeSwap(removeNode, pred);
      //}
    }

    int diff = 0; 

    AVLNode<Key,Value>* parent = removeNode->getParent(); 
    if(parent == nullptr){
      return; 
    }

    if(parent->getLeft() == removeNode){
      diff = 1; 
    }
    else{
      diff = -1; 
    }

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
            //AVLNode<Key, Value>* parent = removeNode->getParent(); 
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
                // Handle root node removal
                this->root_ = child; 
                if (child != nullptr){
                    child->setParent(nullptr); 
                }
            }
        } 
    }

    /*if(parent->getLeft() == removeNode){
      if(removeNode->getLeft() != nullptr){
        parent->setLeft(removeNode->getLeft());
      }
      if(removeNode->getRight() != nullptr){
        parent->setLeft(removeNode->getRight()); 
      }
      else{
        parent->setLeft(nullptr);
      }
    }

    if(parent->getRight() == removeNode){
      if(removeNode->getRight() != nullptr){
        parent->setRight(removeNode->getRight());
      }
      if(removeNode->getRight() != nullptr){
        parent->setRight(removeNode->getLeft());
      }
      else{
        parent->setRight(nullptr);
      }
    }*/

    delete removeNode; 
    //might need to set to nullptr 
    removeFix(parent, diff);
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
