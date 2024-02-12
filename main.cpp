#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include "factorizations.h"
#include "trie_node_utils.h"
#include"utils.h"
#include "custom_suffix_tree.h"
#include "second_phase.h"
#include "third_phase.h"
#include <string.h>

using namespace std;

// STEP 1: COSTRUZIONE PREFIX TREE (in-prefix merge)
trie_node *run_word(vector<int> icfl_list_index, string *word, trie_node* root) {

    int word_len = (*word).length();
    int icfl_list_size = icfl_list_index.size();

    vector<int> icfl_list_support = vector<int>(0);
    vector<int> icfl_list_support_len = vector<int>(0);
    for(int i = 0; i < icfl_list_size; i++) {
        icfl_list_support.push_back(icfl_list_index[i]);

        if(i == icfl_list_size - 1) {
            icfl_list_support_len.push_back(word_len - icfl_list_index[i]);
        } else {
            icfl_list_support_len.push_back(icfl_list_index[i+1] - icfl_list_index[i]);
        }
    }

    // Sposta ultimo fattore in prima posizione
    icfl_list_support.insert(icfl_list_support.begin(), icfl_list_support[icfl_list_support.size()-1]);
    icfl_list_support_len.insert(icfl_list_support_len.begin(), icfl_list_support_len[icfl_list_support_len.size()-1]);
    icfl_list_support.pop_back();
    icfl_list_support_len.pop_back();

    int suffix_len = 1;
    int suffix_index = icfl_list_support.size() -1;

    // word_index � l'indice sulla parola rispetto al suffisso su cui stiamo lavorando
    int last_icfl_length = word_len - icfl_list_support[0];
    int word_index = ((word_len - last_icfl_length - suffix_len)+word_len)%word_len;

    int count_insertion = 0;
    string back_suffix = "";
    string suffix = "";
    int back_suffix_len = 0;

    while(true) {

        if(count_insertion == word_len) {
            break;
        }

        back_suffix = (*word).substr(icfl_list_support[suffix_index], icfl_list_support_len[suffix_index]);
        back_suffix_len = back_suffix.length();

        if(back_suffix_len >= suffix_len) {

            suffix = back_suffix.substr(back_suffix_len-suffix_len,suffix_len);
            //cout << word_index << endl;
            //cout << suffix << endl;

            add(root, word_index,suffix_len,icfl_list_index);
            count_insertion++;

        } else {

            icfl_list_support.erase(icfl_list_support.begin() + suffix_index);
            icfl_list_support_len.erase(icfl_list_support_len.begin() + suffix_index);

        }

        if(suffix_index > 0) {

            suffix_index--;

            word_index = (icfl_list_support[suffix_index] + icfl_list_support_len[suffix_index]- suffix_len + word_len)%word_len;

        } else {
            suffix_index = icfl_list_support.size() -1;
            suffix_len++;

            word_index = ((word_len - last_icfl_length - suffix_len) + word_len)%word_len;
        }

        continue;

    }

    return root;
}

// sorting_suffixes_via_icfl_trie
vector<int> sorting_suffixes_via_icfl_trie(string* word) {
    //cout<<"###################### sorting_suffixes_via_icfl_trie"<<endl;

    vector<int> icfl_list = ICFL_recursive(word, (*word).length());

    printVector(icfl_list, "Stampa ICFL");

    for(int i=0;i<icfl_list.size()-1;i++){
        for (int j=icfl_list[i];j<icfl_list[i+1];j++){
            cout<<word->at(j);
        }
        cout<<", ";

    }

    for(int i=icfl_list[icfl_list.size()-1];i<word->length();i++){
        cout<<word->at(i);
    }

    cout<<endl;

    //Le parole di Lyndon ne possono essere al più una per ogni lettera della stringa in input
    char** list_of_lyndon_words=(char**)malloc(sizeof(char*)*word->length());
    for(int i=0;i<icfl_list.size()-1;i++){
        const char* lyndon_word="\0";
        for (int j=icfl_list[i];j<icfl_list[i+1];j++){
            lyndon_word=append(lyndon_word,word->at(j));
        }
        list_of_lyndon_words[i]=strdup(lyndon_word);
    }
    //L'ultima parola di Lyndon
    const char* lyndon_word="\0";
    for(int i=icfl_list[icfl_list.size()-1];i<word->length();i++){
        lyndon_word=append(lyndon_word,word->at(i));
    }
    list_of_lyndon_words[icfl_list.size()-1]=strdup(lyndon_word);


    for(int i=0;i<icfl_list.size();i++){
        cout<<list_of_lyndon_words[i]<<" ";
    }
    cout<<endl;

    int max_size=0;
    for(int i=0;i<icfl_list.size();i++){
        if (strlen(list_of_lyndon_words[i])>max_size){
            max_size=strlen(list_of_lyndon_words[i]);
        } 
    }

    cout<<"\nCREAZIONE ALBERO\n";
    //La root è la stringa vuota
    suffix_tree_node* root = build_suffix_tree_node(NULL,"\0");
    for(int i=0;i<max_size;i++){
        //Viene elaborato prima l'ultima stringa
        const char* lyndon_word=list_of_lyndon_words[icfl_list.size()-1];
        if(i<strlen(lyndon_word)){
            //La stringa si legge da destra verso sinistra
            int starting_position= strlen(lyndon_word)-1-i;
            add_suffix_in_tree(root,lyndon_word+starting_position,icfl_list[icfl_list.size()-1]+starting_position);
        }
        for(int j=0;j<icfl_list.size()-1;j++){
            const char* lyndon_word=list_of_lyndon_words[j];
            if(i<strlen(lyndon_word)){
                //La stringa si legge da destra verso sinistra
                int starting_position= strlen(lyndon_word)-1-i;
                add_suffix_in_tree(root,lyndon_word+starting_position,icfl_list[j]+starting_position);
            }
        }
    }
    
    cout<<"\nALBERO OTTENUTO\n";
    stampa_suffix_tree(root);

    cout<<endl;

    init_chains_of_prefixes(root,word->length());
    
    /*
    array_of_int_vector* array_of_chains = init_array_of_int_vector(strlen(word->c_str()));

    get_chains(array_of_chains,root,word->c_str(),icfl_list);
    cout<<"a"<<endl;
    print_array_of_vector(array_of_chains);
    */

    get_chains(root,word->c_str(),icfl_list);

    /*
    for(int i=0;i<root->sons->used;i++){
        print_array_of_vector(root->sons->data[i]->chains_of_suffixes);
    }
    */
   
    array_of_int_vector* group_ranking = init_array_of_int_vector(0);
    for(int i=0;i<root->sons->used;i++){
        add_in_array_of_int_vector(group_ranking,get_common_prefix_merge(root->sons->data[i]));
    }

    print_int_vector(merge_array_of_vector(group_ranking));
    cout<<endl;


    return icfl_list;

}


// EXP 1: word given by user
void experiment_given_word() {
    //cout<<"###################### experiment_given_word"<<endl;

    string word;

    cout << "inserisci stringa: ";
    getline(cin, word);

    cout<<endl<<"Stringa: "<< word;
    cout << endl;

    vector<int> suffix_array = sorting_suffixes_via_icfl_trie(&word);

    return;
}

void experiment_given_word_by_cli(string word) {
    //cout<<"###################### experiment_given_word"<<endl;
    cout<<endl<<"Stringa: "<< word;
    cout << endl;

    vector<int> suffix_array = sorting_suffixes_via_icfl_trie(&word);

    return;
}

int main(int argc, char** argv) {

    //experiment_given_word();
    //experiment_generate_word();

    experiment_given_word_by_cli(string(argv[1]));


    return 0;

}

