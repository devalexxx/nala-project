//
// Created by Alex on 03/06/2024.
//

#include "../../include/irc/decl.h"
#include "../../include/irc/common.h"
#include "../../include/irc/stmt.h"

#include <string.h>

void internal_make_local_declvar_irc(char* const id, type_p type, expr_p expr, scope_p scope, char* const prefix, FILE* fp) {
    char pid[100];
    sprintf(pid, "%s%d", LOC_PREFIX, scope_next_var(scope));

    scope->vmap = make_varmap(r_strdup(id), r_strdup(pid), scope->vmap, IM_BACK);

    fprintf(fp, "%s%s = %s %d\n", prefix, pid, STACK_ALLOC, type->size);

    if (expr)
        internal_make_assign_irc(id, expr, scope, prefix, fp);
}

void make_param_irc(param_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    internal_make_local_declvar_irc(ptr->id, ptr->type, NULL, scope, prefix, fp);
}

void make_paramlist_irc(paramlist_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    paramlist_p curr = ptr;
    while (curr) {
        make_param_irc(curr->param, scope, prefix, fp);
        curr = curr->tail;
    }
}

void make_decl_irc(decl_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    if (ptr) {
        switch (ptr->kind) {
            case DK_VAR:
                make_declvar_irc(ptr->declvar, scope, prefix, fp);
                break;
            case DK_FUN:
                make_declfun_irc(ptr->declfun, scope, prefix, fp);
                break;
        }
    }
}

void make_declvar_irc(declvar_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    char pid[100];
    switch (scope->kind) {
        case LOCAL:
            internal_make_local_declvar_irc(ptr->id, ptr->type, ptr->expr, scope, prefix, fp);
            break;
        case GLOBAL:
            sprintf(pid, "%s%s", GBL_PREFIX, ptr->id);
            scope->vmap = make_varmap(r_strdup(ptr->id), r_strdup(pid), scope->vmap, IM_BACK);
            fprintf(fp, "%s%s = %s %d\n", prefix, pid, GLOBAL_ALLOC, ptr->type->size);
            break;
    }
}

void make_declfun_irc(declfun_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    if (ptr) {
        char pid[50];
        sprintf(pid, "%s%s", GBL_PREFIX, ptr->id);
        scope->vmap = make_varmap(r_strdup(ptr->id), r_strdup(pid), scope->vmap, IM_BACK);

        scope_p new_scope = make_scope(LOCAL, copy_varmap(scope->vmap));

        fprintf(fp, "%s%s {\n", GBL_PREFIX, ptr->id);

        char* np = r_strdup(prefix);
        r_strcat(&np, "    ");

        make_paramlist_irc(ptr->paramlist, new_scope, np, fp);
        make_stmtlist_irc (ptr->stmtlist, new_scope, np, fp);

        fprintf(fp, "}\n");

        FREE      (np);
        free_scope(new_scope);
    }
}

void make_decllist_irc(decllist_p ptr, scope_p scope, char* const prefix, FILE* fp) {
    decllist_p curr = ptr;
    while (curr) {
        make_decl_irc(curr->decl, scope, prefix, fp);
        curr = curr->tail;
    }
}