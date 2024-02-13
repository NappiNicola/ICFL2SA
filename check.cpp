#include "generic_vector.h"
#include <string.h>
#include <iostream>

using namespace std;

bool check_suffix_array(const char* S,int_vector* SA){
    //controlla se i suffissi sono ordinati
    bool ord_bool = true;
    //controlla se sono presenti tutti i suffissi
    bool pres_bool = true;
    for(int i=0;i<strlen(S)-1;i++){
        if(strcmp(S+SA->data[i],S+SA->data[i+1])>0){
            ord_bool = false;
        }
    }
    if(!ord_bool) cout<<"\nNon tutti i suffissi sono ordinati. \n";
    for(int i=0;i<strlen(S)-1;i++){
        if(!element_in_int_vector(SA,i)){
            pres_bool = false;
        }
    }
    if(!pres_bool) cout<<"\nNon tutti gli indici sono presenti. \n";
    return ord_bool&&pres_bool;
}