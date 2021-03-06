#include<stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"

int main(int argc, char const *argv[]){
	lexer_T* lexer=init_lexer("def name = \"Jatta\";\n out(name);\n");
	parser_T* parser=init_parser(lexer);
	AST_T* ast=parser_parse(parser);
	visitor_T* visitor=init_visitor();
	visitor_visit(visitor,ast);
	// printf("%d\n", ast->type);
	// printf("%d\n", ast->compound_size);

	return 0;
}
