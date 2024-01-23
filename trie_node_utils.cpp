#include <iostream>
#include <string>
#include <vector>

#include "trie_node_utils.h"

using namespace std;


// fact of
int fact_of(int index_to_insert, vector<int>& mask_index){

    int fact_index = mask_index.size() - 1;
    int mask_index_length = mask_index.size();

    for(int i = 1; i < mask_index_length; i++){

        if((index_to_insert >= mask_index[i-1]) & (index_to_insert < mask_index[i])) {
            return i-1;
        }

    }

    return fact_index;
}


// LCP length
int LCP_length(string* X, string* Y){

    int i = 0, j = 0;

    int X_len = (*X).length();
    int Y_len = (*Y).length();

    while ((i < X_len) & (j < Y_len)){

        if ((*X)[i] != (*Y)[j]) {
            break;
        }

        i = i + 1;
        j = j + 1;
    }

    //cout << (*X).substr(0,i) << endl;

    return (*X).substr(0,i).length();

}

vector<int> commonPrefixMerge(trie_node* root) {

    vector<int> common_prefix_vct;
    vector<int> common_prefix_vct_current;

    int children_size = root->children.size();
    int bool_merge_size = root->bool_merge.size();

    // Caso Base
    if(children_size == 0) {

        for(int i = 0; i < bool_merge_size; i++) {

            //cout << "bool_merge i: " << root->bool_merge.at(i) << endl;
            if(root->bool_merge.at(i) == true) {
                common_prefix_vct.push_back(-1);
            } else {
                common_prefix_vct.push_back(root->ranking.at(root->ranking_index_0));
                root->ranking_index_0++;
            }
        }

        return common_prefix_vct;
    }

    trie_node* node;
    int i;

    // Compute commonprefix for all children
    vector<vector<int>> lists;
    for(i = 0; i < children_size; i++) {

        node = root->children.at(i);
        common_prefix_vct_current = commonPrefixMerge(node);

        /*
        // INFO VCT #########################################################################
        cout << "common_prefix_vct_current: [ ";
        for(int i = 0; i < common_prefix_vct_current.size(); i++) {
            cout << common_prefix_vct_current[i] << " ";
        }
        cout << " ]" << endl;
        // ##################################################################################
        */

        lists.push_back(common_prefix_vct_current);
    }

    if(lists.size() == 1) {

        common_prefix_vct = lists[0];

    } else {

        bool check_completed = false;
        bool check_last_insert = true;
        while(true) {

            check_completed = true;

            for(i = 0; i < children_size; i++) {

                //common_prefix_vct_current = node.commonPrefixMerge();
                common_prefix_vct_current = lists.at(i);

                while(true) {
                    /*
                    cout << "Xb: " << (root->children.at(i))->bool_index_1 << endl;
                    cout << "Xsize: " << common_prefix_vct_current.size() << endl;
                    cout << "Xitem: " << common_prefix_vct_current[(root->children.at(i))->bool_index_1] <<endl;
                    */
                    if (((root->children.at(i))->bool_index_1 < common_prefix_vct_current.size()) & (common_prefix_vct_current[(root->children.at(i))->bool_index_1] != -1)){

                        common_prefix_vct.push_back(common_prefix_vct_current.at((root->children.at(i))->bool_index_1));
                        //cout << "common_prefix_vct_current.at((root->children.at(i))->bool_index_1): " << common_prefix_vct_current.at((root->children.at(i))->bool_index_1) << endl;
                        int b = (root->children.at(i))->bool_index_1 + 1;

                        (root->children.at(i))->bool_index_1 = b;

                        /*
                        cout << "b: " << b << endl;
                        cout << "case1: " << endl;
                        */

                    } else {
                        int b = (root->children.at(i))->bool_index_1 + 1;

                        (root->children.at(i))->bool_index_1 = b;

                        /*
                        cout << "b: " << b << endl;
                        cout << "case2: " << endl;
                        */

                        break;

                    }
                }

                //cout << "(root->children.at(i))->bool_index_1: " << (root->children.at(i))->bool_index_1 << endl;

                if ((root->children.at(i))->bool_index_1 < common_prefix_vct_current.size()) {
                    check_completed = false;
                } else {

                    if(common_prefix_vct_current.size() == ((root->children.at(i))->bool_index_1-1)) {
                        check_last_insert = false;
                    }
                }

                continue;

            }

            if (check_last_insert) {
                common_prefix_vct.push_back(-1);
                //cout << "push -1" << endl;
            }

            if(check_completed) {
                break;
            }

        }

    }

    /*
    // INFO VCT #########################################################################
    cout << "common_prefix_vct: [ ";
    for(int i = 0; i < common_prefix_vct.size(); i++) {
        cout << common_prefix_vct[i] << " ";
    }
    cout << " ]" << endl;
    // ##################################################################################
    */

    int index_0 = 0;
    int num_minus_1 = 0;
    int ranking_index = 0;
    int j = 0;
    for (i=0; i < bool_merge_size; i++) {

        if(root->bool_merge.at(i) == false) {
            index_0 = i;

            while(true) {
                if (common_prefix_vct[j] == -1) {
                    num_minus_1++;

                    if (num_minus_1 == index_0 + 1) {
                        common_prefix_vct[j] = root->ranking[ranking_index];
                        ranking_index++;
                        break;
                    }

                }
                j++;
            }
        }
    }

    /*
    // INFO VCT #########################################################################
    cout << "common_prefix_vct: [ ";
    for(int i = 0; i < common_prefix_vct.size(); i++) {
        cout << common_prefix_vct[i] << " ";
    }
    cout << " ]" << endl;
    // ##################################################################################
    */

    return common_prefix_vct;
}


vector<int> computeSuffixArray(trie_node* root) {

    vector<int> suffix_array;
    vector<int> common_prefix_vct_current;

    int children_size = root->children.size();
    for(int i = 0; i < children_size; i++) {

        common_prefix_vct_current = commonPrefixMerge(root->children.at(i));

        /*
        // INFO VCT #########################################################################
        cout << "common_prefix_vct_current: [ ";
        for(int i = 0; i < common_prefix_vct_current.size(); i++) {
            cout << common_prefix_vct_current[i] << " ";
        }
        cout << " ]" << endl;
        // ##################################################################################
        */

        // CONCATENATION
        suffix_array.insert(suffix_array.end(), common_prefix_vct_current.begin(), common_prefix_vct_current.end());

        /*
        // INFO SA #########################################################################
        cout << "suffix_array: [ ";
        for(int i = 0; i < suffix_array.size(); i++) {
            cout << suffix_array[i] << " ";
        }
        cout << " ]" << endl;
        // ##################################################################################
        */
    }

    return suffix_array;
}


void inPrefixMerge(trie_node* root, int x_j, vector<int>& mask_index) {

    int len_parent_bool_merge = (*(root->parent)).bool_merge.size();

    // controllo se il ranking del padre � vuoto ==> in questo caso inserisco in testa
    if (len_parent_bool_merge == 0) {

        root->bool_merge.insert(root->bool_merge.begin(),false);
        root->num_of_true_in_bool_merge.insert(root->num_of_true_in_bool_merge.begin(),-1);

        return;
    }

    int last_factor_index = mask_index.size() - 1;
    int word_len = (*(root->word_pointer)).length();
    int i = 0;
    int x_i, fact_index_i, fact_index_j, l, new_i, new_j, new_index, num_of_true_in_bool_merge_size;
    string s1, s2;

    // il ranking del padre non � vuoto quindi posso scansionare
    while(true) {

        // Abbiamo analizzato tutto ranking_j quindi dobbimao inserire in coda
        if(i == len_parent_bool_merge) {

            root->bool_merge.push_back(false);
            root->num_of_true_in_bool_merge.push_back(-1);

            return;

        }

        // TROVARE x_i
        trie_node *new_parent = root->parent;
        new_index = i;

        do {

            if((*new_parent).bool_merge[new_index] == false) {

                // devo contare i false prima
                int count_false = 1;
                for(int k=new_index-1; k >= 0; k--) {

                    if((*new_parent).bool_merge[k] == false) {
                        count_false++;
                    }
                }

                x_i = (*new_parent).ranking[count_false-1];

                break;

            } else {

                // Cerco in che posizione si trova il true in parent bool_merge
                new_index = (*new_parent).num_of_true_in_bool_merge.at(new_index);
                new_parent = new_parent->parent;

            }

        }while(true);


        fact_index_i = fact_of(x_i, mask_index);
        fact_index_j = fact_of(x_j, mask_index);

        // CASE 1: i and j both in the last factor
        if ((fact_index_i == last_factor_index) & (fact_index_j == last_factor_index)) {

            i = i + 1;

            continue;
        }


        // CASE 2: i and j both in the same factor (different than last factor)
        if ((fact_index_i == fact_index_j) & (fact_index_i < last_factor_index)) {

            root->bool_merge.insert(root->bool_merge.begin() + i, false);
            root->num_of_true_in_bool_merge.insert(root->num_of_true_in_bool_merge.begin() + i, -1);

            // update num_of_true_in_bool_merge
            num_of_true_in_bool_merge_size = root->num_of_true_in_bool_merge.size();
            for(int j = i+1; j < num_of_true_in_bool_merge_size; j++){
                if(root->num_of_true_in_bool_merge.at(j) != -1) {
                    root->num_of_true_in_bool_merge.at(j) = root->num_of_true_in_bool_merge.at(j) + 1;
                }
            }

            return;
        }


        // CASE 3: i and j occurs in different factors
        if (fact_index_i != fact_index_j) {

            // SUBCASE (a): i occurs in the last factor
            if (fact_index_i == last_factor_index) {

                i = i + 1;
                continue;
            }

            // SUBCASE (b): j occurs in the last factor
            if (fact_index_j == last_factor_index) {

                s1 = (*(root->word_pointer)).substr(x_i, word_len - (*(root->parent)).ranking[i]);
                //cout << "s1: " << s1 << endl;

                s2 = ((*(root->word_pointer))).substr(x_j, word_len - x_j);
                //cout << "s2: " << s2 << endl;

                l = LCP_length(&s1, &s2);
                //cout << "l: " << l << endl;

                new_i = x_i + l;
                //cout << "new_i: " << new_i << endl;

                new_j = x_j + l;
                //cout << "new_j: " << new_j << endl;

                if (new_j >= word_len){

                    root->bool_merge.insert(root->bool_merge.begin() + i, false);
                    root->num_of_true_in_bool_merge.insert(root->num_of_true_in_bool_merge.begin() + i, -1);

                    // update num_of_true_in_bool_merge
                    num_of_true_in_bool_merge_size = root->num_of_true_in_bool_merge.size();
                    for(int j = i+1; j < num_of_true_in_bool_merge_size; j++){
                        if(root->num_of_true_in_bool_merge.at(j) != -1) {
                            root->num_of_true_in_bool_merge.at(j) = root->num_of_true_in_bool_merge.at(j) + 1;
                        }
                    }

                    return;
                }

                if (new_i >= word_len){

                    root->bool_merge.insert(root->bool_merge.begin() + i, false);
                    root->num_of_true_in_bool_merge.insert(root->num_of_true_in_bool_merge.begin() + i, -1);

                    // update num_of_true_in_bool_merge
                    num_of_true_in_bool_merge_size = root->num_of_true_in_bool_merge.size();
                    for(int j = i+1; j < num_of_true_in_bool_merge_size; j++){
                        if(root->num_of_true_in_bool_merge.at(j) != -1) {
                            root->num_of_true_in_bool_merge.at(j) = root->num_of_true_in_bool_merge.at(j) + 1;
                        }
                    }

                    return;
                }

                if ((*(root->word_pointer))[new_i] < (*(root->word_pointer))[new_j]) {

                    i = i + 1;
                    continue;

                } else {

                    root->bool_merge.insert(root->bool_merge.begin() + i, false);
                    root->num_of_true_in_bool_merge.insert(root->num_of_true_in_bool_merge.begin() + i, -1);

                    // update num_of_true_in_bool_merge
                    num_of_true_in_bool_merge_size = root->num_of_true_in_bool_merge.size();
                    for(int j = i+1; j < num_of_true_in_bool_merge_size; j++){
                        if(root->num_of_true_in_bool_merge.at(j) != -1) {
                            root->num_of_true_in_bool_merge.at(j) = root->num_of_true_in_bool_merge.at(j) + 1;
                        }
                    }

                    return;
                }
                continue;
            }


            // SUBCASE (c): both i and j do not occurs in last factors
            if ((fact_index_i != last_factor_index) & (fact_index_j != last_factor_index)) {

                //if ((*(root->parent)).ranking[i] > x_j ) {
                if (x_i > x_j ) {

                    root->bool_merge.insert(root->bool_merge.begin() + i, false);
                    root->num_of_true_in_bool_merge.insert(root->num_of_true_in_bool_merge.begin() + i, -1);

                    // update num_of_true_in_bool_merge
                    num_of_true_in_bool_merge_size = root->num_of_true_in_bool_merge.size();
                    for(int j = i+1; j < num_of_true_in_bool_merge_size; j++){
                        if(root->num_of_true_in_bool_merge.at(j) != -1) {
                            root->num_of_true_in_bool_merge.at(j) = root->num_of_true_in_bool_merge.at(j) + 1;
                        }
                    }

                    return;

                } else {

                    //s1 = (*(root->word_pointer)).substr(x_i, word_len - (*(root->parent)).ranking[i]);
                    s1 = (*(root->word_pointer)).substr(x_i, word_len - x_i);
                    s2 = (*(root->word_pointer)).substr(x_j, word_len - x_j);

                    l = LCP_length(&s1, &s2);

                    new_i = x_i + l;
                    new_j = x_j + l;

                    if (new_j >= word_len){
                        root->bool_merge.insert(root->bool_merge.begin() + i, false);
                        root->num_of_true_in_bool_merge.insert(root->num_of_true_in_bool_merge.begin() + i, -1);

                        // update num_of_true_in_bool_merge
                        num_of_true_in_bool_merge_size = root->num_of_true_in_bool_merge.size();
                        for(int j = i+1; j < num_of_true_in_bool_merge_size; j++){
                            if(root->num_of_true_in_bool_merge.at(j) != -1) {
                                root->num_of_true_in_bool_merge.at(j) = root->num_of_true_in_bool_merge.at(j) + 1;
                            }
                        }

                        return;
                    }

                    if(new_i >= word_len) {

                        i = i + 1;
                        continue;

                    }

                    if ((*(root->word_pointer))[new_i] < (*(root->word_pointer))[new_j]) {

                        i = i + 1;
                        continue;

                    } else {

                        root->bool_merge.insert(root->bool_merge.begin() + i, false);
                        root->num_of_true_in_bool_merge.insert(root->num_of_true_in_bool_merge.begin() + i, -1);

                        // update num_of_true_in_bool_merge
                        num_of_true_in_bool_merge_size = root->num_of_true_in_bool_merge.size();
                        for(int j = i+1; j < num_of_true_in_bool_merge_size; j++){
                            if(root->num_of_true_in_bool_merge.at(j) != -1) {
                                root->num_of_true_in_bool_merge.at(j) = root->num_of_true_in_bool_merge.at(j) + 1;
                            }
                        }

                        return;
                    }
                    continue;
                }
            }


        }

    }

}


void add(trie_node* root, int ranking_item_index, int ranking_item_length, vector<int>& mask_index)
{
    trie_node* node = root;

    int i = 0;
    while(true) {

        if(node->children.size() == 0){
            break;
        }

        trie_node* current_node = node->children[i];

        /*
        cout << "suffisso distinto da inserire: " << (*(root->word_pointer)).substr(ranking_item_index,ranking_item_length) << endl;
        cout << "suffisso corrente: " << (*(root->word_pointer)).substr(current_node->ranking.at(0),current_node->suffix_length) << endl;
        cout << endl;
        */

        if ((*(root->word_pointer)).substr(ranking_item_index,ranking_item_length)==(*(root->word_pointer)).substr(current_node->ranking.at(0),current_node->suffix_length)) {

            //cout << "suffisso da inserire == suffisso corrente" << endl;
            current_node->ranking.insert(current_node->ranking.begin(),ranking_item_index);
            inPrefixMerge(current_node, ranking_item_index, mask_index);

            /*
            // INFO NODO #########################################################################
            cout << "ranking: [ ";
            for(int i = 0; i < current_node->ranking.size(); i ++ ) {
                cout << current_node->ranking.at(i) << " ";
            }
            cout << "]" << endl;

            cout << "bool_merge: [ ";
            for(int i = 0; i < current_node->bool_merge.size(); i ++ ) {
                cout << current_node->bool_merge.at(i) << " ";
            }
            cout << "]" << endl;

            cout << "num_of_1: [ ";
            for(int i = 0; i < current_node->num_of_true_in_bool_merge.size(); i ++ ) {
                cout << current_node->num_of_true_in_bool_merge.at(i) << " ";
            }
            cout << "]" << endl;
            // ###################################################################################
            */
            return;

        }

        /*
        cout << "suffisso distinto da inserire: " << (*(*this).word_pointer).substr(ranking_item_index,ranking_item_length) << endl;
        cout << "suffisso corrente: " << (*(*this).word_pointer).substr((*current_node).ranking.at(0),(*current_node).suffix_length) << endl;
        cout << endl;
        */

        if (((*(root->word_pointer)).substr(ranking_item_index,ranking_item_length)).rfind((*(root->word_pointer)).substr(current_node->ranking.at(0),current_node->suffix_length), 0) == 0) {

            //cout << "suffisso corrente is prefix of suffisso da inserire" << endl;
            node = current_node;
            i = 0;

            continue;

        }

        // Siamo alla fine
        if(i == node->children.size()-1) {
            break;
        }

        i++;

    }

    trie_node* new_node = new trie_node(ranking_item_length, root->word_pointer);
    new_node->parent = node;

    int parent_bool_merge_size = new_node->parent->bool_merge.size();
    int index_true = 0;
    for(int i = 0; i < parent_bool_merge_size; i++) {
        new_node->bool_merge.push_back(true);

        new_node->num_of_true_in_bool_merge.push_back(index_true);
        index_true++;
    }

    new_node->ranking.insert(new_node->ranking.begin(), ranking_item_index);
    inPrefixMerge(new_node, ranking_item_index, mask_index);

    // INSERT with BINARY SEARCH %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    int low = 0, high = node->children.size() - 1, loc;

    while (low <= high) {
		int mid = low + (high - low) / 2;
		if ((*(new_node->word_pointer)).substr(new_node->ranking[0],new_node->suffix_length) == ((*((node->children).at(mid))->word_pointer)).substr(((node->children).at(mid))->ranking[0],((node->children).at(mid))->suffix_length)) {
			low = mid + 1;
			break;
		} else if ((*(new_node->word_pointer)).substr(new_node->ranking[0],new_node->suffix_length) > ((*((node->children).at(mid))->word_pointer)).substr(((node->children).at(mid))->ranking[0],((node->children).at(mid))->suffix_length))
			low = mid + 1;
		else
			high = mid - 1;
	}

	loc = low;
    node->children.insert(node->children.begin() + loc, new_node);

    /*
    // INFO NODO #########################################################################
    cout << "ranking: [ ";
    for(int i = 0; i < new_node->ranking.size(); i ++ ) {
        cout << new_node->ranking.at(i) << " ";
    }
    cout << "]" << endl;

    cout << "bool_merge: [ ";
    for(int i = 0; i < new_node->bool_merge.size(); i ++ ) {
        cout << new_node->bool_merge.at(i) << " ";
    }
    cout << "]" << endl;

    cout << "num_of_1: [ ";
    for(int i = 0; i < new_node->num_of_true_in_bool_merge.size(); i ++ ) {
        cout << new_node->num_of_true_in_bool_merge.at(i) << " ";
    }
    cout << "]" << endl;
    // ###################################################################################

    // INFO PARENT NODO #########################################################################
    trie_node* parent_node = new_node->parent;

    cout << "p ranking: [ ";
    for(int i = 0; i < parent_node->ranking.size(); i ++ ) {
        cout << parent_node->ranking.at(i) << " ";
    }
    cout << "]" << endl;

    cout << "p bool_merge: [ ";
    for(int i = 0; i < parent_node->bool_merge.size(); i ++ ) {
        cout << parent_node->bool_merge.at(i) << " ";
    }
    cout << "]" << endl;

    cout << "p num_of_1: [ ";
    for(int i = 0; i < parent_node->num_of_true_in_bool_merge.size(); i ++ ) {
        cout << parent_node->num_of_true_in_bool_merge.at(i) << " ";
    }
    cout << "]" << endl;
    // ###################################################################################
    */

    /*
    for(int i = 0; i < node->children.size(); i++) {

        string suffix = ((*((node->children).at(i))->word_pointer)).substr(((node->children).at(i))->ranking[0],((node->children).at(i))->suffix_length);
        cout << "child: " << suffix << endl;

    }
    */
}

