#include <stdio.h>
#include <errno.h>

//extern FILE *yyin;
//extern FILE *yyout;
//extern int yyparse(void);
//
//int allocated_ptr = 0, freed_ptr = 0;

int main(int argc, char **argv) {
//    yyout = stdout;
//    if (argc > 1) {
//        if (!(yyin = fopen(argv[1], "r"))) {
//            printf("Failed to open %s with errno : %d", argv[1], errno);
//            return 1;
//        }
//    }
//    else {
//        fprintf(stderr, "No input file.");
//        return 1;
//    }
//    yyparse();
//    fclose(yyin);
//
//    FILE* tmp = tmpfile();
//
//    FILE *asm_code;
//    if (argc > 2) {
//        if(!(asm_code = fopen(argv[2], "w"))) {
//            printf("Failed to open %s with errno : %d", argv[2], errno);
//            asm_code = stdout;
//        }
//    }
//    else {
//        asm_code = stdout;
//    }
//
//    int c;
//    fseek(tmp, 0, SEEK_SET);
//    while ((c = getc(tmp)) != EOF) {
//        putc(c, asm_code);
//    }
//
//    fclose(tmp);
//    if (asm_code != stdout)
//        fclose(asm_code);
//
//    printf("\n\nallocated: %d, freed: %d\n", allocated_ptr, freed_ptr);

    return 0;
}
