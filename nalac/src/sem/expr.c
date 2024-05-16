//
// Created by Alex on 06/06/2024.
//

#include "../../include/sem/expr.h"

bool is_expr_semvalid(expr_p ptr, context_p cntx, FILE* fp) {
    if (ptr) {
        idtypemap_p tmap = NULL;
        typelist_p  tlst = NULL;
        exprlist_p  elst = NULL;
        type_p      lhs  = NULL;
        type_p      rhs  = NULL;
        bool        flag = FALSE;

        switch (ptr->kind) {
            case EK_IDEN:
                tmap = get_context_type(ptr->id, cntx);
                if (tmap)
                    return TRUE;
                else
                    fprintf(fp, "BadExpression: Identifier out of scope.");
                break;
            case EK_UNAR:
                return is_expr_semvalid(ptr->unary->expr, cntx, fp);
            case EK_BINA:
                if (is_expr_semvalid(ptr->binary->left, cntx, fp) && is_expr_semvalid(ptr->binary->right, cntx, fp)) {
                    lhs = infer_expr_type(ptr->binary->left,  cntx, fp);
                    rhs = infer_expr_type(ptr->binary->right, cntx, fp);
                    if (comp_type(lhs, rhs))
                        flag = TRUE;
                    else
                        fprintf(fp, "TypeError: You can't use op on different types.");

                    free_type(lhs);
                    free_type(rhs);
                }

                return flag;
            case EK_CALL:
                elst = ptr->call->args;
                while (elst) {
                    tlst = make_typelist(infer_expr_type(elst->expr, cntx, fp), tlst, IM_BACK);
                    elst = elst->tail;
                }

                if (ptr->call->expr->kind == EK_IDEN) {
                    tmap = get_context_type(ptr->call->expr->id, cntx);
                    if (tmap) {
                        if (tmap->value->kind == TK_FUN) {
                            if (comp_typelist(tlst, tmap->value->typefun->typelist))
                                flag = TRUE;
                            else
                                fprintf(fp, "TypeError: Given call argument must match function signature.\n");
                        }
                        else
                            fprintf(fp, "TypeError: %s is not a callable.\n", ptr->call->expr->id);
                    }
                    else
                        fprintf(fp, "Identifier %s not in scope.\n", ptr->call->expr->id);
                }
                else
                    fprintf(fp, "Call expression callable must be an identifier (eg. variable name).\n");

                free_typelist(tlst);

                return flag;
            case EK_LINT:
            case EK_LREL:
            case EK_LCHR:
            case EK_LSTR:
                return TRUE;
        }
    }
    return FALSE;
}

void internal_infer_expr_type(expr_p ptr, typelist_p* list, context_p cntx, FILE* fp) {
    if (ptr) {
        idtypemap_p tmap = NULL;

        switch (ptr->kind) {
            case EK_IDEN:
                tmap = get_context_type(ptr->id, cntx);
                if (tmap) {
                    *list = make_typelist(copy_type(tmap->value), *list, IM_BACK);
                }
                break;
            case EK_UNAR:
                internal_infer_expr_type(ptr->unary->expr, list, cntx, fp);
                break;
            case EK_BINA:
                internal_infer_expr_type(ptr->binary->left,  list, cntx, fp);
                internal_infer_expr_type(ptr->binary->right, list, cntx, fp);
                break;
            case EK_LINT:
                *list = make_typelist(make_typepri_type(make_typepri(PK_SIGNED,     4)), *list, IM_BACK);
                break;
            case EK_LREL:
                *list = make_typelist(make_typepri_type(make_typepri(PK_FLOATING_P, 4)), *list, IM_BACK);
                break;
            case EK_LCHR:
                *list = make_typelist(make_typepri_type(make_typepri(PK_UNSIGNED  , 4)), *list, IM_BACK);
                break;
            case EK_LSTR:
                break;
            case EK_CALL:
                tmap = get_context_type(ptr->call->expr->id, cntx);
                if (tmap) {
                    if (tmap->value->kind == TK_FUN) {
                        *list = make_typelist(copy_type(tmap->value->typefun->rtype), *list, IM_BACK);
                    }
                    else {
                        fprintf(fp, "InternalError: This error should not append (internal_infer_expr_type->EK_CALL).");
                    }
                }
                break;
        }
    }
}

type_p infer_expr_type(expr_p ptr, context_p cntx, FILE* fp) {
    type_p ret = NULL;

    if (ptr) {
        typelist_p list = NULL;
        internal_infer_expr_type(ptr, &list, cntx, fp);

        if (list) {
            typelist_p lcurr = list;
            type_p     tcurr = NULL;
            bool       flag  = TRUE;
            while (lcurr && flag) {
                if (tcurr) {
                    if (!comp_type(tcurr, lcurr->type))
                        flag = FALSE;
                }

                tcurr = lcurr->type;
                lcurr = lcurr->tail;
            }

            if (flag)
                ret = copy_type(list->type);

            free_typelist(list);
        }
        else
            fprintf(fp, "Unexpected error: list null in infer_expr_type");
    }

    return ret;
}