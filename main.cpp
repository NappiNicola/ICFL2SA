#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "factorizations.h"
#include "utils.h"
#include "custom_suffix_tree.h"
#include "first_phase.h"
#include "second_phase.h"
#include "third_phase.h"
#include "check.h"
#include <string.h>

using namespace std;

// STEP 1: COSTRUZIONE PREFIX TREE (in-prefix merge)


// sorting_suffixes_via_icfl_trie
vector<int> sorting_suffixes_via_icfl_trie(string* word) {
    //cout<<"###################### sorting_suffixes_via_icfl_trie"<<endl;

    int lenght_of_word=strlen(word->c_str());

    vector<int> icfl_list = ICFL_recursive(word, (*word).length());

    printVector(icfl_list, "Stampa ICFL");

    /*
    for(int i=0;i<icfl_list.size()-1;i++){
        for (int j=icfl_list[i];j<icfl_list[i+1];j++){
            cout<<word->at(j);
        }
        cout<<", ";

    }
    */
    

    /*
    for(int i=icfl_list[icfl_list.size()-1];i<word->length();i++){
        cout<<word->at(i);
    }
    */

    

    cout<<endl;

    //Le parole di Lyndon ne possono essere al più una per ogni lettera della stringa in input
    char** list_of_lyndon_words= get_lyndon_words(word,icfl_list);

    /*
    for(int i=0;i<icfl_list.size();i++){
        cout<<list_of_lyndon_words[i]<<" ";
    }
    cout<<endl;
    */

    

    int max_size=0;
    for(int i=0;i<icfl_list.size();i++){
        if (strlen(list_of_lyndon_words[i])>max_size){
            max_size=strlen(list_of_lyndon_words[i]);
        } 
    }

    clock_t tStart = clock();
    //cout<<"\nCREAZIONE ALBERO\n";
    //La root è la stringa vuota
    suffix_tree_node* root = creazione_albero(list_of_lyndon_words,icfl_list,word->c_str(),lenght_of_word,max_size);
    
    printf("Creazione albero, Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    //cout<<"\nALBERO OTTENUTO\n";
    //stampa_suffix_tree(root);

    cout<<endl;

    tStart = clock();
    sort_sons_of_all_nodes(root);
    printf("sort_sons_of_all_nodes, Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    
    //tStart = clock();
    //init_chains_of_prefixes(root,word->length());
    //printf("init_chains_of_prefixes, Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    
    /*
    array_of_int_vector* array_of_chains = init_array_of_int_vector(strlen(word->c_str()));

    get_chains(array_of_chains,root,word->c_str(),icfl_list);
    cout<<"a"<<endl;
    print_array_of_vector(array_of_chains);
    */

//LA FUNZIONE GET_CHAINS PERMETTE DI COMPUTARE LE GROUP_CHAINS E SALVARLE NEL NODO FIGLIO DI ROOT,
//QUESTA IMPLEMENTAZIONE PERÒ NON FA CONTO DELLA MEMORIA USATA IN QUANTO PER OGNI NODO
//VIENE USATO SOLO L'ARRAY DI INDICI OTTENUTO DURANTE LA CRAZIONE DELL'ALBERO
    //tStart = clock();
    //get_chains(root,word->c_str(),icfl_list);
    //printf("get_chains, Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    //get_chains(root,word->c_str(),icfl_list);

//LA FUNZIONE GET_CHAINS_2 PERMETTE DI COMPUTARE ANCHE LE COMMON_CHAINS, SALVANDO QUINDI I RISULTATI
//PARZIALI E FARLO DIVENTARE UN PROBLEMA DI PROGRAMMAZIONE DINAMICA.
//QUESTO OVVIAMENTE A DISCAPITO DELLA MEMORIA USATA
    //tStart = clock();
    //get_chains_2(word->c_str(),icfl_list,root,root->common_chain_of_suffiexes);
    //printf("get_chains_2, Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    /*
    for(int i=0;i<root->sons->used;i++){
        print_array_of_vector(root->sons->data[i]->chains_of_suffixes);
    }
    */

    tStart = clock();
    for(int i=0;i<root->sons->used;i++){
        get_chains_3(root->sons->data[i],root->sons->data[i]);
    }
    printf("get_chains, Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


   
   tStart = clock();

    array_of_int_vector* group_ranking = init_array_of_int_vector(0);
    for(int i=0;i<root->sons->used;i++){
        add_in_array_of_int_vector(group_ranking,get_common_prefix_merge(root->sons->data[i]));
    }

    int_vector* SA = merge_array_of_vector(group_ranking);

    printf("common+concat, Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    print_int_vector(SA);

    if(check_suffix_array(word->c_str(),SA)) cout<<"Il SA è valido."<<endl;
    


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

char* experiment_given_word_by_input_file() {
    //cout<<"###################### experiment_given_word"<<endl;
    char * word = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* fp = fopen("./input_file.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    getline(&word, &len, fp);

    cout<<endl<<"Stringa: "<< word;
    cout << endl;

    std::string x(word);

    vector<int> suffix_array = sorting_suffixes_via_icfl_trie(&x);

    return word;
}

int main(int argc, char** argv) {

    //experiment_given_word();
    //experiment_generate_word();

    //experiment_given_word_by_cli(string(argv[1]));

    clock_t tStart = clock();

    experiment_given_word_by_input_file();

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    


    return 0;

}

