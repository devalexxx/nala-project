%option noyywrap

%{
    #include "../../src/gen/parser.tab.h"

    unsigned int line, car = 1;
    void err(char*);
    void track(void);
%}

alpha       [a-zA-Z_]
digit       [0-9]
alnum       {alpha}|{digit}
print       [ -~]
 
IDENTIFIER   {alpha}+{alnum}*
LITERAL_INT  "0"|[0-9]{digit}*
LITERAL_REL  "0"|{digit}*"."{digit}+
LITERAL_CHR  (\'{print}\')|(\'\\[nftrbv]\')
LITERAL_STR  \"{print}*\"

WRONG_L_CHR  \'{print}*\'

%%
":="     { track(); return O_ASS;  }

"+"	     { track(); return O_ADD;  }
"-"	     { track(); return O_SUB;  }
"*" 	 { track(); return O_MUL;  }
"/"	     { track(); return O_DIV;  }

{IDENTIFIER}   { track(); yylval.sval = strdup(yytext); return IDENTIFIER; }
{LITERAL_INT}  { track(); yylval.ival = atoi(yytext);   return L_INT;      }
{LITERAL_REL}  { track(); yylval.rval = atof(yytext);   return L_REL;      }
{LITERAL_CHR}  { track(); yylval.cval = yytext[0];      return L_CHR;      }
{LITERAL_STR}  { track(); yylval.sval = strdup(yytext); return L_STR;      }

"\n"           { line += 1; car = 1; }
"\t"	       { car += 4; }
" " 	       { car += 1; }
[\r\f]+

.             { err("Unexpected token."); }
{WRONG_L_CHR} { err("String must use \"");}

%%

void track(void) {
    car += strlen(yytext);
}

void err(char* message) {
    printf("Error at line %d:%d\n\twith message:\t%s\n\twith token:\t%s\n", line, car, message, yytext);
}
