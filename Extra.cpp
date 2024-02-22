#include "Extra.h"


template<typename D>
void merge(D** a, int na, D** b, int nb, D** c){
    int ia=0, ib=0, ic=0;
    while(ia < na && ib < nb){
        if(*(a+ia)<*(b+ib)){
            *(c+ic)=*(a+ia);
            ia++;
        }
        else{
            *(c+ic)=*(b+ib);
            ib++;
        }
        ic++;
    }
    for(;ia < na; ia++, ic++)
        *(c+ic)=*(a+ia);
    for(;ib < nb; ib++, ic++)
        *(c+ic)=*(b+ib);
}
