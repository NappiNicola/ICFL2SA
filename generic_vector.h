#ifndef CUSTOM_GENERIC_VECTOR_H_INCLUDED
#define CUSTOM_GENERIC_VECTOR_H_INCLUDED

#include <cstdint>

using namespace std;

typedef struct int_vector
{
    int* data;
    size_t size;
    size_t used;

}int_vector;
int_vector* init_int_vector(size_t size);
bool add_in_int_vector(int_vector* x,int element);


#endif