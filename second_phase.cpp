#include <iostream>
#include "generic_vector.h"
#include "custom_suffix_tree.h"
#include <string.h>
#include <vector>
#include "second_phase.h"

using namespace std;


int get_factor(vector<int> icfl_list,int index){

    if(index >= icfl_list[icfl_list.size()-1]){
        return icfl_list.size()-1;
    }

    for(int i=1;i<icfl_list.size();i++){
        if(index >= icfl_list.at(i-1) && index <= icfl_list.at(i)){
            return index;
        }
    }

    return 0;

}

int_vector* in_prefix_merge(const char* S, vector<int> icfl_list, int_vector* e, int_vector* g){

    int_vector* result = init_int_vector(strlen(S));

    int i=0;
    int j=0;

    print_int_vector(e);
    cout<<"+";
    print_int_vector(g);

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
                    S[element_of_g + LCP((char*)S,element_of_e,element_of_g) +1] 
                    <
                    S[element_of_e + LCP((char*)S,element_of_e,element_of_g) +1]){
                    
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

                    if(S[element_of_g + LCP((char*)S,element_of_e,element_of_g) +1] < S[element_of_e + LCP((char*)S,element_of_e,element_of_g) +1]){
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
    cout<<"=";
    print_int_vector(result);
    cout<<endl;

    return result;
}

array_of_int_vector* get_chains(suffix_tree_node* root,const char* S, vector<int> icfl_list){

    if(root->sons->used==0){
        array_of_int_vector* chain = init_array_of_int_vector(strlen(S));
        get_ranks_from_leaf_to_root(root,S,chain,icfl_list);
        print_array_of_vector(chain);
        compute_chain(chain,S,icfl_list);
        return root->chains_of_suffixes;
    }
    //Arriviamo alle foglie
    for(int i=0;i<root->sons->used;i++){
        get_chains(root->sons->data[i],S,icfl_list);
    }

    /*

    //per ogni figlio del nodo
    for(int i=0;i<root->sons->used;i++){
        //per ogni catena del figlio
        array_of_int_vector* temp = get_chains(root->sons->data[i],S,icfl_list);
        for(int j=0;j<temp->used;j++){
            add_in_array_of_int_vector(
                root->chains_of_suffixes,
                in_prefix_merge(S,icfl_list,root->array_of_indexes,temp->data[j],strlen(root->suffix))
            );
        }
    }

    */

    return root->chains_of_suffixes;

}

array_of_int_vector* get_ranks_from_leaf_to_root(suffix_tree_node* root,const char* S, array_of_int_vector* sequence,vector<int> icfl_list){

    if(root->father->father==NULL){
        add_in_array_of_int_vector(root->chains_of_suffixes,duplicate_int_vector(root->array_of_indexes));
        add_in_array_of_int_vector(sequence,root->chains_of_suffixes->data[root->chains_of_suffixes->used-1]);
        return root->chains_of_suffixes;
    }

    //Itero ricorsivamente fino a prende l'ultimo vettore instanziato nella chains_of_suffixes della root
    get_ranks_from_leaf_to_root(root->father,S,sequence,icfl_list);
    add_in_array_of_int_vector(sequence,root->array_of_indexes);

    return root->chains_of_suffixes;

}

void compute_chain(array_of_int_vector* sequence,const char* S,vector<int> icfl_list){
    int_vector* root_sequence=sequence->data[0];
    for(int i=1;i<sequence->used;i++){
        sequence->data[0]=in_prefix_merge(S,icfl_list,sequence->data[0],sequence->data[i]);
    }
    (*root_sequence).data=sequence->data[0]->data;
    (*root_sequence).size=sequence->data[0]->size;
    (*root_sequence).used=sequence->data[0]->used;

    //print_array_of_vector(sequence);
}




