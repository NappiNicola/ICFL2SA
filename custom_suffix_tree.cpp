#include <iostream>
#include <vector>
#include <malloc.h>
#include <string.h>
#include "custom_suffix_tree.h"
using namespace std;

nodes_vector* init_nodes_vector(size_t size){
    nodes_vector* x= (nodes_vector*)malloc(sizeof(nodes_vector));
    x->size=size;
    x->data=(suffix_tree_node**)malloc(sizeof(suffix_tree_node*)*size);
    x->used=0;

    return x;
}

bool add_in_nodes_vector(nodes_vector* x,suffix_tree_node* element){
    if (x->size==x->used){
        x->size += 1;
        x->data = (suffix_tree_node**)realloc(x->data,sizeof(suffix_tree_node*)*x->size);
    }
    x->data[x->used++]=element;

    return 1;
}

//Costruttore del nodo prefix_tree_node

suffix_tree_node* build_suffix_tree_node(suffix_tree_node* father,const char* suffix){
    suffix_tree_node* x= (suffix_tree_node*)malloc(sizeof(suffix_tree_node));

    x->father=father;
    x->suffix=suffix;

    x->array_of_indexes = init_int_vector(0);
    x->sons=init_nodes_vector(0);
    
    return x;
}

/*
La funzione aggiunge nel sottoalbero dettato da root il prefisso prefix.
Se viene trovato gli viene aggiunto l'indice alla lista degli indici.
Se non viene trovato viene creato nel punto opportuno (una foglia) e gli viene aggiunto l'indice alla lista.
IN: Root,Prefix,Indice
OUT: Bool (True se l'inserimento è andato a buon fine)
*/

bool add_suffix_in_tree(suffix_tree_node* root,const char* suffix,int indice){

    //Controlliamo se il suffisso che vogliamo inserire è contenuto nel nodo in cui ci troviamo

    if(strcmp(root->suffix,suffix)==0){
        return add_in_int_vector(root->array_of_indexes,indice);
    }

    int16_t index_of_child_with_the_same_prefix = find_index_of_child_with_the_same_suffix(root,suffix);

    //Il prefisso non è in nessuno dei figli quindi prima creamo un figlio, lo aggiungiamo ai figli di root e gli inseriamo l'indice

    if(index_of_child_with_the_same_prefix == -1){
        suffix_tree_node* x=build_suffix_tree_node(root,suffix);
        add_in_int_vector(x->array_of_indexes,indice);
        add_in_nodes_vector(root->sons,x);

        return true;
    }

    // Il prefisso è contenuto in uno dei dei figli di root, ricorsivamente chiamiamo la funzione su tale figlio

    return add_suffix_in_tree(root->sons->data[index_of_child_with_the_same_prefix],suffix,indice);

}

/*
Funzione che cerca il prefisso della stringa suffix passata in input tra i figli del nodo node passata input
Restituisce -1 se non è stato trovato.
IN: Nodo, Prefix
OUT: indice del figlio che ha lo stesso prefisso di Prefix 
*/

int16_t find_index_of_child_with_the_same_suffix(suffix_tree_node* node,const char* suffix){
    for(int16_t i=0;i<node->sons->size;i++){

            //SE E SOLO SE IL SUFFISSO È MAGGIORE O UGUALE AL SUFFISSO NEL FIGLIO DEL NODO
            //Questo perché se il figlio del nodo avesse una cardinalità maggiore, sicuramente non sarà prefisso.
            if(strlen(suffix) >= strlen(node->sons->data[i]->suffix)){
                if (std::string(suffix).compare(0,strlen(node->sons->data[i]->suffix),node->sons->data[i]->suffix) == 0){
                    return i;
                }
            }
    }
    return -1;
}


void stampa_suffix_tree(suffix_tree_node* root){
    if (root->sons->size==0){
        cout<<"("<<root->suffix;
        cout<<"[";
        for(size_t j = 0; j<root->array_of_indexes->size;j++){
            cout<<root->array_of_indexes->data[j]<<",";
        }
        cout<<"])";
        return;
    }
    cout<<root->suffix<<"(";
    for(size_t i = 0; i<root->sons->used;i++){
        stampa_suffix_tree(root->sons->data[i]);
    }
    cout<<"[";
        for(size_t j = 0; j<root->array_of_indexes->size;j++){
            cout<<root->array_of_indexes->data[j]<<",";
        }
    cout<<"])";

    return;
}