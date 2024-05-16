//
// Created by Alex on 15/05/2024.
//

#ifndef NALA_PROJECT_AST_TYPE_H
#define NALA_PROJECT_AST_TYPE_H

#include "stdio.h"

#include "../common.h"

typedef struct type_s  type_t;
typedef        type_t* type_p;

typedef struct typelist_s  typelist_t;
typedef        typelist_t* typelist_p;

typedef enum prikind_s  prikind_t;
enum prikind_s {
    PK_SIGNED, PK_UNSIGNED, PK_FLOATING_P
};

typedef struct typepri_s  typepri_t;
typedef        typepri_t* typepri_p;
struct typepri_s {
    prikind_t kind;
    uint8_t  size;
};

typedef struct typefun_s  typefun_t;
typedef        typefun_t* typefun_p;
struct typefun_s {
    type_p     rtype;
    typelist_p typelist;
};

typedef enum typekind_e typekind_t;
enum typekind_e {
    TK_PRI, TK_VOID, TK_FUN
};

struct type_s {
    typekind_t kind;
    uint32_t   size;
    union {
        typepri_p typepri;
        typefun_p typefun;
    };
};

struct typelist_s {
    type_p     type;
    typelist_p tail;
};

typepri_p make_typepri(prikind_t , uint8_t);
typepri_p copy_typepri(typepri_p);
bool      comp_typepri(typepri_p, typepri_p);
void      free_typepri(typepri_p);

typefun_p make_typefun(type_p , typelist_p);
typefun_p copy_typefun(typefun_p);
bool      comp_typefun(typefun_p, typefun_p);
void      free_typefun(typefun_p);

type_p make_type        (typekind_t);
type_p copy_type        (type_p);
bool   comp_type        (type_p, type_p);
type_p make_typepri_type(typepri_p);
type_p make_typefun_type(typefun_p);
void   free_type        (type_p);

typelist_p make_typelist(type_p, typelist_p, insertmode_t);
bool       comp_typelist(typelist_p, typelist_p);
void       free_typelist(typelist_p);

void make_type_repr    (type_p,     char*, FILE*);
void make_typelist_repr(typelist_p, char*, FILE*);

#endif
