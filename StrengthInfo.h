//
// Created by Sapir on 21/02/2024.
//

#ifndef TRY2_COPY_STRENGTHINFO_H
#define TRY2_COPY_STRENGTHINFO_H

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


#endif //TRY2_COPY_STRENGTHINFO_H
