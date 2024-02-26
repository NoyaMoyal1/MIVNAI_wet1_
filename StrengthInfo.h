
#ifndef MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H
#define MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H


class StrengthInfo {
private:
    int m_strength;
    int m_strengthContestantID;
    char m_subTree;
public:
    StrengthInfo(int strength, int id);

    void setTree(char subTree);

    char getTree();


    int getIdFromInfo();

    void setStrengthFromInfo(int strength);

    int getStrengthFromInfo();
};

void mergeStrength(StrengthInfo** a, int na , StrengthInfo** b, int nb , StrengthInfo** c);

#endif //MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H