#include<stdio.h>
#include "include/lexer.h"
#include "include/parser.h"

int main(int argc, char const *argv[]){
	lexer_T* lexer=init_lexer("var name = \"Jatta\";\n print(name);\n");
	parser_T* parser=init_parser(lexer);
	AST_T* ast=parser_parse(parser);
	printf("%d\n", ast->type);
	printf("%d\n", ast->compound_size);

	return 0;
}
