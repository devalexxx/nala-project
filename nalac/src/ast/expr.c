#include "../../include/ast/expr.h"

unary_p make_unary(op_t op, expr_p expr) {
    unary_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->op     = op;
        ptr->expr   = expr;
    }

    return ptr;
}

void free_unary(unary_p ptr) {
    if (ptr) {
        free_expr(ptr->expr);
        FREE     (ptr);
    }
}

binary_p make_binary(op_t op, expr_p left, expr_p right) {
    binary_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->op      = op;
        ptr->left    = left;
        ptr->right   = right;
    }

    return ptr;
}

void free_binary(binary_p ptr) {
    if (ptr) {
        free_expr(ptr->left);
        free_expr(ptr->right);
        FREE     (ptr);
    }
}

call_p make_call(expr_p expr, exprlist_p args) {
    call_p ptr = MALLOC(sizeof (*ptr));
    if (ptr) {
        ptr->expr = expr;
        ptr->args = args;
    }
    return ptr;
}

void free_call(call_p ptr) {
    if (ptr) {
        free_expr    (ptr->expr);
        free_exprlist(ptr->args);
        FREE         (ptr);
    }
}

expr_p make_expr(exprkind_t kind) {
    expr_p ptr = MALLOC(sizeof(*ptr));

    if (ptr)
        ptr->kind = kind;

    return ptr;
}

expr_p make_iden_expr(str id) {
    expr_p ptr = make_expr(EK_IDEN);

    if (ptr)
        ptr->id = id;

    return ptr;
}

expr_p make_lstr_expr(str sval) {
    expr_p ptr = make_expr(EK_LSTR);

    if (ptr)
        ptr->sval = sval;

    return ptr;
}

expr_p make_lint_expr(int ival) {
    expr_p ptr = make_expr(EK_LINT);

    if (ptr)
        ptr->ival = ival;

    return ptr;
}

expr_p make_lrel_expr(double rval) {
    expr_p ptr = make_expr(EK_LREL);

    if (ptr)
        ptr->rval = rval;

    return ptr;
}

expr_p make_lchr_expr(char cval) {
    expr_p ptr = make_expr(EK_LCHR);

    if (ptr)
        ptr->cval  = cval;

    return ptr;
}

expr_p make_unary_expr(unary_p unary) {
    expr_p ptr = make_expr(EK_UNAR);

    if (ptr)
        ptr->unary = unary;

    return ptr;
}

expr_p make_binary_expr(binary_p binary) {
    expr_p ptr = make_expr(EK_BINA);

    if (ptr)
        ptr->binary= binary;

    return ptr;
}

expr_p make_call_expr(call_p call) {
    expr_p ptr = make_expr(EK_CALL);

    if (ptr)
        ptr->call = call;

    return ptr;
}

void free_expr(expr_p ptr) {
    if (ptr) {
        switch (ptr->kind) {
            case EK_IDEN:
                FREE(ptr->id);
                break;
            case EK_UNAR:
                free_unary(ptr->unary);
                break;
            case EK_BINA:
                free_binary(ptr->binary);
                break;
            case EK_CALL:
                free_call(ptr->call);
                break;
            case EK_LSTR:
                FREE(ptr->sval);
                break;
            case EK_LINT:
            case EK_LREL:
            case EK_LCHR:
                break;
        };

        FREE(ptr);
    }
}

exprlist_p make_exprlist(expr_p expr, exprlist_p list, insertmode_t mode) {
    exprlist_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->expr = expr;
        ptr->tail = NULL;

        switch (mode) {
            case IM_FRONT:
                ptr->tail = list;
                return ptr;
            case IM_BACK:
                if (list) {
                    exprlist_p tmp = list;
                    while (tmp->tail) {
                        tmp = tmp->tail;
                    }
                    tmp->tail = ptr;
                }
                else
                    list = ptr;

                break;
        }
    }

    return list;
}

void free_exprlist(exprlist_p ptr) {
    if (ptr) {
        free_expr    (ptr->expr);
        free_exprlist(ptr->tail);
        FREE         (ptr);
    }
}