//
// Created by Alex on 16/05/2024.
//

#include "../../include/ast/decl.h"

char* declkind_to_str(declkind_t dt) {
    switch (dt) {
        case DK_VAR:
            return "DK_VAR";
        case DK_FUN:
            return "DK_FUN";
    }
}

void make_declvar_repr(declvar_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "%s├── ", prefix);

    str np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "│   ");
        make_type_repr(ptr->type, np, fp);

        if (ptr->expr) {
            fprintf(fp, "%s├── ", prefix);
            make_expr_repr(ptr->expr, np, fp);
        }

        FREE(np);
    }

    fprintf(fp, "%s└── %s\n", prefix, ptr->id);
}

void make_param_repr(param_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "param\n%s├── ", prefix);

    str np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "│   ");
        make_type_repr(ptr->type, np, fp);
        FREE(np);
    }

    fprintf(fp, "%s└── %s\n", prefix, ptr->id);
}

void make_paramlist_item_repr(paramlist_p ptr, char* const prefix, FILE* fp) {
    if (ptr) {
        int is_next = ptr->tail != NULL;

        fprintf(fp, "%s", prefix);
        fprintf(fp, "%s",  is_next ? "├── " : "└── ");

        str np = r_strdup(prefix);
        if (np) {
            r_strcat(&np, is_next ? "│   ": "    ");
            make_param_repr(ptr->param, np, fp);
            FREE(np);
        }

        make_paramlist_item_repr(ptr->tail, prefix, fp);
    }
}

void make_paramlist_repr(paramlist_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "paramlist");
    if (ptr) {
        fprintf(fp, "\n");
        make_paramlist_item_repr(ptr, prefix, fp);
    }
    else {
        fprintf(fp, " (NULL)\n");
    }
}

void make_declfun_repr(declfun_p ptr, char* const prefix, FILE* fp) {
    str np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "│   ");

        fprintf(fp, "%s├── ", prefix);
        make_type_repr(ptr->type, np, fp);

        fprintf(fp, "%s├── ", prefix);
        make_paramlist_repr(ptr->paramlist, np, fp);

//    printf("%s├── ", prefix);
//    show_decllist(ptr->decllist, np);

        fprintf(fp, "%s├── ", prefix);
        make_stmtlist_repr(ptr->stmtlist, np, fp);

        FREE(np);
    }

    fprintf(fp, "%s└── %s\n", prefix, ptr->id);
}

void make_decl_repr(decl_p ptr, char* const prefix, FILE* fp) {
    if (ptr) {
        fprintf(fp, "decl (%s)\n", declkind_to_str(ptr->kind));
        switch (ptr->kind) {
            case DK_VAR:
                make_declvar_repr(ptr->declvar, prefix, fp);
                break;
            case DK_FUN:
                make_declfun_repr(ptr->declfun, prefix, fp);
                break;
        }
    }
}

void make_decllist_item_repr(decllist_p ptr, char* const prefix, FILE* fp) {
    if (ptr != NULL) {
        int is_next = ptr->tail != NULL;

        fprintf(fp, "%s", prefix);
        fprintf(fp, "%s", is_next ? "├── " : "└── ");

        str np = r_strdup(prefix);
        if (np) {
            r_strcat(&np, is_next ? "│   ": "    ");
            make_decl_repr(ptr->decl, np, fp);
            FREE(np);
        }

        make_decllist_item_repr(ptr->tail, prefix, fp);
    }
}

void make_decllist_repr(decllist_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "decllist");
    if (ptr != NULL) {
        fprintf(fp, "\n");
        make_decllist_item_repr(ptr, prefix, fp);
    }
    else {
        fprintf(fp, " (NULL)\n");
    }
}