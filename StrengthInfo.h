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
    StrengthInfo(int strength);
    void setTree(char subTree);
    void setStrengthFromInfo(int strength);
    int getStrengthFromInfo();
};


#endif //TRY2_COPY_STRENGTHINFO_H
