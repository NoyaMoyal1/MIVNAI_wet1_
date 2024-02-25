#include "Team.h"
int Team::getNumOfContestant (){
return m_numOfContestant;
}
void Team::setNumOfContestant (int num){
     m_numOfContestant = num;
}

int Team::getTeamStrength (){
    return m_teamStrength;
}

AVLTree<StrengthPairKey,StrengthInfo>* Team::getLeftTreeStrength(){
    return m_leftTreeStrength;
}
AVLTree<StrengthPairKey,StrengthInfo>* Team::getRightTreeStrength(){
    return m_rightTreeStrength;
}
AVLTree<StrengthPairKey,StrengthInfo>* Team::getMiddleTreeStrength(){
    return m_middleTreeStrength;
}

AVLTree<int,Contestant>* Team::getLeftTreeID() {
    return m_leftTreeID;
}
AVLTree<int,Contestant>* Team::getRightTreeID(){
    return m_rightTreeID;
}
AVLTree<int,Contestant>* Team::getMiddleTreeID(){
    return m_middleTreeID;
}
int Team::getAusterity(){
    return m_austerityStrength;
}

void Team::setLeftTreeStrength(AVLTree<StrengthPairKey,StrengthInfo>* newTree){
    m_leftTreeStrength = newTree;
}
void Team::setRightTreeStrength(AVLTree<StrengthPairKey,StrengthInfo>* newTree){
    m_rightTreeStrength= newTree;
}
void Team::setMiddleTreeStrength(AVLTree<StrengthPairKey,StrengthInfo>* newTree){
    m_middleTreeStrength= newTree;
}
void Team::setLeftTreeID(AVLTree<int,Contestant>* newTree){
    m_leftTreeID= newTree;
}
void Team::setRightTreeID(AVLTree<int,Contestant>* newTree){
    m_rightTreeID= newTree;
}
void Team::setMiddleTreeID(AVLTree<int,Contestant>* newTree){
    m_middleTreeID= newTree;
}

int Team::calcStrength(){
    int sumOfTrees = (m_leftTreeID->getNodeCount() + m_rightTreeID->getNodeCount()+m_middleTreeID->getNodeCount());
    if (sumOfTrees == 0 ) {
        return 0;
    }
    if (sumOfTrees % 3 == 0 ){
        int rightMax = m_rightTreeStrength->getMaxOfTree()->getData()->getStrengthFromInfo();
        int middleMax = m_middleTreeStrength->getMaxOfTree()->getData()->getStrengthFromInfo();
        int leftMax = m_leftTreeStrength->getMaxOfTree()->getData()->getStrengthFromInfo();
        return (rightMax+middleMax+leftMax);
    }
    else return 0;
}
void Team::setTeamStrength(int strength){
    m_teamStrength=strength;
}
Country* Team::getCountry(){
    return this->m_countryPtr;
}

Sport Team::getSport () {
    return m_sport;
}
int Team::getTeamID(){
    return this->m_teamID;
}
void Team::addContestantToChosenTeam(Node<int,Contestant>* nodeToAdd,Node<StrengthPairKey,StrengthInfo>* strengthNode ) {
    //assumes that the contestant and team found and that the sport identical plus country
    if (m_middleTreeID->getRoot() == nullptr && m_rightTreeID->getRoot() == nullptr && m_leftTreeID->getRoot() == nullptr) {
        m_leftTreeID->setRoot(m_leftTreeID->insertNodeToTree( nodeToAdd, m_leftTreeID->getRoot()));
        m_leftTreeStrength->setRoot(m_leftTreeStrength->insertNodeToTree(strengthNode, m_leftTreeStrength->getRoot()));
    }
    //belong to the right tree
    else if (m_rightTreeID->getRoot() != nullptr) {
        int rightMin = m_rightTreeID->getMinOfTree()->getKey();
        if (nodeToAdd->getKey() > rightMin) {
            m_rightTreeID->setRoot( m_rightTreeID->insertNodeToTree(nodeToAdd, m_rightTreeID->getRoot()));
            m_rightTreeStrength->setRoot(m_rightTreeStrength->insertNodeToTree(strengthNode, m_rightTreeStrength->getRoot()));
            strengthNode->getData()->setTree('R');
        }
    }
    //belong to the left tree
    else if (m_leftTreeID->getRoot() != nullptr) {
        int leftMax = m_leftTreeID->getMaxOfTree()->getKey();
        if (nodeToAdd->getKey() < leftMax) {
            m_leftTreeID->setRoot(m_leftTreeID->insertNodeToTree(nodeToAdd, m_leftTreeID->getRoot()));
            m_leftTreeStrength->setRoot(m_leftTreeStrength->insertNodeToTree(strengthNode, m_leftTreeStrength->getRoot()));
            strengthNode->getData()->setTree('L');
        }
    }
    //belong to middle tree
    else {
            // Node belongs to the middle tree
            m_middleTreeID->setRoot(m_middleTreeID->insertNodeToTree(nodeToAdd, m_middleTreeID->getRoot()));
            m_middleTreeStrength->setRoot(m_middleTreeStrength->insertNodeToTree(strengthNode, m_middleTreeStrength->getRoot()));
            strengthNode->getData()->setTree('M');
        }
    evenTeamsTrees();
    setTeamStrength(calcStrength());
    calcAusterity();
}

void Team::removeContestantFromChosenTeam(int contestantID, int contestantStrength) {
    //assumes that the contestant and team found and that the sport identical plus country
    StrengthPairKey key = StrengthPairKey(contestantStrength, contestantID);
    if (m_rightTreeID->getRoot() != nullptr &&m_rightTreeID->findKey(contestantID, m_rightTreeID->getRoot()) ) {
            m_rightTreeID->setRoot(m_rightTreeID->DeleteNodeFromTree(m_rightTreeID->getRoot(), contestantID));
            m_rightTreeStrength->setRoot(m_rightTreeStrength->DeleteNodeFromTree(m_rightTreeStrength->getRoot(), key));
    }
    if (m_leftTreeID->getRoot() != nullptr && m_leftTreeID->findKey(contestantID, m_leftTreeID->getRoot())) {
        m_leftTreeID->setRoot(m_leftTreeID->DeleteNodeFromTree(m_leftTreeID->getRoot(), contestantID));
        m_leftTreeStrength->setRoot(m_leftTreeStrength->DeleteNodeFromTree(m_leftTreeStrength->getRoot(), key));
        // Node belongs to the middle tree
    }
    //belong to the left tree
    if (m_middleTreeID->getRoot() != nullptr && m_middleTreeID->findKey(contestantID, m_middleTreeID->getRoot())) {
        m_middleTreeID->setRoot(m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), contestantID));
        m_middleTreeStrength->setRoot(m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key));
    }
    evenTeamsTrees();
    setTeamStrength(calcStrength());
    calcAusterity();
}


int max (int a, int b){
    return (a>b) ? a : b;
}

int min (int a, int b){
    return (a<b) ? a : b;
}



void Team::evenTeamsTrees () {
    int leftCount , rightCount, middleCount;

    leftCount = m_leftTreeID->getNodeCount();
    middleCount = m_middleTreeID->getNodeCount();
    rightCount = m_rightTreeID->getNodeCount();


//while trees not even
    while ((max(leftCount, max(middleCount, rightCount)) -
            min(leftCount, min(middleCount, rightCount))) > 1) {

        if (rightCount > middleCount + 1) {
            // Move the min node from the right tree to the middle tree
            Node<int, Contestant> *oldMinNode = m_rightTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_rightTreeID->setRoot(m_rightTreeID->DeleteNodeFromTree(m_rightTreeID->getRoot(), oldMinNode->getKey()));

            m_middleTreeID->setRoot(m_middleTreeID->insertNodeToTree(newMaxNode, m_middleTreeID->getRoot()));

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_rightTreeStrength->findKey(key, m_rightTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_rightTreeStrength->setRoot(m_rightTreeStrength->DeleteNodeFromTree(m_rightTreeStrength->getRoot(), key));

            m_middleTreeStrength->setRoot(m_middleTreeStrength->insertNodeToTree(newStrengthNode, m_middleTreeStrength->getRoot()));
            leftCount = m_leftTreeID->getNodeCount();
            middleCount = m_middleTreeID->getNodeCount();
            rightCount = m_rightTreeID->getNodeCount();
            continue;
        }
        if (leftCount > middleCount + 1) {
            // Move the max node from the left tree to the middle tree

            Node<int, Contestant> *oldMaxNode = m_leftTreeID->getMaxOfTree();
            Node<int, Contestant> *newMinNode = new Node<int, Contestant>(oldMaxNode->getKey(), oldMaxNode->getData());

            m_leftTreeID->setRoot(m_leftTreeID->DeleteNodeFromTree(m_leftTreeID->getRoot(), oldMaxNode->getKey()));

            m_middleTreeID->setRoot(m_middleTreeID->insertNodeToTree(newMinNode, m_middleTreeID->getRoot()));

            StrengthPairKey key = StrengthPairKey(newMinNode->getData()->get_strength(), newMinNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_leftTreeStrength->findKey(key, m_leftTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_leftTreeStrength->setRoot(m_leftTreeStrength->DeleteNodeFromTree(m_leftTreeStrength->getRoot(), key));
            m_middleTreeStrength->setRoot(m_middleTreeStrength->insertNodeToTree(newStrengthNode, m_middleTreeStrength->getRoot()));
            leftCount = m_leftTreeID->getNodeCount();
            middleCount = m_middleTreeID->getNodeCount();
            rightCount = m_rightTreeID->getNodeCount();
            continue;
        }
        if (middleCount > rightCount + 1) {
            // Move the max node from the middle tree to the right tree
            Node<int, Contestant> *oldMaxNode = m_middleTreeID->getMaxOfTree();
            Node<int, Contestant> *newMinNode = new Node<int, Contestant>(oldMaxNode->getKey(), oldMaxNode->getData());

            m_middleTreeID->setRoot(m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMaxNode->getKey()));
            m_rightTreeID->setRoot(m_rightTreeID->insertNodeToTree(newMinNode, m_rightTreeID->getRoot()));

            m_rightTreeID->setRoot(m_rightTreeID->insertNodeToTree(newMinNode, m_rightTreeID->getRoot()));

            StrengthPairKey key = StrengthPairKey(newMinNode->getData()->get_strength(), newMinNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->setRoot(m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key));
            m_rightTreeStrength->setRoot(m_rightTreeStrength->insertNodeToTree(newStrengthNode, m_rightTreeStrength->getRoot()));
            leftCount = m_leftTreeID->getNodeCount();
            middleCount = m_middleTreeID->getNodeCount();
            rightCount = m_rightTreeID->getNodeCount();
            continue;
        }
        if (middleCount > leftCount + 1) {
            // Move the min node from the middle tree to the left tree
            Node<int, Contestant> *oldMinNode = m_middleTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_middleTreeID->setRoot(m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMinNode->getKey()));

            m_leftTreeID->setRoot(m_leftTreeID->insertNodeToTree(newMaxNode, m_leftTreeID->getRoot()));

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->setRoot(m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key));

           m_leftTreeStrength->setRoot(m_leftTreeStrength->insertNodeToTree(newStrengthNode, m_leftTreeStrength->getRoot()));
            leftCount = m_leftTreeID->getNodeCount();
            middleCount = m_middleTreeID->getNodeCount();
            rightCount = m_rightTreeID->getNodeCount();
            continue;
        }
        if (leftCount > rightCount + 1) {
            // move max node from left to middle , and max from middle to right
            //because we got here it means we have
            // x+2 on left, x+1 on middle , x on right
            //only right can be null
            // Move the max node from the left tree to the middle tree

            Node<int, Contestant> *oldMaxNode = m_leftTreeID->getMaxOfTree();
            Node<int, Contestant> *newMinNode = new Node<int, Contestant>(oldMaxNode->getKey(), oldMaxNode->getData());

            m_leftTreeID->setRoot(m_leftTreeID->DeleteNodeFromTree(m_leftTreeID->getRoot(), oldMaxNode->getKey()));
            m_middleTreeID->setRoot(m_middleTreeID->insertNodeToTree(newMinNode, m_middleTreeID->getRoot()));

            StrengthPairKey key = StrengthPairKey(newMinNode->getData()->get_strength(), newMinNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_leftTreeStrength->findKey(key, m_leftTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_leftTreeStrength->setRoot(m_leftTreeStrength->DeleteNodeFromTree(m_leftTreeStrength->getRoot(), key));
            m_middleTreeStrength->setRoot(m_middleTreeStrength->insertNodeToTree( newStrengthNode,m_middleTreeStrength->getRoot()));

            // Move the max node from the middle tree to the right tree
            Node<int, Contestant> *oldMaxNode2 = m_middleTreeID->getMaxOfTree();
            Node<int, Contestant> *newMinNode2 = new Node<int, Contestant>(oldMaxNode2->getKey(), oldMaxNode2->getData());

            m_middleTreeID->setRoot(m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMaxNode2->getKey()));
            m_rightTreeID->setRoot(m_rightTreeID->insertNodeToTree(newMinNode2, m_rightTreeID->getRoot()));

            m_rightTreeID->setRoot(m_rightTreeID->insertNodeToTree(newMinNode2, m_rightTreeID->getRoot()));

            StrengthPairKey key2 = StrengthPairKey(newMinNode2->getData()->get_strength(), newMinNode2->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode2 = m_middleTreeStrength->findKey(key2, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode2 = new Node<StrengthPairKey,StrengthInfo> (key2 , strengthNode2->getData());

            m_middleTreeStrength->setRoot(m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key2));
            m_rightTreeStrength->setRoot(m_rightTreeStrength->insertNodeToTree(newStrengthNode2, m_rightTreeStrength->getRoot()));
            leftCount = m_leftTreeID->getNodeCount();
            middleCount = m_middleTreeID->getNodeCount();
            rightCount = m_rightTreeID->getNodeCount();
            continue;
        }

        if (rightCount > leftCount + 1) {
            // move min node from right to middle , and min from middle to left
            //because we got here it means we have
            // x+2 on right , x+1 on middle , x on left
            //only left can be null

            // Move the min node from the right tree to the middle tree
            Node<int, Contestant> *oldMinNode2 = m_rightTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode2 = new Node<int, Contestant>(oldMinNode2->getKey(), oldMinNode2->getData());

            m_rightTreeID->setRoot(m_rightTreeID->DeleteNodeFromTree(m_rightTreeID->getRoot(), oldMinNode2->getKey()));
            m_middleTreeID->setRoot(m_middleTreeID->insertNodeToTree(newMaxNode2, m_middleTreeID->getRoot()));

            StrengthPairKey key2 = StrengthPairKey(newMaxNode2->getData()->get_strength(), newMaxNode2->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode2 = m_rightTreeStrength->findKey(key2, m_rightTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode2 = new Node<StrengthPairKey,StrengthInfo> (key2 , strengthNode2->getData());

            m_rightTreeStrength->setRoot(m_rightTreeStrength->DeleteNodeFromTree(m_rightTreeStrength->getRoot(), key2));
            m_middleTreeStrength->setRoot(m_middleTreeStrength->insertNodeToTree( newStrengthNode2,m_middleTreeStrength->getRoot()));


            // Move the min node from the middle tree to the left tree
            Node<int, Contestant> *oldMinNode = m_middleTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_middleTreeID->setRoot(m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMinNode->getKey()));
            m_leftTreeID->setRoot(m_leftTreeID->insertNodeToTree(newMaxNode, m_leftTreeID->getRoot()));

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->setRoot(m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key));
            m_leftTreeStrength->setRoot(m_leftTreeStrength->insertNodeToTree(newStrengthNode, m_leftTreeStrength->getRoot()));

            leftCount = m_leftTreeID->getNodeCount();
            middleCount = m_middleTreeID->getNodeCount();
            rightCount = m_rightTreeID->getNodeCount();
            continue;
        }

    }
    return;
}
void Team::increaseNumOfContestants(){
    m_numOfContestant++;
}
void Team::decreaseNumOfContestants(){
    m_numOfContestant--;
}


//int Team::calcAusterity1();
/*
void Team::calcAusterity(){
    int strength1 = calcAusterity1();
}
 */


int Team::calcAusThreeFromOneTree(AVLTree<int, Contestant>* IDTreeRemove,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemove){

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength1 = StrengthTreeRemove->getMinOfTree();
    StrengthInfo* tempStrength1 = tempNodeStrength1->getData();
    StrengthTreeRemove->setRoot(StrengthTreeRemove->DeleteNodeFromTree(StrengthTreeRemove->getRoot(),tempNodeStrength1->getKey() ));

    Node<int, Contestant>* tempNodeContestant1 = IDTreeRemove->findKey(tempStrength1->getIdFromInfo(), IDTreeRemove->getRoot());
    Contestant* tempContestant1 = tempNodeContestant1->getData();
    IDTreeRemove->setRoot(IDTreeRemove->DeleteNodeFromTree(IDTreeRemove->getRoot(),tempNodeContestant1->getKey() ));


    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength2 = StrengthTreeRemove->getMinOfTree();
    StrengthInfo* tempStrength2 = tempNodeStrength2->getData();
    StrengthTreeRemove->setRoot(StrengthTreeRemove->DeleteNodeFromTree(StrengthTreeRemove->getRoot(),tempNodeStrength2->getKey() ));

    Node<int, Contestant>* tempNodeContestant2 = IDTreeRemove->findKey(tempStrength2->getIdFromInfo(), IDTreeRemove->getRoot());
    Contestant* tempContestant2 = tempNodeContestant2->getData();
    IDTreeRemove->setRoot(IDTreeRemove->DeleteNodeFromTree(IDTreeRemove->getRoot(),tempNodeContestant2->getKey() ));

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength3 = StrengthTreeRemove->getMinOfTree();
    StrengthInfo* tempStrength3 = tempNodeStrength3->getData();
    StrengthTreeRemove->setRoot(StrengthTreeRemove->DeleteNodeFromTree(StrengthTreeRemove->getRoot(),tempNodeStrength3->getKey() ));

    Node<int, Contestant>* tempNodeContestant3 = IDTreeRemove->findKey(tempStrength3->getIdFromInfo(), IDTreeRemove->getRoot());
    Contestant* tempContestant3 = tempNodeContestant3->getData();
    IDTreeRemove->setRoot(IDTreeRemove->DeleteNodeFromTree(IDTreeRemove->getRoot(),tempNodeContestant3->getKey() ));

    evenTeamsTrees();
    int AusStrength = calcStrength();

    Node<int, Contestant>* newNodeContestant1 = new Node<int, Contestant>(tempContestant1->get_contestantID(), tempContestant1);
    Node<int, Contestant>* newNodeContestant2 = new Node<int, Contestant>(tempContestant2->get_contestantID(), tempContestant2);
    Node<int, Contestant>* newNodeContestant3 = new Node<int, Contestant>(tempContestant3->get_contestantID(), tempContestant3);

    StrengthPairKey strengthPair1 = StrengthPairKey(tempStrength1->getStrengthFromInfo(),tempStrength1->getIdFromInfo());
    StrengthPairKey strengthPair2 = StrengthPairKey(tempStrength2->getStrengthFromInfo(),tempStrength2->getIdFromInfo());
    StrengthPairKey strengthPair3 = StrengthPairKey(tempStrength3->getStrengthFromInfo(),tempStrength3->getIdFromInfo());

    Node<StrengthPairKey,StrengthInfo>* newNodeStrength1 = new Node<StrengthPairKey,StrengthInfo>(strengthPair1, tempStrength1);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength2 = new Node<StrengthPairKey,StrengthInfo>(strengthPair2, tempStrength2);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3 = new Node<StrengthPairKey,StrengthInfo>(strengthPair3, tempStrength3);

    IDTreeRemove->setRoot(IDTreeRemove->insertNodeToTree(newNodeContestant1, IDTreeRemove->getRoot()));
    IDTreeRemove->setRoot(IDTreeRemove->insertNodeToTree(newNodeContestant2, IDTreeRemove->getRoot()));
    IDTreeRemove->setRoot(IDTreeRemove->insertNodeToTree(newNodeContestant3, IDTreeRemove->getRoot()));

    StrengthTreeRemove->setRoot(StrengthTreeRemove->insertNodeToTree(newNodeStrength1, StrengthTreeRemove->getRoot()));
    StrengthTreeRemove->setRoot(StrengthTreeRemove->insertNodeToTree(newNodeStrength2, StrengthTreeRemove->getRoot()));
    StrengthTreeRemove->setRoot(StrengthTreeRemove->insertNodeToTree(newNodeStrength3, StrengthTreeRemove->getRoot()));

    evenTeamsTrees();
    return AusStrength;
}


int Team::calcAusTwoAndOneNoProblem(AVLTree<int, Contestant>* IDTreeRemoveTwo,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveTwo,
                                    AVLTree<int, Contestant>* IDTreeRemoveOne,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveOne) {

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength1 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength1 = tempNodeStrength1->getData();
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength1->getKey() ));

    Node<int, Contestant>* tempNodeContestant1 = IDTreeRemoveTwo->findKey(tempStrength1->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant1 = tempNodeContestant1->getData();
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant1->getKey() ));

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength2 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength2 = tempNodeStrength2->getData();
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength2->getKey() ));

    Node<int, Contestant>* tempNodeContestant2 = IDTreeRemoveTwo->findKey(tempStrength2->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant2 = tempNodeContestant2->getData();
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant2->getKey() ));

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength3 = StrengthTreeRemoveOne->getMinOfTree();
    StrengthInfo* tempStrength3 = tempNodeStrength3->getData();
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->DeleteNodeFromTree(StrengthTreeRemoveOne->getRoot(),tempNodeStrength3->getKey() ));

    Node<int, Contestant>* tempNodeContestant3 = IDTreeRemoveOne->findKey(tempStrength3->getIdFromInfo(), IDTreeRemoveOne->getRoot());
    Contestant* tempContestant3 = tempNodeContestant3->getData();
    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->DeleteNodeFromTree(IDTreeRemoveOne->getRoot(),tempNodeContestant3->getKey() ));

    evenTeamsTrees();
    int AusStrength = calcStrength();

    Node<int, Contestant>* newNodeContestant1 = new Node<int, Contestant>(tempContestant1->get_contestantID(), tempContestant1);
    Node<int, Contestant>* newNodeContestant2 = new Node<int, Contestant>(tempContestant2->get_contestantID(), tempContestant2);
    Node<int, Contestant>* newNodeContestant3 = new Node<int, Contestant>(tempContestant3->get_contestantID(), tempContestant3);

    StrengthPairKey strengthPair1 = StrengthPairKey(tempStrength1->getStrengthFromInfo(),tempStrength1->getIdFromInfo());
    StrengthPairKey strengthPair2 = StrengthPairKey(tempStrength2->getStrengthFromInfo(),tempStrength2->getIdFromInfo());
    StrengthPairKey strengthPair3 = StrengthPairKey(tempStrength3->getStrengthFromInfo(),tempStrength3->getIdFromInfo());

    Node<StrengthPairKey,StrengthInfo>* newNodeStrength1 = new Node<StrengthPairKey,StrengthInfo>(strengthPair1, tempStrength1);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength2 = new Node<StrengthPairKey,StrengthInfo>(strengthPair2, tempStrength2);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3 = new Node<StrengthPairKey,StrengthInfo>(strengthPair3, tempStrength3);

    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->insertNodeToTree(newNodeContestant1, IDTreeRemoveTwo->getRoot()));
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->insertNodeToTree(newNodeContestant2, IDTreeRemoveTwo->getRoot()));
    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->insertNodeToTree(newNodeContestant3, IDTreeRemoveOne->getRoot()));

    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength1, StrengthTreeRemoveTwo->getRoot()));
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength2, StrengthTreeRemoveTwo->getRoot()));
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3, StrengthTreeRemoveOne->getRoot()));

    evenTeamsTrees();
    return AusStrength;
}

int Team::calcAusTwoAndOneWithProblemMovingRight(AVLTree<int, Contestant>* IDTreeRemoveTwo,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveTwo,
                                AVLTree<int, Contestant>* IDTreeRemoveOne,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveOne){

    // removes min node from two strength tree
    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength1 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength1 = tempNodeStrength1->getData();
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength1->getKey() ));

    // removes fitting node from two id tree
    Node<int, Contestant>* tempNodeContestant1 = IDTreeRemoveTwo->findKey(tempStrength1->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant1 = tempNodeContestant1->getData();
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant1->getKey() ));

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength2 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength2 = tempNodeStrength2->getData();
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength2->getKey() ));

    Node<int, Contestant>* tempNodeContestant2 = IDTreeRemoveTwo->findKey(tempStrength2->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant2 = tempNodeContestant2->getData();
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant2->getKey() ));
    // done dealing with two tree removal

    //other func - switch to min. removes from tree
    Node<int, Contestant>* tempNodeContestant3Max = IDTreeRemoveOne->getMaxOfTree();
    Contestant* tempContestant3Max =tempNodeContestant3Max->getData();
    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->DeleteNodeFromTree(IDTreeRemoveOne->getRoot(),tempNodeContestant3Max->getKey() ));

    StrengthPairKey strengthKey3Max = StrengthPairKey(tempContestant3Max->get_strength(), tempContestant3Max->get_contestantID());
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->DeleteNodeFromTree(StrengthTreeRemoveOne->getRoot(),strengthKey3Max ));

    Node<int, Contestant>* tempNodeContestant3NextToMax = IDTreeRemoveOne->getMaxOfTree();
    Contestant* tempContestant3NextToMax = tempNodeContestant3NextToMax->getData();
    // done dealing with one tree removal max

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength3Option = StrengthTreeRemoveOne->getMinOfTree();
    StrengthInfo* tempStrength3Option = tempNodeStrength3Option->getData();

    evenTeamsTrees();
    int AusStrengthMax = calcStrength();
    //done checking the max option

    Node<int, Contestant>* newNodeContestant3Max = new Node<int, Contestant>(tempContestant3Max->get_contestantID(), tempContestant3Max);
    StrengthPairKey strengthPair3Max = StrengthPairKey(tempContestant3Max->get_strength(),tempContestant3Max->get_contestantID());
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3Max = new Node<StrengthPairKey,StrengthInfo>(strengthPair3Max, tempContestant3Max->getStrengthInfo());


    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->insertNodeToTree(newNodeContestant3Max, IDTreeRemoveOne->getRoot()));
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3Max, StrengthTreeRemoveOne->getRoot()));

    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(), tempContestant3NextToMax->get_contestantID()));
    StrengthPairKey strengthPair3NextToMax = StrengthPairKey(tempContestant3NextToMax->get_strength(),tempContestant3NextToMax->get_contestantID());
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(), strengthPair3NextToMax));

    Node<int, Contestant>* newNodeContestant3NextToMax = new Node<int, Contestant>(tempContestant3NextToMax->get_contestantID(), tempContestant3NextToMax);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3NextToMax = new Node<StrengthPairKey,StrengthInfo>(strengthPair3NextToMax, tempContestant3NextToMax->getStrengthInfo());

    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->insertNodeToTree(newNodeContestant3NextToMax, IDTreeRemoveOne->getRoot()));
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3NextToMax, StrengthTreeRemoveOne->getRoot()));
    //done fixing tree before removing option

    Node<int, Contestant>* tempNodeContestant3Option = IDTreeRemoveOne->findKey(tempStrength3Option->getIdFromInfo(), IDTreeRemoveOne->getRoot());
    Contestant* tempContestant3Option = tempNodeContestant3Option->getData();
    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->DeleteNodeFromTree(IDTreeRemoveOne->getRoot(),tempContestant3Option->get_contestantID() ));

    evenTeamsTrees();
    int AusStrengthOption = calcStrength();
    //done checking option

    Node<int, Contestant>* newNodeContestant1 = new Node<int, Contestant>(tempContestant1->get_contestantID(), tempContestant1);
    Node<int, Contestant>* newNodeContestant2 = new Node<int, Contestant>(tempContestant2->get_contestantID(), tempContestant2);
    Node<int, Contestant>* newNodeContestant3 = new Node<int, Contestant>(tempContestant3Option->get_contestantID(), tempContestant3Option);

    StrengthPairKey strengthPair1 = StrengthPairKey(tempStrength1->getStrengthFromInfo(),tempStrength1->getIdFromInfo());
    StrengthPairKey strengthPair2 = StrengthPairKey(tempStrength2->getStrengthFromInfo(),tempStrength2->getIdFromInfo());
    StrengthPairKey strengthPair3 = StrengthPairKey(tempStrength3Option->getStrengthFromInfo(),tempStrength3Option->getIdFromInfo());

    Node<StrengthPairKey,StrengthInfo>* newNodeStrength1 = new Node<StrengthPairKey,StrengthInfo>(strengthPair1, tempStrength1);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength2 = new Node<StrengthPairKey,StrengthInfo>(strengthPair2, tempStrength2);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3 = new Node<StrengthPairKey,StrengthInfo>(strengthPair3, tempStrength3Option);

    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->insertNodeToTree(newNodeContestant1, IDTreeRemoveTwo->getRoot()));
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->insertNodeToTree(newNodeContestant2, IDTreeRemoveTwo->getRoot()));
    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->insertNodeToTree(newNodeContestant3, IDTreeRemoveOne->getRoot()));

    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength1, StrengthTreeRemoveTwo->getRoot()));
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength2, StrengthTreeRemoveTwo->getRoot()));
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3, StrengthTreeRemoveOne->getRoot()));

    evenTeamsTrees();

    if(AusStrengthOption > AusStrengthMax){
        return AusStrengthOption;
    }
    else{
        return AusStrengthMax;
    }
}


int Team::calcAusTwoAndOneWithProblemMovingLeft(AVLTree<int, Contestant>* IDTreeRemoveTwo,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveTwo,
                                                 AVLTree<int, Contestant>* IDTreeRemoveOne,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveOne){

    // removes min node from two strength tree
    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength1 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength1 = tempNodeStrength1->getData();
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength1->getKey() ));

    // removes fitting node from two id tree
    Node<int, Contestant>* tempNodeContestant1 = IDTreeRemoveTwo->findKey(tempStrength1->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant1 = tempNodeContestant1->getData();
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant1->getKey() ));

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength2 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength2 = tempNodeStrength2->getData();
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength2->getKey() ));

    Node<int, Contestant>* tempNodeContestant2 = IDTreeRemoveTwo->findKey(tempStrength2->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant2 = tempNodeContestant2->getData();
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant2->getKey() ));
    // done dealing with two tree removal

    //other func - switch to min. removes from one tree
    Node<int, Contestant>* tempNodeContestant3Min = IDTreeRemoveOne->getMinOfTree();
    Contestant* tempContestant3Min =tempNodeContestant3Min->getData();
    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->DeleteNodeFromTree(IDTreeRemoveOne->getRoot(),tempNodeContestant3Min->getKey() ));

    StrengthPairKey strengthKey3Min = StrengthPairKey(tempContestant3Min->get_strength(), tempContestant3Min->get_contestantID());
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->DeleteNodeFromTree(StrengthTreeRemoveOne->getRoot(),strengthKey3Min ));

    Node<int, Contestant>* tempNodeContestant3NextToMin = IDTreeRemoveOne->getMinOfTree();
    Contestant* tempContestant3NextToMin = tempNodeContestant3NextToMin->getData();
    // done dealing with one tree removal min

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength3Option = StrengthTreeRemoveOne->getMinOfTree();
    StrengthInfo* tempStrength3Option = tempNodeStrength3Option->getData();

    evenTeamsTrees();
    int AusStrengthMax = calcStrength();
    //done checking the min option

    Node<int, Contestant>* newNodeContestant3Min = new Node<int, Contestant>(tempContestant3Min->get_contestantID(), tempContestant3Min);
    StrengthPairKey strengthPair3Min = StrengthPairKey(tempContestant3Min->get_strength(),tempContestant3Min->get_contestantID());
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3Min = new Node<StrengthPairKey,StrengthInfo>(strengthPair3Min, tempContestant3Min->getStrengthInfo());


    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->insertNodeToTree(newNodeContestant3Min, IDTreeRemoveOne->getRoot()));
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3Min, StrengthTreeRemoveOne->getRoot()));

    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(), tempContestant3NextToMin->get_contestantID()));
    StrengthPairKey strengthPair3NextToMin = StrengthPairKey(tempContestant3NextToMin->get_strength(),tempContestant3NextToMin->get_contestantID());
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(), strengthPair3NextToMin));

    Node<int, Contestant>* newNodeContestant3NextToMin = new Node<int, Contestant>(tempContestant3NextToMin->get_contestantID(), tempContestant3NextToMin);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3NextToMin = new Node<StrengthPairKey,StrengthInfo>(strengthPair3NextToMin, tempContestant3NextToMin->getStrengthInfo());

    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->insertNodeToTree(newNodeContestant3NextToMin, IDTreeRemoveOne->getRoot()));
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3NextToMin, StrengthTreeRemoveOne->getRoot()));
    //done fixing tree before removing option

    Node<int, Contestant>* tempNodeContestant3Option = IDTreeRemoveOne->findKey(tempStrength3Option->getIdFromInfo(), IDTreeRemoveOne->getRoot());
    Contestant* tempContestant3Option = tempNodeContestant3Option->getData();
    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->DeleteNodeFromTree(IDTreeRemoveOne->getRoot(),tempContestant3Option->get_contestantID() ));

    evenTeamsTrees();
    int AusStrengthOption = calcStrength();
    //done checking option

    Node<int, Contestant>* newNodeContestant1 = new Node<int, Contestant>(tempContestant1->get_contestantID(), tempContestant1);
    Node<int, Contestant>* newNodeContestant2 = new Node<int, Contestant>(tempContestant2->get_contestantID(), tempContestant2);
    Node<int, Contestant>* newNodeContestant3 = new Node<int, Contestant>(tempContestant3Option->get_contestantID(), tempContestant3Option);

    StrengthPairKey strengthPair1 = StrengthPairKey(tempStrength1->getStrengthFromInfo(),tempStrength1->getIdFromInfo());
    StrengthPairKey strengthPair2 = StrengthPairKey(tempStrength2->getStrengthFromInfo(),tempStrength2->getIdFromInfo());
    StrengthPairKey strengthPair3 = StrengthPairKey(tempStrength3Option->getStrengthFromInfo(),tempStrength3Option->getIdFromInfo());

    Node<StrengthPairKey,StrengthInfo>* newNodeStrength1 = new Node<StrengthPairKey,StrengthInfo>(strengthPair1, tempStrength1);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength2 = new Node<StrengthPairKey,StrengthInfo>(strengthPair2, tempStrength2);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3 = new Node<StrengthPairKey,StrengthInfo>(strengthPair3, tempStrength3Option);

    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->insertNodeToTree(newNodeContestant1, IDTreeRemoveTwo->getRoot()));
    IDTreeRemoveTwo->setRoot(IDTreeRemoveTwo->insertNodeToTree(newNodeContestant2, IDTreeRemoveTwo->getRoot()));
    IDTreeRemoveOne->setRoot(IDTreeRemoveOne->insertNodeToTree(newNodeContestant3, IDTreeRemoveOne->getRoot()));

    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength1, StrengthTreeRemoveTwo->getRoot()));
    StrengthTreeRemoveTwo->setRoot(StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength2, StrengthTreeRemoveTwo->getRoot()));
    StrengthTreeRemoveOne->setRoot(StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3, StrengthTreeRemoveOne->getRoot()));

    evenTeamsTrees();

    if(AusStrengthOption > AusStrengthMax){
        return AusStrengthOption;
    }
    else{
        return AusStrengthMax;
    }
}









void Team::calcAusterity(){
    if(m_numOfContestant % 3 != 0 || m_numOfContestant == 0 || m_numOfContestant == 3){
        m_austerityStrength = 0;
        return;
    }

    int austerityMax = m_teamStrength;
    int curAusterity = 0;
    if (m_numOfContestant != 6  ) {
        curAusterity = calcAusThreeFromOneTree(m_leftTreeID, m_leftTreeStrength);
        if (curAusterity > austerityMax) {
            austerityMax = curAusterity;
        }
        curAusterity = calcAusThreeFromOneTree(m_middleTreeID, m_middleTreeStrength);
        if (curAusterity > austerityMax) {
            austerityMax = curAusterity;
        }
        curAusterity = calcAusThreeFromOneTree(m_rightTreeID, m_rightTreeStrength);
        if (curAusterity > austerityMax) {
            austerityMax = curAusterity;
        }
    }
    curAusterity = calcAusTwoAndOneNoProblem(m_middleTreeID, m_middleTreeStrength, m_leftTreeID, m_leftTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    curAusterity = calcAusTwoAndOneNoProblem(m_middleTreeID, m_middleTreeStrength, m_rightTreeID, m_rightTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    curAusterity = calcAusTwoAndOneNoProblem(m_rightTreeID, m_rightTreeStrength, m_leftTreeID, m_leftTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    curAusterity = calcAusTwoAndOneNoProblem(m_leftTreeID, m_leftTreeStrength, m_rightTreeID, m_rightTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    curAusterity = calcAusTwoAndOneWithProblemMovingLeft(m_rightTreeID, m_rightTreeStrength, m_middleTreeID, m_middleTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    curAusterity = calcAusTwoAndOneWithProblemMovingRight(m_leftTreeID, m_leftTreeStrength, m_middleTreeID, m_middleTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    m_austerityStrength = austerityMax;
    return;
}