//
// Created by Alex on 15/05/2024.
//

#include "../include/common.h"

#include <stdio.h>
#include <string.h>

int allocated_ptr = 0, freed_ptr = 0;

void* r_malloc(size_t size) {
    void* ptr = malloc(size);

    if (ptr)
        allocated_ptr += 1;
    else
        fprintf(stderr, "Heap allocation failed.");

    return ptr;
}

void r_free(void* ptr) {
    if (ptr) {
        freed_ptr++;
        free(ptr);
    }
    else
        fprintf(stderr, "Trying to free NULL pointer.");
}

void r_strcat(str_p dest, char* const src) {
    str tmp = REALLOC(*dest, (strlen(*dest) + strlen(src) + 1) * sizeof(**dest));

    if (tmp) {
        *dest = tmp;
        strcat(*dest, src);
    }
    else
        fprintf(stderr, "Heap reallocation failed on r_strcat.");
}

str r_strdup(char* const src) {
    str ptr = NULL;

    if (src) {
        ptr = MALLOC(strlen(src) + 1);
        if (ptr)
            strcpy(ptr, src);
        else
            fprintf(stderr, "Heap allocation failed on r_strdup.");
    }
    else
        fprintf(stderr, "Trying to duplication NULL pointer on r_strdup.");

    return ptr;
}

void print_heap_history(void) {
    fprintf(stderr, "Heap history:\n\talloc:\t%d\n\tfree:\t%d\n", allocated_ptr, freed_ptr);
}