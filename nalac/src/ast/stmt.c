#include "../../include/ast/expr.h"
#include "../../include/ast/stmt.h"
#include "../../include/ast/decl.h"

assign_p make_assign(expr_p left, expr_p right) {
    assign_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->left    = left;
        ptr->right   = right;
    }

    return ptr;
}

void free_assign(assign_p ptr) {
    if (ptr) {
        free_expr(ptr->left);
        free_expr(ptr->right);
        FREE     (ptr);
    }
}

return_p make_return(expr_p expr) {
    return_p ptr = MALLOC(sizeof(*ptr));

    if (ptr)
        ptr->expr = expr;

    return ptr;
}

void free_return(return_p ptr) {
    if (ptr) {
        free_expr(ptr->expr);
        FREE     (ptr);
    }
}

stmt_p make_stmt(stmtkind_t kind) {
    stmt_p ptr = MALLOC(sizeof(*ptr));

    if (ptr)
        ptr->kind = kind;

    return ptr;
}

stmt_p make_assign_stmt(assign_p assign) {
    stmt_p ptr = make_stmt(SK_ASSIGN);

    if (ptr)
        ptr->assign = assign;

    return ptr;
}

stmt_p make_return_stmt(return_p ret) {
    stmt_p ptr = make_stmt(SK_RETURN);

    if (ptr)
        ptr->ret = ret;

    return ptr;
}

stmt_p make_decl_stmt(decl_p decl) {
    stmt_p ptr = make_stmt(SK_DECL);

    if (ptr)
        ptr->decl = decl;

    return ptr;
}

stmt_p make_expr_stmt(expr_p expr) {
    stmt_p ptr = make_stmt(SK_EXPR);

    if (ptr)
        ptr->expr = expr;

    return ptr;
}

void free_stmt(stmt_p ptr) {
    if (ptr) {
        switch (ptr->kind) {
            case SK_ASSIGN:
                free_assign(ptr->assign);
                break;
            case SK_RETURN:
                free_return(ptr->ret);
                break;
            case SK_DECL:
                free_decl  (ptr->decl);
                break;
            case SK_EXPR:
                free_expr  (ptr->expr);
                break;
        }

        FREE(ptr);
    }
}

stmtlist_p make_stmtlist(stmt_p stmt, stmtlist_p list, insertmode_t mode) {
    stmtlist_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->stmt = stmt;
        ptr->tail = NULL;

        switch (mode) {
            case IM_FRONT:
                ptr->tail = list;
                return ptr;
            case IM_BACK:
                if (list) {
                    stmtlist_p tmp = list;
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

void free_stmtlist(stmtlist_p ptr) {
    if (ptr) {
        free_stmt    (ptr->stmt);
        free_stmtlist(ptr->tail);
        FREE         (ptr);
    }
}