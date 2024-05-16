#include "../../include/ast/prog.h"

prog_p make_prog(decllist_p decllist, decl_p main) {
    prog_p ptr = MALLOC(sizeof(*ptr));

    if (ptr) {
        ptr->decllist = decllist;
        ptr->main     = main;
    }

    return ptr;
}

void free_prog(prog_p ptr) {
    if (ptr) {
        free_decllist(ptr->decllist);
        free_decl    (ptr->main);
        FREE(ptr);
    }
}
