#include <malloc.h>
#include <iostream>
#include <string.h>
#include "generic_vector.h"

using namespace std;

int_vector* init_int_vector(size_t size){

    int_vector* x= (int_vector*)malloc(sizeof(int_vector));
    x->size=size;
    x->data=(int*)malloc(sizeof(int)*size);
    x->used=0;

    return x;

}

bool add_in_int_vector(int_vector* x,int element){
    if (x->size==x->used){
        x->size += 10;
        x->data = (int*)realloc(x->data,sizeof(int)*x->size);
    }
    x->data[x->used++]=element;

    return 1;
}

bool element_in_int_vector(int_vector* x,int element){
    for(int i=0;i<x->used;i++) if(x->data[i]==element) return true;
    return false;
}

    
int_vector* duplicate_int_vector(int_vector* x){
    int_vector* temp = (int_vector*)malloc(sizeof(int_vector));
    temp->size=x->size;
    temp->used=x->used;
    temp->data=intdup(x->data,x->size);

    return temp;
}

array_of_int_vector* init_array_of_int_vector(size_t size){

    array_of_int_vector* x= (array_of_int_vector*)malloc(sizeof(array_of_int_vector));
    x->size=size;
    x->data=(int_vector**)malloc(sizeof(int_vector*)*size);
    x->used=0;

    return x;

}

bool add_in_array_of_int_vector(array_of_int_vector* x,int_vector* element){
    if (x->size==x->used){
        x->size += 1000;
        x->data = (int_vector**)realloc(x->data,sizeof(int_vector*)*x->size);
    }
    x->data[x->used++]=element;

    return 1;
}


void print_int_vector(int_vector* x){

    for(int i=0;i<x->used;i++){
        cout<<x->data[i]<<",";
    }

}

void print_array_of_vector(array_of_int_vector* x){

    for(int i=0;i<x->used;i++){
        cout<<"[";
        print_int_vector(x->data[i]);
        cout<<"]";
    }

    cout<<endl;

}

int_vector* merge_array_of_vector(array_of_int_vector* x){
    int_vector* res = init_int_vector(0);
    for(int i=0;i<x->used;i++){
        for(int j=0;j<x->data[i]->used;j++){
            add_in_int_vector(res,x->data[i]->data[j]);
        }
    }
    return res;
}

int* intdup(int* src, size_t len){
   int* p = (int*)malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}