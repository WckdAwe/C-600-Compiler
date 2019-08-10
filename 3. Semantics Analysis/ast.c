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