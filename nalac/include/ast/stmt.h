//
// Created by Alex on 15/05/2024.
//

#ifndef NALA_PROJECT_AST_STMT_H
#define NALA_PROJECT_AST_STMT_H

#include "stdio.h"

#include "../common.h"

typedef struct expr_s  expr_t;
typedef        expr_t* expr_p;

typedef struct decl_s  decl_t;
typedef        decl_t* decl_p;

typedef enum stmtkind_e stmtkind_t;
enum stmtkind_e {
    SK_ASSIGN, SK_RETURN, SK_DECL, SK_EXPR
};

typedef struct assign_s  assign_t;
typedef        assign_t* assign_p;
struct assign_s {
    expr_p left;
    expr_p right;
};

typedef struct return_s  return_t;
typedef        return_t* return_p;
struct return_s {
    expr_p expr;
};

typedef struct stmt_s  stmt_t;
typedef        stmt_t* stmt_p;
struct stmt_s {
    stmtkind_t kind;
    union {
        assign_p assign;
        return_p ret;
        decl_p   decl;
        expr_p   expr;
    };
};

typedef struct stmtlist_s  stmtlist_t;
typedef        stmtlist_t* stmtlist_p;
struct stmtlist_s {
    stmt_p     stmt;
    stmtlist_p tail;
};

assign_p make_assign(expr_p, expr_p);
void     free_assign(assign_p);

return_p make_return(expr_p);
void     free_return(return_p);

stmt_p make_assign_stmt(assign_p);
stmt_p make_return_stmt(return_p);
stmt_p make_decl_stmt  (decl_p);
stmt_p make_expr_stmt  (expr_p);
void   free_stmt       (stmt_p);


stmtlist_p make_stmtlist(stmt_p, stmtlist_p, insertmode_t);
void       free_stmtlist(stmtlist_p);

void make_stmt_repr    (stmt_p,     char*, FILE*);
void make_stmtlist_repr(stmtlist_p, char*, FILE*);

#endif
