#ifndef CUSTOM_PREFIX_TREE_H_INCLUDED
#define CUSTOM_PREFIX_TREE_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

typedef struct prefix_tree_node{
    //Qui viene salvato il prefisso presente in questo nodo dell'albero
    string* prefix;

    //Padre del nodo
    prefix_tree_node* father;

    //Array di indici nei quali è presente il prefisso di cui sopra
    vector<int> array_of_indexes;

    //Figli del nodo
    vector<prefix_tree_node*> sons;

}prefix_tree_node;

#endif