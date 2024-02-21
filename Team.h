#ifndef TRY2_COPY_TEAM_H
#define TRY2_COPY_TEAM_H
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
public:
    AVLTree<StrengthPairKey,StrengthInfo>* getLeftTreeStrength();
    AVLTree<StrengthPairKey,StrengthInfo>* getRightTreeStrength();
    AVLTree<StrengthPairKey,StrengthInfo>* getMiddleTreeStrength();
    AVLTree<int,Contestant>* getLeftTreeID();
    AVLTree<int,Contestant>* getRightTreeID();
    AVLTree<int,Contestant>* getMiddleTreeID();
    int getNumOfContestant ();

    void calcAusterity();
    int calcAusterity1();
    Country* getCountry();

    int calcStrength();
    void setTeamStrength(int strength);
    Sport getSport();
    void evenTeamsTrees ();
    void addContestantToChosenTeam(Node<int,Contestant>* nodeToAdd,Node<StrengthPairKey,StrengthInfo>* strengthNode );
};


#endif //MIVANI1_WET1_UPDATED_GIT_TEAM_H
