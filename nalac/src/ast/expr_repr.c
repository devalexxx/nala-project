//
// Created by Alex on 16/05/2024.
//

#include "../../include/ast/expr.h"

void make_exprlist_repr(exprlist_p, char*, FILE*);

char* op_to_str(op_t op) {
    switch (op) {
        case ADD:
            return "ADD";
        case SUB:
            return "SUB";
        case MUL:
            return "MUL";
        case DIV:
            return "DIV";
    }
}

char* exprkind_to_str(exprkind_t kind) {
    switch (kind) {
        case EK_IDEN:
            return "EK_IDEN";
        case EK_UNAR:
            return "EK_UNAR";
        case EK_BINA:
            return "EK_BINA";
        case EK_LINT:
            return "EK_LINT";
        case EK_LREL:
            return "EK_LREL";
        case EK_LCHR:
            return "EK_LCHR";
        case EK_LSTR:
            return "EK_LSTR";
        case EK_CALL:
            return "EK_CALL";
    }
}

void show_unary(unary_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "%s├── %s\n", prefix, op_to_str(ptr->op));
    fprintf(fp, "%s└── ", prefix);

    str np = r_strdup(prefix);
    if (np) {
        r_strcat(&np, "    ");
        make_expr_repr(ptr->expr, np, fp);
        FREE(np);
    }
}

void show_binary(binary_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "%s├── %s\n", prefix, op_to_str(ptr->op));
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

void show_call(call_p ptr, char* const prefix, FILE* fp) {
    if (ptr) {
        fprintf(fp, "%s├── ", prefix);

        str np = r_strdup(prefix);
        if (np) {
            r_strcat(&np, "│   ");
            make_expr_repr(ptr->expr, np, fp);
            FREE(np);
        }

        fprintf(fp, "%s└── ", prefix);
        np = r_strdup(prefix);
        if (np) {
            r_strcat(&np, "    ");
            make_exprlist_repr(ptr->args, np, fp);
            FREE(np);
        }
    }
}

void make_expr_repr(expr_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "expr (%s)\n", exprkind_to_str(ptr->kind));
    switch (ptr->kind) {
        case EK_LINT:
            fprintf(fp, "%s└── %d\n", prefix, ptr->ival);
            break;
        case EK_LREL:
            fprintf(fp, "%s└── %f\n", prefix, ptr->rval);
            break;
        case EK_LCHR:
            fprintf(fp, "%s└── %c\n", prefix, ptr->cval);
            break;
        case EK_LSTR:
            fprintf(fp, "%s└── %s\n", prefix, ptr->sval);
            break;
        case EK_IDEN:
            fprintf(fp, "%s└── %s\n", prefix, ptr->id);
            break;
        case EK_UNAR:
            show_unary(ptr->unary, prefix, fp);
            break;
        case EK_BINA:
            show_binary(ptr->binary, prefix, fp);
            break;
        case EK_CALL:
            show_call(ptr->call, prefix, fp);
            break;
    }
}

void make_exprlist_item_repr(exprlist_p ptr, char* const prefix, FILE* fp) {
    if (ptr) {
        int is_next = ptr->tail != NULL;

        fprintf(fp, "%s", prefix);
        fprintf(fp, "%s",  is_next ? "├── " : "└── ");

        str np = r_strdup(prefix);
        if (np) {
            r_strcat(&np, is_next ? "│   ": "    ");
            make_expr_repr(ptr->expr, np, fp);
            FREE(np);
        }

        make_exprlist_item_repr(ptr->tail, prefix, fp);
    }
}

void make_exprlist_repr(exprlist_p ptr, char* const prefix, FILE* fp) {
    fprintf(fp, "exprlist");
    if (ptr) {
        fprintf(fp, "\n");
        make_exprlist_item_repr(ptr, prefix, fp);
    }
    else {
        fprintf(fp, " (NULL)\n");
    }
}