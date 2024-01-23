#ifndef TRIE_NODE_UTILS_H_INCLUDED
#define TRIE_NODE_UTILS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct trie_node {

    // puntatore al nodo padre
    trie_node* parent;

    // suffix_length indica la lunghezza del suffisso rappresentato dal nodo
    int suffix_length;

    // ranking è il vettore di ranking associato al suffisso rappresentato dal nodo
    vector<int> ranking;

    // ranking è il vettore di ranking associato al suffisso rappresentato dal nodo
    vector<trie_node*> children;

    // puntatore alla parola originale
    string* word_pointer;

    // vettore di bool utilizzato per l'applicazione delle operazioni di merge
    vector<bool> bool_merge;

    // vettore di bool utilizzato per l'applicazione delle operazioni di merge
    vector<int> num_of_true_in_bool_merge;

    int ranking_index_0;

    int bool_index_1;

    // COstruttore
    trie_node(int s_length, string* original_word) {

        suffix_length = s_length;
        word_pointer = original_word;
        ranking_index_0 = 0;
        bool_index_1 = 0;

        parent = NULL;
        ranking = vector<int>(0);
        children = vector<trie_node*>(0);
        bool_merge= vector<bool>(0);
        num_of_true_in_bool_merge = vector<int>(0);

    }

};

void add(trie_node* root, int ranking_item_index, int ranking_item_length, vector<int>& mask_index);

vector<int> computeSuffixArray(trie_node* root);

int fact_of(int index_to_insert, vector<int>& mask_index);

int LCP_length(string* X, string* Y);

void inPrefixMerge(trie_node* root, int x_j, vector<int>& mask_index);

// Metodo per calcolare la common prefix merge a partire da un nodo
vector<int> commonPrefixMerge(trie_node* root);


#endif // TRIE_NODE_UTILS_H_INCLUDED
