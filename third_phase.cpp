#include <iostream>
#include "generic_vector.h"
#include "custom_suffix_tree.h"
#include <string.h>
#include <vector>
#include "second_phase.h"
#include "utils.h"

using namespace std;


int_vector* find_common_elements_with_quick_sort(int_vector* x,int_vector* y){
    int_vector* res=init_int_vector(0);

    int_vector* x_temp = duplicate_int_vector(x);
    int_vector* y_temp = duplicate_int_vector(y);

    print_int_vector(x_temp);
    cout<<"\n";
    print_int_vector(y_temp);
    cout<<"\n";

    quicksort(x_temp,0,x_temp->used-1);
    quicksort(y_temp,0,y_temp->used-1);

    print_int_vector(x_temp);
    cout<<"\n";
    print_int_vector(y_temp);
    cout<<"\n";

    int i,j;
    i=j=0;

    while (i<x_temp->used && j<y_temp->used){
        if (x_temp->data[i] == y_temp->data[j]){
            add_in_int_vector(res,x_temp->data[i]);
            i++;
            j++;
        }
        else if(x_temp->data[i] < y_temp->data[j]){
            i++;
        }
        else{
            j++;
        }
    }
    
    print_int_vector(res);
    cout<<"\n";

    return res;
}

int_vector* find_common_elements(int_vector* x,int_vector* y){
    int_vector* res=init_int_vector(0);
    
    for(int i=0;i<x->used;i++){
        if(element_in_int_vector(y,x->data[i])){
            add_in_int_vector(res,x->data[i]);
        }
    }

    return res;
}

int_vector* common_prefix_merge(int_vector* x,int_vector* y){
    int_vector* res = init_int_vector(0);

    int_vector* common_elements = find_common_elements(x,y);

    int i,j,z;
    i=j=z=0;

    while(i<x->used){
        if(x->data[i] != common_elements->data[z]){
            add_in_int_vector(res,x->data[i]);
            i++;
        }
        else{
            while(y->data[j] != common_elements->data[z]){
                add_in_int_vector(res,y->data[j]);
                j++;
            }
            add_in_int_vector(res,common_elements->data[z]);
            z++;
            i++;
            j++;
        }
    }

    while(j<y->used){
        add_in_int_vector(res,y->data[j]);
        j++;
    }

    return res;

}


int_vector* get_common_prefix_merge(suffix_tree_node* root){
    int_vector* res = init_int_vector(0);

    for(int i=0;i<root->chains_of_suffixes->used;i++){
        res = common_prefix_merge(res,root->chains_of_suffixes->data[i]);
    }
    return res;
}

