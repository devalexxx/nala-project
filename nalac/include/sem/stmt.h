//
// Created by Alex on 06/06/2024.
//

#ifndef NALA_PROJECT_SEM_STMT_H
#define NALA_PROJECT_SEM_STMT_H

#include "../../include/ast/stmt.h"
#include "../../include/sem/context.h"

bool internal_is_assign_semvalid(char*, expr_p, context_p, FILE*);

bool is_assign_semvalid  (assign_p,   context_p, FILE*);
bool is_return_semvalid  (return_p,   context_p, FILE*);
bool is_stmt_semvalid    (stmt_p,     context_p, FILE*);
bool is_stmtlist_semvalid(stmtlist_p, context_p, FILE*);

#endif
