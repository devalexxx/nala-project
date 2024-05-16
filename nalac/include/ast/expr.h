//
// Created by Alex on 15/05/2024.
//

#ifndef NALA_PROJECT_AST_EXPR_H
#define NALA_PROJECT_AST_EXPR_H

#include "stdio.h"

#include "../common.h"

typedef struct expr_s  expr_t;
typedef        expr_t* expr_p;

typedef struct exprlist_s  exprlist_t;
typedef        exprlist_t* exprlist_p;

typedef enum op_e op_t;
enum op_e {
    ADD, SUB, MUL, DIV
};

typedef struct unary_s  unary_t;
typedef        unary_t* unary_p;
struct unary_s {
    op_t   op;
    expr_p expr;
};

typedef struct binary_s  binary_t;
typedef        binary_t* binary_p;
struct binary_s {
    op_t   op;
    expr_p left;
    expr_p right;
};

typedef struct call_s  call_t;
typedef        call_t* call_p;
struct call_s {
    expr_p     expr;
    exprlist_p args;
};

typedef enum exprkind_e exprkind_t;
enum exprkind_e {
    EK_IDEN, EK_UNAR, EK_BINA, EK_LINT, EK_LREL, EK_LCHR, EK_LSTR, EK_CALL
};

struct expr_s {
    exprkind_t kind;
    union {
        str      id;
        unary_p  unary;
        binary_p binary;
        call_p   call;
        int      ival;
        double   rval;
        char     cval;
        str      sval;
    };
};

struct exprlist_s {
    expr_p     expr;
    exprlist_p tail;
};

unary_p make_unary(op_t, expr_p);
void    free_unary(unary_p);

binary_p make_binary(op_t, expr_p, expr_p);
void     free_binary(binary_p);

call_p make_call(expr_p, exprlist_p);
void   free_call(call_p);

expr_p make_iden_expr  (str);
expr_p make_lstr_expr  (str);
expr_p make_lint_expr  (int);
expr_p make_lrel_expr  (double);
expr_p make_lchr_expr  (char);
expr_p make_unary_expr (unary_p);
expr_p make_binary_expr(binary_p);
expr_p make_call_expr  (call_p);
void   free_expr       (expr_p);

exprlist_p make_exprlist(expr_p, exprlist_p, insertmode_t);
void       free_exprlist(exprlist_p);

void make_expr_repr(expr_p, char*, FILE*);

#endif
