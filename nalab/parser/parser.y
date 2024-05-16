%{
    #include <stdio.h>

    extern unsigned int line, car;

    void       yyerror(const char*);
    extern int yylex  (void);
%}

%define parse.error detailed

%token O_ASS
%token O_ADD O_SUB O_MUL O_DIV

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
}

%nterm in

%start in

%left  O_ADD O_SUB
%left  O_MUL O_DIV
%right UNARY

%%

in
    :
    ;


%%

void yyerror(const char *message)
{
    printf("Error at line %d:%d\n\twith message:\t%s\n", line, car, message);
}
