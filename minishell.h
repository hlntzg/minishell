/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:53:06 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/29 10:53:15 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>		/* readline */
#include <readline/readline.h>	/* readline */
#include <readline/history.h>	/* readline */
#include <signal.h>		/* signals */
#include <termios.h>		/* terminal attributs */

typedef enum input_type {
	WORD = 1,
	PIPE = 2,
	REDIN = 3,
	REDOUT = 4,
	APPEND = 5,
	HEREDOC = 6,
	ENVMT = 7,
	BUILTIN = 8
}	token_type;

typedef struct s_data
{
	char	*prompt;
}	t_data;

typedef struct s_tok
{
	token_type input;
	void	*content;
	t_tok	*next;
}	t_tok;

/*AST example 1*/
typedef struct Parser
{
	enum { WORD, PIPE, REDIN, REDOUT, APPEND, HEREDOC, ENVMT, 
			BUILTIN} type;
	union {
		// lots of specific things for each type of token
		int		integerExp;
        char	*stringExp;
        char	*variableExp;
        struct { char	*operator;
                   struct Exp*      left;
                   struct Exp*      right; }       binaryExp;
        struct { char	*operator;
                   struct Exp*      operand; }     unaryExp;
          struct { char	*name;
                   struct Exp_list* arguments; }   callExp;
          struct { struct Exp*  record;
                   char	*attribute; }       projectionExp;
          struct rec { char	*attribute;
                       struct Exp*  value;
                       struct rec*  next; }        recordExp;
	} tokens;
} ast;

//Exp_list: a list of ASTs;
typedef struct Exp_list { 
  ast*             elem;
  struct Exp_list* next;
} ast_list;

/* It's a good idea to define a constructor for every kind of 
expression to simplify the task of constructing ASTs:
ast* make_binaryExp ( string operator, ast* left, ast* right ) {
  ast* e = (ast*) malloc(sizeof(ast));
  e->tag = binary_exp;
  e->op.binary.operator = operator;
  e->op.binary.left = left;
  e->op.binary.right = right;
  return e;
};
For example,
make_binaryExp("+",make_binaryExp("-",make_variableExp("x"),make_integerExp(2)),
               make_integerExp(3))
constructs the AST for the input (x-2)+3. */


AST example 2
Tagged union
We define our AST type as a struct holding two members,

an enum called tag, enumerating each node type, and
a union called data, consisting of data members for each tag type.
typedef struct AST AST; // Forward reference

struct AST {
  enum {
    AST_NUMBER,
    AST_ADD,
    AST_MUL,
  } tag;
  union {
    struct AST_NUMBER { int number; } AST_NUMBER;
    struct AST_ADD { AST *left; AST *right; } AST_ADD;
    struct AST_MUL { AST *left; AST *right; } AST_MUL;
  } data;
} ast; 

//void	set_signals(void);

#endif
