#include "dyn_arr.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>


struct dyn_arr* init_array(const size_t _Count)
{
    if(_Count >= MAX_SIZE_ARR)
    {
        fprintf(stderr, "Error: Array size exceeds maximum limit.\n");
        return NULL;
    }
    struct dyn_arr* arr = (struct dyn_arr*)malloc(sizeof(struct dyn_arr));
    if(!arr){
        fprintf(stderr, "Fatal error: Failed to allocate memory for structure.\n");
        return NULL;
    }
    arr->_data = (int*)calloc(_Count, sizeof(int));
    if(!arr->_data){
        fprintf(stderr, "Fatal error: Failed to allocate memory for data buffer.\n");
        free(arr);
        return NULL;
    }

    arr->_capacity = _Count;
    arr->_size     = _Count;

    return arr;
}

void remove_array(struct dyn_arr** arr) 
{
    if(is_darr(*arr))
    {
        free((*arr)->_data);
        free(*arr);          

        (*arr)->_data = NULL;
        *arr          = NULL;
    }
}

static bool realloc_mem_darr(struct dyn_arr** arr, size_t cap)
{
    int* tmp = (int*)realloc((*arr)->_data, cap * sizeof(int));
    if(!tmp) {
        fprintf(stderr, "Error: Invalid resize parameters.\n");
        return false;
    }          
    (*arr)->_data     = tmp;
    (*arr)->_capacity = cap;

    tmp = NULL;
    return true;
    // int new_capacity = (*arr)->_capacity * 2;
    // int* new_arr = (int*)calloc(new_capacity, sizeof(int));
    // if(!new_arr){
    //     perror("error:\n");
    //     return;
    // }
    // // Инициализация новой области в памяти
    // int i = 0;
    // while (i < (*arr)->_size) {
    //     *(new_arr + i) = ((*arr)->_data + i);
    //     i += 1;
    // }
    // free((*arr)->_data);
    // (*arr)->_data     = new_arr;
    // (*arr)->_capacity = new_capacity;
    // new_arr = NULL; // Может быть бесмыслена
}


struct dyn_arr* resize(struct dyn_arr* arr, const int _newSize)
{
    if(!is_darr(arr) || _newSize < 0)
    {
        printf("error:\n");
        return arr;
    }
    if(_newSize == arr->_size){
        return arr;
    }
    if(_newSize > arr->_capacity)
    {
        if(!realloc_mem_darr(&arr, _newSize)) 
        {
            printf("error:\n");
            return arr;
        }
    }
    arr->_size     = _newSize;

    return arr;
}

void clear(struct dyn_arr* arr)
{
    if(is_empty(arr)){
        fprintf(stderr, "Warning: Attempt to clear an empty or invalid array.\n");
        return;
    }
    for (size_t i = 0; i < arr->_size; i++) {
        arr->_data[i] = 0;
    }
    arr->_size = 0;
}


int set(struct dyn_arr* arr, const size_t index, const int value)
{
    if(is_ivalid_index(arr, index)) 
    { 
        fprintf(stderr, "Error: Index %u is out of bounds.\n", index);
        return -1;
    } 
    arr->_data[index] = value;
    return 0;
}

int get(const struct dyn_arr* arr, const size_t index)
{
    if(is_ivalid_index(arr, index))
    { 
        fprintf(stderr, "Error: Index %u is out of bounds.\n", index);
        return -1;
    } 
    return arr->_data[index];
}


void front(struct dyn_arr** arr, const int value)
{
    if(!is_dyn_arr(&arr)){
        perror("error:\n");
        return;
    }
    if(is_full(&arr))
    {
        if(!realloc_mem_darr(&arr, (*arr)->_capacity * 1.5)) 
        {
            printf("error:\n");
            return arr;
        }   
    }
    int i = (*arr)->_size - 1;
    while (i >= 0) {
        (*arr)->_data[i + 1] = (*arr)->_data[i];
        i--;
    }
    *((*arr)->_data) = value;
}

void push_back(struct dyn_arr** arr, const int value)
{
    if(!is_dyn_arr(&arr))
    {
        fprintf(stderr, "Error: Array pointer is NULL.\n");
        return;
    }
    if(is_full(&arr))
    {
        if(!realloc_mem_darr(&arr, (*arr)->_capacity * 1.5)) 
        {
            return arr;
        }
    }
    (*arr)->_data[(*arr)->_size] = value;
    (*arr)->_size   += 1;
}