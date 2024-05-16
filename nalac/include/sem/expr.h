//
// Created by Alex on 06/06/2024.
//

#ifndef NALA_PROJECT_SEM_EXPR_H
#define NALA_PROJECT_SEM_EXPR_H

#include "../../include/ast/expr.h"
#include "../../include/ast/type.h"
#include "../../include/sem/context.h"

bool is_expr_semvalid(expr_p, context_p, FILE*);

type_p infer_expr_type(expr_p, context_p, FILE*);

#endif
