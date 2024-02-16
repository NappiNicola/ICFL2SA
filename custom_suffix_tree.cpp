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

    x->common_chain_of_suffiexes = init_int_vector(0);
    
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

    /*
    Es. 
    Suffisso da inserire: abba
    Nuffisso presente nel nodo: ab
    */
    int16_t index_of_child_with_the_same_suffix = find_index_of_child_a_is_prefix_of_b(root,suffix);

    //Il prefisso non è in nessuno dei figli quindi prima creamo un figlio, lo aggiungiamo ai figli di root e gli inseriamo l'indice

    if(index_of_child_with_the_same_suffix == -1){
        //Creo un nuovo figlio del nodo root
        suffix_tree_node* x=build_suffix_tree_node(root,suffix);
        add_in_int_vector(x->array_of_indexes,indice);
        add_in_nodes_vector(root->sons,x);
        x->father=root;
        return true;
    }

    // Il prefisso è contenuto in uno dei dei figli di root, ricorsivamente chiamiamo la funzione su tale figlio

    return add_suffix_in_tree(root->sons->data[index_of_child_with_the_same_suffix],suffix,indice);

}

/*
Funzione che cerca il prefisso della stringa suffix passata in input tra i figli del nodo node passata input
Restituisce -1 se non è stato trovato.
IN: Nodo, Prefix
OUT: indice del figlio che ha lo stesso prefisso di Prefix 
*/

int16_t find_index_of_child_a_is_prefix_of_b(suffix_tree_node* node,const char* suffix){
    for(int16_t i=0;i<node->sons->size;i++){

            //SE E SOLO SE IL SUFFISSO È MAGGIORE O UGUALE AL SUFFISSO NEL FIGLIO DEL NODO
            //Questo perché se il figlio del nodo avesse una cardinalità maggiore, sicuramente non sarà prefisso.
            /*
            if(strlen(suffix) >= strlen(node->sons->data[i]->suffix)){
                if (std::string(suffix).compare(0,strlen(node->sons->data[i]->suffix),node->sons->data[i]->suffix) == 0){
                    return i;
                }
            }
            */
           //cout<<suffix<<endl<<node->sons->data[i]->suffix<<endl;
            //cout<<LCP_with_given_strings(suffix,node->sons->data[i]->suffix)<<endl<<strlen(suffix)<<endl;
            if(LCP_with_given_strings(suffix,node->sons->data[i]->suffix) == strlen(node->sons->data[i]->suffix)){
                     //cout<<suffix<<endl<<node->sons->data[i]->suffix<<endl;
                     //cout<<LCP_with_given_strings(suffix,node->sons->data[i]->suffix)<<endl<<strlen(suffix)<<endl;
                return i;
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

bool init_chains_of_prefixes(suffix_tree_node* root,int size_of_the_word){

    root->chains_of_suffixes = init_array_of_int_vector(size_of_the_word);

    //Itero ricorsivamente
    if(root->sons->used==0 && root->father->father!=NULL){
        add_in_array_of_int_vector(root->chains_of_suffixes,duplicate_int_vector(root->array_of_indexes));
        //cout<<root->suffix<<endl;
        //print_array_of_vector(root->chains_of_suffixes);
        return 1;
    }

    for(int i=0;i<root->sons->used;i++){
        init_chains_of_prefixes(root->sons->data[i],size_of_the_word);
    }

    return 1;

}

int LCP(char* w, int index1,int index2){
    int i=0;
    while (w[index1+i]==w[index2+i]){
        i++;
    }
    return i;
}
int LCP_with_given_strings(const char* x,const char* y){
    int i=0;
    int max_len=strlen(x);
    while (x[i]==y[i] && i<max_len){
        i++;
    }
    return i;
}