#include <malloc.h>
#include "utils.h"
#include <string.h>

char** get_lyndon_words(string* word,vector<int> icfl_list);
suffix_tree_node* creazione_albero(char** list_of_lyndon_words,vector<int> icfl_list,const char* S,int lenght_of_word,int max_size);