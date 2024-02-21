#include "Contestant.h"

Contestant::Contestant(int contestantID, Country* countryPtr, Sport sport, int strength):
        m_contestantID(contestantID), m_countryPtr(countryPtr), m_sport(sport), m_strength(strength)
        ,m_strengthInfo(new StrengthInfo(m_strength)),m_numOfCurrTeams(0) {
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

int Contestant::get_strength(){
    return m_strength;
}
void Contestant::set_strength(int newStrength){
    m_strength = newStrength;
}

void Contestant::changeStrengthInfo(int newStrength){
    m_strengthInfo->setStrength(newStrength);
}