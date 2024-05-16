%{
    #include <stdio.h>
    #include <string.h>
    #include "../../include/ast/prog.h"

    extern unsigned int   line, car;
    extern          char* yytext;

    void yyerror    (const char*);
    extern int yylex(void);

    prog_p program = NULL;
%}

%define parse.error detailed

%token T_U8 T_U16 T_U32 T_U64
%token T_I8 T_I16 T_I32 T_I64
%token T_F32 T_F64
%token T_VOID
%token K_RET
%token K_MAIN
%token EOL
%token COMMA
%token O_ASS
%token O_ADD O_SUB O_MUL O_DIV
%token UNARY
%token OPAREN CPAREN
%token OBRACE CBRACE
%token OBRACK CBRACK

%token <ival> L_INT
%token <rval> L_REL 
%token <cval> L_CHR
%token <sval> L_STR
%token <sval> IDENTIFIER

%union value {
    int         ival;
    double      rval;
    char        cval;
    char*       sval;

    prog_p      prog;
    decl_p      decl;
    decllist_p  decllist;
    stmt_p      stmt;
    stmtlist_p  stmtlist;
    expr_p      expr;
    exprlist_p  exprlist;
    type_p      type;
    typelist_p  typelist;
    param_p     param;
    paramlist_p paramlist;
}

%nterm <prog>      in
%nterm <decl>      main
%nterm <decl>      decl
%nterm <decl>      declvar
%nterm <decl>      declfun
%nterm <decllist>  decllist
%nterm <stmt>      stmt
%nterm <stmt>      coupound_stmt
%nterm <stmtlist>  coupound_stmtlist
%nterm <expr>      expr
%nterm <expr>      primary
%nterm <expr>      postfix
%nterm <expr>      unary
%nterm <exprlist>  arglist
%nterm <type>      type
%nterm <typelist>  typelist
%nterm <param>     param
%nterm <paramlist> paramlist

%destructor { FREE          ($$); } <sval>

%destructor { free_decl     ($$); } <decl>
%destructor { free_decllist ($$); } <decllist>
%destructor { free_stmt     ($$); } <stmt>
%destructor { free_stmtlist ($$); } <stmtlist>
%destructor { free_expr     ($$); } <expr>
%destructor { free_exprlist ($$); } <exprlist>
%destructor { free_type     ($$); } <type>
%destructor { free_typelist ($$); } <typelist>
%destructor { free_param    ($$); } <param>
%destructor { free_paramlist($$); } <paramlist>

%start in

%left  O_ADD O_SUB
%left  O_MUL O_DIV

%%

in
    : EOL decllist main { $$ = program = make_prog($2, $3); }
    |     decllist main { $$ = program = make_prog($1, $2); }
    ;

main
    : K_MAIN OBRACE coupound_stmtlist CBRACE
        {
            $$ = make_declfun_decl(make_declfun(
                r_strdup("main"),
                make_typepri_type(make_typepri(PK_SIGNED, 4)),
                NULL, $3
            ));
        }
    ;

primary
    : IDENTIFIER                       { $$ = make_iden_expr($1); }
    | IDENTIFIER OPAREN arglist CPAREN { $$ = make_call_expr(make_call(make_iden_expr($1), $3)); }
    | L_INT                            { $$ = make_lint_expr($1); }
    | L_REL                            { $$ = make_lrel_expr($1); }
    | L_CHR                            { $$ = make_lchr_expr($1); }
    | L_STR                            { $$ = make_lstr_expr($1); }
    | OPAREN expr CPAREN               { $$ = $2; }
    ;

postfix
    : primary                    {$$ = $1;}
/*  | postfix OBRACK expr CBRACK { $$ = NULL; } */
    ;

unary
    : postfix     { $$ = $1; }
    | O_SUB unary { $$ = make_unary_expr (make_unary (SUB, $2)); }
    ;

expr
    : unary            { $$ = $1; }
    | expr O_ADD unary { $$ = make_binary_expr(make_binary(ADD, $1, $3)); }
    | expr O_SUB unary { $$ = make_binary_expr(make_binary(SUB, $1, $3)); }
    | expr O_MUL unary { $$ = make_binary_expr(make_binary(MUL, $1, $3)); }
    | expr O_DIV unary { $$ = make_binary_expr(make_binary(DIV, $1, $3)); }
    ;

arglist
    :                    { $$ = NULL; }
    | expr               { $$ = make_exprlist($1, NULL, IM_FRONT); }
    | arglist COMMA expr { $$ = make_exprlist($3, $1,   IM_BACK ); }

type
    : T_U8                        { $$ = make_typepri_type(make_typepri(PK_UNSIGNED,   1)); }
    | T_U16                       { $$ = make_typepri_type(make_typepri(PK_UNSIGNED,   2)); }
    | T_U32                       { $$ = make_typepri_type(make_typepri(PK_UNSIGNED,   4)); }
    | T_U64                       { $$ = make_typepri_type(make_typepri(PK_UNSIGNED,   8)); }
    | T_I8                        { $$ = make_typepri_type(make_typepri(PK_SIGNED,     1)); }
    | T_I16                       { $$ = make_typepri_type(make_typepri(PK_SIGNED,     2)); }
    | T_I32                       { $$ = make_typepri_type(make_typepri(PK_SIGNED,     4)); }
    | T_I64                       { $$ = make_typepri_type(make_typepri(PK_SIGNED,     8)); }
    | T_F32                       { $$ = make_typepri_type(make_typepri(PK_FLOATING_P, 4)); }
    | T_F64                       { $$ = make_typepri_type(make_typepri(PK_FLOATING_P, 8)); }
    | T_VOID                      { $$ = make_type(TK_VOID);                                }
    | type OPAREN typelist CPAREN { $$ = make_typefun_type(make_typefun($1, $3));           }
    ;

typelist
    :                     { $$ = NULL; }
    | type                { $$ = make_typelist($1, NULL, IM_FRONT); }
    | typelist COMMA type { $$ = make_typelist($3, $1,   IM_BACK ); }
    ;

stmt
    : expr O_ASS expr EOL { $$ = make_assign_stmt(make_assign($1, $3)); }
    |      K_RET expr EOL { $$ = make_return_stmt(make_return($2)    ); }
    ;

coupound_stmt
    : stmt     { $$ = $1;                 }
    | expr EOL { $$ = make_expr_stmt($1); }
    | declvar  { $$ = make_decl_stmt($1); }
    ;

coupound_stmtlist
    :                                 { $$ = NULL;                           }
    | coupound_stmtlist coupound_stmt { $$ = make_stmtlist($2, $1, IM_BACK); }
    ;

declvar
    : type IDENTIFIER            EOL { $$ = make_declvar_decl(make_declvar($2, $1, NULL)); }
    | type IDENTIFIER O_ASS expr EOL { $$ = make_declvar_decl(make_declvar($2, $1, $4)  ); }
    ;

declfun
    : type IDENTIFIER OPAREN paramlist CPAREN OBRACE coupound_stmtlist CBRACE
        { $$ = make_declfun_decl(make_declfun($2, $1, $4, $7)); }
    ;

decl
    : declvar { $$ = $1; }
    | declfun { $$ = $1; }
    ;

decllist
    :               { $$ = NULL; }
    | decllist decl { $$ = make_decllist($2, $1, IM_BACK); }
    ;

param
    : type IDENTIFIER { $$ = make_param($2, $1); }
    ;

paramlist
    :                       { $$ = NULL; }
    | param                 { $$ = make_paramlist($1, NULL, IM_FRONT); }
    | paramlist COMMA param { $$ = make_paramlist($3, $1,   IM_BACK ); }

%%

void yyerror(const char *message)
{
    if (strstr(yytext, "\n") != NULL)
        line -= strlen(yytext);
    else
        car -= strlen(yytext);

    fprintf(stderr, "Error at line %d:%d\n\twith message:\t%s\n", line, car, message);
}
