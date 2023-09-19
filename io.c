#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

#define LINE_COUNT 7

screens* targets;

void read_line(char* buf, FILE* file) {
    fgets(buf, LINE_LENGTH, file );
}

void open_file(FILE** file) {
    if((*file = fopen("screens.txt", "r")) != NULL) {
        return;
    }
    if((*file = fopen("screens.txt", "w")) != NULL) {
        printf("screens.txt was created please fill in the arguments!");
        fprintf(*file, "PRIMARY ID + ON ARGS\nPRIMARY ID + OFF ARGS\nSECONDARY ID + ON ARGS\nSECONDARY ID + OFF ARGS\nTERTIARY ID + ON ARGS\nTERTIARY ID + OFF ARGS\nLIB PATH\n");
        exit(0);
    } else {
        fprintf(stderr, "Monitor File \"screen.txt\" could not be created.\nPlease create it and put two lines for on and off argument lists for each monitor in the file.\nThe seventh line needs to specify the multimonitor library.");
        freeTargets();
        exit(1);
    }
}

void remove_newline(char* str) {
    unsigned long length = strlen(str);
    if(length != 0 && str[length-1] == '\n') {
        str[length-1] = '\0';
    }
}

void* mallocWrapper(size_t size) {
    void* ptr = malloc(size);
    if(!ptr) {
        fprintf(stderr, "Malloc failed!\n");
        exit(1);
    }
    return ptr;
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
    targets->primary= mallocWrapper(sizeof(command));
    targets->secondary=mallocWrapper(sizeof(command));
    targets->tertiary=mallocWrapper(sizeof(command));
    targets->primary->on= mallocWrapper(strlen (buf[0])+1);
    targets->primary->off= mallocWrapper(strlen (buf[1])+1);
    targets->secondary->on= mallocWrapper(strlen (buf[2])+1);
    targets->secondary->off= mallocWrapper(strlen (buf[3])+1);
    targets->tertiary->on= mallocWrapper(strlen (buf[4])+1);
    targets->tertiary->off= mallocWrapper(strlen (buf[5])+1);
    targets->lib= mallocWrapper(strlen(buf[6])+1);
    strcpy(targets->primary->on, buf[0]);
    strcpy(targets->primary->off, buf[1]);
    strcpy(targets->secondary->on, buf[2]);
    strcpy(targets->secondary->off, buf[3]);
    strcpy(targets->tertiary->on, buf[4]);
    strcpy(targets->tertiary->off, buf[5]);
    strcpy(targets->lib, buf[6]);
}

void freeTargets() {
    free(targets->primary->on);
    free(targets->primary->off);
    free(targets->secondary->on);
    free(targets->secondary->off);
    free(targets->tertiary->on);
    free(targets->tertiary->off);
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
