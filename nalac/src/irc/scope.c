//
// Created by Alex on 03/06/2024.
//

#include "../../include/irc/scope.h"
#include <string.h>
#include <printf.h>

varmap_p make_varmap(char* key, char* value, varmap_p sptr, insertmode_t mode) {
    varmap_p ptr = MALLOC(sizeof (*ptr));
    if (ptr) {
        ptr->key   = key;
        ptr->value = value;
        ptr->tail  = NULL;

        switch (mode) {
            case IM_FRONT:
                ptr->tail = sptr;
                return ptr;
            case IM_BACK:
                if (sptr) {
                    varmap_p tmp = sptr;
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

varmap_p copy_varmap(varmap_p sptr) {
    varmap_p ptr  = NULL;
    varmap_p curr = sptr;
    while (curr) {
        ptr  = make_varmap(r_strdup(curr->key), r_strdup(curr->value), ptr, IM_BACK);
        curr = curr->tail;
    }

    return ptr;
}

void free_varmap(varmap_p ptr) {
    if (ptr) {
        FREE      (ptr->key);
        FREE      (ptr->value);
        free_varmap(ptr->tail);
        FREE      (ptr);
    }
}

varmap_p varmap_get(varmap_p ptr, char* key) {
    varmap_p curr = ptr;
    while (curr && strcmp(curr->key, key) != 0) {
        curr = curr->tail;
    }
    return curr;
}

scope_p make_scope(scopekind_t kind, varmap_p vmap) {
    scope_p ptr = MALLOC(sizeof (*ptr));
    if (ptr) {
        ptr->kind = kind;
        ptr->vmap = vmap;
        ptr->idx  = 0;
    }
    return ptr;
}

void free_scope(scope_p ptr) {
    if (ptr) {
        free_varmap(ptr->vmap);
        FREE       (ptr);
    }
}

uint32_t scope_next_var(scope_p ptr) {
    return ++ptr->idx;
}