#include "include/parser.h"
#include "include/scope.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


parser_T* init_parser(lexer_T* lexer){
	parser_T* parser=calloc(1,sizeof(struct PARSER_STRUCT));
	parser->lexer=lexer;
	parser->current_token=lexer_get_next_token(lexer);
	parser->prev_token=parser->current_token;
	parser->scope=init_scope();
	return parser;
}

void parser_eat(parser_T* parser,int token_type){
	if(parser->current_token->type==token_type){
		parser->prev_token=parser->current_token;
		parser->current_token =lexer_get_next_token(parser->lexer);
	}
	else{
		printf("Unexpected token type \'%s\' having token value \'%d\' ", 
			parser->current_token->value,
			parser->current_token->type);
		exit(1);
	}
}

AST_T* parser_parse(parser_T* parser,scope_T* scope){
	return parser_parse_statements(parser,scope);
}


AST_T* parser_parse_statement(parser_T* parser,scope_T* scope){
	if(parser->current_token->type==TOKEN_ID){
		return parser_parse_id(parser,scope);
	}
    return (void*)0;
	
}

// AST_T* parser_parse_statements(parser_T* parser){
// 	AST_T* compound = init_ast(AST_COMPOUND); 
// 	compound->compound_value=calloc(1,sizeof(struct AST_STRUCT*));
// 	AST_T* ast_statement = parser_parse_statement(parser);
// 	compound->compound_value[0]=ast_statement;
// 	compound->compound_size+=1;
	
// 	while(parser->current_token->type==TOKEN_SEMI){
// 		parser_eat(parser,TOKEN_SEMI);
// 		AST_T* ast_statement=parser_parse_statement(parser);
// 		if(ast_statement){
// 		compound->compound_size+=1;
// 		compound->compound_value=realloc(compound->compound_value,compound->compound_size*sizeof(struct AST_STRUCT*));
// 		compound->compound_value[compound->compound_size-1]=parser_parse_statement(parser);

// 		}
// 	}
// 	// if(compound->compound_size>=1)compound->compound_size-1-=1;
// 	return compound;
// }

AST_T* parser_parse_statements(parser_T* parser,scope_T* scope){
	AST_T* compound = init_ast(AST_COMPOUND);
	compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));
	compound->scope=scope;

	AST_T* ast_statement = parser_parse_statement(parser,scope);
	ast_statement->scope=scope;
	compound->compound_value[0] = ast_statement;
	compound->compound_size += 1;

	while (parser->current_token->type == TOKEN_SEMI){
		parser_eat(parser, TOKEN_SEMI);

		AST_T* ast_statement = parser_parse_statement(parser,scope);

		if (ast_statement){
				compound->compound_size += 1;
				compound->compound_value = realloc(
				compound->compound_value,
				compound->compound_size * sizeof(struct AST_STRUCT*)
			);
			compound->compound_value[compound->compound_size-1] = ast_statement;
		}
	}

	return compound;
}

AST_T* parser_parse_expr(parser_T* parser,scope_T* scope){
    switch (parser->current_token->type)
    {
        case TOKEN_STRING: return parser_parse_string(parser,scope);
        case TOKEN_ID: return parser_parse_id(parser,scope);
    }
    return init_ast(AST_NOOP);
}

AST_T* parser_parse_factor(parser_T* parser,scope_T* scope){
}

AST_T* parser_parse_term(parser_T* parser,scope_T* scope){
}

AST_T* parser_parse_function_definition(parser_T* parser,scope_T* scope){
	parser_eat(parser,TOKEN_ID);
	char* function_name=parser->current_token->value;
	AST_T* function_def=init_ast(AST_FUNCTION_DEFINITION);
	function_def->function_definition_name=function_name;
	parser_eat(parser,TOKEN_ID);
	parser_eat(parser,TOKEN_LPAREN);
	AST_T* arg=parser_parse_variable(parser,scope);
	function_def->function_definition_arguments=calloc(1,sizeof(struct AST_STRUCT*));
	function_def->function_definition_arguments_size+=1;
	function_def->function_definition_arguments[0]=arg;
	
	while(parser->current_token->type==TOKEN_COMMA){
		parser_eat(parser,TOKEN_COMMA);
		function_def->function_definition_arguments_size+=1;
		function_def->function_definition_arguments=
			realloc(function_def->function_definition_arguments,
					function_def->function_definition_arguments_size* sizeof(struct AST_STRUCT*));
		AST_T* arg=parser_parse_variable(parser,scope);
		function_def->function_definition_arguments[function_def->function_definition_arguments_size-1]=arg;
	}
	
	parser_eat(parser,TOKEN_RPAREN);
	parser_eat(parser,TOKEN_LBRACE);
	function_def->function_definition_body=parser_parse_statements(parser,scope);
	parser_eat(parser,TOKEN_RBRACE);
	function_def->scope=scope;
	return function_def;
}


AST_T* parser_parse_function_call(parser_T* parser,scope_T* scope){
	AST_T* function_call=init_ast(AST_FUNCTION_CALL);
	char* function_name=parser->prev_token->value;
	function_call->function_call_name=function_name;
	parser_eat(parser,TOKEN_LPAREN);
	function_call->function_call_arguments=calloc(1,sizeof(struct AST_STRUCT*));
	AST_T* fuction_statement=parser_parse_expr(parser,scope);
	function_call->function_call_arguments[0]=fuction_statement;
	function_call->function_call_arguments_size+=1;
	while(parser->current_token->type==TOKEN_COMMA){
		parser_eat(parser,TOKEN_COMMA);
		function_call->function_call_arguments_size+=1;
		function_call->function_call_arguments=realloc(function_call->function_call_arguments,function_call->function_call_arguments_size*sizeof(struct AST_STRUCT*));
		function_call->function_call_arguments[function_call->function_call_arguments_size-1]=parser_parse_expr(parser,scope);		
	}
	parser_eat(parser,TOKEN_RPAREN);
	function_call->scope=scope;
	return function_call;
}

AST_T* parser_parse_variable_definition(parser_T* parser,scope_T* scope){
	parser_eat(parser,TOKEN_ID);// eat "var"
	char* variable_definition_name=parser->current_token->value;
	parser_eat(parser,TOKEN_ID);
	parser_eat(parser,TOKEN_EQUALS);
	AST_T* variable_definition_value=parser_parse_expr(parser,scope);
	AST_T* variable_definition=init_ast(AST_VARIABLE_DEFINITION);
	variable_definition->variable_definition_variable_name=variable_definition_name;
	variable_definition->variable_definition_value=variable_definition_value;
	variable_definition->scope=scope;
	return variable_definition;
}

AST_T* parser_parse_variable(parser_T* parser,scope_T* scope){
	char *token_value=parser->current_token->value;
	parser_eat(parser,TOKEN_ID);
	if(parser->current_token->type==TOKEN_LPAREN)return parser_parse_function_call(parser,scope);

	AST_T* ast_variable=init_ast(AST_VARIABLE);
	ast_variable->variable_name=token_value;
	ast_variable->scope=scope;
	return ast_variable;
}

AST_T* parser_parse_string(parser_T* parser,scope_T* scope){
	char* token_value=parser->current_token->value;
	AST_T* ast_string=init_ast(AST_STRING);
	ast_string->string_value=token_value;
	parser_eat(parser,TOKEN_STRING);
	ast_string->scope=scope;
	return ast_string;
}

AST_T* parser_parse_id(parser_T* parser,scope_T* scope){
	if(strcmp(parser->current_token->value, "def") == 0){
		return parser_parse_variable_definition(parser,scope);
	}
	else if(strcmp(parser->current_token->value,"funk")==0){
		return parser_parse_function_definition(parser,scope);
	}
	else{
		return parser_parse_variable(parser,scope);
	}
	
}
