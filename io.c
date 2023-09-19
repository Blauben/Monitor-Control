#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

#define LINE_COUNT 4

screens* targets;

void read_line(char* buf, FILE* file) {
    fgets(buf, LINE_LENGTH, file );
}

void open_file(FILE** file) {
    if((*file = fopen("screens.txt", "r")) == NULL) {
        fprintf(stderr, "Monitor File \"screen.txt\" could not be opened.\nPlease create it and put the identifier for the first monitor in the first line etc...\nThe fourth line needs to specify the multimonitor library.");
        freeTargets();
        exit(1);
    }
}

void remove_newline(char* str) {
    unsigned long length = strlen(str);
    if(str[length-1] == '\n') {
        str[length-1] = '\0';
    }
}

void initScreenTargets() {
    targets = malloc(sizeof (screens));
    FILE* file;
    open_file(&file);
    char buf[LINE_COUNT][LINE_LENGTH];
    for(int i = 0; i < LINE_COUNT; i++) {
        memset(buf[i],'\0',LINE_LENGTH);
        read_line(buf[i], file);
        remove_newline(buf[i]);
    }
    fclose(file);
    targets->primary= malloc(strlen (buf[0])+1);
    targets->secondary=malloc(strlen (buf[1])+1);
    targets->tertiary=malloc(strlen (buf[2])+1);
    targets->lib= malloc(strlen(buf[3])+1);
    if(!targets || !targets->primary || !targets->secondary || !targets->tertiary || !targets->lib) {
        fprintf(stderr, "Malloc failed!\n");
        freeTargets();
        exit(1);
    }
    strcpy(targets->primary, buf[0]);
    strcpy(targets->secondary, buf[1]);
    strcpy(targets->tertiary, buf[2]);
    strcpy(targets->lib, buf[3]);
}

void freeTargets() {
    free(targets->primary);
    free(targets->secondary);
    free(targets->tertiary);
    free(targets->lib);
    free(targets);
}

void extract_indices(char* buf, bool* monitors) {
    char* num_str = strtok(buf, " ");
    while(num_str != NULL) {
        char **err = NULL;
        unsigned long index = strtol(num_str, err, 10);
        if (num_str != NULL && err == NULL && index > 0 && index <= 3) {
            monitors[index-1] = true;
        }
        num_str = strtok(NULL, " ");
    }
}

void args_from_cli(bool* monitors) {
    printf("Please enter the indices (primary 1, secondary 2, tertiary 3) of the monitors to be switched on, the others will be turned off!\n");
    const int buf_size = 100;
    char buf[buf_size];
    memset(buf, '\0', buf_size);
    fgets(buf, buf_size, stdin);
    extract_indices(buf, monitors);
}
