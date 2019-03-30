/*H*
 * 
 * FILENAME: semantics.c
 * DESCRIPTION: Declarative semantics for the language
 * AUTHORS: José Antonio Riaza Valverde
 * UPDATED: 30.03.2019
 * 
 *H*/

#include "semantics.h"



/**
  * 
  * This function creates a derivation from a new goal,
  * returning a pointer to a newly initialized Derivation
  * struct.
  *
  **/
Derivation *semantics_query(Term *goal) {
	Derivation *D = derivation_alloc();
	State *state = state_init_goal(goal);
	derivation_push_state(D, state);
	return D;
}

/**
  * 
  * This function finds and returns the next computed
  * answer of a derivation.
  *
  **/
Substitution *semantics_answer(Program *program, Derivation *D) {
	int i;
	State *point, *state;
	Rule *rule;
	Clause *clause;
	Term *term, *body;
	Substitution *mgu;
	while(1) {
		point = derivation_pop_state(D);
		// If no more points, there are no more answers
		if(point == NULL)
			return NULL;
		derivation_push_visited_state(D, point);
		term = term_select_most_left(point->goal);
		// If no more terms, this choice point is an answer
		if(term == NULL)
			return point->substitution;
		// Else, do a resolution step
		// If not callable, error
		//if(!term_is_callable(term))
			// error
		// If is a built-in predicate
		if(builtin_check_predicate(term_list_get_head(term))) {
			builtin_run_predicate(program, D, point, term);
		} else {
			rule = program_get_rule(program, term->term.list->head->term.string);
			// If rule does not exist, fail
			if(rule == NULL)
				continue;
			// For each clause in the rule, check unification
			for(i = rule->nb_clauses-1; i >= 0; i--) {
				clause = clause_rename_variables(rule->clauses[i], &(program->renames));
				mgu = semantics_unify_terms(term->term.list->tail, clause->head, 0);
				if(mgu != NULL) {
					state = state_inference(point, clause->body, mgu);
					derivation_push_state(D, state);
					substitution_free(mgu);
				}
				clause_free(clause);
			}
		}
	}
}