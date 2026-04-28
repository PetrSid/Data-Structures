#include <stdio.h>

#include "dyn_arr.h"

int main()
{
    struct dyn_arr* arr = init_array(10);
    
    remove_array(&arr);
    return 0;
}