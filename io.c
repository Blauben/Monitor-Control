#include <stdlib.h>
#include <stdio.h>
#include "io.h"

#define LINE_COUNT 3

screens targets;

void read_line(char* buf, FILE* file) {
    for(int i=0; i<LINE_COUNT;i++) {
        fgets(buf, LINE_LENGTH, file );
    }
}

FILE* open_file(FILE* file) {
    if((file = fopen("screens", "r")) == NULL) {
        fprintf(stderr, "Monitor File \"screen\" could not be opened. Please create it and put the identifier for the first monitor in the first line ect...");
        exit(1);
    }
}

void initScreenTargets() {
    FILE file;
    open_file(&file);
    char buf[LINE_COUNT][30];
    for(int i = 0; i < LINE_COUNT; i++) {
        read_line(buf[i], &file);
    }
    targets.primary=buf[0];
    targets.secondary=buf[1];
    targets.tertiary=buf[2];
}
