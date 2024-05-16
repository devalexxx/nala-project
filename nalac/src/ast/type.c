#include "../../include/ast/type.h"

typepri_p make_typepri(prikind_t kind, uint8_t size) {
    typepri_p ptr = MALLOC(sizeof (*ptr));

    if (ptr) {
        ptr->kind = kind;
        ptr->size = size;
    }

    return ptr;
}

typepri_p copy_typepri(typepri_p other) {
    return make_typepri(other->kind, other->size);
}

bool comp_typepri(typepri_p lhs, typepri_p rhs) {
    if (lhs && rhs)
        return lhs->kind == rhs->kind && lhs->size == rhs->size;
    else
        return FALSE;
}

void free_typepri(typepri_p ptr) {
    if (ptr)
        FREE(ptr);
}

typefun_p make_typefun(type_p rtype, typelist_p typelist) {
    typefun_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->rtype    = rtype;
        ptr->typelist = typelist;
    }

    return ptr;
}

typefun_p copy_typefun(typefun_p other) {
    typefun_p ptr = make_typefun(NULL, NULL);

    if (ptr) {
        if (other->rtype)
            ptr->rtype = copy_type(other->rtype);

        if (other->typelist) {
            typelist_p typelist = NULL;
            typelist_p tmp      = other->typelist;
            while(tmp) {
                typelist = make_typelist(copy_type(tmp->type), typelist, IM_BACK);
                tmp = tmp->tail;
            }
            ptr->typelist = typelist;
        }
    }

    return ptr;
}

bool comp_typefun(typefun_p lhs, typefun_p rhs) {
    if (lhs && rhs)
        return comp_type(lhs->rtype, rhs->rtype) && comp_typelist(lhs->typelist, rhs->typelist);
    else
        return FALSE;
}

void free_typefun(typefun_p ptr) {
    if (ptr) {
        free_type    (ptr->rtype);
        free_typelist(ptr->typelist);
        FREE         (ptr);
    }
}

type_p make_type(typekind_t kind) {
    type_p ptr = MALLOC(sizeof(*ptr));

    if (ptr)
        ptr->kind = kind;

    return ptr;
}

type_p copy_type(type_p other) {
    type_p ptr = make_type(other->kind);

    if (ptr) {
        switch (other->kind) {
            case TK_PRI:
                ptr->typepri = copy_typepri(other->typepri);
                break;
            case TK_VOID:
                break;
            case TK_FUN:
                ptr->typefun = copy_typefun(other->typefun);
                break;
        }
    }

    return ptr;
}

// @TODO: strongest comparison
bool comp_type(type_p lhs, type_p rhs) {
    if (lhs && rhs) {
        if (lhs->kind == rhs->kind) {
            switch (lhs->kind) {
                case TK_PRI:
                    return comp_typepri(lhs->typepri, rhs->typepri);
                case TK_VOID:
                    return TRUE;
                case TK_FUN:
                    return comp_typefun(lhs->typefun, rhs->typefun);
            }
        }
    }
    return FALSE;
}

type_p make_typepri_type(typepri_p ptr) {
    type_p ret = make_type(TK_PRI);

    if (ptr) {
        ret->size    = ptr->size;
        ret->typepri = ptr;
    }

    return ret;
}

type_p make_typefun_type(typefun_p ptr) {
    type_p ret   = make_type(TK_FUN);

    if (ptr) {
        ret->size    = 8;
        ret->typefun = ptr;
    }

    return ret;
}

void free_type(type_p ptr) {
    if (ptr) {
        switch (ptr->kind) {
            case TK_PRI:
                free_typepri(ptr->typepri);
                break;
            case TK_FUN:
                free_typefun(ptr->typefun);
                break;
            case TK_VOID:
                break;
        }

        FREE(ptr);
    }
}

typelist_p make_typelist(type_p type, typelist_p list, insertmode_t mode) {
    typelist_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->type = type;
        ptr->tail = NULL;

        switch (mode) {
            case IM_FRONT:
                ptr->tail = list;
                return ptr;
            case IM_BACK:
                if (list) {
                    typelist_p tmp = list;
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

bool comp_typelist(typelist_p lhs, typelist_p rhs) {
    typelist_p lcurr = lhs;
    typelist_p rcurr = rhs;
    while (lcurr && rcurr) {
        if (!comp_type(lcurr->type, rcurr->type))
            return FALSE;

        lcurr = lcurr->tail;
        rcurr = rcurr->tail;
    }

    if (lcurr && !rcurr || rcurr && !lcurr)
        return FALSE;

    return TRUE;
}


void free_typelist(typelist_p ptr) {
    if (ptr) {
        free_type    (ptr->type);
        free_typelist(ptr->tail);
        FREE         (ptr);
    }
}