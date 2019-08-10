#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef __AST_H__
#define __AST_H__

// Operations
typedef struct ast_node{
	Operation op;
	Type type;
	
	AST_Node *left;
	AST_Node *right;
}AST_Node;

// If's
typedef struct ast_if_node{
	Operation op;
	
	AST_Node *condition;
	AST_Node *if_branch;
	AST_Node *else_brach;
} AST_IF_Node;

// While Loop
typedef struct ast_while_node{
	Operation op;
	
	AST_Node *condition;
	AST_Node *while_branch;
}AST_WHILE_Node;

// For loop
typedef struct ast_for_node{
	Operation op;

	//(i=0; i<10; i++)
	AST_Node *start_condition;
	AST_Node *end_condition;
	int increment;

	//{

	//}
	AST_Node *for_branch;
}AST_FOR_Node;

//Leaf for static or ids
typedef struct ast_leaf_node{
	Operation op;
	char *name;

	Type_Struct value;
}



AST_Node *create_ast_node(Operation op, Type type, AST_Node *left, AST_Node *right);
AST_Node *create_ast_if_node(AST_Node *condition, AST_Node *if_branch, AST_Node *else_branch);
AST_Node *create_ast_while_node(AST_Node *condition, AST_Node *while_branch);
AST_Node *create_ast_for_node(AST_Node *start_condition, AST_Node *end_condition, int increment, AST_Node *for_branch);
AST_Node *create_leaf_node(Type_Struct *value, char *name);
#endif

