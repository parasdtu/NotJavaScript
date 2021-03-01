#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "AST.h"


typedef struct PARSER_STRUCT{
    lexer_T* lexer;
    token_T* current_token;
    token_T* prev_token;

} parser_T;

parser_T* init_parser(lexer_T* lexer);

void parser_eat(parser_T* parser, int token_type);// eats the current token if current lexer token == expected token 

AST_T* parser_parse(parser_T* parser); //returns AST ROOT

AST_T* parser_parse_statement(parser_T* parser);//parse indiviudal statement

AST_T* parser_parse_statements(parser_T* parser);//parses the whole source code

AST_T* parser_parse_expr(parser_T* parser);//parses the TOKEN_ID,TOKEN_STRING

AST_T* parser_parse_factor(parser_T* parser);

AST_T* parser_parse_term(parser_T* parser);

AST_T* parser_parse_function_call(parser_T* parser);
        
AST_T* parser_parse_variable_definition(parser_T* parser);

AST_T* parser_parse_function_definition(parser_T* parser);

AST_T* parser_parse_variable(parser_T* parser);

AST_T* parser_parse_string(parser_T* parser);

AST_T* parser_parse_id(parser_T* parser);// parses TOKEN_ID example->identifiers, keywords

#endif