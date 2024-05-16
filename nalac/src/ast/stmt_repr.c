//
// Created by Alex on 16/05/2024.
//

#include "../../include/ast/stmt.h"
#include "../../include/ast/decl.h"

char* stmtkind_to_str(stmtkind_t kind) {
    switch (kind) {
        case SK_ASSIGN:
            return "SK_ASSIGN";
        case SK_RETURN:
            return "SK_RETURN";
        case SK_DECL:
            return "SK_DECL";
        case SK_EXPR:
            return "SK_EXPR";
    }
}

void make_return_repr(return_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "%s└── ", prefix);

    str np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "    ");
        make_expr_repr(ptr->expr, np, fp);
        FREE(np);
    }
}

void make_assign_repr(assign_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "%s├── ", prefix);

    str np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "│   ");
        make_expr_repr(ptr->left, np, fp);
        FREE(np);
    }

    fprintf(fp, "%s└── ", prefix);

    np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "    ");
        make_expr_repr(ptr->right, np, fp);
        FREE(np);
    }
}

void make_stmt_repr(stmt_p ptr, char* const prefix, FILE* fp) {
    if (ptr) {
        str np = NULL;
        fprintf(fp, "stmt (%s)\n", stmtkind_to_str(ptr->kind));
        switch (ptr->kind) {
            case SK_RETURN:
                make_return_repr(ptr->ret, prefix, fp);
                break;
            case SK_ASSIGN:
                make_assign_repr(ptr->assign, prefix, fp);
                break;
            case SK_DECL:
                fprintf(fp, "%s└── ", prefix);

                np = r_strdup(prefix);
                if (np) {
                    r_strcat(&np, "    ");
                    make_decl_repr(ptr->decl, np, fp);
                    FREE(np);
                }

                break;
            case SK_EXPR:
                fprintf(fp, "%s└── ", prefix);

                np = r_strdup(prefix);
                if (np) {
                    r_strcat(&np, "    ");
                    make_expr_repr(ptr->expr, np, fp);
                    FREE(np);
                }
                break;
        }
    }
}

void make_stmtlist_item_repr(stmtlist_p ptr, char* const prefix, FILE* fp) {
    if (ptr != NULL) {
        int is_next = ptr->tail != NULL;

        fprintf(fp, "%s", prefix);
        fprintf(fp, "%s",  is_next ? "├── " : "└── ");

        str np = r_strdup(prefix);
        if (np) {
            r_strcat(&np, is_next ? "│   ": "    ");
            make_stmt_repr(ptr->stmt, np, fp);
            FREE(np);
        }

        make_stmtlist_item_repr(ptr->tail, prefix, fp);
    }
}

void make_stmtlist_repr(stmtlist_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "stmtlist");
    if (ptr != NULL) {
        fprintf(fp, "\n");
        make_stmtlist_item_repr(ptr, prefix, fp);
    }
    else {
        fprintf(fp, " (NULL)\n");
    }
}