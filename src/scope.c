#include "include/scope.h"
#include <string.h>
scope_T* init_scope(){
	scope_T* scope=calloc(1,sizeof(struct SCOPE_STRUCT));
	scope->function_definitions=(void*)0;
	scope->function_definitions_size=0;
	scope->variable_definitions=(void*)0;
	scope->variable_definitions_size=0;
	return scope;
}

AST_T* scope_add_function_definition(scope_T* scope, AST_T* fdef){
	if(scope->function_definitions==(void*)0){
		scope->function_definitions=calloc(1,sizeof(struct AST_STRUCT*));
		scope->function_definitions_size=1;
		scope->function_definitions[0]=fdef;
	}
	else{
		scope->function_definitions_size+=1;
		scope->function_definitions=realloc(scope->function_definitions,
			scope->function_definitions_size * sizeof(struct AST_STRUCT**));
		scope->function_definitions[scope->function_definitions_size-1]=fdef;
	}
	return fdef;
}

AST_T* scope_get_function_definition(scope_T* scope, char* fname){
	for(int i=0;i<scope->function_definitions_size;i++){
		if(strcmp(fname,scope->function_definitions[i]->function_definition_name)==0)return scope->function_definitions[i];
	}
	return (void*)0; 
}

AST_T* scope_add_variable_definition(scope_T* scope, AST_T* node){
	if(scope->variable_definitions==(void*)0){
		scope->variable_definitions=calloc(1,sizeof(struct AST_T*));
		scope->variable_definitions_size=1;
		scope->variable_definitions[0]=node;
	}
	else{
		scope->variable_definitions_size+=1;
		scope->variable_definitions=realloc(scope->variable_definitions, scope->variable_definitions_size*sizeof(struct AST_T*));
		scope->variable_definitions[scope->variable_definitions_size-1]=node;
	}
	return node;
}

AST_T* scope_get_variable_definition(scope_T* scope, char* name){
	for(int i=0;i<scope->variable_definitions_size;i++){
		if(strcmp(name,scope->variable_definitions[i]->variable_definition_variable_name)==0)return scope->variable_definitions[i];
	}
	return (void*)0; 
}

