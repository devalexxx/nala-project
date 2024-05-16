//
// Created by Alex on 15/05/2024.
//

#include "../include/args.h"

#include "string.h"
#include "stdio.h"

args_p parse_args(int argc, char** argv) {
    args_p ptr = MALLOC(sizeof (*ptr));

    if (ptr) {
        ptr->input_path   = NULL;
        ptr->ast_out_path = NULL;
        ptr->ir_out_path  = NULL;
        ptr->hhis         = FALSE;

        if (argc < 2) {
            fprintf(stderr, "You must at least provide the source file.\n");
            free_args(ptr);
            exit(1);
        }
        else {
            if (argv[1][0] == '-') {
                fprintf(stderr, "You must at least provide the source file.\n");
                free_args(ptr);
                exit(1);
            }
            else
                ptr->input_path = r_strdup(argv[1]);
        }

        parseflag_t flag = NONE;
        for (int i = 1; i < argc; ++i) {
            switch (flag) {
                case AST_OUT:
                    if (argv[i][0] != '-') {
                        ptr->ast_out_path = r_strdup(argv[i]);
                        flag = NONE;
                    }
                    else {
                        fprintf(stderr, "You must provide a path after -a/-A.\n");
                        free_args(ptr);
                        exit(1);
                    }
                    break;
                case IR_OUT:
                    if (argv[i][0] != '-') {
                        ptr->ir_out_path = r_strdup(argv[i]);
                        flag = NONE;
                    }
                    else {
                        fprintf(stderr, "You must provide a path after -i/-I.\n");
                        free_args(ptr);
                        exit(1);
                    }
                    break;
                case NONE:
                    if (strcasecmp(argv[i], "-a") == 0) {
                        if (argc <= i + 1) {
                            fprintf(stderr, "You must provide a path after -a/-A.\n");
                            free_args(ptr);
                            exit(1);
                        }
                        flag = AST_OUT;
                    }
                    if (strcasecmp(argv[i], "-i") == 0) {
                        if (argc <= i + 1) {
                            fprintf(stderr, "You must provide a path after -i/-I.\n");
                            free_args(ptr);
                            exit(1);
                        }
                        flag = IR_OUT;
                    }

                    if (strcasecmp(argv[i], "-hh") == 0)
                        ptr->hhis = TRUE;
                    break;
            }
        }
    }

    return ptr;
}

void free_args(args_p ptr) {
    if (ptr) {
        if (ptr->input_path)
            FREE(ptr->input_path);

        if (ptr->ast_out_path)
            FREE(ptr->ast_out_path);

        if (ptr->ir_out_path)
            FREE(ptr->ir_out_path);

        FREE(ptr);
    }
}