#ifndef MIVANI1_WET1_UPDATED_GIT_TEAM_H
#define MIVANI1_WET1_UPDATED_GIT_TEAM_H


class Team {
private:
    int m_teamID;
    Country* m_countryPtr;
    Sport m_sport;
    int m_teamStrength = 0;
    int m_numOfContestant = 0;
    AVLTree<Contestant>* m_leftTreeID;
    AVLTree<Contestant>* m_middleTreeID;
    AVLTree<Contestant>* m_rightTreeID;
    AVLTree<StrengthInfo>* m_leftTreeStrength;
    AVLTree<StrengthInfo>* m_middleTreeStrength;
    AVLTree<StrengthInfo>* m_rightTreeStrength;
    Team(int teamID, Country* countryPtr, Sport sport):
            m_teamID(teamID), m_countryPtr(countryPtr) , m_sport(sport),
            m_leftTreeID(nullptr), m_middleTreeID(nullptr), m_rightTreeID(nullptr),
            m_leftTreeStrength(nullptr), m_middleTreeStrength(nullptr), m_rightTreeStrength(nullptr){
        m_leftTreeID = new AVLTree<Contestant>();
        m_middleTreeID = new AVLTree<Contestant>();
        m_rightTreeID = new AVLTree<Contestant>();
        m_leftTreeStrength = new AVLTree<StrengthInfo>();
        m_middleTreeStrength = new AVLTree<StrengthInfo>();
        m_rightTreeStrength = new AVLTree<StrengthInfo>();
    }

    void calcStrength();
    void evenTeamsTrees ();
    void addContestantToChosenTeam(Node<Contestant>* nodeToAdd,Node<StrengthInfo>* strengthNode );
};



#endif //MIVANI1_WET1_UPDATED_GIT_TEAM_H
