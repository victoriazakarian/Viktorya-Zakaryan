#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h> // sizze_t
#include <stdlib.h> // memcpy
#include <stdbool.h>
#include <string.h>

typedef struct {
	void* data;
	size_t size;
	size_t capacity;
	size_t elem_size;
} Vector;

bool vector_init(Vector* vec, size_t elem_size, size_t initial_capacity);
void vector_destroy(Vector* vec);
bool vector_push_back(Vector* vec, const void* element);
bool vector_pop_back(Vector* vec, void* destination);
void* vector_at(Vector* vec, size_t index);
bool vector_get(const Vector* vec, size_t index, void* out_value);
bool vector_set(Vector* vec, size_t index, const void* value);

size_t vector_size(const Vector* vec);
size_t vector_capacity(const Vector* vec);
bool   vector_empty(const Vector* vec);
void   vector_clear(Vector* vec);
bool   vector_reserve(Vector* vec, size_t new_capacity);
bool   vector_shrink_to_fit(Vector* vec);


#endif
