#include <malloc.h>
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
        x->size += 1;
        x->data = (int*)realloc(x->data,sizeof(int)*x->size);
    }
    x->data[x->used++]=element;

    return 1;
}


