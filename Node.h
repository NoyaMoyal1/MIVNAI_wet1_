
#ifndef MIVNAI_WET1_NEW_NODE_H
#define MIVNAI_WET1_NEW_NODE_H
#include <iostream>
//#include "wet1util.h"


template <typename K, typename D>
class Node {
private:
    K key ;
    D *data;
    Node *left;
    Node *right;
    int height;

public:
//constructor
    explicit Node(K key): key(key), data(nullptr), left(nullptr), right(nullptr), height(0) {}
    Node(K key, D* data): key(key), data(data), left(nullptr), right(nullptr), height(0) {}

    //copy constractor
    Node(Node<K, D>* nodePtr): key(nodePtr->key), data(nodePtr->data), left(nodePtr->left), right(nodePtr->right), height(nodePtr->height) {}
//destructor - when removing template class , first destruct the template and then the node
    virtual~ Node(){
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right = nullptr;
        }
    }

    bool isSameKey (const Node other) const ;

    void setKey(K newKey);
    int getHeight () const ;
    int getBalanceFactor() const;
    Node<K,D>* getRight() const;
    Node<K,D>* getLeft() const;
    D* getData() const;
    K getKey() const;
    void firstSetData (D* newDataPtr);
    void setRight(Node<K,D>* newRight);
    void setLeft(Node<K,D>* newLeft);
    void setHeight(int newHeight);
    void setData(D* newData);
    void setNewData(D** newData, int x);
    int max (int a, int b) const;

};

template <typename K, typename D>
void Node<K,D>::setKey(K newKey){
    this->key = newKey;
}
template <typename K, typename D>
void Node<K,D>::setData(D* newData){
    data = newData;
}
template <typename K, typename D>
void Node<K,D>::setNewData(D** newData, int x){
    data = *(newData+x);
}
template <typename K, typename D>
void Node<K,D>::setHeight(int newHeight){
    height = newHeight;
}
template <typename K, typename D>
void Node<K,D>::setRight(Node<K,D>* newRight){
    right = newRight;
}
template <typename K, typename D>
void Node<K,D>::setLeft(Node<K,D>* newLeft){
    left = newLeft;
}
template <typename K, typename D>
int Node<K,D>::max (int a, int b) const{
    return (a>b) ? a : b;
}
//maybe delete it
template <typename K, typename D>
bool Node<K,D>::isSameKey (const Node other) const {
    if (other.key == key) {
        return true;
    }
    return false;
}
//changedddddddddddddddddddd
template<typename K, typename D>
int Node<K,D>::getHeight() const {
    if(left == nullptr && right == nullptr){
        return 0;
    }
    if(left == nullptr){
        return 1 + right->height;
    }
    if(right == nullptr){
        return 1+ left->height;
    }
    return 1 + max(left->height , right->height);
}

template<typename K, typename D>
Node<K,D>* Node<K,D>::getRight() const {
    return right;
}

template<typename K, typename D>
Node<K,D>* Node<K,D>::getLeft() const {
    return left;
}

template<typename K, typename D>
D* Node<K,D>::getData() const {
    return data;
}

template<typename K, typename D>
K Node<K,D>::getKey() const{
    return key;
}

template<typename K, typename D>
void Node<K,D>::firstSetData (D* newDataPtr){
    data=newDataPtr;
}

template<typename K, typename D>
int Node<K,D>::getBalanceFactor() const{
    if (this->left != nullptr && this->right != nullptr) {//2 child
        return (this->left->getHeight() - this->right->getHeight());
    }
    if (this->left == nullptr && this->right != nullptr) {//right child
        return -(this->getHeight());
    }
    if (this->left != nullptr && this->right == nullptr) {//left child
        return (this->getHeight());
    }
    return 0;//leaf
}



/*
Node<int>* root = new Node<int>(21);

Node<int>* a = new Node<int>(23);
Node<int>* b = new Node<int>(22);
Node<int>* c = new Node<int>(19);
root = root->insertNode(a);
root = root->insertNode(b);
root = root->insertNode(c);
root = root->deleteNode(root,23);
root->preOrderPrint();

Node<int>* a = new Node<int>(23);
Node<int>* b = new Node<int>(22);
Node<int>* c = new Node<int>(19);
//  root->preOrderPrint();

//root->preOrderPrint();
root = root->deleteNode(root,23);
// root->preOrderPrint();
// root = root->deleteNode(root,7);
root = root->deleteNode(root,21);
root->preOrderPrint();
    return 0;
    }
*/

#endif //MIVNAI_WET1_NEW_NODE_H