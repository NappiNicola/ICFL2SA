#include "generic_vector.h"
#include "custom_suffix_tree.h"
#include <string.h>
#include <vector>

using namespace std;

void sort_sons_of_all_nodes(suffix_tree_node* root);

int get_factor(vector<int> icfl_list,int index);
int_vector* in_prefix_merge(const char* S, vector<int> icfl_list, int_vector* e, int_vector* g);
array_of_int_vector* get_chains(suffix_tree_node* root,const char* S, vector<int> icfl_list);
array_of_int_vector* get_ranks_from_leaf_to_root(suffix_tree_node* root,const char* S, array_of_int_vector* sequence,vector<int> icfl_list);
void compute_chain(array_of_int_vector* sequence,const char* S,vector<int> icfl_list);

void get_chains_2(const char* S, vector<int> icfl_list,suffix_tree_node* root,int_vector* prev_common_chain_of_suffiexes);
void add_chain_to_root(suffix_tree_node* root,int_vector* common_chain_of_suffiexes);

int_vector* get_chain_from_bit_vector(suffix_tree_node* root);
void create_bit_vector(const char* S,vector<int> icfl_list, suffix_tree_node* root);
void get_chains_3(suffix_tree_node* root,suffix_tree_node* node);