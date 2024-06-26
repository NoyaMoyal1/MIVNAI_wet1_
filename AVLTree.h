#ifndef MIVNAI_WET1_NEW_AVLTREE_H
#define MIVNAI_WET1_NEW_AVLTREE_H
#include "Node.h"

template <typename K, typename D>
class AVLTree {
private:
    Node<K,D>* m_root;

public:
    //constructor
    explicit AVLTree(K rootKey): m_root(new Node<K,D>(rootKey)){}

    //destructor - when removing template class , first destruct the template and then the node
    virtual~ AVLTree(){
        delete m_root;
    }

    Node<K,D>* rightRotation(Node<K,D>* node);
    Node<K,D>* leftRotation(Node<K,D>* node);
    Node<K,D>* LRRotation(Node<K,D>* node);
    Node<K,D>* RLRotation(Node<K,D>* node);

    Node<K,D>* balance(Node<K,D>* unbalancedNode);
    Node<K,D>* findKey(int key, Node<K,D>* curRoot) const;
    Node<K,D>* insertNodeToTree(Node<K,D>* Newnode, Node<K,D>* currRoot);
    Node<K,D>* DeleteNodeFromTree(Node<K,D>* currRoot, K key);
    Node<K,D>* getRoot();
    void setRoot(Node<K,D>* newRoot);

    void preOrderPrint(Node<K,D>* root);
};
template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::getRoot(){
    return m_root;
}
template <typename K, typename D>
void AVLTree<K,D>::setRoot(Node<K,D>* newRoot){
    m_root = newRoot;
}
// Assume we got a valid input that isn't already in the tree - NEED TO CHECK OUTSIDE IN THE ADD FUNCTION!!
template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::insertNodeToTree(Node<K,D>* Newnode, Node<K,D>* currRoot){
    if(currRoot->getKey() < Newnode->getKey()){
        if(currRoot->getRight() == nullptr){
            currRoot->setRight(Newnode);
            currRoot->setHeight(currRoot->getHeight());
            //height = max(left->getHeight(), right->getHeight())+1;
            return currRoot;
        }
        else{
            currRoot->setRight(this->insertNodeToTree(Newnode, currRoot->getRight()));
        }
    }
    if(currRoot->getKey() > Newnode->getKey()){
        if (currRoot->getLeft() == nullptr){
            currRoot->setLeft(Newnode);
            currRoot->setHeight(currRoot->getHeight());
            return currRoot;
        }
        else{
            currRoot->setLeft(this->insertNodeToTree(Newnode, currRoot->getLeft()));
        }
    }
    currRoot->setHeight(currRoot->getHeight());
    int balanceFactor = currRoot->getBalanceFactor();
    if (balanceFactor == -2 || balanceFactor == 2){
        return balance(currRoot);
    }
    return currRoot;
}

template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::balance(Node<K,D>* unbalancedNode){
    if(unbalancedNode->getBalanceFactor() == 2){
        if(unbalancedNode->getLeft()->getBalanceFactor() >= 0){
            return rightRotation(unbalancedNode);
        }
        else if (unbalancedNode->getLeft()->getBalanceFactor() == -1){
            return LRRotation(unbalancedNode);
        }
    }
    else if (unbalancedNode->getBalanceFactor() == -2){
        if(unbalancedNode->getRight()->getBalanceFactor() <=0){
            return leftRotation(unbalancedNode);
        }
        else if (unbalancedNode->getRight()->getBalanceFactor() == 1){
            return RLRotation(unbalancedNode);;
        }
    }
    return unbalancedNode;
}

//find key in AVL tree and return a pointer to it
template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::findKey(int key, Node<K,D>* curRoot) const{
    if (key == curRoot->getKey()){
        return curRoot;
    }
    else if (key < curRoot->getKey() && curRoot->getLeft() != nullptr){
        return findKey(key, curRoot->getLeft());
    }
    else if (key > curRoot->getKey() && curRoot->getRight() != nullptr){
        return findKey(key, curRoot->getRight());
    }
    return nullptr;
}

template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::DeleteNodeFromTree(Node<K,D>* currRoot, K key) {
    if (currRoot == nullptr) {
        return nullptr;
    }
    if (key < currRoot->getKey()) {
        currRoot->setLeft(this->DeleteNodeFromTree(currRoot->getLeft(), key));
    }
    else if (key > currRoot->getKey()) {
        currRoot->setRight(this->DeleteNodeFromTree(currRoot->getRight(), key));
    }
    if (key == currRoot->getKey()){ //find the node to delete
        if (currRoot->getLeft() == nullptr && currRoot->getRight() == nullptr) {//is leaf
            delete currRoot;
            return nullptr;

        }
        else if (currRoot->getLeft() == nullptr) {// have one child
            Node<K,D>* temp = new Node<K,D>(currRoot->getRight());
            delete currRoot;
            return temp;
        }
        else if (currRoot->getRight() == nullptr) {// have one child
            Node<K,D>* temp = new Node<K,D>(currRoot->getLeft());
            delete currRoot;
            return temp;
        }
        else {//have two child
            Node<K,D>* temp = currRoot->getRight();
            while (temp->getLeft() != nullptr) {
                temp = temp->getLeft();
            }
            currRoot->setKey(temp->getKey());
            currRoot->setData(temp->getData());
            currRoot->setRight(this->DeleteNodeFromTree(currRoot->getRight(), temp->getKey()));
        }
    }
    // Update height of the current node
    currRoot->setHeight(currRoot->getHeight());
    if (currRoot->getBalanceFactor() == 2 || currRoot->getBalanceFactor() == -2){
        return balance(currRoot);
    }
    return currRoot;
}

template <typename K, typename D>
//LL rotation - this is Tree, node is unbalanced node. right rotation and updates the heights, and returns the new root
Node<K,D>* AVLTree<K,D>::rightRotation(Node<K,D>* node){
    Node<K,D>* x = node->getLeft();
    node->setLeft(x->getRight());
    x->setRight(node);
    node->setHeight(node->getHeight());
    x->setHeight(x->getHeight());
    return x;
}

template <typename K, typename D>
//RR rotation - left rotation, updates the heights, and returns the new root
Node<K,D>* AVLTree<K,D>::leftRotation(Node<K,D>* node){
    Node<K,D>* x = node->getRight();
    node->setRight(x->getLeft());
    x->setLeft(node);
    node->setHeight(node->getHeight());
    x->setHeight(x->getHeight());;
    return x;
}

template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::LRRotation(Node<K,D>* node){
    node->setLeft(leftRotation(node->getLeft()));
    return rightRotation(node);
}

//RR rotation - rotates, updates the heights, and returns the new root
template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::RLRotation(Node<K,D>* node){
    node->setRight(rightRotation(node->getRight()));
    return leftRotation(node);
}


template <typename K, typename D>
void AVLTree<K,D>::preOrderPrint(Node<K,D>* root){
    if(root != nullptr)
    {
        std::cout << root->getKey() << " ";
        this->preOrderPrint(root->getLeft());
        this->preOrderPrint(root->getRight());
    }
}

#endif //MIVNAI_WET1_NEW_AVLTREE_H
