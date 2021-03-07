#include <stdio.h>
#include <stdlib.h>
#include "include/io.h"

char* get_file_contents(const char* filepath){
	char* contents = (void*)0;
	FILE* f=fopen(filepath,"r");

	if(f){
		int file_size=0;
		fseek(f,0,SEEK_END);
		file_size=ftell(f);
		fseek(f,0,SEEK_SET);

		contents=calloc(file_size,file_size);
		if(contents) fread(contents,1,file_size,f);
		fclose(f);
		return contents;
	}
	else{
		printf("Error: File not found!\n");
		exit(2);
	}
	
	exit(3);
}