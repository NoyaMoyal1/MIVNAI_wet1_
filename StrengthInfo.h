
#ifndef MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H
#define MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H


class StrengthInfo {
private:
    int m_strength;
    char m_subTree;
public:
    StrengthInfo(int strength);

    void setTree(char subTree);

    void setStrengthFromInfo(int strength);

    int getStrengthFromInfo();
};


#endif //MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H