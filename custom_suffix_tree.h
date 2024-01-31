#ifndef CUSTOM_PREFIX_TREE_H_INCLUDED
#define CUSTOM_PREFIX_TREE_H_INCLUDED

#include <string>
#include <vector>
#include "generic_vector.h"

using namespace std;

struct nodes_vector;

typedef struct suffix_tree_node{
    //Qui viene salvato il prefisso presente in questo nodo dell'albero
    string* suffix;

    //Padre del nodo
    suffix_tree_node* father;

    //Array di indici nei quali è presente il prefisso di cui sopra
    int_vector* array_of_indexes;

    //Figli del nodo
    nodes_vector* sons;

}suffix_tree_node;

suffix_tree_node* build_suffix_tree_node(suffix_tree_node* father,string* prefix);
bool add_suffix_in_tree(suffix_tree_node* root,string* prefix,int indice);
int16_t find_index_of_child_with_the_same_suffix(suffix_tree_node* node,string* prefix);

typedef struct nodes_vector
    {
        suffix_tree_node** data;
        size_t size;
        size_t used;

    }nodes_vector;

nodes_vector* init_nodes_vector(size_t size);
bool add_in_nodes_vector(nodes_vector* x,suffix_tree_node* element);


#endif