#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "../include/ast/prog.h"
#include "../include/sem/prog.h"
#include "../include/irc/prog.h"
#include "../include/args.h"

extern FILE   *yyin;
extern FILE   *yyout;
extern prog_p program;

extern int  yyparse      (void);
extern void yylex_destroy(void);

int main(int argc, char **argv) {
    int exit_flag = EXIT_SUCCESS;

    clock_t start = clock();

    args_p args = parse_args(argc, argv);
    bool   hhis = args->hhis;

    // Parsing
    if (!(yyin = fopen(args->input_path, "r"))) {
        printf("Failed to open %s\n\twith error: %s\n", args->input_path, strerror(errno));
        free_args(args);
        return EXIT_FAILURE;
    }
    yyout = stdout;
    yyparse();
    fclose(yyin);
    yylex_destroy();

    // Optional Ast output
    if (args->ast_out_path) {
        FILE* ast_out;
        if ((ast_out = fopen(args->ast_out_path, "w"))) {
            make_prog_repr(program, ast_out);
            fclose(ast_out);
        }
        else {
            printf("Failed to open %s\n\twith error: %s\n", args->ast_out_path, strerror(errno));
        }
    }

    // Semantic analysis
    FILE* sem_out = stderr;
    putc('\n', sem_out);
    bool is_semvalid = is_prog_semvalid(program, sem_out);
    if (is_semvalid) {
        exit_flag = EXIT_SUCCESS;

        // Optional IR output
        if (args->ir_out_path) {
            FILE* ir_output;
            if ((ir_output = fopen(args->ir_out_path, "w"))) {
                make_prog_irc(program, ir_output);
                fclose(ir_output);
            }
            else {
                printf("Failed to open %s\n\twith error: %s\n", args->ir_out_path, strerror(errno));
                exit_flag = EXIT_FAILURE;
            }
        }

    }
    else {
        putc('\n', sem_out);
        exit_flag = EXIT_FAILURE;
    }

    // Release objects
    free_prog(program);
    free_args   (args);

    if (hhis) {
        print_heap_history();
        putc('\n', stdout);
    }

    clock_t end = clock();
    printf("Elapsed time: %fs\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    return exit_flag;
}
