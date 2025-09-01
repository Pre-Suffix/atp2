#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct num_e {
    double value;
    struct num_e *next;
};

typedef struct num_e Numbers;

/**
 * Allocates a number array
 */
Numbers *numalloc() {
    Numbers *nums = nullptr;
    nums = (Numbers *) calloc(1, sizeof(Numbers));
    
    if(nums != nullptr)
        nums->next = nullptr;

    return nums;
}

/**
 * Pushes a number to the end of the array
 */
int numpush(Numbers *arr, double value) {
    if(arr == nullptr) return 1;

    Numbers *elem = arr;
    while(elem->next != nullptr)
        elem = elem->next;
    
    elem->value = value;
    elem->next = numalloc();

    return (elem->next == nullptr);
}

/**
 * Pushes a number to the start of the array
 */
int numshift(Numbers **arr, double value) {
    if(arr == nullptr) return 1;

    Numbers *elem = numalloc();
    if(elem == nullptr) return 1;

    elem->value = value;
    elem->next = *arr;

    *arr = elem;

    return 0;
}

/**
 * Fetches a number from an array
 */
double numfetch(Numbers *arr, unsigned int index) {
    double ret = NAN;

    if(arr == nullptr) return ret;

    Numbers *elem = arr;
    for(int i = 0; i < index; i++) {
        if(elem->next == nullptr) return ret;

        elem = elem->next;
    }

    ret = elem->value;

    return ret;
}

/**
 * Prints an array to a FILE pointer
 */
void numprint(Numbers *arr, FILE *output) {
    if(output == nullptr) return;

    if(arr == nullptr) {
        fputs("[ ]\n", output);
        return;
    }

    fprintf(output, "[ ");
    Numbers *elem = arr;
    while(elem->next != nullptr) {
        fprintf(output, "%lf ", elem->value);
        elem = elem->next;
    }

    fputs("]\n", output);
} 