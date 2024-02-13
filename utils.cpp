#include<iostream>
#include<string.h>
#include "custom_suffix_tree.h"

#include "generic_vector.h"
#include "utils.h"

using namespace std;

void print(string word){
    cout<<word<<endl;
}

void printVector(vector<int> vec, string msg){
    print(msg);
    for(int i=0; i<vec.size(); i++)
        cout<<vec.at(i)<<" ";
    cout<<endl;
}

char* append(const char *s, char c) {
    int len = strlen(s);
    char buf[len+2];
    strcpy(buf, s);
    buf[len] = c;
    buf[len + 1] = 0;
    return strdup(buf);
}

void quicksort(int_vector* x, int start, int end){
    int i, j, pivot, temp;
    if(start<end){

        pivot=start;
        
        i=start;
        j=end;     

        while(i<j){
            while(x->data[i]<=x->data[pivot]&&i<end) i++;
            while(x->data[j]>x->data[pivot]) j--;

            if(i<j){   
               temp=x->data[i];
               x->data[i]=x->data[j];
               x->data[j]=temp;
            }
        }

        temp=x->data[pivot];
        x->data[pivot]=x->data[j];
        x->data[j]=temp;
        quicksort(x,start,j-1);
        quicksort(x,j+1,end);
    }
}

void quicksort_of_nodes(nodes_vector* x, int start, int end){
    int i, j, pivot;
    suffix_tree_node* temp;
    if(start<end){

        pivot=start;
        
        i=start;
        j=end;     

        while(i<j){
            while(strcmp(x->data[i]->suffix,x->data[pivot]->suffix)<=0 && i<end) i++;
            while(strcmp(x->data[j]->suffix,x->data[pivot]->suffix)>0) j--;

            if(i<j){   
               temp=x->data[i];
               x->data[i]=x->data[j];
               x->data[j]=temp;
            }
        }

        temp=x->data[pivot];
        x->data[pivot]=x->data[j];
        x->data[j]=temp;
        quicksort_of_nodes(x,start,j-1);
        quicksort_of_nodes(x,j+1,end);
    }
}