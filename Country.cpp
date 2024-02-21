#include "Country.h"
Country::Country(int countryID, int medals):
        m_countryID(countryID) , m_medals(medals), m_numOfTeams(0),m_numOfContestant(0){}
int Country::get_countryID(){
    return this->m_countryID;
}
int Country::get_medals(){
    return this->m_medals;
}
int Country::get_numsTeam(){
    return this->m_numOfTeams;
}
int Country::get_numsContestant(){
    return this->m_numOfContestant;
}


void Country::countryWonMedal(){
    m_medals++;
}
void Country::removeOneTeam(){
    m_numOfTeams--;
}
void Country::removeOneContestant(){
    m_numOfContestant--;
}
void Country::addOneTeam(){
    m_numOfTeams++;
}
void Country::addOneContestant(){
    m_numOfContestant++;
}