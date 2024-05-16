//
// Created by Alex on 06/06/2024.
//

#ifndef NALA_PROJECT_SEM_CONTEXT_H
#define NALA_PROJECT_SEM_CONTEXT_H

#include "../../include/ast/type.h"

typedef enum contextkind_e contextkind_t;
enum contextkind_e {
    CK_PRG, CK_FUN
};

typedef struct idtypemap_s  idtypemap_t;
typedef        idtypemap_t* idtypemap_p;
struct idtypemap_s {
    char*       key;
    type_p      value;
    bool        owned;
    idtypemap_p tail;
};

typedef struct contextfun_s  contextfun_t;
typedef        contextfun_t* contextfun_p;
struct contextfun_s {
    type_p      type;
};

typedef struct context_s  context_t;
typedef        context_t* context_p;
struct context_s {
    contextkind_t kind;
    contextfun_p  cfun;
    idtypemap_p   tmap;
    context_p     above;
};

idtypemap_p make_idtypemap(char*, type_p, idtypemap_p, insertmode_t, bool);
void        free_idtypemap(idtypemap_p);

contextfun_p make_contextfun(type_p);
void         free_contextfun(contextfun_p);

context_p make_contextfun_context(contextfun_p, idtypemap_p, context_p);
context_p make_contextprg_context(idtypemap_p);
void      free_context           (context_p);

idtypemap_p get_context_type(char*, context_p);

#endif
