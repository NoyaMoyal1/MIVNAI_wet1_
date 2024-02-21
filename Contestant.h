
#ifndef MIVANI1_WET1_UPDATED_GIT_CONTESTANT_H
#define MIVANI1_WET1_UPDATED_GIT_CONTESTANT_H

#include "StrengthInfo.h"
#define THREE 3

class Contestant {
private:
    int m_contestantID;
    Country* m_countryPtr;
    Sport m_sport;
    int m_strength;
    int m_teamArray[THREE] = {0};
    StrengthInfo* m_strengthInfo;
    int m_numOfCurrTeams;


public:
    Contestant(int contestantID, Country* countryPtr, Sport sport, int strength):
        m_contestantID(contestantID), m_countryPtr(countryPtr), m_sport(sport), m_strength(strength)
        ,m_strengthInfo(new StrengthInfo(m_strength)),m_numOfCurrTeams(0) {}

    ~Contestant() {
        delete m_strengthInfo;
    }
    Contestant(const Contestant& other) = delete;

    int get_contestantID();
    Country* get_Country();
    Sport get_sport();
    int* get_teamsArr();//?
    int get_numTeam();
    int get_strength();
    void set_strength(int power);
    void changeStrengthInfo(int teamId);
};


int Contestant:: get_contestantID(){
    return m_contestantID;
}
Country* Contestant::get_Country(){
    return m_countryPtr;
}
Sport Contestant::get_sport(){
    return m_sport;
}
int* Contestant::get_teamsArr(){
    return m_teamArray;
}
int Contestant::get_numTeam(){
    return m_numOfCurrTeams;
}

int Contestant::get_strength(){
    return m_strength;
}
void Contestant::set_strength(int newStrength){
    m_strength = newStrength;
}

void Contestant::changeStrengthInfo(int newStrength){
    m_strengthInfo->setStrength(newStrength);
}
#endif //MIVANI1_WET1_UPDATED_GIT_CONTESTANT_H
