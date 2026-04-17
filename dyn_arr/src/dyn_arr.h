#include <stdint.h>

#define MAX_SIZE_ARR 1 << 30

typedef struct dyn_arr
{
    int* _data;         // ptr to start in memory area

    uint32_t _capacity; // actual size in array
    uint32_t _size;     // size in array
} array;

array* init_array(int _Count);
array* resize(array* arr, int _newSize);

void remove_array(array** arr);

int set(array* arr, int index, int data);
int get(array* arr, int index);

int _isarr_bc(array* arr, int index);