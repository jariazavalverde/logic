/*H*
 * 
 * FILENAME: unification.c
 * DESCRIPTION: Functions for syntactic unification
 * AUTHORS: José Antonio Riaza Valverde
 * UPDATED: 30.03.2019
 * 
 *H*/

#include "unification.h"



/**
  * 
  * This function returns the most general unifier of two terms.
  * If terms are not unifiable, returns NULL.
  * 
  **/
Substitution *semantics_unify_terms(Term *term1, Term *term2, int occurs_check) {
	Substitution *subs;
	if(
		term1->type == TYPE_VARIABLE && strcmp(term1->term.string, "_") == 0 ||
		term2->type == TYPE_VARIABLE && strcmp(term2->term.string, "_") == 0
	) {
		return substitution_alloc(0);
	} else if(term1->type == TYPE_VARIABLE) {
		subs = substitution_alloc(1);
		substitution_add_link(subs, term1->term.string, term2);
		return subs;
	} else if(term2->type == TYPE_VARIABLE) {
		subs = substitution_alloc(1);
		substitution_add_link(subs, term2->term.string, term1);
		return subs;
	} else if(term1->type == term2->type) {
		switch(term1->type) {
			case TYPE_LIST:
				return semantics_unify_lists(term1, term2, occurs_check); 
			case TYPE_ATOM:
				return semantics_unify_atoms(term1, term2);
			case TYPE_STRING:
				return semantics_unify_strings(term1, term2);
			case TYPE_NUMERAL:
				return semantics_unify_numerals(term1, term2);
			case TYPE_DECIMAL:
				return semantics_unify_decimals(term1, term2);
			default:
				return NULL;
		}
	}
	return NULL;
}

/**
  * 
  * This function returns the most general unifier of two lists.
  * If lists are not unifiable, returns NULL.
  * 
  **/
Substitution *semantics_unify_lists(Term *term1, Term *term2, int occurs_check) {
	int i = 0;
	Term *list1, *list2, *term_ap1 = NULL, *term_ap2 = NULL;
	Substitution *mgu, *subs2, *subs;
	if(term_list_is_null(term1) && term_list_is_null(term2))
		return substitution_alloc(0);
	else if(term_list_is_null(term1) || term_list_is_null(term2))
		return NULL;
	subs = substitution_alloc(0);
	while(term1->type == TYPE_LIST && term2->type == TYPE_LIST
	&& !term_list_is_null(term1) && !term_list_is_null(term2)) {
		mgu = semantics_unify_terms(
			term_list_get_head(term1),
			term_list_get_head(term2),
			occurs_check);
		if(mgu == NULL) {
			if(i > 0) {
				term_free(term1);
				term_free(term2);
			}
			substitution_free(subs);
			return NULL;
		}
		subs2 = substitution_compose(subs, mgu, 1);
		term_ap1 = term_apply_substitution(term_list_get_tail(term1), mgu);
		term_ap2 = term_apply_substitution(term_list_get_tail(term2), mgu);
		if(i > 0) {
			term_free(term1);
			term_free(term2);
		}
		term1 = term_ap1;
		term2 = term_ap2;
		substitution_free(subs);
		substitution_free(mgu);
		subs = subs2;
		i++;
	}
	mgu = semantics_unify_terms(term1, term2, occurs_check);
	if(i > 0) {
		term_free(term1);
		term_free(term2);
	}
	if(mgu == NULL) {
		substitution_free(subs);
		return NULL;
	}
	subs2 = substitution_compose(subs, mgu, 1);
	substitution_free(subs);
	substitution_free(mgu);
	return subs2;
}

/**
  * 
  * This function returns the most general unifier of two numerals.
  * If numerals are not unifiable, returns NULL.
  * 
  **/
Substitution *semantics_unify_numerals(Term *num1, Term *num2) {
	if(num1->term.numeral ==  num2->term.numeral)
		return substitution_alloc(0); 
	return NULL;
}

/**
  * 
  * This function returns the most general unifier of two decimals.
  * If decimals are not unifiable, returns NULL.
  * 
  **/
Substitution *semantics_unify_decimals(Term *dec1, Term *dec2) {
	if(dec1->term.decimal == dec2->term.decimal)
		return substitution_alloc(0); 
	return NULL;
}

/**
  * 
  * This function returns the most general unifier of two atoms.
  * If atoms are not unifiable, returns NULL.
  * 
  **/
Substitution *semantics_unify_atoms(Term *atom1, Term *atom2) {
	if(strcmp(atom1->term.string, atom2->term.string) == 0)
		return substitution_alloc(0); 
	return NULL;
}

/**
  * 
  * This function returns the most general unifier of two strings.
  * If strings are not unifiable, returns NULL.
  * 
  **/
Substitution *semantics_unify_strings(Term *str1, Term *str2) {
	if(strcmp(str1->term.string, str2->term.string) == 0)
		return substitution_alloc(0); 
	return NULL;
}