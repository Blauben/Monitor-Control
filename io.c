/*
 * commands.c
 *
 *  Created on: 23.04.2022
 *      Author: Balthazar
 */

#include <stdlib.h>
#include "io.h"

int* def_enum() {
	char** string= open_file();
	int first, second, third;
	for(int i=0; i<3; i++) {
		char* line=string[i];
		int value=*(strchr(line, "=")+1);
		assign_enum(line, value);
		}
	return assign_enum(NULL, 0);
}

static int* assign_enum(char* line, int valueOfScreen) {
	static int values[3];

	static char* keys[3]={"primary","secondary","tertiary"};

	if(line == NULL || valueOfScreen == 0) {
		return &values;
	} else {
		for(int i=0; i<3;i++) {
			if (strstr(line, keys[i]) != NULL) {
				values[i]=valueOfScreen;
			}
		}
	}
	return NULL;
}

static char** open_file() {
	FILE *file;
	if((file = fopen("screens.txt", "r")) == NULL) {
		printf("Monitor File could not be opened");
		exit(1);
	} else {
		return read_file(file);
	}
}

static char** read_file(FILE* file) {
	char buf[3][30];
	for(int i=0; i<3;i++) {
		while(fgets(buf[i], siezof(buf[i]), file )!=0);
	}
	return &buf;
}
