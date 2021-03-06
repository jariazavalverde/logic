/*H*
 * 
 * FILENAME: builtin.h
 * DESCRIPTION: Functions for evaluating built-in predicates
 * AUTHORS: José Antonio Riaza Valverde
 * UPDATED: 18.11.2019
 * 
 *H*/

#ifndef HERBRAND_BUILTIN_H
#define HERBRAND_BUILTIN_H

#include "term.h"
#include "derivation.h"
#include "substitution.h"
#include "unification.h"
#include "hashmap.h"
#include "program.h"
#include "parser.h"
#include "exception.h"
#include "evaluable.h"
#include "type_check.h"

#ifndef HERBRAND_PATH
#define HERBRAND_PATH L"/usr/local/herbrand/"
#endif

#define BUILTIN_HASH_SIZE 1024
wchar_t *builtin_keys[BUILTIN_HASH_SIZE];
void (*builtin_handlers[BUILTIN_HASH_SIZE])();
int builtin_arities[BUILTIN_HASH_SIZE];

/**
  * 
  * This function cheks if an atom is a built-in
  * predicate.
  * 
  **/
int builtin_check_predicate(Term *term);

/**
  * 
  * This function runs a built-in predicate.
  * 
  **/
int builtin_run_predicate(Program *program, Derivation *D, State *point, Term *term);

// Builtin predicates
void builtin_consult(Program *program, Derivation *D, State *point, Term *term);
void builtin_import(Program *program, Derivation *D, State *point, Term *term);
void builtin_and(Program *program, Derivation *D, State *point, Term *term);
void builtin_or(Program *program, Derivation *D, State *point, Term *term);
void builtin_ite(Program *program, Derivation *D, State *point, Term *term);
void builtin_cut(Program *program, Derivation *D, State *point, Term *term);
void builtin_not(Program *program, Derivation *D, State *point, Term *term);
void builtin_call(Program *program, Derivation *D, State *point, Term *term);
void builtin_once(Program *program, Derivation *D, State *point, Term *term);
void builtin_repeat(Program *program, Derivation *D, State *point, Term *term);
void builtin_true(Program *program, Derivation *D, State *point, Term *term);
void builtin_false(Program *program, Derivation *D, State *point, Term *term);
void builtin_catch(Program *program, Derivation *D, State *point, Term *term);
void builtin_throw(Program *program, Derivation *D, State *point, Term *term);
void builtin__catcher(Program *program, Derivation *D, State *point, Term *term);
void builtin_unification(Program *program, Derivation *D, State *point, Term *term);
void builtin_not_unification(Program *program, Derivation *D, State *point, Term *term);
void builtin_asserta(Program *program, Derivation *D, State *point, Term *term);
void builtin_assertz(Program *program, Derivation *D, State *point, Term *term);
void builtin_retract(Program *program, Derivation *D, State *point, Term *term);
void builtin_retractall(Program *program, Derivation *D, State *point, Term *term);
void builtin_term_eq(Program *program, Derivation *D, State *point, Term *term);
void builtin_term_ne(Program *program, Derivation *D, State *point, Term *term);
void builtin_term_lt(Program *program, Derivation *D, State *point, Term *term);
void builtin_term_le(Program *program, Derivation *D, State *point, Term *term);
void builtin_term_gt(Program *program, Derivation *D, State *point, Term *term);
void builtin_term_ge(Program *program, Derivation *D, State *point, Term *term);
void builtin_arithmetic_eq(Program *program, Derivation *D, State *point, Term *term);
void builtin_arithmetic_ne(Program *program, Derivation *D, State *point, Term *term);
void builtin_arithmetic_lt(Program *program, Derivation *D, State *point, Term *term);
void builtin_arithmetic_le(Program *program, Derivation *D, State *point, Term *term);
void builtin_arithmetic_gt(Program *program, Derivation *D, State *point, Term *term);
void builtin_arithmetic_ge(Program *program, Derivation *D, State *point, Term *term);
void builtin_typeof(Program *program, Derivation *D, State *point, Term *term);
void builtin_atom(Program *program, Derivation *D, State *point, Term *term);
void builtin_number(Program *program, Derivation *D, State *point, Term *term);
void builtin_char(Program *program, Derivation *D, State *point, Term *term);
void builtin_integer(Program *program, Derivation *D, State *point, Term *term);
void builtin_float(Program *program, Derivation *D, State *point, Term *term);
void builtin_string(Program *program, Derivation *D, State *point, Term *term);
void builtin_ground(Program *program, Derivation *D, State *point, Term *term);
void builtin_list(Program *program, Derivation *D, State *point, Term *term);
void builtin_var(Program *program, Derivation *D, State *point, Term *term);
void builtin_nonvar(Program *program, Derivation *D, State *point, Term *term);
void builtin_atom_length(Program *program, Derivation *D, State *point, Term *term);
void builtin_atom_concat(Program *program, Derivation *D, State *point, Term *term);
void builtin_atom_chars(Program *program, Derivation *D, State *point, Term *term);
void builtin_char_code(Program *program, Derivation *D, State *point, Term *term);
void builtin_findall(Program *program, Derivation *D, State *point, Term *term);
void builtin_is(Program *program, Derivation *D, State *point, Term *term);
void builtin_succ(Program *program, Derivation *D, State *point, Term *term);
void builtin_halt(Program *program, Derivation *D, State *point, Term *term);
void builtin_current_herbrand_flag(Program *program, Derivation *D, State *point, Term *term);
void builtin_set_herbrand_flag(Program *program, Derivation *D, State *point, Term *term);

#endif