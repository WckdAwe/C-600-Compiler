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



AST__DECL_node* new_single_decl_node(Type variable_type, char* id)
{   	AST_DECL_node* new_node;
   	new_node = (AST_DECL_node*)malloc(sizeof(AST_DECL_node))
	
    	new_node->variable_type=variable_type;
    	new_node->id=id
    	new_node->dim=0;
		//initial value? there could be none.	
    	return new_node;
}

AST_node* new_exp_node(Operation op_type , AST_NODE* left_exp , AST_NODE* right_exp) 
//exp 'OP' exp : (op,exp,exp)
{
    	AST_node* new_node ; 
    	new_node = (AST_node*)malloc(sizeof(AST_node)); 

    	new_node->left=left_exp;
    	new_node->right=right_exp;
    	new_node->op_type=op_type;

    	return new_node;
} 

AST_node* new_asgn_node(AST_NODE* variable,AST_NODE* value)
{
	AST_ASGN_node = new_node;
	new_node = (AST_ASGN_node*)malloc(sizeof(ASGN_node));

	new_node->op_type=ASSIGN;
	new_node->left=variable;
	new_node->right=value; //or expression

	return new_node;
	
}

AST_node* new_condition_node(Operation op_type,AST_NODE* expr1,AST_NODE* expr2)
{
	AST_node* new_node;
	new_node = (AST_node*)malloc(sizeof(AST_node));
	
	new_node->left = expr1;
	new_node->right = expr2;
	new_node->op_type = op_type; //EQUOP , OROP ,ANDOP , RELOP

	
}


//const data nodes
AST_node* new_iconst_node(int data)
{
	AST_node *new_node;
	new_node = (AST_node*)malloc(sizeof(AST_node));
	
	new_node->op_type=LEAF;
	new_node->node_data->intdata=data;
	new_node->left=NULL;
	new_node->right=NULL;

	return new_node;
}

AST_node* new_fconst_data(float data)
{
	AST_node *new_node;
	new_node = (AST_node*)malloc(sizeof(AST_node));
	
	new_node->op_type=LEAF;
	new_node->node_data->float=data;
	new_node->left=NULL;
	new_node->right=NULL;

	return new_node;

}


AST_node* new_cconst_node(char data)
{
	AST_node *new_node;
	new_node = (AST_node*)malloc(sizeof(AST_node));
	
	new_node->op_type=LEAF;
	new_node->node_data->chardata=data;
	new_node->left=NULL;
	new_node->right=NULL;

	return new_node;

}

AST_node* new_sconst_node(char* data)
{
	AST_CONST *new_node;
	new_node = (AST_node*)malloc(sizeof(AST_node));
	
	new_node->op_type=LEAF;
	new_node->node_data->strdata=data;
	new_node->left=NULL;
	new_node->right=NULL;

	return new_node;

}

