#ifndef MIVNAI_WET1_NEW_AVLTREE_H
#define MIVNAI_WET1_NEW_AVLTREE_H
#include "Node.h"

template <typename K, typename D>
class AVLTree {
private:
    Node<K,D>* m_root;
    int m_nodeCount;

public:
    //constructor
    AVLTree(): m_root(nullptr), m_nodeCount(0){}

    //destructor - when removing template class , first destruct the template and then the node
    virtual~ AVLTree(){
        deleteAllTree(m_root);
        delete m_root;
    }

    Node<K,D>* rightRotation(Node<K,D>* node);
    Node<K,D>* leftRotation(Node<K,D>* node);
    Node<K,D>* LRRotation(Node<K,D>* node);
    Node<K,D>* RLRotation(Node<K,D>* node);
    Node<K,D>* getMaxOfTree ();
    Node<K,D>* getMinOfTree ();
    int getNodeCount() const;

    Node<K,D>* balance(Node<K,D>* unbalancedNode);
    Node<K,D>* findKey(K key, Node<K,D>* curRoot) const;
    Node<K,D>* insertNodeToTree(Node<K,D>* Newnode, Node<K,D>* currRoot);
    Node<K,D>* DeleteNodeFromTree(Node<K,D>* currRoot, K key);
    Node<K,D>* getRoot();
    void setRoot(Node<K,D>* newRoot);

    void preOrderPrint(Node<K,D>* root);
    void inOrderPrint(Node<K,D>* root);

    void changeTreeFromFull(int sizeOfArray);
    Node<K,D>* FullTreeRemoveNode(int* numOfNodesToRemovePtr, Node<K,D>* currRoot);
    Node<K,D>* buildFullTreeRoot(int sizeOfTree, K nullKey);
    int calcSizeOfFullTree(int sizeOfArray);
    void convertTreeToArray (Node<K,D>* currRoot, D** data, int* index);
    void convertArrayToTree (Node<K,D>* currRoot, D** data, int* index);
    void buildTreeBeforeInsertArray(int sizeOfArray, K nullKey);
    void deleteAllTree(Node<K,D>* root);


};

template <typename K, typename D>
void AVLTree<K,D>::deleteAllTree(Node<K,D>* root){
    if (root == nullptr){
        return;
    }
    deleteAllTree(root->getLeft());
    delete root->getData();
    deleteAllTree(root->getRight());
}
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
Node<K,D>* AVLTree<K,D>::insertNodeToTree(Node<K,D>* newNode, Node<K,D>* currRoot) {
    if(currRoot == nullptr) {
        m_nodeCount++;
        newNode->setHeight(0);
        return newNode;
    }

    if(currRoot->getKey() < newNode->getKey()) {
        currRoot->setRight(insertNodeToTree(newNode, currRoot->getRight()));
    }
    else if(currRoot->getKey()> newNode->getKey()) {
        currRoot->setLeft(insertNodeToTree(newNode, currRoot->getLeft()));
    }

    // update height
    currRoot->setHeight( currRoot->getHeight() );

    return balance(currRoot);
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
            return RLRotation(unbalancedNode);
        }
    }
    return unbalancedNode;
}

//find key in AVL tree and return a pointer to it
template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::findKey(K key, Node<K,D>* curRoot) const{
    if ( curRoot == nullptr ){
        return nullptr;
    }
    if (curRoot != nullptr && key == curRoot->getKey()){
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
            m_nodeCount--;
            delete currRoot;
            return nullptr;

        }
        else if (currRoot->getLeft() == nullptr) {// have one child
            try{
                Node<K,D>* temp = new Node<K,D>(currRoot->getRight());
                m_nodeCount--;
                delete currRoot;
                return temp;
            }
            catch (const std::bad_alloc &e)
            {
                throw StatusType::ALLOCATION_ERROR;
            }
        }
        else if (currRoot->getRight() == nullptr) {// have one child
            try{
                Node<K,D>* temp = new Node<K,D>(currRoot->getLeft());
                m_nodeCount--;
                delete currRoot;
                return temp;
            }
            catch (const std::bad_alloc &e)
            {
                throw StatusType::ALLOCATION_ERROR;
            }
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

template <typename K, typename D>
void AVLTree<K,D>::inOrderPrint(Node<K,D>* root){
    if(root != nullptr)
    {
        this->preOrderPrint(root->getLeft());
        std::cout << root->getKey() << " ";
        this->preOrderPrint(root->getRight());
    }
}


template <typename K, typename D>
int AVLTree<K,D>::getNodeCount() const{
    return m_nodeCount;
}
template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::getMaxOfTree (){
    Node<K,D>* temp = m_root;
    while (temp != nullptr ){
        if (temp->getRight() == nullptr){
            return temp;
        }
        temp=temp->getRight();
    }
    return nullptr ; //if the tree is empty
}

template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::getMinOfTree (){
    Node<K,D>* temp = m_root;
    while (temp != nullptr ){
        if (temp->getLeft() == nullptr){
            return temp;
        }
        temp=temp->getLeft();
    }
    return nullptr ; //if the tree is empty
}
template <typename K, typename D>
int AVLTree<K,D>::calcSizeOfFullTree(int sizeOfArray){
    if (sizeOfArray == 0 ) return 0;
    int hezka = 1;
    int sum = 0;
    while (sum+1 < sizeOfArray){
        sum += 2 << hezka;
        hezka++;
    }
    return sum+1;
}

template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::buildFullTreeRoot(int sizeOfTree, K nullKey){
    if(sizeOfTree == 0){
        return nullptr;
    }
    try{
        Node<K,D>* root = new Node<K,D>(nullKey);
        root->setLeft(buildFullTreeRoot((sizeOfTree-1)/2, nullKey));
        root->setRight(buildFullTreeRoot((sizeOfTree-1)/2, nullKey));
        return root;
    }
    catch (const std::bad_alloc &e)
    {
        throw StatusType::ALLOCATION_ERROR;
    }
}

template <typename K, typename D>
void AVLTree<K,D>::changeTreeFromFull(int sizeOfArray){
    int numOfNodesToRemove = m_nodeCount - sizeOfArray;
    m_root = FullTreeRemoveNode(&numOfNodesToRemove, m_root);
}

template <typename K, typename D>
Node<K,D>* AVLTree<K,D>::FullTreeRemoveNode(int* numOfNodesToRemovePtr, Node<K,D>* currRoot){
    if(*numOfNodesToRemovePtr == 0 || currRoot == nullptr){
        return currRoot;
    }
    currRoot->setRight(FullTreeRemoveNode(numOfNodesToRemovePtr, currRoot->getRight()));
    if(currRoot->getRight() == nullptr && currRoot->getLeft() == nullptr){
        *numOfNodesToRemovePtr--;
        m_nodeCount--;
        return DeleteNodeFromTree(currRoot, currRoot->getKey());
    }
    currRoot->setLeft(FullTreeRemoveNode(numOfNodesToRemovePtr, currRoot->getLeft()));
    return currRoot;
}


template<typename K, typename D>
void AVLTree<K,D>::convertTreeToArray (Node<K,D>* currRoot, D** data, int* index){
    if(currRoot == nullptr){
        return;
    }
    convertTreeToArray(currRoot->getLeft(), data, index);
    *(data + (*index))= currRoot->getData();
    (*index)++;
    convertTreeToArray(currRoot->getRight(), data, index);
}

template<typename K, typename D>
void AVLTree<K,D>::buildTreeBeforeInsertArray(int sizeOfArray, K nullKey){
    int sizeOfTree = calcSizeOfFullTree(sizeOfArray);
    m_root = buildFullTreeRoot(sizeOfTree, nullKey);
    m_nodeCount = sizeOfTree;
    changeTreeFromFull(sizeOfArray);
}



template<typename K, typename D>
void AVLTree<K,D>::convertArrayToTree (Node<K,D>* currRoot, D** data, int* index){
    if(currRoot == nullptr){
        return;
    }
    convertArrayToTree(currRoot->getLeft(), data, index);
    currRoot->setData(*data +(*index));
    (*index)++;
    convertArrayToTree(currRoot->getRight(), data, index);
}

#endif //MIVNAI_WET1_NEW_AVLTREE_H