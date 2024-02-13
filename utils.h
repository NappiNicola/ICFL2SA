#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include<iostream>
#include<vector>

#include "generic_vector.h"
#include "custom_suffix_tree.h"

using namespace std;

void print(string word);
void printVector(vector<int> vec, string msg);
char* append(const char *s, char c);
void quicksort(int_vector* x, int start, int end);
void quicksort_of_nodes(nodes_vector* x, int start, int end);

#endif