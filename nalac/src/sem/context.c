//
// Created by Alex on 06/06/2024.
//

#include <string.h>
#include "../../include/sem/context.h"

idtypemap_p make_idtypemap(char* key, type_p value, idtypemap_p sptr, insertmode_t mode, bool owned) {
    idtypemap_p ptr = MALLOC(sizeof (*ptr));
    if (ptr) {
        ptr->key   = key;
        ptr->value = value;
        ptr->owned = owned;
        ptr->tail  = NULL;

        switch (mode) {
            case IM_FRONT:
                ptr->tail = sptr;
                return ptr;
            case IM_BACK:
                if (sptr) {
                    idtypemap_p tmp = sptr;
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

void free_idtypemap(idtypemap_p ptr) {
    if (ptr) {
        if (ptr->owned)
            free_type(ptr->value);

        free_idtypemap(ptr->tail);
        FREE          (ptr);
    }
}

contextfun_p make_contextfun(type_p type) {
    contextfun_p ptr = MALLOC(sizeof (*ptr));
    if (ptr) {
        ptr->type = type;
    }
    return ptr;
}

void free_contextfun(contextfun_p ptr) {
    if (ptr) {
        FREE(ptr);
    }
}

context_p  make_context(contextkind_t kind, context_p actx) {
    context_p ptr = MALLOC(sizeof (*ptr));
    if (ptr) {
        ptr->kind  = kind;
        ptr->above = actx;
    }
    return ptr;
}

context_p make_contextfun_context(contextfun_p cfun, idtypemap_p tmap, context_p actx) {
    context_p ptr = make_context(CK_FUN, actx);
    if (ptr) {
        ptr->cfun = cfun;
        ptr->tmap = tmap;
    }
    return ptr;
}

context_p make_contextprg_context(idtypemap_p tmap) {
    context_p ptr = make_context(CK_PRG, NULL);
    if (ptr) {
        ptr->tmap = tmap;
    }
    return ptr;
}

void free_context(context_p ptr) {
    if (ptr) {
        switch (ptr->kind) {
            case CK_FUN:
                free_contextfun(ptr->cfun);
                break;
            case CK_PRG:
                break;
        }
        free_idtypemap(ptr->tmap);
        FREE          (ptr);
    }
}

idtypemap_p get_context_type(char* key, context_p ctx) {
    context_p   currctx = ctx;
    idtypemap_p currmap = NULL;
    bool        flag    = TRUE;
    while (currctx && flag) {
        currmap = currctx->tmap;
        while (currmap && flag) {
            if (strcmp(currmap->key, key) == 0)
                flag = FALSE;
            else
                currmap = currmap->tail;
        }
        currctx = currctx->above;
    }

    return currmap;
}