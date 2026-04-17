#include <stdio.h>

#include "dyn_arr.h"

int main()
{
    array* arr = init_array(10);

    set(arr, 0, 5);
    int var = get(arr, 0);

    arr = resize(arr, 15);
    printf("%d", var);
    
    remove_array(&arr);
    return 0;
}