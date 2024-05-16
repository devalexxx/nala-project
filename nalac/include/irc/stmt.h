//
// Created by Alex on 04/06/2024.
//

#ifndef NALA_PROJECT_IRC_STMT_H
#define NALA_PROJECT_IRC_STMT_H

#include "../../include/ast/stmt.h"
#include "../../include/irc/scope.h"

void internal_make_assign_irc(char*, expr_p, scope_p, char*, FILE*);

void make_assign_irc  (assign_p, scope_p, char*, FILE*);
void make_return_irc  (return_p, scope_p, char*, FILE*);

void make_stmt_irc    (stmt_p,     scope_p, char*, FILE*);
void make_stmtlist_irc(stmtlist_p, scope_p, char*, FILE*);

#endif
