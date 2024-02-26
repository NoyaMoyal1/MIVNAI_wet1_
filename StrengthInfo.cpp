#include "StrengthInfo.h"

StrengthInfo::StrengthInfo(int strength, int id) : m_strength(strength) ,m_strengthContestantID(id) , m_subTree('V'){}

char StrengthInfo::getTree(){
    return m_subTree;
}

void StrengthInfo::setTree(char subTree){
    m_subTree=subTree;
}
void StrengthInfo::setStrengthFromInfo(int strength) {
    m_strength=strength;
}
int StrengthInfo::getStrengthFromInfo(){
    return m_strength;
}
int StrengthInfo::getIdFromInfo(){
    return m_strengthContestantID;
}

void mergeStrength(StrengthInfo** a, int na , StrengthInfo** b, int nb , StrengthInfo** c) {
    int ia = 0, ib = 0, ic = 0;
    while (ia < na && ib < nb) {
        if ( ((*(a + ia))->getStrengthFromInfo() < (*(b + ib))->getStrengthFromInfo()) ||
                ( ( (*(a + ia))->getStrengthFromInfo() == (*(b + ib))->getStrengthFromInfo()) &&
                        ((*(a + ia))->getIdFromInfo() < (*(b + ib))->getIdFromInfo())) ){
            *(c + ic) = *(a + ia);
            ia++;
        } else {
            *(c + ic) = *(b + ib);
            ib++;
        }
        ic++;
    }
    for (; ia < na; ia++, ic++)
        *(c + ic) = *(a + ia);
    for (; ib < nb; ib++, ic++)
        *(c + ic) = *(b + ib);

}
