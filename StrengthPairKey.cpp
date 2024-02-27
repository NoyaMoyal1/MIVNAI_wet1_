
#include "StrengthPairKey.h"

bool operator<(const StrengthPairKey& l, const StrengthPairKey& r){
    if (l.nodeStrength < r.nodeStrength){
        return true;
    }
    if (l.nodeStrength > r.nodeStrength){
        return false;
    }
    if (l.nodeStrength == r.nodeStrength){
        if (l.nodeID < r.nodeID){
            return true;
        }
        if (l.nodeID > r.nodeID){
            return false;
        }
    }
    return false;
}

bool operator>(const StrengthPairKey& l, const StrengthPairKey& r){
    return r<l;
}

bool operator==(const StrengthPairKey& l, const StrengthPairKey& r){
    if ((l.nodeStrength == r.nodeStrength) && (l.nodeID == r.nodeID)){
        return true;
    }
    return false;
}

StrengthPairKey& StrengthPairKey::operator=(const StrengthPairKey& newSpk){
    if(this == &newSpk){
        return *this;
    }
    nodeStrength = newSpk.nodeStrength;
    nodeID = newSpk.nodeID;
    return *this;

}