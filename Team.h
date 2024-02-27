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
public:
    Team(int teamID, Country* countryPtr, Sport sport):
            m_teamID(teamID), m_countryPtr(countryPtr) , m_sport(sport),
            m_leftTreeID(nullptr), m_middleTreeID(nullptr), m_rightTreeID(nullptr),
            m_leftTreeStrength(nullptr), m_middleTreeStrength(nullptr), m_rightTreeStrength(nullptr){
        m_leftTreeID = new AVLTree<int,Contestant>();
        m_middleTreeID = new AVLTree<int,Contestant>();
        m_rightTreeID = new AVLTree<int,Contestant>();
        m_leftTreeStrength = new AVLTree<StrengthPairKey,StrengthInfo>();
        m_middleTreeStrength = new AVLTree<StrengthPairKey,StrengthInfo>();
        m_rightTreeStrength = new AVLTree<StrengthPairKey,StrengthInfo>();
    }
    ~Team(){
        m_countryPtr = nullptr;
        delete m_leftTreeStrength;
        delete m_middleTreeStrength;
        delete m_rightTreeStrength;
        delete m_leftTreeID;
        delete m_middleTreeID;
        delete m_rightTreeID;
    }

    AVLTree<StrengthPairKey,StrengthInfo>* getLeftTreeStrength();
    AVLTree<StrengthPairKey,StrengthInfo>* getRightTreeStrength();
    AVLTree<StrengthPairKey,StrengthInfo>* getMiddleTreeStrength();
    AVLTree<int,Contestant>* getLeftTreeID();
    AVLTree<int,Contestant>* getRightTreeID();
    AVLTree<int,Contestant>* getMiddleTreeID();

    void setLeftTreeStrength(AVLTree<StrengthPairKey,StrengthInfo>* newTree);
    void setRightTreeStrength(AVLTree<StrengthPairKey,StrengthInfo>* newTree);
    void setMiddleTreeStrength(AVLTree<StrengthPairKey,StrengthInfo>* newTree);
    void setLeftTreeID(AVLTree<int,Contestant>* newTree);
    void setRightTreeID(AVLTree<int,Contestant>* newTree);
    void setMiddleTreeID(AVLTree<int,Contestant>* newTree);

    void setNumOfContestant (int num);
    int getNumOfContestant ();
    int getTeamID();
    void calcAusterity();
    int getAusterity();

    Country* getCountry();

    int getTeamStrength ();
    int calcStrength();
    void setTeamStrength(int strength);
    Sport getSport();
    void evenTeamsTrees ();
    void addContestantToChosenTeam(Node<int,Contestant>* nodeToAdd,Node<StrengthPairKey,StrengthInfo>* strengthNode );
    void removeContestantFromChosenTeam(int contestantID, int contestantStrength);
    void increaseNumOfContestants();
    void decreaseNumOfContestants();
    void setKeyAfterUnite();
    void setContestantKeyAfterUnite(Node<int, Contestant>* curRoot);
    void setStrengthKeyAfterUnite(Node<StrengthPairKey, StrengthInfo>* curRoot);



    int calcAusTwoFromRightOneFromMiddle(AVLTree<int, Contestant>* IDTreeRemoveTwo,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveTwo,
                                         AVLTree<int, Contestant>* IDTreeRemoveOne,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveOne);

    int calcAusTwoFromLeftOneFromMiddle(AVLTree<int, Contestant>* IDTreeRemoveTwo,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveTwo,
                                        AVLTree<int, Contestant>* IDTreeRemoveOne,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveOne);


    int calcAusTwoAndOneNoProblem(AVLTree<int, Contestant>* IDTreeRemoveTwo,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveTwo,
                                  AVLTree<int, Contestant>* IDTreeRemoveOne,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemoveOne);

    int calcAusThreeFromOneTree(AVLTree<int, Contestant>* IDTreeRemove,AVLTree<StrengthPairKey, StrengthInfo>* StrengthTreeRemove);


};

int max (int a, int b);
int min (int a, int b);

#endif //MIVANI1_WET1_UPDATED_GIT_TEAM_H
