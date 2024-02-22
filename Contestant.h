

#ifndef TRY2_COPY_CONTESTANT_H
#define TRY2_COPY_CONTESTANT_H

#include "StrengthInfo.h"
#include "Country.h"

#define THREE 3

class Contestant {
private:
    int m_contestantID;
    Country* m_countryPtr;
    Sport m_sport;
    int m_teamArray[THREE] ;
    StrengthInfo* m_strengthInfo;
    int m_numOfCurrTeams;


public:
    Contestant(int contestantID, Country* countryPtr, Sport sport, int strength);

    ~Contestant();
    Contestant(const Contestant& other) = delete;

    int get_contestantID();
    Country* get_Country();
    Sport get_sport();
    int* get_teamsArr();//?
    int get_numTeam();
    int get_strength();
    StrengthInfo* getStrengthInfo();
    void set_strength(int power);
    void increaseTeamNumAndArray(int teamID);
    void decreaseTeamNumAndArray(int teamID);

};


#endif //MIVANI1_WET1_UPDATED_GIT_CONTESTANT_H
