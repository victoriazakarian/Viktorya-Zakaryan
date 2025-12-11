#include "vector.h"

bool vector_init (Vector* vec, size_t elem_size, size_t initial_capacity)
{
	if (vec == NULL || elem_size == 0)
		return false;

	if (initial_capacity == 0)
		initial_capacity = 4;

	vec->data = malloc(elem_size * initial_capacity);
	if (vec->data == NULL)
		return false;

	vec->size = 0;
	vec->capacity = initial_capacity;
	vec->elem_size = elem_size;

	return true;
}

void vector_destroy(Vector* vec)
{
	if (vec == NULL) return;

	free(vec->data);

	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
	vec->elem_size = 0;
}

bool vector_reserve(Vector* vec, size_t new_capacity)
{
	if (!vec || new_capacity <= vec->capacity) return true;

	void* new_data = realloc(vec->data,vec->elem_size * new_capacity);
	if (new_data == NULL)
		return false;

	vec->data = new_data;
	vec->capacity = new_capacity;
	return true;
}

bool vector_push_back(Vector* vec, const void* element)
{
	if (vec == NULL || element == NULL) return false;

	if (vec->size == vec->capacity)
	{
		size_t new_cap = vec->capacity * 2;
		if (new_cap < 8) new_cap = 8;

		if (!vector_reserve(vec, new_cap))
			return false;
	}

	void* dest = (char*)vec->data + vec->size * vec->elem_size;
	memcpy(dest, element, vec->elem_size);

	vec->size++;
	return true;
}

bool vector_pop_back(Vector* vec, void* destination)
{
	if (vec == NULL || vec->size == 0) return false;

	vec->size--;

	if (destination != NULL)
	{
		const void* src = (const char*)vec->data + (vec->size - 1) * vec->elem_size;
		memcpy(destination, src, vec->elem_size);
	}

	return true;
}

void* vector_at(Vector* vec, size_t index)
{
	if (vec == NULL || vec->data == NULL) return NULL;

	return (char*)vec->data + index * vec->elem_size;
}

bool vector_get(const Vector* vec, size_t index, void* out_value)
{
	if (vec == NULL || out_value == NULL || index >= vec->size)
		return false;
	const void* src = (const char*)vec->data + index * vec->elem_size;
	memcpy(out_value, src, vec->elem_size);
	return true;
}

bool vector_set(Vector* vec, size_t index, const void* value)
{
	if (vec == NULL || value == NULL || index >= vec->size)
		return false;

	void* dest = (char*)vec->data + index * vec->elem_size;
	memcpy(dest, value, vec->elem_size);
	return true;
}

size_t vector_size(const Vector* vec) { return vec ? vec->size : 0; }
size_t vector_capacity(const Vector* vec) { return vec ? vec->capacity : 0 ;}
bool vector_empty(const Vector* vec) { return vector_size(vec) == 0; }

void vector_clear(Vector* vec)
{
	if (vec)
		vec->size = 0;
}

bool vector_shrink_to_fit(Vector* vec)
{
	if (!vec || vec->size == vec->capacity) return true;
    	if (vec->size == 0) {
        	free(vec->data);
        	vec->data = NULL;
        	vec->capacity = 0;
        	return true;
    	}
    	void* new_data = realloc(vec->data, vec->elem_size * vec->size);
    	if (!new_data) return false;
    	vec->data = new_data;
    	vec->capacity = vec->size;
    	return true;
}
