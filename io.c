#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

#define LINE_COUNT 3

screens targets;

void read_line(char* buf, FILE* file) {
    for(int i=0; i<LINE_COUNT;i++) {
        fgets(buf, LINE_LENGTH, file );
    }
}

void open_file(FILE** file) {
    if((*file = fopen("screens.txt", "r")) == NULL) {
        fprintf(stderr, "Monitor File \"screen.txt\" could not be opened. Please create it and put the identifier for the first monitor in the first line etc...");
        getchar();
        exit(1);
    }
}

void initScreenTargets() {
    printf("Initializing Screen IDs.\n");
    FILE* file;
    open_file(&file);
    char buf[LINE_COUNT][LINE_LENGTH];
    for(int i = 0; i < LINE_COUNT; i++) {
        memset(buf[i],'\0',LINE_LENGTH);
        read_line(buf[i], file);
    }
    fclose(file);
    targets.primary=buf[0];
    targets.secondary=buf[1];
    targets.tertiary=buf[2];
    printf("%s\n", targets.primary);
    printf("%s\n", targets.secondary);
    printf("%s\n", targets.tertiary);
}

void extract_indices(char* buf, bool* monitors) {
    char* num_str = strtok(buf, " ");
    while(num_str != NULL) {
        int index = atoi(num_str);
        if (index > 0 && index <= 3) {
            monitors[index] = true;
        }
        num_str = strtok(NULL, " ");
    }
}

void args_from_cli(bool* monitors) {
    printf("Please enter the indices of the monitors to be switched on, the others will be turned off!\n");
    const int buf_size = 100;
    char buf[buf_size];
    fgets(buf, buf_size, stdin);
    extract_indices(buf, monitors);
}
