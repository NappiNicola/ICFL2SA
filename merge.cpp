#include "merge.h"

int get_factor(vector<int> icfl_list,int index){

    if(index >= icfl_list[icfl_list.size()-1]){
        return icfl_list.size()-1;
    }

    for(int i=0;i<icfl_list.size()-1;i++){
        if(index >= icfl_list.at(i) && index < icfl_list.at(i+1)){
            return index;
        }
    }

    return -1;

}

int_vector* in_prefix_merge(const char* S, vector<int> icfl_list, int_vector* e, int_vector* g){

    int_vector* result = init_int_vector(strlen(S));

    int i=0;
    int j=0;

    //cout<<" last:"<<icfl_list[icfl_list.size()-1]<<" ";

    while( i<e->used && j<g->used){

        int element_of_e=e->data[i];
        int element_of_g=g->data[j];

        //A

        if(element_of_e >= icfl_list[icfl_list.size()-1] && element_of_g >= icfl_list[icfl_list.size()-1]){
            add_in_int_vector(result,element_of_e);
            i++;
        }

        //B

        else if(get_factor(icfl_list,element_of_e)==get_factor(icfl_list,element_of_g)){
            add_in_int_vector(result,element_of_g);
            j++;
        }

        //C

        else{

            //1)

            if(element_of_e >= icfl_list[icfl_list.size()-1]){

                add_in_int_vector(result,element_of_e);
                i++;
            }

            //2)

            else if(element_of_g >= icfl_list[icfl_list.size()-1]){

                //cout<<"Secondo caso \n";

                //CONTROLLO LCP
                //LCP = Lunghezza dell suffisso del padre

                if(
                    S[element_of_g + LCP((char*)S,element_of_e,element_of_g)] 
                    <
                    S[element_of_e + LCP((char*)S,element_of_e,element_of_g)]){

                        //cout<<element_of_e<<endl<<element_of_g<<endl;
                        //cout<<S+element_of_e<<endl<<S+element_of_g<<endl<<LCP((char*)S,element_of_e,element_of_g)<<endl;
                    
                    
                        add_in_int_vector(result,element_of_g);
                        j++;
                }

                else{
                    add_in_int_vector(result,element_of_e);
                    i++;
                }
            }

            //3)

            else{

                if(element_of_e > element_of_g){
                    add_in_int_vector(result,element_of_g);
                    j++;
                }

                else{

                    if(S[element_of_g + LCP((char*)S,element_of_e,element_of_g)] < S[element_of_e + LCP((char*)S,element_of_e,element_of_g)]){
                        add_in_int_vector(result,element_of_g);
                        j++;
                    }

                    else{
                        add_in_int_vector(result,element_of_e);
                        i++;
                    }

                }

            }
        }

    }

    while(j<g->used){
        add_in_int_vector(result,g->data[j]);
        j++;
    }

    while(i<e->used){
        add_in_int_vector(result,e->data[i]);
        i++;
    }

    return result;
}

bit_vector* in_prefix_merge_bit_vector(const char* S, vector<int> icfl_list, int_vector* father, int_vector* child){

    //FATHER = 1
    //CHILD = 0

    bit_vector* result = init_bit_vector(strlen(S));

    int i=0;
    int j=0;

    //cout<<" last:"<<icfl_list[icfl_list.size()-1]<<" ";

    while( i<father->used && j<child->used){

        int element_of_e=father->data[i];
        int element_of_g=child->data[j];

        //A

        if(element_of_e >= icfl_list[icfl_list.size()-1] && element_of_g >= icfl_list[icfl_list.size()-1]){
            add_in_bit_vector(result,true);
            i++;
        }

        //B

        else if(get_factor(icfl_list,element_of_e)==get_factor(icfl_list,element_of_g)){
            add_in_bit_vector(result,false);
            j++;
        }

        //C

        else{

            //1)

            if(element_of_e >= icfl_list[icfl_list.size()-1]){

                add_in_bit_vector(result,true);
                i++;
            }

            //2)

            else if(element_of_g >= icfl_list[icfl_list.size()-1]){

                //cout<<"Secondo caso \n";

                //CONTROLLO LCP
                //LCP = Lunghezza dell suffisso del padre

                if(
                    S[element_of_g + LCP((char*)S,element_of_e,element_of_g)] 
                    <
                    S[element_of_e + LCP((char*)S,element_of_e,element_of_g)]){

                        //cout<<element_of_e<<endl<<element_of_g<<endl;
                        //cout<<S+element_of_e<<endl<<S+element_of_g<<endl<<LCP((char*)S,element_of_e,element_of_g)<<endl;
                    
                    
                        add_in_bit_vector(result,false);
                        j++;
                }

                else{
                    add_in_bit_vector(result,true);
                    i++;
                }
            }

            //3)

            else{

                if(element_of_e > element_of_g){
                    add_in_bit_vector(result,false);
                    j++;
                }

                else{

                    if(S[element_of_g + LCP((char*)S,element_of_e,element_of_g)] < S[element_of_e + LCP((char*)S,element_of_e,element_of_g)]){
                        add_in_bit_vector(result,false);
                        j++;
                    }

                    else{
                        add_in_bit_vector(result,true);
                        i++;
                    }

                }

            }
        }

    }

    while(j<child->used){
        add_in_bit_vector(result,false);
        j++;
    }

    while(i<father->used){
        add_in_bit_vector(result,true);
        i++;
    }

    return result;
}