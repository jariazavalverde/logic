/*H*
 * 
 * FILENAME: clause.c
 * DESCRIPTION: Data structures and functions for type checking
 * AUTHORS: José Antonio Riaza Valverde
 * UPDATED: 14.11.2019
 * 
 *H*/

#ifndef LOGIC_TYPE_CHECK_H
#define LOGIC_TYPE_CHECK_H

#include <stdlib.h>
#include "term.h"
#include "substitution.h"
#include "unification.h"

/**
  * 
  * This function returns a pointer to a term
  * containing the type of a given term.
  * 
  **/
Term *tc_get_type_term(Term *term);

/**
  * 
  * This function returns a pointer to a term
  * containing the type of a given callable
  * expression.
  * 
  **/
Term *tc_get_type_expr(Term *expr);

/**
  * 
  * This function checks the type of an expression,
  * returning a pointer to a substitution if the
  * expression type checks. Otherwise, returns null.
  * 
  **/
Substitution *tc_check_type_expr(Term *expr, Term *type);

#endif