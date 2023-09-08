#include <stdlib.h>
#include <string.h>
#include "dbl_vector.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

void dv_init( dbl_vector_t* vec ) {
    vec->size = 0;
    vec->capacity = DV_INITIAL_CAPACITY;
    vec->data = malloc(DV_INITIAL_CAPACITY * sizeof(double));
    if (vec->data == NULL) exit(12);
}

void dv_ensure_capacity( dbl_vector_t* vec, size_t new_size ) {
    size_t new_capacity = max(vec->capacity * DV_GROWTH_FACTOR, new_size);
    double* old_data = vec->data;
    if (new_size > vec->capacity) {
        vec->capacity = new_capacity;
        vec->data = realloc(old_data, new_capacity * sizeof(double ));
        if (vec->data == NULL) exit(12);
    }
}

void dv_destroy( dbl_vector_t* vec ) {
    vec->capacity = 0;
    vec->size = 0;
    free(vec->data);
}

void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest ) {
    dest->size = vec->size;
    dv_ensure_capacity(dest, vec->size);
    memcpy(dest->data, vec->data, vec->size * sizeof(double));
}

void dv_clear( dbl_vector_t* vec ) {
    memset(vec->data, 0, vec->size);
    vec->size = 0;
}

void dv_push( dbl_vector_t* vec, double new_item ) {
    dv_ensure_capacity(vec, vec->size + 1);
    vec->data[vec->size] = new_item;
    vec->size++;
}

void dv_pop( dbl_vector_t* vec ) {
    if (vec->size > 0) vec->size--;
}

double dv_last( dbl_vector_t* vec ) {
    double result = NAN;
    if (vec->size > 0) return vec->data[vec->size -1];
    return result;
}

void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item ) {
    size_t loc = min(pos, vec->size);
    dv_ensure_capacity(vec, vec->size + 1);
    for (size_t i = vec->size; loc < i; i--) vec->data[i] = vec->data[i-1];
    vec->data[loc] = new_item;
    vec->size++;

}

void dv_remove_at( dbl_vector_t* vec, size_t pos ) {
    if (pos >= vec->size) return;
    for (size_t i = pos; i < vec->size - 1; i++) vec->data[i] = vec->data[i+1];
    vec->size--;
}

void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info ) {
    for (int i = 0; i < vec->size; ++i) callback(vec->data[i], info);
}