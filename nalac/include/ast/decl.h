//
// Created by Alex on 15/05/2024.
//

#ifndef NALA_PROJECT_AST_DECL_H
#define NALA_PROJECT_AST_DECL_H

#include "stdio.h"

#include "../common.h"
#include "type.h"
#include "expr.h"
#include "stmt.h"

typedef struct decllist_s  decllist_t;
typedef        decllist_t* decllist_p;

typedef enum declkind_e declkind_t;
enum declkind_e {
    DK_VAR, DK_FUN
};

typedef struct declvar_s  declvar_t;
typedef        declvar_t* declvar_p;
struct declvar_s {
    str     id;
    type_p  type;
    expr_p  expr;
};

typedef struct param_s  param_t;
typedef        param_t* param_p;
struct param_s {
    str    id;
    type_p type;
};

typedef struct paramlist_s  paramlist_t;
typedef        paramlist_t* paramlist_p;
struct paramlist_s {
    param_p     param;
    paramlist_p tail;
};

typedef struct declfun_s  declfun_t;
typedef        declfun_t* declfun_p;
struct declfun_s {
    str         id;
    type_p      type;
    paramlist_p paramlist;
//    decllist_p  decllist;
    stmtlist_p  stmtlist;
};

typedef struct decl_s  decl_t;
typedef        decl_t* decl_p;
struct decl_s {
    declkind_t kind;
    union {
        declvar_p declvar;
        declfun_p declfun;
    };
};

struct decllist_s {
    decl_p     decl;
    decllist_p tail;
};

param_p make_param(str, type_p);
void    free_param(param_p);

paramlist_p make_paramlist(param_p, paramlist_p, insertmode_t);
void        free_paramlist(paramlist_p);

declvar_p make_declvar(str, type_p, expr_p);
void      free_declvar(declvar_p);

declfun_p make_declfun(str, type_p, paramlist_p, stmtlist_p);
void      free_declfun(declfun_p);

decl_p make_declvar_decl(declvar_p);
decl_p make_declfun_decl(declfun_p);
void   free_decl        (decl_p);

decllist_p make_decllist(decl_p, decllist_p, insertmode_t);
void       free_decllist(decllist_p);

void make_decl_repr    (decl_p,     char*, FILE*);
void make_decllist_repr(decllist_p, char*, FILE*);

#endif
