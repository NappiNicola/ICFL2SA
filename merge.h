#include "generic_vector.h"
#include "utils.h"
#include <vector>
#include <string.h>

int_vector* in_prefix_merge(const char* S, vector<int> icfl_list, int_vector* e, int_vector* g);
bit_vector* in_prefix_merge_bit_vector(const char* S, vector<int> icfl_list, int_vector* father, int_vector* child);