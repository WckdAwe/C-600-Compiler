#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h" 
#include "general.h"


AST_Node *create_ast_node(Operation op, Type type, AST_Node *left, AST_Node *right){
	AST_Node *ast_node = emalloc(sizeof(AST_Node));
	
	ast_node->op = op;
	ast_node->type = type;
	
	ast_node->left = left;
	ast_node->right = right;

	return ast_node;
}


AST_Node *create_ast_if_node(AST_Node *condition, AST_Node *if_branch, AST_Node *else_branch){
	
	AST_IF_Node *ast_node = emalloc(sizeof(AST_IF_Node));

	ast_node->op = IF;

	ast_node->condition = condition;
	ast_node->if_branch = if_branch;
	ast_node->else_brach = else_branch;
  
	return (AST_Node *) ast_node;
}


AST_Node *create_ast_while_node(AST_Node *condition, AST_Node *while_branch){
	
	AST_WHILE_Node *ast_node = emalloc(sizeof(AST_WHILE_Node));

	ast_node->op = WHILE;

	ast_node->condition = condition;
	ast_node->while_branch = while_branch;
  
	return (AST_Node *) ast_node;
}


AST_Node *create_ast_for_node(AST_Node *start_condition, AST_Node *end_condition, int increment, AST_Node *for_branch){
	AST_FOR_Node *ast_node = emalloc(sizeof(AST_FOR_Node));

	ast_node->op = FOR;

	ast_node->start_condition = start_condition;
	ast_node->end_condition = end_condition;
	ast_node->increment = increment;
	ast_node->for_branch = for_branch;

	return (AST_Node *) ast_node;
}

AST_Node *create_leaf_node(Type_Struct *value, char *name){
	struct ast_leaf_node *ast_node = emalloc(sizeof(struct ast_leaf_node));

	ast_node->op = LEAF;
	ast_node->name = name;

	ast_node->value = value;

	return (struct ast_node*) ast_node;
}

AST_Node *new_ast_enum_leaf_node(Type_Struct *ts_value, char *name, Type_Struct *enumeration){
	struct ast_enum_leaf_node *ast_node = emalloc(sizeof(struct ast_enum_leaf_node));

	ast_node->op = ENUM;
	ast_node->values = ts_value;
	ast_node->name = name;
	ast_node->enumeration = enumeration;

	return (struct AST_Node*) ast_node;
	
}