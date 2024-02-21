#include "StrengthInfo.h"


void StrengthInfo::setTree(char subTree){
    m_subTree=subTree;
}
void StrengthInfo::setStrength(int strength){
    m_strength=strength;
}
int StrengthInfo::getStrength(){
    return m_strength;
}