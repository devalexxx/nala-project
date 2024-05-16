//
// Created by Alex on 15/05/2024.
//

#ifndef NALA_PROJECT_ARGS_H
#define NALA_PROJECT_ARGS_H

#include "common.h"

typedef struct args_s  args_t;
typedef        args_t* args_p;
struct args_s {
    str  input_path;
    str  ast_out_path;
    str  ir_out_path;
    bool hhis;
};


typedef enum parseflag_e parseflag_t;
enum parseflag_e {
    AST_OUT, IR_OUT, NONE
};

args_p parse_args(int, char**);
void   free_args (args_p);

#endif //COMPILER_ARGS_H
