//
// Created by Alex on 03/06/2024.
//

#include "../../include/irc/prog.h"
#include "../../include/irc/decl.h"

void make_prog_irc(prog_p ptr, FILE* fp) {
    if (ptr) {
        scope_p scope = make_scope(GLOBAL, NULL);
        make_decllist_irc(ptr->decllist, scope, "", fp);
        make_decl_irc    (ptr->main,     scope, "", fp);
        free_scope(scope);
    }
}