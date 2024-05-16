//
// Created by Alex on 03/06/2024.
//

#ifndef NALA_PROJECT_IRC_SCOPE_H
#define NALA_PROJECT_IRC_SCOPE_H

#include "../common.h"

typedef struct varmap_s  varmap_t;
typedef        varmap_t* varmap_p;
struct varmap_s {
    char*    key;
    char*    value;
    varmap_p tail;
};

typedef enum scopekind_e scopekind_t;
enum scopekind_e {
    LOCAL, GLOBAL
};

typedef struct scope_s  scope_t;
typedef        scope_t* scope_p;
struct scope_s {
    scopekind_t kind;
    varmap_p    vmap;
    uint32_t    idx;
};

varmap_p make_varmap(char*, char*, varmap_p, insertmode_t mode);
varmap_p copy_varmap(varmap_p);
void     free_varmap(varmap_p);
varmap_p varmap_get (varmap_p, char*);

scope_p make_scope(scopekind_t, varmap_p);
void    free_scope(scope_p);

uint32_t scope_next_var(scope_p);

#endif
