//
// Created by Alex on 16/05/2024.
//

#include "../../include/ast/type.h"

char* typekind_to_str(typekind_t typekind) {
    switch (typekind) {
        case TK_PRI:
            return "TK_PRI";
        case TK_FUN:
            return "TK_FUN";
        case TK_VOID:
            return "TK_VOID";
    }
}

char* primitivekind_to_str(prikind_t kind) {
    switch (kind) {
        case PK_SIGNED:
            return "PK_SIGNED";
        case PK_UNSIGNED:
            return "PK_UNSIGNED";
        case PK_FLOATING_P:
            return "PK_FLOATING_P";
    }
}

void make_typefun_repr(typefun_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "%s├── ", prefix);

    str np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "│   ");
        make_type_repr(ptr->rtype, np, fp);
        FREE(np);
    }

    fprintf(fp, "%s└── ", prefix);

    np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "    ");
        make_typelist_repr(ptr->typelist, np, fp);
        FREE(np);
    }
}

void make_type_repr(type_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "type (%s)\n", typekind_to_str(ptr->kind));

    switch (ptr->kind) {
        case TK_PRI:
            fprintf(fp, "%s├── %s\n%s└── %d\n",
                    prefix, primitivekind_to_str(ptr->typepri->kind), prefix, ptr->typepri->size
            );
            break;
        case TK_FUN:
            make_typefun_repr(ptr->typefun, prefix, fp);
            break;
        case TK_VOID:
            break;
    }
}

void make_typelist_item_repr(typelist_p ptr, char* const prefix, FILE* fp) {
    if (ptr != NULL) {
        int is_next = ptr->tail != NULL;

        fprintf(fp, "%s", prefix);
        fprintf(fp, "%s", is_next ? "├── " : "└── ");

        str np = r_strdup(prefix);
        if (np) {
            r_strcat(&np, is_next ? "│   ": "    ");
            make_type_repr(ptr->type, np, fp);
            FREE(np);
        }

        make_typelist_item_repr(ptr->tail, prefix, fp);
    }
}

void make_typelist_repr(typelist_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "typelist");
    if (ptr != NULL) {
        fprintf(fp, "\n");
        make_typelist_item_repr(ptr, prefix, fp);
    }
    else {
        fprintf(fp, " (NULL)\n");
    }
}