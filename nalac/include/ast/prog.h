//
// Created by Alex on 30/04/2024.
//

#ifndef NALA_PROJECT_AST_PROGRAM_H
#define NALA_PROJECT_AST_PROGRAM_H

#include "decl.h"
#include "stmt.h"

#include "stdio.h"

typedef struct prog_s  prog_t;
typedef        prog_t* prog_p;
struct prog_s {
    decllist_p decllist;
    decl_p     main;
};

prog_p make_prog(decllist_p, decl_p);
void   free_prog(prog_p);

void make_prog_repr(prog_p, FILE*);

#endif
