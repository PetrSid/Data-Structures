#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_SIZE_ARR 1 << 30
#define MAX_P        1.5

struct dyn_arr
{
    int* _data;       // ptr to start in memory area

    size_t _capacity; // actual size in array
    size_t _size;     // size in array
};

/*Test_Name*/
struct dyn_arr* darr_init(const size_t _Count);
void            darr_remw(struct dyn_arr** arr);
inline size_t   darr_capacity(const struct dyn_arr* arr) { return arr->_capacity; }
inline size_t   darr_size(const struct dyn_arr* arr)     { return arr->_size; }
struct dyn_arr* darr_resize(struct dyn_arr* arr, const int _newSize);
void            darr_clear(struct dyn_arr* arr);
int             darr_set(struct dyn_arr* arr, const size_t index, const int value);
int             darr_get(const struct dyn_arr* arr, const size_t index);
void            darr_push_front(struct dyn_arr** arr, const int value);
void            darr_push_back(struct dyn_arr** arr, const int value);


/*Скрытые Методы*/
static bool realloc_mem_darr(struct dyn_arr** arr, size_t cap);

/*Скрытые Методы*/
static inline bool is_darr(struct dyn_arr* arr)                     { return arr != NULL; }
static inline bool is_empty(struct dyn_arr* arr)                    { return arr != NULL && arr->_size == 0; }
static inline bool is_full(struct dyn_arr* arr)                     { return arr != NULL && arr->_size >= arr->_capacity; }
static inline bool is_ivalid_index(struct dyn_arr* arr, size_t idx) { return arr != NULL && idx >= arr->_size; }

#endif //!DYN_ARR_H