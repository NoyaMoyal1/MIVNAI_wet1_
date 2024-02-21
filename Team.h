#ifndef MIVANI1_WET1_UPDATED_GIT_TEAM_H
#define MIVANI1_WET1_UPDATED_GIT_TEAM_H



#include "Contestant.h"
#include "AVLTree.h"
#include "StrengthPairKey.h"


class Team {
private:
    int m_teamID;
    Country* m_countryPtr;
    Sport m_sport;
    int m_teamStrength = 0;
    int m_numOfContestant = 0;
    int m_austerityStrength = 0;
    AVLTree<int,Contestant>* m_leftTreeID;
    AVLTree<int,Contestant>* m_middleTreeID;
    AVLTree<int,Contestant>* m_rightTreeID;
    AVLTree<StrengthPairKey,StrengthInfo>* m_leftTreeStrength;
    AVLTree<StrengthPairKey,StrengthInfo>* m_middleTreeStrength;
    AVLTree<StrengthPairKey,StrengthInfo>* m_rightTreeStrength;
    Team(int teamID, Country* countryPtr, Sport sport):
            m_teamID(teamID), m_countryPtr(countryPtr) , m_sport(sport),
            m_leftTreeID(nullptr), m_middleTreeID(nullptr), m_rightTreeID(nullptr),
            m_leftTreeStrength(nullptr), m_middleTreeStrength(nullptr), m_rightTreeStrength(nullptr),
            m_austerityStrength(0){
        m_leftTreeID = new AVLTree<int,Contestant>();
        m_middleTreeID = new AVLTree<int,Contestant>();
        m_rightTreeID = new AVLTree<int,Contestant>();
        m_leftTreeStrength = new AVLTree<StrengthPairKey,StrengthInfo>();
        m_middleTreeStrength = new AVLTree<StrengthPairKey,StrengthInfo>();
        m_rightTreeStrength = new AVLTree<StrengthPairKey,StrengthInfo>();
    }

    void calcAusterity();
    int calcAusterity1();

    void calcStrength();
    void evenTeamsTrees ();
    void addContestantToChosenTeam(Node<int,Contestant>* nodeToAdd,Node<StrengthPairKey,StrengthInfo>* strengthNode );
};

void Team::calcStrength(){
    int sumOfTrees = (m_leftTreeID->getNodeCount() + m_rightTreeID->getNodeCount()+m_middleTreeID->getNodeCount());
    if (sumOfTrees == 0 ) {
        m_teamStrength = 0;
        return;
    }
    if (sumOfTrees % 3 == 0 ){
        int rightMax = m_rightTreeStrength->getMaxOfTree()->getData()->getStrength();
        int middleMax = m_middleTreeStrength->getMaxOfTree()->getData()->getStrength();
        int leftMax = m_leftTreeStrength->getMaxOfTree()->getData()->getStrength();
        m_teamStrength = rightMax+middleMax+leftMax;
    }
    else m_teamStrength = 0;
}


void Team::addContestantToChosenTeam(Node<int,Contestant>* nodeToAdd,Node<StrengthPairKey,StrengthInfo>* strengthNode ) {
    //assumes that the contestant and team found and that the sport identical plus country
    if (m_middleTreeID != nullptr && m_rightTreeID != nullptr && m_rightTreeID != nullptr) {

        int leftMax = m_rightTreeID->getMaxOfTree()->getKey();
        int rightMin = m_leftTreeID->getMinOfTree()->getKey();

        //belong to the left tree
        if (nodeToAdd->getKey() < leftMax) {
            m_leftTreeID->insertNodeToTree(nodeToAdd, m_leftTreeID->getRoot());
            m_leftTreeStrength->insertNodeToTree(strengthNode, m_leftTreeStrength->getRoot());
            strengthNode->getData()->setTree('L');
        }
            //belong to the right tree
        else if (nodeToAdd->getKey() > rightMin) {
            m_rightTreeID->insertNodeToTree(nodeToAdd, m_rightTreeID->getRoot());
            m_rightTreeStrength->insertNodeToTree(strengthNode,m_rightTreeStrength->getRoot());
            strengthNode->getData()->setTree('R');
        } else {
            // Node belongs to the middle tree
            m_middleTreeID->insertNodeToTree(nodeToAdd, m_middleTreeID->getRoot());
            m_middleTreeStrength->insertNodeToTree(strengthNode, m_middleTreeStrength->getRoot());
            strengthNode->getData()->setTree('M');
        }
        evenTeamsTrees();
        calcStrength();

    }
}



void Team::evenTeamsTrees () {

    int leftCount = m_leftTreeID->getNodeCount();
    int middleCount = m_middleTreeID->getNodeCount();
    int rightCount = m_rightTreeID->getNodeCount();

//while trees not even
    while ((std::max(leftCount, std::max(middleCount, rightCount)) -
            std::min(leftCount, std::min(middleCount, rightCount))) > 1) {

        if (rightCount > middleCount + 1) {
            // Move the min node from the right tree to the middle tree
            Node<int, Contestant> *oldMinNode = m_rightTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_rightTreeID->DeleteNodeFromTree(m_rightTreeID->getRoot(), oldMinNode->getKey());
            m_middleTreeID->insertNodeToTree(newMaxNode, m_middleTreeID->getRoot());

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_rightTreeStrength->findKey(key, m_rightTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_rightTreeStrength->DeleteNodeFromTree(m_rightTreeStrength->getRoot(), key);
            m_middleTreeStrength->insertNodeToTree( newStrengthNode,m_rightTreeStrength->getRoot());

            continue;
        }
        if (leftCount > middleCount + 1) {
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
            continue;
        }
        if (middleCount > rightCount + 1) {
            // Move the max node from the middle tree to the right tree
            Node<int, Contestant> *oldMaxNode = m_middleTreeID->getMaxOfTree();
            Node<int, Contestant> *newMinNode = new Node<int, Contestant>(oldMaxNode->getKey(), oldMaxNode->getData());

            m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMaxNode->getKey());
            m_rightTreeID->insertNodeToTree(newMinNode, m_rightTreeID->getRoot());

            StrengthPairKey key = StrengthPairKey(newMinNode->getData()->get_strength(), newMinNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key);
            m_rightTreeStrength->insertNodeToTree( newStrengthNode,m_rightTreeStrength->getRoot());

            continue;
        }
        if (middleCount > leftCount + 1) {
            // Move the min node from the middle tree to the left tree
            Node<int, Contestant> *oldMinNode = m_middleTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMinNode->getKey());
            m_leftTreeID->insertNodeToTree(newMaxNode, m_leftTreeID->getRoot());

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key);
            m_leftTreeStrength->insertNodeToTree( newStrengthNode,m_leftTreeStrength->getRoot());

            continue;
        }
        if (leftCount > rightCount + 1) {
            // move max node from left to middle , and max from middle to right

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
            m_rightTreeID->insertNodeToTree(newMinNode2, m_rightTreeID->getRoot());

            StrengthPairKey key2 = StrengthPairKey(newMinNode2->getData()->get_strength(), newMinNode2->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode2 = m_middleTreeStrength->findKey(key2, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode2 = new Node<StrengthPairKey,StrengthInfo> (key2 , strengthNode2->getData());

            m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key2);
            m_rightTreeStrength->insertNodeToTree( newStrengthNode2,m_rightTreeStrength->getRoot());

            continue;
        }

        if (rightCount > leftCount + 1) {
            // move min node from right to middle , and min from middle to left

            // Move the min node from the middle tree to the left tree
            Node<int, Contestant> *oldMinNode = m_middleTreeID->getMinOfTree();
            Node<int, Contestant> *newMaxNode = new Node<int, Contestant>(oldMinNode->getKey(), oldMinNode->getData());

            m_middleTreeID->DeleteNodeFromTree(m_middleTreeID->getRoot(), oldMinNode->getKey());
            m_leftTreeID->insertNodeToTree(newMaxNode, m_leftTreeID->getRoot());

            StrengthPairKey key = StrengthPairKey(newMaxNode->getData()->get_strength(), newMaxNode->getKey());
            Node<StrengthPairKey,StrengthInfo> *strengthNode = m_middleTreeStrength->findKey(key, m_middleTreeStrength->getRoot());
            Node<StrengthPairKey,StrengthInfo> *newStrengthNode = new Node<StrengthPairKey,StrengthInfo> (key , strengthNode->getData());

            m_middleTreeStrength->DeleteNodeFromTree(m_middleTreeStrength->getRoot(), key);
            m_leftTreeStrength->insertNodeToTree( newStrengthNode,m_leftTreeStrength->getRoot());

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

            continue;
        }
    }
    return;
}

int Team::calcAusterity1();

void Team::calcAusterity(){
    int strength1 = calcAusterity1();
}

#endif //MIVANI1_WET1_UPDATED_GIT_TEAM_H
