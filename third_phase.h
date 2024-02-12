#include <iostream>
#include "generic_vector.h"
#include "custom_suffix_tree.h"
#include <string.h>
#include <vector>
#include "second_phase.h"
#include "utils.h"

using namespace std;


int_vector* find_common_elements_with_quick_sort(int_vector* x,int_vector* y);
int_vector* find_common_elements(int_vector* x,int_vector* y);
int_vector* common_prefix_merge(int_vector* x,int_vector* y);
int_vector* get_common_prefix_merge(suffix_tree_node* root);