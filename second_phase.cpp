#include <iostream>
#include "generic_vector.h"
#include "custom_suffix_tree.h"
#include <string.h>
#include <vector>
#include "second_phase.h"
#include "merge.h"
#include "utils.h"

using namespace std;

array_of_int_vector* get_chains(suffix_tree_node* root,const char* S, vector<int> icfl_list){

    if(root->sons->used==0){
        array_of_int_vector* chain = init_array_of_int_vector(strlen(S));
        get_ranks_from_leaf_to_root(root,S,chain,icfl_list);
        //print_array_of_vector(chain);
        compute_chain(chain,S,icfl_list);
        return root->chains_of_suffixes;
    }
    //Arriviamo alle foglie
    for(int i=0;i<root->sons->used;i++){
        get_chains(root->sons->data[i],S,icfl_list);
    }

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

    //Viene effettuato in_prefix_merge della catena passata in inuput 
    //Il primo puntatore è il puntatore della catena in root
    //

    int_vector* root_sequence=sequence->data[0];
    for(int i=1;i<sequence->used;i++){
        sequence->data[0]=in_prefix_merge(S,icfl_list,sequence->data[0],sequence->data[i]);
    }
    (*root_sequence).data=sequence->data[0]->data;
    (*root_sequence).size=sequence->data[0]->size;
    (*root_sequence).used=sequence->data[0]->used;

    //print_array_of_vector(sequence);
}


void get_chains_2(const char* S, vector<int> icfl_list,suffix_tree_node* root,int_vector* prev_common_chain_of_suffiexes){

    root->common_chain_of_suffiexes = in_prefix_merge(S,icfl_list,prev_common_chain_of_suffiexes,root->array_of_indexes);

    if(root->sons->used==0){
        add_chain_to_root(root,root->common_chain_of_suffiexes);
    }

    else{
        for(int i=0;i<root->sons->used;i++){
            get_chains_2(S, icfl_list,root->sons->data[i],root->common_chain_of_suffiexes);
        }
    }



}

void add_chain_to_root(suffix_tree_node* root,int_vector* common_chain_of_suffiexes){
    if(root->father->father==NULL){
        add_in_array_of_int_vector(root->chains_of_suffixes,common_chain_of_suffiexes);
    }
    else{
        add_chain_to_root(root->father,common_chain_of_suffiexes);
    }
}


void sort_sons_of_all_nodes(suffix_tree_node* root){
    quicksort_of_nodes(root->sons,0,root->sons->used-1);

    for(int i=0;i<root->sons->used;i++){
        sort_sons_of_all_nodes(root->sons->data[i]);
    }
}

int_vector* join_int_vector_with_bit_vector(int_vector* father_chain,int_vector* son_chain,bit_vector* bit_vec){
    //i=indice array dei suffissi del nodo padre
    //j=indice array dei suffissi del nodo figlio
    //z=indice bit vector del nodo figlio
    int i,j;
    i=j=0;
    int_vector* result=init_int_vector(0);
    for(int z=0;z<bit_vec->used;z++){
        if(bit_vec->data[z]){
            add_in_int_vector(result,father_chain->data[i]);
            i++;
        }
        else{
           add_in_int_vector(result,son_chain->data[j]);
            j++; 
        }
    }
    return result;
}

int_vector* get_chain_from_bit_vector(suffix_tree_node* root){
    if(root->father==NULL){
        return root->array_of_indexes;
    }
    int_vector* father_chain = get_chain_from_bit_vector(root->father);
    return join_int_vector_with_bit_vector(father_chain,root->array_of_indexes,root->bit_vec);
}

void create_bit_vector(const char* S,vector<int> icfl_list, suffix_tree_node* root){
    int_vector* father_chain = get_chain_from_bit_vector(root->father);
    root->bit_vec=in_prefix_merge_bit_vector(S,icfl_list,father_chain,root->array_of_indexes);
}

void get_chains_3(suffix_tree_node* root,suffix_tree_node* node){
    if(node->sons->used==0){
        add_in_array_of_int_vector(root->chains_of_suffixes,get_chain_from_bit_vector(node));
    }
    for(int i=0;i<node->sons->used;i++){
        get_chains_3(root,node->sons->data[i]);
    }
}