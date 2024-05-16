//
// Created by Alex on 06/06/2024.
//

#ifndef NALA_PROJECT_SEM_DECL_H
#define NALA_PROJECT_SEM_DECL_H

#include "../../include/ast/decl.h"
#include "../../include/sem/context.h"

bool is_declvar_semvalid (declvar_p,  context_p, FILE*);
bool is_declfun_semvalid (declfun_p,  context_p, FILE*);
bool is_decl_semvalid    (decl_p,     context_p, FILE*);

bool is_decllist_semvalid(decllist_p, context_p, FILE*);

#endif
