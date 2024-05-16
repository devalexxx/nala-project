//
// Created by Alex on 04/06/2024.
//

#include "../../include/irc/stmt.h"
#include "../../include/irc/decl.h"
#include "../../include/irc/expr.h"
#include "../../include/irc/common.h"

void internal_make_assign_irc(char* const id, expr_p rhs, scope_p scope, char* const prefix, FILE* fp) {
    char lhs[100];

    varmap_p vmap = varmap_get(scope->vmap, id);
    if (vmap) {
        sprintf(lhs, "%s", vmap->value);
    }
    else {
        sprintf(lhs, "!!(id not found)");
    }

    taclist_p tacs = expr_to_tac(rhs, scope);
    taclist_to_irc(tacs, prefix, fp);

    fprintf(fp, "%s%s %s %s\n", prefix, OP_STR, last_taclist(tacs)->lhs, lhs);

    free_taclist(tacs);
}

void make_assign_irc(assign_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    if (ptr) {
        if (ptr->left->kind == EK_IDEN) {
            internal_make_assign_irc(ptr->left->id, ptr->right, scope, prefix, fp);
        }
    }
}

void make_return_irc(return_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    if (ptr) {
        taclist_p tacs = expr_to_tac(ptr->expr, scope);
        taclist_to_irc(tacs, prefix, fp);

        fprintf(fp, "%s%s %s\n", prefix, OP_RET, last_taclist(tacs)->lhs);

        free_taclist(tacs);
    }
}

void make_expr_irc(expr_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    if (ptr) {
        taclist_p tacs = expr_to_tac(ptr, scope);
        scope->idx--;

        taclist_p ltac = NULL;
        taclist_p curr = tacs;
        if (curr->tail) {
            while (curr->tail->tail) {
                curr = curr->tail;
            }
            ltac       = curr->tail;
            curr->tail = NULL;
            taclist_to_irc(tacs, prefix, fp);
            curr->tail = ltac;
        }
        else {
            ltac = curr;
        }

        fprintf(fp, "%s%s\n", prefix, ltac->rhs);

        free_taclist(tacs);
    }
}

void make_stmt_irc(stmt_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    if (ptr) {
        switch (ptr->kind) {
            case SK_ASSIGN:
                make_assign_irc(ptr->assign, scope, prefix, fp);
                break;
            case SK_RETURN:
                make_return_irc(ptr->ret, scope, prefix, fp);
                break;
            case SK_DECL:
                make_decl_irc(ptr->decl, scope, prefix, fp);
                break;
            case SK_EXPR:
                make_expr_irc(ptr->expr, scope, prefix, fp);
                break;
        }
    }
}

void make_stmtlist_irc(stmtlist_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    stmtlist_p curr   = ptr;
    while (curr) {
        make_stmt_irc(curr->stmt, scope, prefix, fp);
        curr = curr->tail;
    }
}