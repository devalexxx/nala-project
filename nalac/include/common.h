//
// Created by Alex on 15/05/2024.
//

#ifndef NALA_PROJECT_COMMON_H
#define NALA_PROJECT_COMMON_H

#include <stdlib.h>
#include <stdint.h>

#define TRUE  1
#define FALSE 0

#define MALLOC  r_malloc
#define FREE    r_free
#define REALLOC realloc

typedef uint8_t bool;

void* r_malloc(size_t size);
void  r_free  (void* ptr);

typedef char*  str;
typedef char** str_p;

typedef enum insertmode_e insertmode_t;
enum insertmode_e {
    IM_FRONT, IM_BACK
};

void r_strcat(str_p, char*);
str  r_strdup(char*);

void print_heap_history(void);

#endif
