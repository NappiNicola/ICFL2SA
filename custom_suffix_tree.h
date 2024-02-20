#ifndef CUSTOM_PREFIX_TREE_H_INCLUDED
#define CUSTOM_PREFIX_TREE_H_INCLUDED

#include <string>
#include <vector>
#include "generic_vector.h"

using namespace std;

struct nodes_vector;

typedef struct suffix_tree_node{
    //Qui viene salvato il prefisso presente in questo nodo dell'albero
    const char* suffix;

    //Padre del nodo
    suffix_tree_node* father;

    //Array di indici nei quali è presente il prefisso di cui sopra
    int_vector* array_of_indexes;

    //Figli del nodo
    nodes_vector* sons;

    //Una catena per ogni sotto albero, è importante solo quella del figlio del primo nodo
    //group_chains
    array_of_int_vector* chains_of_suffixes;

    //Chain of suffixes dal figlio di root al nodo
    int_vector* common_chain_of_suffiexes;

    //bit_vector del nodo
    bit_vector* bit_vec;

}suffix_tree_node;

suffix_tree_node* build_suffix_tree_node(suffix_tree_node* father,const char* suffix);
suffix_tree_node* add_suffix_in_tree(suffix_tree_node* root,const char* suffix,int indice);
int16_t find_index_of_child_a_is_prefix_of_b(suffix_tree_node* node, const char* suffix);
void stampa_suffix_tree(suffix_tree_node* root);

typedef struct nodes_vector
    {
        suffix_tree_node** data;
        size_t size;
        size_t used;

    }nodes_vector;

nodes_vector* init_nodes_vector(size_t size);
bool add_in_nodes_vector(nodes_vector* x,suffix_tree_node* element);
bool init_chains_of_prefixes(suffix_tree_node* root,int size_of_the_word);
int LCP(char* w, int index1,int index2);
int LCP_with_given_strings(const char* x,const char* y);

#endif