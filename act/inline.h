/*************************************************************************
 *
 *  Copyright (c) 2021 Rajit Manohar
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 *
 **************************************************************************
 */
#ifndef __ACT_INLINE_H__
#define __ACT_INLINE_H__

#include <act/expr.h>
#include <act/act_id.h>

struct act_inline_table;

/**
 * @file inline.h
 *
 * @brief Helper functions to handle function inlining. Used to
 * inline simple functions (without internal loops) and return a
 * single expression that corresponds to the inlined function. This is
 * done by keeping track of current bindings of all variables to a
 * symbolic expression, and updating the symbolic expression as you
 * go through the function definition.
 */

/**
 * Create a new inline table linked to a parent in the current scope
 * @param sc is the current scope
 * @param parent is the parent inline table
 * @param ismacro is set to true if this is used for macro expansion,
 * false otherwise
 * @return a new inline table
 */
act_inline_table *act_inline_new (Scope *sc, act_inline_table *parent,
				  bool ismacro = false);

/**
 * Release storage for a previously allocated inline table
 */
void act_inline_free (act_inline_table *);

/**
 * Set an identifier to an expression. An expression array is provided
 * in case the identifier corresponds to a structure. The inline table
 * bindings are updated.
 *
 * @param Hs is the current inline binding table
 * @param id is the identifier to be set
 * @param e is the array of expressions for values (e[0] will contain
 * the value if the  * identifier is simple one)
 */
void act_inline_setval (act_inline_table *Hs, ActId *id, Expr **e);

/**
 * @param Hs is the current inline binding table
 * @param s is the name of the identifier
 * @return the binding for an identifier from the table
 */
Expr **act_inline_getval (act_inline_table *Hs, const char *s);

/**
 * @param tab is the current inline binding table
 * @param s is the identifier to search for
 * @returns 1 if there is a binding present, 0 otherwise
 */
int act_inline_isbound (act_inline_table *, const char *s);

/**
 * Return the result of inlining all function calls into the
 * expression specified. The result might be a structure, so this
 * returns an array of expressions.
 */
Expr **act_inline_expr (act_inline_table *, Expr *, int recurse_fn = 1);

/**
 * Return the simple result of inlining all function calls into the
 * expression specified. If the result is a structure, the first item
 * from the structure is returned.
 */
Expr *act_inline_expr_simple (act_inline_table *, Expr *, int recurse_fn = 1);

/**
 * Given inline tables corresponding to a set of conditions (e.g. via
 * a selection statement), this computes unified expressions that
 * combine the guard to select the correct expression result.
 */
act_inline_table *act_inline_merge_tables (int nT, act_inline_table **T, Expr **cond);

#endif /*  __ACT_INLINE_H__ */
