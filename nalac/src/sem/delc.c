//
// Created by Alex on 06/06/2024.
//

#include "../../include/sem/decl.h"
#include "../../include/sem/stmt.h"

bool is_declvar_semvalid(declvar_p ptr, context_p cntx, FILE* fp) {
    if (ptr) {
        cntx->tmap = make_idtypemap(ptr->id, ptr->type, cntx->tmap, IM_BACK, FALSE);

        if (ptr->expr) {
            return internal_is_assign_semvalid(ptr->id, ptr->expr, cntx, fp);
        }
        return TRUE;
    }
    return FALSE;
}

bool is_declfun_semvalid(declfun_p ptr, context_p cntx, FILE* fp) {
    bool flag = TRUE;
    if (ptr) {
        cntx->tmap = make_idtypemap(ptr->id, ptr->type, cntx->tmap, IM_BACK, FALSE);

        contextfun_p cntxfun  = make_contextfun        (ptr->type);
        context_p    new_cntx = make_contextfun_context(cntxfun, NULL, cntx);

        paramlist_p lcurr = ptr->paramlist;
        while (lcurr) {
            cntx->tmap = make_idtypemap(lcurr->param->id, lcurr->param->type, cntx->tmap, IM_BACK, FALSE);
            lcurr = lcurr->tail;
        }

        if (!is_stmtlist_semvalid(ptr->stmtlist, new_cntx, fp))
            flag = FALSE;

        free_context(new_cntx);
    }
    return flag;
}

bool is_decl_semvalid(decl_p ptr, context_p cntx, FILE* fp) {
    if (ptr) {
        switch (ptr->kind) {
            case DK_VAR:
                return is_declvar_semvalid(ptr->declvar, cntx, fp);
            case DK_FUN:
                return is_declfun_semvalid(ptr->declfun, cntx, fp);
        }
    }
    return FALSE;
}

bool is_decllist_semvalid(decllist_p ptr, context_p cntx, FILE* fp) {
    bool       flag = TRUE;
    decllist_p curr = ptr;
    while (curr) {
        if (!is_decl_semvalid(curr->decl, cntx, fp))
            flag = FALSE;
        curr = curr->tail;
    }
    return flag;
}