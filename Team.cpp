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
    if (m_middleTreeID == nullptr && m_rightTreeID == nullptr && m_leftTreeID == nullptr) {
        m_leftTreeID->setRoot(nodeToAdd);
        m_leftTreeStrength->setRoot(strengthNode);
    } //belong to the right tree
    if (m_rightTreeID != nullptr) {
        int rightMin = m_rightTreeID->getMinOfTree()->getKey();
        if (nodeToAdd->getKey() > rightMin) {
            m_rightTreeID->insertNodeToTree(nodeToAdd, m_rightTreeID->getRoot());
            m_rightTreeStrength->insertNodeToTree(strengthNode, m_rightTreeStrength->getRoot());
            strengthNode->getData()->setTree('R');
        }
    }
        //belong to the left tree
    else if (m_leftTreeID != nullptr) {
        int leftMax = m_leftTreeID->getMaxOfTree()->getKey();
        if (nodeToAdd->getKey() < leftMax) {
            m_leftTreeID->insertNodeToTree(nodeToAdd, m_leftTreeID->getRoot());
            m_leftTreeStrength->insertNodeToTree(strengthNode, m_leftTreeStrength->getRoot());
            strengthNode->getData()->setTree('L');
        } else if (m_middleTreeID != nullptr) {
            {
                // Node belongs to the middle tree
                m_middleTreeID->insertNodeToTree(nodeToAdd, m_middleTreeID->getRoot());
                m_middleTreeStrength->insertNodeToTree(strengthNode, m_middleTreeStrength->getRoot());
                strengthNode->getData()->setTree('M');
            }
        } else {
            m_middleTreeID->setRoot(nodeToAdd);
            m_middleTreeStrength->setRoot(strengthNode);
            strengthNode->getData()->setTree('M');
        }
    }
    evenTeamsTrees();
    setTeamStrength(calcStrength());
    calcAusterity();
}

void Team::removeContestantFromChosenTeam(int contestantID, int contestantStrength) {
    //assumes that the contestant and team found and that the sport identical plus country
    StrengthPairKey key = StrengthPairKey(contestantStrength, contestantID);
    if (m_rightTreeID != nullptr) {
        int rightMin = m_rightTreeID->getMinOfTree()->getKey();
        if (contestantID > rightMin) {
            m_rightTreeID->DeleteNodeFromTree(m_rightTreeID->getRoot(), contestantID);
            m_leftTreeStrength->DeleteNodeFromTree(m_leftTreeStrength->getRoot(), key);
        }
    }
        //belong to the left tree
    else if (m_leftTreeID != nullptr) {
        int leftMax = m_leftTreeID->getMaxOfTree()->getKey();
        if (contestantID > leftMax) {
            m_leftTreeID->DeleteNodeFromTree(m_leftTreeID->getRoot(), contestantID);
            m_leftTreeStrength->DeleteNodeFromTree(m_leftTreeStrength->getRoot(), key);
            // Node belongs to the middle tree
        }
    } else if (m_middleTreeID != nullptr) {
        m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), contestantID);
        m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key);
    }
    evenTeamsTrees();
    setTeamStrength(calcStrength());
    calcAusterity();
}


void Team::evenTeamsTrees () {
    int leftCount , rightCount, middleCount;

    if ( m_leftTreeID == nullptr) leftCount=0;
    else leftCount = m_leftTreeID->getNodeCount();

    if ( m_middleTreeID == nullptr) middleCount=0;
    else middleCount = m_middleTreeID->getNodeCount();

    if ( m_rightTreeID == nullptr) rightCount=0;
    else rightCount = m_rightTreeID->getNodeCount();


//while trees not even
    while ((std::max(leftCount, std::max(middleCount, rightCount)) -
            std::min(leftCount, std::min(middleCount, rightCount))) > 1) {

        if (rightCount > middleCount + 1) {
            // Move the min node from the right tree to the middle tree
            Node<int, Contestant> *oldMinNode = m_rightTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_rightTreeID->DeleteNodeFromTree(m_rightTreeID->getRoot(), oldMinNode->getKey());

            if ( m_middleTreeID != nullptr)  m_middleTreeID->insertNodeToTree(newMaxNode, m_middleTreeID->getRoot());
            else m_middleTreeID->setRoot(newMaxNode);

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_rightTreeStrength->findKey(key, m_rightTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_rightTreeStrength->DeleteNodeFromTree(m_rightTreeStrength->getRoot(), key);

            if ( m_middleTreeStrength != nullptr)  m_middleTreeStrength->insertNodeToTree(newStrengthNode, m_middleTreeStrength->getRoot());
            else m_middleTreeStrength->setRoot(newStrengthNode);

            continue;
        }
        if (leftCount > middleCount + 1) {
            // Move the max node from the left tree to the middle tree

            Node<int, Contestant> *oldMaxNode = m_leftTreeID->getMaxOfTree();
            Node<int, Contestant> *newMinNode = new Node<int, Contestant>(oldMaxNode->getKey(), oldMaxNode->getData());

            m_leftTreeID->DeleteNodeFromTree(m_leftTreeID->getRoot(), oldMaxNode->getKey());

            if ( m_middleTreeID != nullptr)  m_middleTreeID->insertNodeToTree(newMinNode, m_middleTreeID->getRoot());
            else m_middleTreeID->setRoot(newMinNode);

            StrengthPairKey key = StrengthPairKey(newMinNode->getData()->get_strength(), newMinNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_leftTreeStrength->findKey(key, m_leftTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_leftTreeStrength->DeleteNodeFromTree(m_leftTreeStrength->getRoot(), key);
            if ( m_middleTreeStrength != nullptr)  m_middleTreeStrength->insertNodeToTree(newStrengthNode, m_middleTreeStrength->getRoot());
            else m_middleTreeStrength->setRoot(newStrengthNode);
            continue;
        }
        if (middleCount > rightCount + 1) {
            // Move the max node from the middle tree to the right tree
            Node<int, Contestant> *oldMaxNode = m_middleTreeID->getMaxOfTree();
            Node<int, Contestant> *newMinNode = new Node<int, Contestant>(oldMaxNode->getKey(), oldMaxNode->getData());

            m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMaxNode->getKey());
            m_rightTreeID->insertNodeToTree(newMinNode, m_rightTreeID->getRoot());

            if ( m_rightTreeID != nullptr)  m_rightTreeID->insertNodeToTree(newMinNode, m_rightTreeID->getRoot());
            else m_rightTreeID->setRoot(newMinNode);

            StrengthPairKey key = StrengthPairKey(newMinNode->getData()->get_strength(), newMinNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key);

            if ( m_rightTreeStrength != nullptr)  m_rightTreeStrength->insertNodeToTree(newStrengthNode, m_rightTreeStrength->getRoot());
            else m_rightTreeStrength->setRoot(newStrengthNode);

            continue;
        }
        if (middleCount > leftCount + 1) {
            // Move the min node from the middle tree to the left tree
            Node<int, Contestant> *oldMinNode = m_middleTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMinNode->getKey());

            if ( m_leftTreeID != nullptr)  m_leftTreeID->insertNodeToTree(newMaxNode, m_leftTreeID->getRoot());
            else m_leftTreeID->setRoot(newMaxNode);

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key);

            if ( m_leftTreeStrength != nullptr)  m_leftTreeStrength->insertNodeToTree(newStrengthNode, m_leftTreeStrength->getRoot());
            else m_leftTreeStrength->setRoot(newStrengthNode);

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

            m_leftTreeID->DeleteNodeFromTree(m_leftTreeID->getRoot(), oldMaxNode->getKey());
            m_middleTreeID->insertNodeToTree(newMinNode, m_middleTreeID->getRoot());

            StrengthPairKey key = StrengthPairKey(newMinNode->getData()->get_strength(), newMinNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_leftTreeStrength->findKey(key, m_leftTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_leftTreeStrength->DeleteNodeFromTree(m_leftTreeStrength->getRoot(), key);
            m_middleTreeStrength->insertNodeToTree( newStrengthNode,m_middleTreeStrength->getRoot());

            // Move the max node from the middle tree to the right tree
            Node<int, Contestant> *oldMaxNode2 = m_middleTreeID->getMaxOfTree();
            Node<int, Contestant> *newMinNode2 = new Node<int, Contestant>(oldMaxNode2->getKey(), oldMaxNode2->getData());

            m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMaxNode2->getKey());
            if ( m_rightTreeID != nullptr)  m_rightTreeID->insertNodeToTree(newMinNode2, m_rightTreeID->getRoot());
            else m_rightTreeID->setRoot(newMinNode2);

            m_rightTreeID->insertNodeToTree(newMinNode2, m_rightTreeID->getRoot());

            StrengthPairKey key2 = StrengthPairKey(newMinNode2->getData()->get_strength(), newMinNode2->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode2 = m_middleTreeStrength->findKey(key2, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode2 = new Node<StrengthPairKey,StrengthInfo> (key2 , strengthNode2->getData());

            m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key2);
            if ( m_rightTreeStrength != nullptr)  m_rightTreeStrength->insertNodeToTree(newStrengthNode2, m_rightTreeStrength->getRoot());
            else m_rightTreeStrength->setRoot(newStrengthNode2);
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

            m_rightTreeID->DeleteNodeFromTree(m_rightTreeID->getRoot(), oldMinNode2->getKey());
            m_middleTreeID->insertNodeToTree(newMaxNode2, m_middleTreeID->getRoot());

            StrengthPairKey key2 = StrengthPairKey(newMaxNode2->getData()->get_strength(), newMaxNode2->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode2 = m_rightTreeStrength->findKey(key2, m_rightTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode2 = new Node<StrengthPairKey,StrengthInfo> (key2 , strengthNode2->getData());

            m_rightTreeStrength->DeleteNodeFromTree(m_rightTreeStrength->getRoot(), key2);
            m_middleTreeStrength->insertNodeToTree( newStrengthNode2,m_rightTreeStrength->getRoot());


            // Move the min node from the middle tree to the left tree
            Node<int, Contestant> *oldMinNode = m_middleTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMinNode->getKey());
            if ( m_leftTreeID != nullptr)  m_leftTreeID->insertNodeToTree(newMaxNode, m_leftTreeID->getRoot());
            else m_leftTreeID->setRoot(newMaxNode);

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key);
            if ( m_leftTreeStrength != nullptr)  m_leftTreeStrength->insertNodeToTree(newStrengthNode, m_leftTreeStrength->getRoot());
            else m_leftTreeStrength->setRoot(newStrengthNode);

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
    StrengthTreeRemove->DeleteNodeFromTree(StrengthTreeRemove->getRoot(),tempNodeStrength1->getKey() );

    Node<int, Contestant>* tempNodeContestant1 = IDTreeRemove->findKey(tempStrength1->getIdFromInfo(), IDTreeRemove->getRoot());
    Contestant* tempContestant1 = tempNodeContestant1->getData();
    IDTreeRemove->DeleteNodeFromTree(IDTreeRemove->getRoot(),tempNodeContestant1->getKey() );


    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength2 = StrengthTreeRemove->getMinOfTree();
    StrengthInfo* tempStrength2 = tempNodeStrength2->getData();
    StrengthTreeRemove->DeleteNodeFromTree(StrengthTreeRemove->getRoot(),tempNodeStrength2->getKey() );

    Node<int, Contestant>* tempNodeContestant2 = IDTreeRemove->findKey(tempStrength2->getIdFromInfo(), IDTreeRemove->getRoot());
    Contestant* tempContestant2 = tempNodeContestant2->getData();
    IDTreeRemove->DeleteNodeFromTree(IDTreeRemove->getRoot(),tempNodeContestant2->getKey() );

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength3 = StrengthTreeRemove->getMinOfTree();
    StrengthInfo* tempStrength3 = tempNodeStrength3->getData();
    StrengthTreeRemove->DeleteNodeFromTree(StrengthTreeRemove->getRoot(),tempNodeStrength3->getKey() );

    Node<int, Contestant>* tempNodeContestant3 = IDTreeRemove->findKey(tempStrength3->getIdFromInfo(), IDTreeRemove->getRoot());
    Contestant* tempContestant3 = tempNodeContestant3->getData();
    IDTreeRemove->DeleteNodeFromTree(IDTreeRemove->getRoot(),tempNodeContestant3->getKey() );

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

    IDTreeRemove->insertNodeToTree(newNodeContestant1, IDTreeRemove->getRoot());
    IDTreeRemove->insertNodeToTree(newNodeContestant2, IDTreeRemove->getRoot());
    IDTreeRemove->insertNodeToTree(newNodeContestant3, IDTreeRemove->getRoot());

    StrengthTreeRemove->insertNodeToTree(newNodeStrength1, StrengthTreeRemove->getRoot());
    StrengthTreeRemove->insertNodeToTree(newNodeStrength2, StrengthTreeRemove->getRoot());
    StrengthTreeRemove->insertNodeToTree(newNodeStrength3, StrengthTreeRemove->getRoot());

    evenTeamsTrees();
    return AusStrength;
}


int Team::calcAusTwoAndOneNoProblem(AVLTree<int, Contestant>* IDTreeRemoveTwo,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveTwo,
                                    AVLTree<int, Contestant>* IDTreeRemoveOne,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveOne) {

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength1 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength1 = tempNodeStrength1->getData();
    StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength1->getKey() );

    Node<int, Contestant>* tempNodeContestant1 = IDTreeRemoveTwo->findKey(tempStrength1->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant1 = tempNodeContestant1->getData();
    IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant1->getKey() );

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength2 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength2 = tempNodeStrength2->getData();
    StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength2->getKey() );

    Node<int, Contestant>* tempNodeContestant2 = IDTreeRemoveTwo->findKey(tempStrength2->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant2 = tempNodeContestant2->getData();
    IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant2->getKey() );

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength3 = StrengthTreeRemoveOne->getMinOfTree();
    StrengthInfo* tempStrength3 = tempNodeStrength3->getData();
    StrengthTreeRemoveOne->DeleteNodeFromTree(StrengthTreeRemoveOne->getRoot(),tempNodeStrength3->getKey() );

    Node<int, Contestant>* tempNodeContestant3 = IDTreeRemoveOne->findKey(tempStrength3->getIdFromInfo(), IDTreeRemoveOne->getRoot());
    Contestant* tempContestant3 = tempNodeContestant3->getData();
    IDTreeRemoveOne->DeleteNodeFromTree(IDTreeRemoveOne->getRoot(),tempNodeContestant3->getKey() );

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

    IDTreeRemoveTwo->insertNodeToTree(newNodeContestant1, IDTreeRemoveTwo->getRoot());
    IDTreeRemoveTwo->insertNodeToTree(newNodeContestant2, IDTreeRemoveTwo->getRoot());
    IDTreeRemoveOne->insertNodeToTree(newNodeContestant3, IDTreeRemoveOne->getRoot());

    StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength1, StrengthTreeRemoveTwo->getRoot());
    StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength2, StrengthTreeRemoveTwo->getRoot());
    StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3, StrengthTreeRemoveOne->getRoot());

    evenTeamsTrees();
    return AusStrength;
}

int Team::calcAusTwoAndOneWithProblem(AVLTree<int, Contestant>* IDTreeRemoveTwo,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveTwo,
                                AVLTree<int, Contestant>* IDTreeRemoveOne,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveOne){

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength1 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength1 = tempNodeStrength1->getData();
    StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength1->getKey() );

    Node<int, Contestant>* tempNodeContestant1 = IDTreeRemoveTwo->findKey(tempStrength1->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant1 = tempNodeContestant1->getData();
    IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant1->getKey() );

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength2 = StrengthTreeRemoveTwo->getMinOfTree();
    StrengthInfo* tempStrength2 = tempNodeStrength2->getData();
    StrengthTreeRemoveTwo->DeleteNodeFromTree(StrengthTreeRemoveTwo->getRoot(),tempNodeStrength2->getKey() );

    Node<int, Contestant>* tempNodeContestant2 = IDTreeRemoveTwo->findKey(tempStrength2->getIdFromInfo(), IDTreeRemoveTwo->getRoot());
    Contestant* tempContestant2 = tempNodeContestant2->getData();
    IDTreeRemoveTwo->DeleteNodeFromTree(IDTreeRemoveTwo->getRoot(),tempNodeContestant2->getKey() );

    Node<int, Contestant>* tempNodeContestant3Max = IDTreeRemoveOne->getMaxOfTree();
    Contestant* tempContestant3Max =tempNodeContestant3Max->getData();
    IDTreeRemoveOne->DeleteNodeFromTree(IDTreeRemoveOne->getRoot(),tempNodeContestant3Max->getKey() );

    StrengthPairKey strengthKey3Max = StrengthPairKey(tempContestant3Max->get_strength(), tempContestant3Max->get_contestantID());
    StrengthTreeRemoveOne->DeleteNodeFromTree(StrengthTreeRemoveOne->getRoot(),strengthKey3Max );

    Node<StrengthPairKey, StrengthInfo>* tempNodeStrength3Option = StrengthTreeRemoveOne->getMinOfTree();
    StrengthInfo* tempStrength3Option = tempNodeStrength3Option->getData();

    evenTeamsTrees();
    int AusStrengthMax = calcStrength();

    Node<int, Contestant>* newNodeContestant3Max = new Node<int, Contestant>(tempContestant3Max->get_contestantID(), tempContestant3Max);
    StrengthPairKey strengthPair3Max = StrengthPairKey(tempContestant3Max->get_strength(),tempContestant3Max->get_contestantID());
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3Max = new Node<StrengthPairKey,StrengthInfo>(strengthPair3Max, tempContestant3Max->getStrengthInfo());

    IDTreeRemoveOne->insertNodeToTree(newNodeContestant3Max, IDTreeRemoveOne->getRoot());
    StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3Max, StrengthTreeRemoveTwo->getRoot());

    Node<int, Contestant>* tempNodeContestant3Option = IDTreeRemoveOne->findKey(tempStrength3Option->getIdFromInfo(), IDTreeRemoveOne->getRoot());
    Contestant* tempContestant3Option = tempNodeContestant3Option->getData();
    IDTreeRemoveOne->DeleteNodeFromTree(IDTreeRemoveOne->getRoot(),tempContestant3Option->get_contestantID() );

    evenTeamsTrees();
    int AusStrengthOption = calcStrength();

    Node<int, Contestant>* newNodeContestant1 = new Node<int, Contestant>(tempContestant1->get_contestantID(), tempContestant1);
    Node<int, Contestant>* newNodeContestant2 = new Node<int, Contestant>(tempContestant2->get_contestantID(), tempContestant2);
    Node<int, Contestant>* newNodeContestant3 = new Node<int, Contestant>(tempContestant3Option->get_contestantID(), tempContestant3Option);

    StrengthPairKey strengthPair1 = StrengthPairKey(tempStrength1->getStrengthFromInfo(),tempStrength1->getIdFromInfo());
    StrengthPairKey strengthPair2 = StrengthPairKey(tempStrength2->getStrengthFromInfo(),tempStrength2->getIdFromInfo());
    StrengthPairKey strengthPair3 = StrengthPairKey(tempStrength3Option->getStrengthFromInfo(),tempStrength3Option->getIdFromInfo());

    Node<StrengthPairKey,StrengthInfo>* newNodeStrength1 = new Node<StrengthPairKey,StrengthInfo>(strengthPair1, tempStrength1);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength2 = new Node<StrengthPairKey,StrengthInfo>(strengthPair2, tempStrength2);
    Node<StrengthPairKey,StrengthInfo>* newNodeStrength3 = new Node<StrengthPairKey,StrengthInfo>(strengthPair3, tempStrength3Option);

    IDTreeRemoveTwo->insertNodeToTree(newNodeContestant1, IDTreeRemoveTwo->getRoot());
    IDTreeRemoveTwo->insertNodeToTree(newNodeContestant2, IDTreeRemoveTwo->getRoot());
    IDTreeRemoveOne->insertNodeToTree(newNodeContestant3, IDTreeRemoveOne->getRoot());

    StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength1, StrengthTreeRemoveTwo->getRoot());
    StrengthTreeRemoveTwo->insertNodeToTree(newNodeStrength2, StrengthTreeRemoveTwo->getRoot());
    StrengthTreeRemoveOne->insertNodeToTree(newNodeStrength3, StrengthTreeRemoveOne->getRoot());

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
    if (m_numOfContestant == 6){
        m_austerityStrength = m_teamStrength;
        return;
    }
    int austerityMax = m_teamStrength;
    int curAusterity = 0;
    curAusterity = calcAusThreeFromOneTree(m_leftTreeID, m_leftTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    curAusterity = calcAusThreeFromOneTree(m_middleTreeID, m_middleTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    curAusterity = calcAusThreeFromOneTree(m_rightTreeID, m_rightTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
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
    curAusterity = calcAusTwoAndOneWithProblem(m_leftTreeID, m_leftTreeStrength, m_middleTreeID, m_middleTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    curAusterity = calcAusTwoAndOneWithProblem(m_rightTreeID, m_rightTreeStrength, m_middleTreeID, m_middleTreeStrength);
    if (curAusterity > austerityMax){
        austerityMax = curAusterity;
    }
    m_austerityStrength = austerityMax;
    return;
}