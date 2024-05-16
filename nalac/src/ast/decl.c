#include "../../include/ast/decl.h"

param_p make_param(str id, type_p type) {
    param_p ptr = MALLOC(sizeof (*ptr));

    if (ptr) {
        ptr->id     = id;
        ptr->type   = type;
    }

    return ptr;
}

void free_param(param_p ptr) {
    if (ptr) {
        FREE     (ptr->id);
        free_type(ptr->type);
        FREE     (ptr);
    }
}

paramlist_p make_paramlist(param_p param, paramlist_p list, insertmode_t mode) {
    paramlist_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->param = param;
        ptr->tail  = NULL;

        switch (mode) {
            case IM_FRONT:
                ptr->tail = list;
                return ptr;
            case IM_BACK:
                if (list) {
                    paramlist_p tmp = list;
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

void free_paramlist(paramlist_p ptr) {
    if (ptr) {
        free_param    (ptr->param);
        free_paramlist(ptr->tail);
        FREE          (ptr);
    }
}

declvar_p make_declvar(str id, type_p type, expr_p expr) {
    declvar_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->id       = id;
        ptr->type     = type;
        ptr->expr     = expr;
    }

    return ptr;
}

void free_declvar(declvar_p ptr) {
    if (ptr) {
        FREE     (ptr->id);
        free_type(ptr->type);
        free_expr(ptr->expr);
        FREE     (ptr);
    }
}

declfun_p make_declfun(str id, type_p rtype, paramlist_p paramlist, stmtlist_p stmtlist) {
    declfun_p ptr  = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->id = id;

        typelist_p  typelist = NULL;
        paramlist_p tmp      = paramlist;
        while(tmp) {
            typelist = make_typelist(copy_type(tmp->param->type), typelist, IM_BACK);
            tmp      = tmp->tail;
        }
        ptr->type      = make_typefun_type(make_typefun(rtype, typelist));
        ptr->paramlist = paramlist;
        ptr->stmtlist  = stmtlist;
    }

    return ptr;
}

void free_declfun(declfun_p ptr) {
    if (ptr) {
        FREE          (ptr->id);
        free_type     (ptr->type);
        free_paramlist(ptr->paramlist);
        free_stmtlist (ptr->stmtlist);
        FREE          (ptr);
    }
}

decl_p make_decl(declkind_t kind) {
    decl_p ptr = MALLOC(sizeof(*ptr));

    if (ptr)
        ptr->kind  = kind;

    return ptr;
}

decl_p make_declvar_decl(declvar_p vptr) {
    decl_p ptr   = make_decl(DK_VAR);

    if (ptr)
        ptr->declvar = vptr;

    return ptr;
}

decl_p make_declfun_decl(declfun_p fptr) {
    decl_p ptr   = make_decl(DK_FUN);

    if (ptr)
        ptr->declfun = fptr;

    return ptr;
}

void free_decl(decl_p ptr) {
    if (ptr) {
        switch(ptr->kind) {
            case DK_VAR:
                free_declvar(ptr->declvar);
                break;
            case DK_FUN:
                free_declfun(ptr->declfun);
                break;
        }

        FREE(ptr);
    }
}

decllist_p make_decllist(decl_p decl, decllist_p list, insertmode_t mode) {
    decllist_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->decl = decl;
        ptr->tail = NULL;

        switch (mode) {
            case IM_FRONT:
                ptr->tail = list;
                return ptr;
            case IM_BACK:
                if (list) {
                    decllist_p tmp = list;
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

void free_decllist(decllist_p ptr) {
    if (ptr) {
        free_decl    (ptr->decl);
        free_decllist(ptr->tail);
        FREE         (ptr);
    }
}