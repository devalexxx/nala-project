//
// Created by Alex on 04/06/2024.
//

#include <string.h>
#include "../../include/irc/expr.h"
#include "../../include/irc/common.h"

taclist_p make_taclist(char* lhs, char* rhs, taclist_p sptr, insertmode_t mode) {
    taclist_p ptr = MALLOC(sizeof (*ptr));
    if (ptr) {
        ptr->lhs  = lhs;
        ptr->rhs  = rhs;
        ptr->tail = NULL;

        switch (mode) {
            case IM_FRONT:
                ptr->tail = sptr;
                return ptr;
            case IM_BACK:
                if (sptr) {
                    taclist_p tmp = sptr;
                    while (tmp->tail) {
                        tmp = tmp->tail;
                    }
                    tmp->tail = ptr;
                }
                else
                    sptr = ptr;
                break;
        }
    }
    return sptr;
}

void free_taclist(taclist_p ptr) {
    if (ptr) {
        FREE        (ptr->lhs);
        FREE        (ptr->rhs);
        free_taclist(ptr->tail);
        FREE        (ptr);
    }
}

taclist_p last_taclist(taclist_p ptr) {
    taclist_p curr = ptr;
    while (curr->tail) {
        curr = curr->tail;
    }
    return curr;
}

void taclist_to_irc(taclist_p ptr, char* const prefix, FILE* fp) {
    taclist_p curr = ptr;
    while (curr) {
        fprintf(fp, "%s%s = %s\n", prefix, curr->lhs, curr->rhs);
        curr = curr->tail;
    }
}

char* op_as_irc(op_t op) {
    switch (op) {
        case ADD:
            return OP_ADD;
        case SUB:
            return OP_SUB;
        case MUL:
            return OP_MUL;
        case DIV:
            return OP_DIV;
    }
}

void internal_expr_to_tac(expr_p ptr, scope_p scope, taclist_p* tacs) {
    char lhs[100];
    char rhs[100];

    varmap_p vtmp = NULL;

    if (ptr) {
        switch (ptr->kind) {
            case EK_IDEN:
                sprintf(lhs, "%s%d", LOC_PREFIX, scope_next_var(scope));

                if ((vtmp = varmap_get(scope->vmap, ptr->id)))
                    sprintf(rhs, "%s %s", OP_LDR, vtmp->value);
                else
                    sprintf(rhs, "!!(id not found)");
                break;
            case EK_LINT:
                sprintf(lhs, "%s%d", LOC_PREFIX, scope_next_var(scope));
                sprintf(rhs, "%s #%d", OP_LDR, ptr->ival);
                break;
            case EK_LREL:
                sprintf(lhs, "%s%d", LOC_PREFIX, scope_next_var(scope));
                sprintf(rhs, "%s #%f", OP_LDR, ptr->rval);
                break;
            case EK_LCHR:
                sprintf(lhs, "%s%d", LOC_PREFIX, scope_next_var(scope));
                sprintf(rhs, "%s #%c", OP_LDR, ptr->cval);
                break;
            case EK_LSTR:
                // @TODO
                break;
            case EK_UNAR:
                internal_expr_to_tac(ptr->unary->expr, scope, tacs);
                sprintf(lhs, "%s%d", LOC_PREFIX, scope_next_var(scope));
                sprintf(rhs, "%s %s", op_as_irc(ptr->unary->op), last_taclist(*tacs)->lhs);
                break;
            case EK_BINA:
                internal_expr_to_tac(ptr->binary->left, scope, tacs);
                sprintf(rhs, "%s %s", op_as_irc(ptr->binary->op), last_taclist(*tacs)->lhs);
                internal_expr_to_tac(ptr->binary->right, scope, tacs);
                sprintf(lhs, "%s%d", LOC_PREFIX, scope_next_var(scope));
                sprintf(rhs + strlen(rhs), " %s", last_taclist(*tacs)->lhs);
                break;
            case EK_CALL:
                vtmp = varmap_get(scope->vmap, ptr->call->expr->id);
                if (vtmp)
                    sprintf(rhs, "%s %s ", OP_CALL, vtmp->value);
                else
                    sprintf(rhs, "%s !!(id not found) ", OP_CALL);

                exprlist_p curr = ptr->call->args;
                while (curr) {
                    internal_expr_to_tac(curr->expr, scope, tacs);
                    sprintf(rhs + strlen(rhs), "%s ", last_taclist(*tacs)->lhs);
                    curr = curr->tail;
                }

                sprintf(lhs, "%s%d", LOC_PREFIX, scope_next_var(scope));

                break;
        }
        *tacs = make_taclist(r_strdup(lhs), r_strdup(rhs), *tacs, IM_BACK);
    }
}

taclist_p expr_to_tac(expr_p ptr, scope_p scope) {
    taclist_p tacs = NULL;
    internal_expr_to_tac(ptr, scope, &tacs);
    return tacs;
}