#include "Contestant.h"

Contestant::Contestant(int contestantID, Country* countryPtr, Sport sport, int strength):
        m_contestantID(contestantID), m_countryPtr(countryPtr), m_sport(sport)
        ,m_strengthInfo(new StrengthInfo(strength, contestantID)),m_numOfCurrTeams(0) {
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
    return m_strengthInfo->getStrengthFromInfo();
}
void Contestant::set_strength(int newStrength){
    m_strengthInfo->setStrengthFromInfo(newStrength);
}
StrengthInfo* Contestant::getStrengthInfo(){
    return m_strengthInfo;
}

void Contestant::increaseTeamNumAndArray(int teamID){
    m_teamArray[m_numOfCurrTeams]=teamID;
    m_numOfCurrTeams++;
}

void Contestant::decreaseTeamNumAndArray(int teamID){
    int i;
    for (i = 0; i < THREE ; ++i) {
        if (m_teamArray[i] == teamID) {
            m_teamArray[i] = -1;
            m_numOfCurrTeams--;
            break;
        }
    }
    for ( int j = i+1 ; j < THREE && i < THREE ; j++ )
        if (m_teamArray[j] != -1){
            m_teamArray[i]=m_teamArray[j];
            m_teamArray[j] = -1;
            i++;
        }

}

void mergeContestant(Contestant** a, int na , Contestant** b, int nb , Contestant** c){
    int ia=0, ib=0, ic=0;

    while(ia < na && ib < nb){
        if((*(a+ia))->get_contestantID() < (*(b+ib))->get_contestantID() ){
            *(c+ic)=*(a+ia);
            ia++;
        }
        else{
            *(c+ic)=*(b+ib);
            ib++;
        }
        ic++;
    }
    for(;ia < na; ia++, ic++)
        *(c+ic)=*(a+ia);
    for(;ib < nb; ib++, ic++)
        *(c+ic)=*(b+ib);
}