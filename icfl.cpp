#include "icfl.h"

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