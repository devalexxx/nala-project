//
// Created by Alex on 03/06/2024.
//

#ifndef NALA_PROJECT_IRC_DECL_H
#define NALA_PROJECT_IRC_DECL_H

#include "../../include/ast/decl.h"
#include "../../include/irc/scope.h"

void make_param_irc    (param_p,     scope_p, char*, FILE*);
void make_paramlist_irc(paramlist_p, scope_p, char*, FILE*);

void make_decl_irc    (decl_p,     scope_p, char*, FILE*);
void make_declvar_irc (declvar_p,  scope_p, char*, FILE*);
void make_declfun_irc (declfun_p,  scope_p, char*, FILE*);
void make_decllist_irc(decllist_p, scope_p, char*, FILE*);

#endif
