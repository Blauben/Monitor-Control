#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include <string.h>
#include <stdbool.h>
#include "io.h"

int main(int argc, char **argv) {
    initScreenTargets();
    bool monitors[] = {false, false, false};
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-1") == 0) {
            monitors[0] = true;
        } else if (strcmp(argv[i], "-2") == 0) {
            monitors[1] = true;
        } else if (strcmp(argv[i], "-3") == 0) {
            monitors[2] = true;
        }
    }
    if(argc == 1) {
        args_from_cli(monitors);
    }
    for (int i = 0; i < 3; i++) {
        const int csize = 100;
        char command[csize];
        memset(command,'\0', csize);
        build_command(command, i, monitors);
        printf("Execute:     %s\n",command);
        system(command);
    }
    freeTargets();
    return EXIT_SUCCESS;
}

void build_command(char* command, int screen, const bool *monitors) {
    const char *on = "/enable /TurnOn";
    const char *off = "/TurnOff /disable";
    char target[LINE_LENGTH];
    build_command_target(target, screen);
    sprintf(command, "%s %s %s\n", targets->lib, monitors[screen]?on:off, target);
}

void build_command_target(char* target, int screen) {
    switch (screen) {
        case 0:
            strcpy(target, targets->primary);
            break;
        case 1:
            strcpy(target, targets->secondary);
            break;
        case 2:
            strcpy(target, targets->tertiary);
            break;
        default:
            return;
    }
}


