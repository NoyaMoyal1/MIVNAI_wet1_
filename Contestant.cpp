//
// Created by noyam on 21/02/2024.
//

#include "Contestant.h"

Contestant::Contestant(int contestantID, Country* countryPtr, Sport sport, int strength):
        m_contestantID(contestantID), m_countryPtr(countryPtr), m_sport(sport)
        ,m_strengthInfo(new StrengthInfo(strength)),m_numOfCurrTeams(0) {
    for (int i = 0; i < THREE ; ++i) {
        m_teamArray[i] = -1;
    }
}
Contestant::~Contestant() {
    delete m_strengthInfo;
}
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

void Contestant::changeStrengthInfo(int newStrength){
    m_strengthInfo->setStrength(newStrength);
}