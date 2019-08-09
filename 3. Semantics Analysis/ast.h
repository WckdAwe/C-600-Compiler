#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttypes.h"

#ifndef ast
#define ast


typedef struct ast_node{
	Operation op;
	Type type;
	
	struct ast_node *left;
	struct ast_node *right;
}AST_node;

struct ast_if_node{
	Operation op;
	
	struct ast_node *condition;
	struct ast_node *if_branch;
	struct ast_node *else_brach;
}

struct ast_while_node{
	Operation op;
	
	struct ast_node *condition;
	struct ast_node *while_branch;
}

struct ast_for_node{
	Operation op;
	Increment inc;
	struct ast_node *init_condition;
	struct ast_node *end_condition;
	struct ast_node *for_branch;
}

