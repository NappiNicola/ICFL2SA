#include <iostream>
#include <vector>
#include <malloc.h>
#include <string.h>
#include "custom_prefix_tree.h"
using namespace std;

//Costruttore del nodo prefix_tree_node

prefix_tree_node* build_prefix_tree_node(prefix_tree_node* father,string* prefix){
    prefix_tree_node* x= (prefix_tree_node*)malloc(sizeof(prefix_tree_node));

    x->father=father;
    x->prefix=prefix;
    
    return x;
}

/*
La funzione aggiunge nel sottoalbero dettato da root il prefisso prefix.
Se viene trovato gli viene aggiunto l'indice alla lista degli indici.
Se non viene trovato viene creato nel punto opportuno (una foglia) e gli viene aggiunto l'indice alla lista.
IN: Root,Prefix,Indice
OUT: Bool (True se l'inserimento è andato a buon fine)
*/

bool add_prefix_in_tree(prefix_tree_node* root,string* prefix,int indice){

    //Controlliamo se il prefisso che vogliamo inserire è contenuto nel nodo in cui ci troviamo

    if(strcmp(root->prefix->c_str(),prefix->c_str())==0){
        root->array_of_indexes.insert(root->array_of_indexes.begin() + root->array_of_indexes.size(),indice);
        return true;
    }

    int16_t index_of_child_with_the_same_prefix = find_index_of_child_with_the_same_prefix(root,prefix);

    //Il prefisso non è in nessuno dei figli quindi prima creamo un figlio, lo aggiungiamo ai figli di root e gli inseriamo l'indice

    if(index_of_child_with_the_same_prefix == -1){
        prefix_tree_node* x=build_prefix_tree_node(root,prefix);
        x->array_of_indexes.insert(root->array_of_indexes.begin() + root->array_of_indexes.size(),indice);
        root->sons.insert(root->sons.begin() + root->sons.size(),x);

        return true;
    }

    // Il prefisso è contenuto in uno dei dei figli di root, ricorsivamente chiamiamo la funzione su tale figlio

    return add_prefix_in_tree(root->sons[index_of_child_with_the_same_prefix],prefix,indice);

}

/*
Funzione che cerca il prefisso della stringa prefix passata in input tra i figli del nodo node passata input
Restituisce -1 se non è stato trovato.
IN: Nodo, Prefix
OUT: indice del figlio che ha lo stesso prefisso di Prefix 
*/

int16_t find_index_of_child_with_the_same_prefix(prefix_tree_node* node,string* prefix){
    for(int16_t i=0;i<node->sons.size();i++){

            //SE E SOLO SE IL PREFISSO È MAGGIORE O UGUALE AL PREFISSO NEL FIGLIO DEL NODO
            //Questo perché se il figlio del nodo avesse una cardinalità maggiore, sicuramente non sarà prefisso.
            if(prefix->length() >= node->sons[i]->prefix->length()){
                if (prefix->compare(0,node->sons[i]->prefix->length(),*node->sons[i]->prefix) == 0){
                    return i;
                }
            }
    }
    return -1;
}
