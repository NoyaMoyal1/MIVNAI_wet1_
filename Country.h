#ifndef MIVANI1_WET1_UPDATED_GIT_COUNTRY_H
#define MIVANI1_WET1_UPDATED_GIT_COUNTRY_H

#include "wet1util.h"

class Country {

    int m_countryID;
    int m_medals;
    int m_numOfTeams;
    int m_numOfContestant;
public:
//constructor
    Country(int countryID, int medals);
    int get_countryID();
    int get_medals();
    int get_numsTeam();
    int get_numsContestant();

    void countryWonMedal();
    void removeOneTeam();
    void removeOneContestant();
    void addOneTeam();
    void addOneContestant();
};





#endif //MIVANI1_WET1_UPDATED_GIT_COUNTRY_H