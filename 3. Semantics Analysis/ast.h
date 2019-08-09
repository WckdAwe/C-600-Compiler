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

//if
struct ast_if_node{
	Operation op;
	
	struct ast_node *condition;
	struct ast_node *if_branch;
	struct ast_node *else_brach;
}

//while
struct ast_while_node{
	Operation op;
	
	struct ast_node *condition;
	struct ast_node *while_branch;
}

//for
struct ast_for_node{
	Operation op;
	Increment inc;
	struct ast_node *init_condition;
	struct ast_node *end_condition;
	struct ast_node *for_branch;
}

//Ids
struct ast_leaf_node{
	Operation op;
	char *name;
	
	Type_Struct *value;
}

//enum
struct ast_enum_node{
	Operation op;
	char *name;
	
	Type_Struct *ts_value;
	Type_Struct *enumeration;
	
};


//Read/Write
struct ast_io_node{
	Operation op;
	struct ast_node *params;
}

//TODO: write signatures 

#endif

