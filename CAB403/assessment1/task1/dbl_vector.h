/*****************************************************************//**
 * \file   dbl_vector.h
 * \brief  API definition for the dbl_vector abstract data type.
 *
 * \author Lawrence
 * \date   August 2021
 *********************************************************************/
#pragma once

#include <stdbool.h>
#include <math.h>

/**
 * dbl_vector is a prototypical implementation of a vector abstract data type.
 *
 * A vector encapsulates an array which dynamically resizes (without loss of data)
 * as items are added, and which may be truncated on demand (with possible loss of
 * data).
 *
 * The ADT includes functions to reserve space, insert, remove, push, pop,
 * get and set elements, and traverse the collection.
 *
 * Notation: in the specification listed below:
 *   [a..b) is the half-open integer sub-range a <= i < b.
 */
typedef struct dbl_vector {
	/// The current number of elements in the vector
	size_t size;

	/// The current storage capacity of the vector
	size_t capacity;

	/// The content of the vector.
	double* data;
} dbl_vector_t;

#define DV_INITIAL_CAPACITY 4
#define DV_GROWTH_FACTOR 1.25

/**
 * Prepares a vector for first-time use. This should be called before anything
 * else is done with a vector. It should not be called more than once.
 *
 * PRE: n/a.
 *
 * POST: vec->capacity == DV_INITIAL_CAPACITY,
 * AND   vec->size == 0,
 * AND   vec->data == malloc(new_mem_size).
 *
 * WHERE new_mem_size is the number of bytes required to store DV_INITIAL_CAPACITY
 *       instances of type double.
 *
 * \param vec The address of a dbl_vector_t to initialise.
 */
void dv_init( dbl_vector_t* vec );

/**
 * Ensures that the storage capacity of a vector is large enough to hold the
 * designated number of items, resizing the encapsulated array if necessary, but
 * keeping the size unchanged.
 *
 * PRE: dv_init(vec) has been invoked previously
 *
 * POST: vec->size == old_size
 * AND
 *   IF new_size <= old_capacity
 *   THEN
 *     vec->capacity == old_capacity
 *     AND vec->data == old_data
 *   OTHERWISE
 *     vec->capacity == new_capacity
 *     AND vec->data == realloc(old_data, new_mem_size)
 *
 * WHERE old_capacity is the previous value of vec->capacity
 * AND old_size == previous value of vec->size
 * AND old_data == previous value of vec->data
 * AND new_capacity == max(old_capacity * DV_GROWTH_FACTOR, new_size)
 * AND new_mem_size == the number of bytes required to store new_capacity instances
 * of type double.
 *
 * \param vec A vector to process.
 * \param new_size The required minimum capacity for the vector.
 */
void dv_ensure_capacity( dbl_vector_t* vec, size_t new_size );

/**
 * Destroy a vector. After this, it will not be fit for further use.
 *
 * PRE: dv_init(vec) has been invoked.
 *
 * POST: vec->capacity == 0,
 * AND vec->size == 0,
 * AND vec->data has been freed,
 * AND vec->data == NULL.
 *
 * \param vec The address of a dbl_vector_t to be destroyed.
 */
void dv_destroy( dbl_vector_t* vec );

/**
 * Duplicate the contents of a vector (the source) into another (the destination).
 *
 * PRE: vec != dest
 * AND dv_init(vec) has been previously invoked,
 * AND dv_init(dest) has been previously invoked.
 *
 * POST: dest->size == vec->size
 * AND dv_ensure_capacity(dest, vec->size) has been invoked
 * AND for all i in [0..vec->size) dest->data[i] == vec->data[i].
 *
 * \param vec The address of a dbl_vector_t from which data is to be copied.
 * \param dest The address of a dbl_vector_t into which data is to be copied.
 */
void dv_copy( dbl_vector_t* vec, dbl_vector_t* dest );

/**
 * Remove all elements from the vector, but keep storage and capacity as-is to
 * enable efficient regrowth if necessary.
 *
 * PRE: dv_init(vec) has previously been invoked.
 *
 * POST: vec->size == 0.
 *
 * \param  The address of a dbl_vector_t to be cleared.
 */
void dv_clear( dbl_vector_t* vec );

/**
 * Append a new item to the end of the vector.
 *
 * PRE: dv_init(vec) has previously been invoked.
 *
 * POST: vec->size == old_size + 1
 * AND dv_ensure_capacity(vec, old_size + 1) has been invoked
 * AND for all i in [0..old_size) vec->data[i] == old_data[i]
 * AND vec->data[old_size] == new_item
 *
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data.
 *
 * \param vec The address of a dbl_vector_t to which a new item is to be appended.
 * \param new_item A double value to be appended to the vector.
 */
void dv_push( dbl_vector_t* vec, double new_item );

/**
 * Remove the last item (if any) from the end of the vector.
 *
 * PRE: dv_init(vec) has previously been invoked.
 *
 * POST: vec->capacity == old_capacity
 * AND vec->data == old_data
 * AND
 *   IF old_size > 0
 *   THEN
 *	   vec->size == old_size - 1
 *     AND for all i in [0..old_size-1) vec->data[i] == old_data[i]
 *   OTHERWISE
 *     vec->size == 0
 *
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data.
 *
 * \param vec The address of a dbl_vector_t from which the last item is to be
 * removed.
 */
void dv_pop( dbl_vector_t* vec );

/**
 * Get the last item from the end of the vector, or NaN if the vector is empty.
 *
 * PRE: dv_init(vec) has previously been invoked.
 *
 * POST: vec->size == old_size
 * AND vec->capacity == old_capacity
 * AND vec->data == old_data
 * AND for all i in [0..vec->size) vec->data[i] == old_data[i]
 * AND
 *   IF vec->size > 0
 *   THEN
 *	   returns vec->data[vec->size - 1]
 *   OTHERWISE
 *	   returns NaN
 *
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data
 * AND old_capacity == previous value of vec->capacity.
 *
 * \param vec The address of a dbl_vector_t from which the last item is to be obtained.
 */
double dv_last( dbl_vector_t* vec );

/**
 * Insert an item at a designated position in the vector. If the position
 * equals or exceeds the size of the vector, the new item is appended.
 *
 * PRE: dv_init(vec) has previously been invoked.
 *
 * POST: vec->size == old_size + 1
 * AND dv_ensure_capacity(vec,old_size+1) has been invoked
 * AND for all i in [0..loc) vec->data[i] == old_data[i]
 * AND for all i in [loc+1..vec->size) vec->data[i] == old_data[i-1]
 * AND vec->data[loc] == new_item
 *
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data
 * AND loc == min(pos, old_size).
 *
 * \param vec The address of a dbl_vector_t from which the last item is to be obtained.
 * \param pos The position at which the new item is to be inserted.
 * \param new_item The value to insert.
 */
void dv_insert_at( dbl_vector_t* vec, size_t pos, double new_item );

/**
 * Remove the item at a designated position in the vector. If the position equals
 * or exceeds the size of the vector, no change is made.
 *
 * PRE: dv_init(vec) has previously been invoked.
 *
 * POST: for all i in [0..loc) vec->data[i] == old_data[i]
 * AND for all i in [loc+1..vec->size) vec->data[i] == old_data[i+1]
 * AND
 *	IF pos >= old_size
 *  THEN
 *    vec->size == old_size
 *  OTHERWISE
 *    vec->size == old_size - 1
 *
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data
 * AND loc == min(pos, old_size).
 *
 * \param vec The address of a dbl_vector_t from which the last item is to be obtained.
 * \param pos The position at which the item is to be removed.
 */
void dv_remove_at( dbl_vector_t* vec, size_t pos );

/**
 * Traverses a vector, invoking the supplied function with each element in turn.
 *
 * PRE: dv_init(vec) has previously been invoked.
 *
 * POST: vec->capacity == old_capacity
 * AND vec->size == old_size
 * AND vec->data == old_data
 * AND for all i in [0..vec->size) callback(vec->data[i], info) has been invoked.
 *
 * WHERE old_size == previous value of vec->size
 * AND old_data == previous value of vec->data
 * AND old_capacity == previous value of vec->capacity
 *
 * \param vec The address of a dbl_vector_t which is to be processed.
 * \param callback A function which will be applied to each element of the vector.
 * \param info The address of a user-supplied data object which will be passed
 * to callback along with each value.
 */
void dv_foreach( dbl_vector_t* vec, void (*callback)(double, void*), void* info );