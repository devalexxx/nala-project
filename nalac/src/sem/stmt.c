//
// Created by Alex on 06/06/2024.
//

#include "../../include/sem/stmt.h"
#include "../../include/sem/decl.h"
#include "../../include/sem/expr.h"

bool internal_is_assign_semvalid(char* const lhs, expr_p rhs, context_p cntx, FILE* fp) {
    bool flag = FALSE;

    idtypemap_p map = get_context_type(lhs, cntx);
    if (map) {
        if (is_expr_semvalid(rhs, cntx, fp)) {
            type_p exprtype = infer_expr_type(rhs, cntx, fp);
            if (exprtype) {
                if (comp_type(map->value, exprtype)) {
                    flag = TRUE;
                }
                else {
                    fprintf(fp, "TypeError: rhs type can't be assigned to lhs type.\n");
                }

                free_type(exprtype);
            }
            else {
                fprintf(fp, "Could not infer expression type.\n");
            }
        }
    }
    else {
        fprintf(fp, "Identifier %s not in scope.\n", lhs);
    }
    return flag;
}

bool is_assign_semvalid(assign_p ptr, context_p cntx, FILE* fp) {
    if (ptr) {
        if (ptr->left->kind == EK_IDEN) {
            return internal_is_assign_semvalid(ptr->left->id, ptr->right, cntx, fp);
        }
        else {
            fprintf(fp, "Assignement left expression must be an identifier (eg. variable name).\n");
        }
    }
    return FALSE;
}

bool is_return_semvalid(return_p ptr, context_p cntx, FILE* fp) {
    bool flag = FALSE;

    if (ptr) {
        if (cntx->kind == CK_FUN) {
            if (is_expr_semvalid(ptr->expr, cntx, fp)) {
                type_p exprtype = infer_expr_type(ptr->expr, cntx, fp);
                if (exprtype) {
                    if (comp_type(cntx->cfun->type->typefun->rtype, exprtype))
                        flag = TRUE;
                    else
                        fprintf(fp, "TypeError: Return expression type must match the function return type.\n");

                    free_type(exprtype);
                }
                else {
                    fprintf(fp, "Could not infer expression type.\n");
                }
            }
        }
        else
            fprintf(fp, "SyntaxError: You can't return something outsite a function declaration.\n");
    }
    return flag;
}

bool is_stmt_semvalid(stmt_p ptr, context_p cntx, FILE* fp) {
    if (ptr) {
        switch (ptr->kind) {
            case SK_ASSIGN:
                return is_assign_semvalid(ptr->assign, cntx, fp);
            case SK_RETURN:
                return is_return_semvalid(ptr->ret,    cntx, fp);
            case SK_DECL:
                return is_decl_semvalid  (ptr->decl,   cntx, fp);
            case SK_EXPR:
                return is_expr_semvalid  (ptr->expr,   cntx, fp);
        }
    }
    return FALSE;
}

bool is_stmtlist_semvalid(stmtlist_p ptr, context_p cntx, FILE* fp) {
    bool       flag = TRUE;
    stmtlist_p curr = ptr;
    while (curr) {
        if (!is_stmt_semvalid(curr->stmt, cntx, fp))
            flag = FALSE;
        curr = curr->tail;
    }
    return flag;
}