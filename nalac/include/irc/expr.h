//
// Created by Alex on 04/06/2024.
//

#ifndef NALA_PROJECT_IRC_EXPR_H
#define NALA_PROJECT_IRC_EXPR_H

#include "../../include/ast/expr.h"
#include "../../include/irc/scope.h"

typedef struct taclist_s  taclist_t;
typedef        taclist_t* taclist_p;
struct taclist_s {
    char*     lhs;
    char*     rhs;
    taclist_p tail;
};

// Rhs can't be NULL
taclist_p make_taclist(char*, char*, taclist_p, insertmode_t);
void      free_taclist(taclist_p);
taclist_p last_taclist(taclist_p);

void taclist_to_irc(taclist_p, char*, FILE*);

taclist_p expr_to_tac(expr_p, scope_p);


#endif
