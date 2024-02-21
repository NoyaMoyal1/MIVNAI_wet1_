
#ifndef MIVNAI_WET1_STRENGTHPAIRKEY_H
#define MIVNAI_WET1_STRENGTHPAIRKEY_H
/////// fix define based on new repo

class StrengthPairKey {
private:
    int nodeStrength;
    int nodeID;

public:
    StrengthPairKey (int nodeStrength, int nodeID): nodeStrength(nodeStrength), nodeID(nodeID){}
    virtual ~StrengthPairKey() = default;

    StrengthPairKey& operator=(const StrengthPairKey& newSpk);
    friend bool operator<(const StrengthPairKey& l, const StrengthPairKey& r);
    friend bool operator>(const StrengthPairKey& l, const StrengthPairKey& r);
    friend bool operator==(const StrengthPairKey& l, const StrengthPairKey& r);


    // WE DON'T WANT TO ADD SETTERS BECAUSE IF WE CHANGE STRENGTH WE NEED TO DELETE AND INSERT TO KEEP TREE GOOD

};

#endif //MIVNAI_WET1_STRENGTHPAIRKEY_H

