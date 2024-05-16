//
// Created by Alex on 06/06/2024.
//

#include "../../include/sem/prog.h"
#include "../../include/sem/decl.h"

bool is_prog_semvalid(prog_p ptr, FILE* fp) {
    context_p cntx  = make_contextprg_context(NULL);
    bool      flag = TRUE;

    if (ptr) {
        if(!(is_decllist_semvalid(ptr->decllist, cntx, fp) && is_decl_semvalid(ptr->main, cntx, fp)))
            flag = FALSE;
    }

    free_context(cntx);
    return flag;
}