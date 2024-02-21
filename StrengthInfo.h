
#ifndef MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H
#define MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H


class StrengthInfo {
private:
    int m_strength;
    char m_subTree;
public:
    StrengthInfo(int strength) : m_strength(strength) , m_subTree('V'){}

    void setTree(char subTree);

    void setStrength(int strength);

    int getStrength();

};

void StrengthInfo::setTree(char subTree){
    m_subTree=subTree;
}
void StrengthInfo::setStrength(int strength){
    m_strength=strength;
}
int StrengthInfo::getStrength(){
    return m_strength;
}
#endif //MIVANI1_WET1_UPDATED_GIT_STRENGTHINFO_H
