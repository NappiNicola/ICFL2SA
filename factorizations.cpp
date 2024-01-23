#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct pre_pair {
  string first;
  string second;
} ;

struct bre_quad {
  string first;
  string second;
  string third;
  int quarter;
};

pre_pair find_pre(string* word) {

    pre_pair my_pre_pair;

    int word_length = (*word).length();

    if (word_length == 1){


        my_pre_pair.first = (*word) + char(200);
        my_pre_pair.second = "";

    } else {

        int i = 0, j = 1;

        while ((j < word_length) & ((*word)[j] <= (*word)[i])){
            if ((*word)[j] < (*word)[i]){
                i = 0;
            } else {
                i = i + 1;
            }

            j = j + 1;

        }

        if (j == word_length){

            my_pre_pair.first = (*word) + char(200);
            my_pre_pair.second = "";

        } else {

            my_pre_pair.first = (*word).substr(0,j + 1);
            my_pre_pair.second = (*word).substr(j + 1,word_length);
        }
    }

    return my_pre_pair;
}

void border(string p, int **pi){
    int l = p.length();
    *pi = (int *) malloc(sizeof(int) * l);
    int k = 0;
    int i, j = 1;

    *(pi[0]) = 0;

    for (i = 1; i < l; i++) {
        while ((k > 0) && (p[k] != p[i])) {
        	k = (*pi)[k-1];
        }

        if (p[k] == p[i]) {
            k++;
        }
        (*pi)[j] = k;
        j++;
    }

}


bre_quad find_bre(pre_pair my_pre_pair) {

    bre_quad my_bre_quad;

    string w = my_pre_pair.first, v = my_pre_pair.second;

    if ((v == "") & (w.find(char(200))!=string::npos)){

        my_bre_quad.first = w;
        my_bre_quad.second = "";
        my_bre_quad.third = "";
        my_bre_quad.quarter = 0;

    } else{
        int n = w.length() - 1;

        int *f = NULL;
        border(w.substr(0,n), &f);

        int i = n;
        int last = f[i-1];

        while (i > 0) {
            if ((unsigned char) w[f[i-1]] < (unsigned char) w[n])
                last = f[i-1];
            i = f[i-1];
        }

        my_bre_quad.first = w.substr(0,n - last);
        my_bre_quad.second = w.substr(n - last,n - last + 1);
        my_bre_quad.third = v;
        my_bre_quad.quarter = last;

    }

    return my_bre_quad;

}

void compute_icfl_recursive(string* word, vector<bre_quad>& br_list, vector<int>& icfl_list_len, vector<int>& icfl_list_index, int& word_sx_bound) {

    //cout<<"###################### compute_icfl_recursive"<<endl;

    pre_pair my_pre_pair = find_pre(word);

    //cout << "my_pre_pair.first: " << my_pre_pair.first << endl;
    //cout << "my_pre_pair.second: " << my_pre_pair.second<< endl;


    bre_quad current_bre_quad = find_bre(my_pre_pair);

    br_list.push_back(current_bre_quad);

    if ((current_bre_quad.second == "") & (current_bre_quad.first.find(char(200))!=string::npos)){
        string w = current_bre_quad.first;

        icfl_list_len.insert(icfl_list_len.begin(), w.length()-1);
        icfl_list_index.insert(icfl_list_index.begin(), word_sx_bound - w.length() + 1);

        word_sx_bound = word_sx_bound - w.length() + 1;

        return;

    } else {

        string s = current_bre_quad.second + current_bre_quad.third;
        compute_icfl_recursive(&s, br_list, icfl_list_len, icfl_list_index, word_sx_bound);

        if (icfl_list_len.at(0) > current_bre_quad.quarter) {

            int l = word_sx_bound - current_bre_quad.first.length();

            icfl_list_len.insert(icfl_list_len.begin(), current_bre_quad.first.length());
            icfl_list_index.insert(icfl_list_index.begin(), word_sx_bound - current_bre_quad.first.length());

            word_sx_bound = word_sx_bound - current_bre_quad.first.length();

        } else {

            icfl_list_len.at(0) = current_bre_quad.first.length() + icfl_list_len.at(0);
            icfl_list_index.at(0) = icfl_list_index.at(0) - current_bre_quad.first.length();

        }
        return;

    }

}

//vector<string> ICFL_recursive(string* word, int word_sx_bound) {
vector<int> ICFL_recursive(string* word, int word_sx_bound) {

    //cout<<"###################### ICFL_recursive"<<endl;

    vector<bre_quad> br_list;
    vector<int> icfl_list_len;
    vector<int> icfl_list_index;
    int max_fact_length = 0;

    compute_icfl_recursive(word, br_list, icfl_list_len, icfl_list_index, word_sx_bound);

    cout << endl;

    /*
    cout << "icfl index: " << endl;
    for(int i = 0; i < icfl_list_index.size(); i++) {
        cout << icfl_list_index.at(i) << " ";
    }
    cout << endl;
    */

    return icfl_list_index;
}


/*
int main(int argc, char** argv) {

    string word = "aaabcaabcadcaabca";
    vector<int> icfl_list = ICFL_recursive(&word, word.length());

    return 0;

}
*/
