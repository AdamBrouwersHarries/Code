#ifndef UTILITY_H
#define UTILITY_H
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"
//define useful boolean types
#define AH_UTIL_BOOL char
#define AH_UTIL_FALSE 0
#define AH_UTIL_TRUE 1
/*
 * Read a ascii file into a single c string (char array)
 * 
 * This function dynamically allocates memory, and returns a pointer to it
 * this memory must be freed after use to avoid a memory leak
 * 
 * Arguments:
 * 		filename: the (relative) path of the file to read in
 * Returns:
 * 		A c string containing the data in the file
 * */
char* file_to_cstring(char* filename)
{
	FILE* inFile;
	int c;
	inFile = fopen(filename, "r");
	if(inFile==NULL)
	{
		return NULL;
	}else{
		int buffer_size = 1;
		char* buffer = malloc(1);
		c = fgetc(inFile);
		while(c!=EOF)
		{
			buffer = (char*)realloc(buffer, ++buffer_size);
			buffer[buffer_size-2] = c;
			c = fgetc(inFile);
		}
		buffer[buffer_size-1] = '\0';
		return buffer; //don't forget to free buffer after use!
	}	
}
/*
 * Takes a string, and returns an array of tokens (c strings) by breaking 
 * the string at any of the delimiter characters. 
 * Ignores/removes delimiter characters
 * 
 * 
 * Arguments:
 * 		data: the string to split
 * 		delimiter: the list of delimiters to split on
 * 		token list: a pointer to an array of c strings, which is populated
 * 					with the tokens split from the original string
 * Returns:
 * 		The number of tokens the string has been split in to.
 * */
int cstring_to_token_array(char* data,char* delimiter,char*** token_list)
{
	char* token_iterator;
	char** output_array = malloc(sizeof(char*));
	output_array = NULL;
	int index = 1;
	token_iterator = strtok(data,delimiter);
	while(token_iterator!=NULL)
	{
		char* buffer = calloc(strlen(token_iterator)+1,sizeof(char));
		strcpy(buffer, token_iterator);
		output_array = realloc(output_array, sizeof(char*)*index);
		output_array[index-1] = buffer;
		index++;
		token_iterator = strtok(NULL, delimiter);		
	}
	*token_list = output_array;
	return index-1;
}
#endif

