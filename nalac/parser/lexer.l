%option noyywrap

%{
    #include "../../include/ast/prog.h"
    #include "parser.tab.h"

    unsigned int line = 1, car = 1;
    void err  (char*);
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

%x SKIP

%%

"u8"     { track(); return T_U8;   }
"u16"    { track(); return T_U16;  }
"u32"    { track(); return T_U32;  }
"u64"    { track(); return T_U64;  }

"i8"     { track(); return T_I8;   }
"i16"    { track(); return T_I16;  }
"i32"    { track(); return T_I32;  }
"i64"    { track(); return T_I64;  }

"f32"    { track(); return T_F32;  }
"f64"    { track(); return T_F64;  }

"void"   { track(); return T_VOID; }

"return" { track(); return K_RET;  }

"main"   { track(); return K_MAIN; }

","      { track(); return COMMA;  }

"="      { track(); return O_ASS;  }

"+"	     { track(); return O_ADD;  }
"-"	     { track(); return O_SUB;  }
"*" 	 { track(); return O_MUL;  }
"/"	     { track(); return O_DIV;  }

"("      { track(); return OPAREN; }
")"      { track(); return CPAREN; }
"{"      { track(); BEGIN(SKIP); return OBRACE; }
"}"      { track(); BEGIN(SKIP); return CBRACE; }
"["      { track(); return OBRACK; }
"]"      { track(); return CBRACK; }

{IDENTIFIER}   { track(); yylval.sval = r_strdup(yytext); return IDENTIFIER; }
{LITERAL_INT}  { track(); yylval.ival = atoi(yytext);     return L_INT;      }
{LITERAL_REL}  { track(); yylval.rval = atof(yytext);     return L_REL;      }
{LITERAL_CHR}  { track(); yylval.cval = yytext[0];        return L_CHR;      }
{LITERAL_STR}  { track(); yylval.sval = r_strdup(yytext); return L_STR;      }


<SKIP>\n+ { BEGIN(INITIAL); line += strlen(yytext); car = 1; }
\n+       { BEGIN(INITIAL); line += strlen(yytext); car = 1; return EOL;}
\t	      { car += 4; }
" "	      { car += 1; }
[\r\f]+

.             { err("Unexpected token."); }
{WRONG_L_CHR} { err("String must use \"");}

%%

void track(void) {
    car += strlen(yytext);
}

void err(char* message) {
    fprintf(stderr, "Error at line %d:%d\n\twith message:\t%s\n\twith token:\t%s\n", line, car, message, yytext);
}
