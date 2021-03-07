#include<stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

int main(int argc, char *argv[]){
	char *temp=get_file_contents(argv[1]);
	// printf("%s\n", temp );
	lexer_T* lexer=init_lexer(temp);
	parser_T* parser=init_parser(lexer);
	AST_T* ast=parser_parse(parser);
	visitor_T* visitor=init_visitor();
	visitor_visit(visitor,ast);
	// printf("%d\n", ast->type);
	// printf("%d\n", ast->compound_size);

	return 0;
}
