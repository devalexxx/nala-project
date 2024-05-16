//
// Created by Alex on 16/05/2024.
//

#include "../../include/ast/prog.h"

void make_prog_repr(prog_p ptr, FILE* fp) {
    if (ptr != NULL) {
        fprintf(fp, "program\n├── ");
        make_decllist_repr(ptr->decllist, "│   ", fp);
        fprintf(fp, "└── ");
        make_decl_repr(ptr->main,     "    ", fp);
        fprintf(fp, "\n");
    }
}