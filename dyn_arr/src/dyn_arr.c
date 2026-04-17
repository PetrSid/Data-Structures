#include "dyn_arr.h"

#include <stdio.h>
#include <stdlib.h>

array* init_array(int _Count)
{
    if(_Count <= 0 || _Count > MAX_SIZE_ARR)
    {
        perror("error: bad alloc or integer overflow, for allocate memory:\n"); 
        perror("correct capasity for array is 0 < Size > 1 << 30\n");

        return NULL;
    }

    // Alocate to pointer to struct
    array* arr = (array*)malloc(sizeof(array));
    if(!arr){
        perror("error: array not saport\n");
        return NULL;
    }
    // Alocate to pointer to data
    arr->_data = (int*)calloc(_Count, sizeof(int));
    if(!arr->_data){
        perror("error: array don`t be allocate memory:\n");
        free(arr);
        return NULL;
    }

    // Initial other variable
    arr->_capacity = _Count;
    arr->_size     = 0;

    return arr;
}

void remove_array(array** arr) 
{
    if(*arr)
    {
        free((*arr)->_data); // remove data
        free(*arr);        // remove all

        *arr = NULL;
    }
}

int _isarr_bc(array* arr, int index) {
    return (!arr || index <= 0 || index >= arr->_capacity)? 0 : 1;
}

int set(array* arr, int index, int data)
{
    if(_isarr_bc(arr, index)) {
        perror("error: invalid index\n");
        return -1;
    } 
    *(arr->_data + index) = data;

    arr->_size += 1;

    return 0;
}

int get(array* arr, int index)
{
    if(_isarr_bc(arr, index)) {
        perror("error: invalid index\n");
        return -1;
    } 
    return *(arr->_data + index);
}

array* resize(array* arr, int _newSize)
{
    // Обработка Ошибок
    if(!arr){
        perror("error:\n");
        return arr;
    }
    if(_newSize <= arr->_capacity){
        perror("error:\n");
        return arr;
    }

    // Создание и прокверка временого массива
    int* data = (int*)calloc(_newSize, sizeof(int));
    if(!data) {
        perror("error: array don`t be allocate memory:\n");
        return arr;
    }

    // Инициализация новой области в памяти
    int i = 0;
    while (i < arr->_capacity) {
        *(data + i) = *(arr->_data + i);
        i += 1;
    }
    
    // Переброс старого указателя на новый
    free(arr->_data);
    
    arr->_data     = NULL;
    arr->_data     = data;
    arr->_capacity = _newSize;

    data = NULL; // Может быть бесмыслена
    return arr;
}