#include <stdio.h>
#include <string.h>
#include "include/visitor.h"

/*-----------Static Functions Start-----------*/

static void builtin_print_function(visitor_T* visitor,AST_T** function_call_arguments,int function_call_arguments_size){
	for(int i=0;i<function_call_arguments_size;i++){
		// printf("%d \n",function_call_arguments[i]->type);
		AST_T* visited_node=visitor_visit(visitor,function_call_arguments[i]);
		if(visited_node->type==AST_STRING)printf("%s \n",visited_node->string_value);
	}
	return ;
}

/*------------Static Functions End------------*/


visitor_T* init_visitor(){
	visitor_T* visitor = calloc(1,sizeof(struct VISITOR_STRUCT));
	visitor->variable_definitions=(void*)0;
	visitor->variable_definitions_size=0;
	return visitor;
}

AST_T* visitor_visit(visitor_T* visitor,AST_T* node){
	if(node->type==AST_VARIABLE_DEFINITION)return visitor_visit_variable_definition(visitor,node);
	else if(node->type==AST_FUNCTION_DEFINITION)return visitor_visit_function_definition(visitor,node);
	else if(node->type==AST_VARIABLE)return visitor_visit_variable(visitor,node);
	else if(node->type==AST_FUNCTION_CALL)return visitor_visit_function_call(visitor,node);
	else if(node->type==AST_STRING)return visitor_visit_string(visitor,node);
	else if(node->type==AST_COMPOUND)return visitor_visit_compound(visitor,node);
	
	printf("Unidentified statement of type :  %d\n", node->type);
	exit(1);

	return (void*)0;
}

AST_T* visitor_visit_variable_definition(visitor_T* visitor, AST_T* node){
	if(visitor->variable_definitions==(void*)0){
		visitor->variable_definitions=calloc(1,sizeof(struct AST_T*));
		visitor->variable_definitions_size=1;
		visitor->variable_definitions[0]=node;
	}
	else{
		visitor->variable_definitions_size+=1;
		visitor->variable_definitions=realloc(visitor->variable_definitions, visitor->variable_definitions_size*sizeof(struct AST_T*));
		visitor->variable_definitions[visitor->variable_definitions_size-1]=node;
	}
	return node;
}

AST_T* visitor_visit_function_definition(visitor_T* visitor, AST_T* node){
}

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node){
	for(int i=0;i<visitor->variable_definitions_size;i++){
		if(strcmp(visitor->variable_definitions[i]->variable_definition_variable_name,node->variable_name)==0){
			// printf("%d \n",visitor->variable_definitions[i]->variable_definition_value->type);
			return visitor_visit(visitor,visitor->variable_definitions[i]->variable_definition_value);
		}
	}
	printf("Unidentified variable name `%s` \n", node->variable_name);
	return (void*)0;
}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node){
	// printf("%s \n",node->function_call_name);
	if(strcmp(node->function_call_name,"out")==0){
		builtin_print_function(visitor,node->function_call_arguments,node->function_call_arguments_size);
	}
	return (void*)0;
}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node){
	return node;
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node){
	for(int i=0;i<node->compound_size;i++){
		visitor_visit(visitor,node->compound_value[i]);
	}
	return (void*)0;
}

