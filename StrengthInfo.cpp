#include "StrengthInfo.h"

StrengthInfo::StrengthInfo(int strength) : m_strength(strength) , m_subTree('V'){}


void StrengthInfo::setTree(char subTree){
    m_subTree=subTree;
}
void StrengthInfo::setStrength(int strength){
    m_strength=strength;
}
int StrengthInfo::getStrength(){
    return m_strength;
}