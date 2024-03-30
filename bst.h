#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2);

    // Add helper functions here
    //static Node<Key,Value>* successor(Node<Key, Value>* current);
    int getHeight(const Node<Key,Value>* node) const;
    void postOrderDeletion(Node<Key, Value>* node);
    Node<Key, Value>* insertHelper(Node<Key, Value>* current, const std::pair<const Key, Value>& keyValuePair, Node<Key,Value>* parent);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) : current_(ptr) //initialize current with the given pointer
{
    // TODO

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(nullptr) //initialize current to nullptr
{
    // TODO
   

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //return this->iterator == rhs; 
    return this->current_ == rhs.current_; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //return whether or not they are unequal
    return this->current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    //use the successor code implementation to get to the next largest node
    //either go to the left most node of the right subtree
    if(current_->getRight() != nullptr) {
        current_ = current_->getRight(); 
        while (current_->getLeft() != nullptr) {
            current_ = current_->getLeft(); 
        }
    }
    //or go to the node where the parents right pointer is pointed at the current node
    else {
      Node<Key,Value>* parent = current_->getParent(); 
      while(parent != nullptr and current_ == parent->getRight()){
        current_ = parent;
        parent = parent->getParent();
      }
      current_ = parent; 
    }
    return *this; 
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(nullptr) //initialize the root to nullptr
{
    // TODO
  
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear(); //use the clear function
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key,Value>::insertHelper(Node<Key, Value>* current, const std::pair<const Key, Value>& keyValuePair, Node<Key,Value>* parent){
    //if the node is a nullptr
    if(current == nullptr) { 
      //insert the new node with the proper information
        Node<Key, Value>* newNode = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, parent);
        //and return that node
        return newNode; 
    }
    //if the key is less than the current node, go to the left
    if (keyValuePair.first < current->getKey()) {
      //recursive call
        current->setLeft(insertHelper(current->getLeft(), keyValuePair, current));
    }
    //if key is greater go to the right
    else if (keyValuePair.first > current->getKey()){
        current->setRight(insertHelper(current->getRight(), keyValuePair, current));
    }
    //if equal, change the value at that key
    else{
      current->setValue(keyValuePair.second);
    }

    //return the current node
    return current; 
}


template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair) {
  //recursively call insertHelper. have the current node as root, and the parent as nullptr
    root_ = insertHelper(root_, keyValuePair, nullptr);
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{    
    //find the node you need to remove 
    Node<Key,Value>* removeNode = internalFind(key);

    //if the node does not exist, then return
    if(removeNode == nullptr) {
        return;
    }

    // Handle the case when the node to be removed has two children
    Node<Key, Value>* pred = nullptr;
    if(removeNode->getLeft() != nullptr and removeNode->getRight() != nullptr){
      //get the predecessor and swap with the node that needs to be removed. this results in removeNode only having 
      //one or two children
        pred = predecessor(removeNode); 
        if (pred != nullptr) {
            nodeSwap(removeNode, pred);
        }
    }
      

    // Handle the case when the node to be removed has no children 
    if (removeNode->getLeft() == nullptr and removeNode->getRight() == nullptr){
        if(removeNode->getParent() != nullptr) {
          //if the node that needs to be removed is on the right, set the parents right pointer to null
            if(removeNode->getParent()->getRight() == removeNode){
                removeNode->getParent()->setRight(nullptr); 
            }
            //otherwise left pointer to null
            else{
                removeNode->getParent()->setLeft(nullptr); 
            }
        }
        //if the node is the root, set the root to nullptr
        else {
            // Handle root node removal
            root_ = nullptr;
        }
    }
    //Handle the case when the node to be removed has one child
    else {
      //if the node to be removed is the root
        if (removeNode == root_) {
          //find the child and set it as the root
            Node<Key, Value>* child = nullptr;
            if (removeNode->getRight() != nullptr and removeNode->getLeft() == nullptr) {
                child = removeNode->getRight();
            }
            if (removeNode->getRight() == nullptr and removeNode->getLeft() != nullptr) {
                child = removeNode->getLeft();
            }
            root_ = child;
            if(child != nullptr) {
                child->setParent(nullptr);
            }
        } 
        else {
          //get the parent and child nodes of removeNode
            Node<Key, Value>* parent = removeNode->getParent(); 
            Node<Key, Value>* child = nullptr; 
            //figure out if the node to be removed is a left or right child
            bool leftBool = (parent->getLeft() == removeNode);
            //set up the child node with the correct value
            if (removeNode->getLeft() != nullptr) {
                child = removeNode->getLeft(); 
            }
            else if (removeNode->getRight() != nullptr) {
                child = removeNode->getRight();
            }

            //set the child node as the parent's child based on where removeNode was initially
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
                root_ = child; 
                if (child != nullptr){
                    child->setParent(nullptr); 
                }
            }
        } 
    }
    
    //delete the node and return 
    delete removeNode; 
    return;
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    //return if null
    if(current == nullptr) {
        return nullptr; 
    }

    //getting the right most value on the left subtree
    if(current->getLeft() != nullptr) {
        current = current->getLeft(); 
        while (current->getRight() != nullptr) { 
            current = current->getRight(); 
        }
        return current; 
    }
    //or get the parent where current is the parents right node
    else { 
        while(current->getParent() != nullptr) {
            if(current->getParent()->getRight() == current){
                return current->getParent();
            }
            else {
                current = current -> getParent(); 
            }
        }
    }
    //otherwise return null
    return nullptr; 
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::postOrderDeletion(Node<Key,Value>* node) {
  //use post order recursion to start at the leaf nodes and eventually delete the entire tree
    if (node == nullptr){
        return; 
    }
    postOrderDeletion(node->getLeft()); 
    postOrderDeletion(node->getRight());
    delete node; 
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    //call post order deletion and then set the root to null
    postOrderDeletion(root_); 
    root_ = nullptr; 
    return; 
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    //go to the left most node in the BST
    Node<Key,Value>* smallestNode = root_; 
    while (smallestNode->getLeft() != nullptr and smallestNode != nullptr) {
        smallestNode = smallestNode->getLeft(); 
    }
    return smallestNode; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO 
    //initially start at the root of the BST 
    Node<Key,Value>* current = root_; 
    //while current is not null
    while (current != nullptr) {
      //if the key is correct, return the current node
        if(current->getKey() == key) {
            return current; 
        }
        //otherwise, the current key is less than the parameter key, go to the right subtree
        else if (current->getKey() < key){
            current = current->getRight(); 
        }
        //otherwise go left
        else{
            current = current->getLeft();
        }
    }
    //return null if not found 
    return nullptr; 
}

//MAY NEED TO CHANGE 
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(const Node<Key,Value>* node) const {
  //height of 0 if the node is null 
    if(node == nullptr){
        return 0; 
    }
    
    //get the height of left and right subtree 
    int leftHeight = getHeight(node->getLeft()); 
    int rightHeight = getHeight(node->getRight()); 

    //return -1 if not balanced 
    if(abs(leftHeight - rightHeight) > 1){
        return -1;
    }
    if(rightHeight == -1 or leftHeight == -1) {
        return -1; 
    }
    //return the max of both heights 
    return std::max(leftHeight, rightHeight) + 1;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    if(root_ == nullptr) {
        return true; 
    }

    //get the left and right heights 
    int leftHeight = getHeight(root_->getLeft());
    int rightHeight = getHeight(root_->getRight()); 

    //not balanced if the heights are different 
    if(rightHeight == -1 or leftHeight == -1){
        return false;
    }
    if(std::abs(leftHeight - rightHeight) > 1){
        return false; 
    }

    //otherwise return true 
    return true; 
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
