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
        if (strcmp(argv[i], "primary") == 0 || strcmp(argv[i], "p")) {
            monitors[0] = true;
        } else if (strcmp(argv[i], "secondary") == 0 || strcmp(argv[i], "s")) {
            monitors[1] = true;
        } else if (strcmp(argv[i], "tertiary") == 0 || strcmp(argv[i], "t")) {
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
        printf("%s\n",command);
        //system(command);
    }
    return EXIT_SUCCESS;
}

void build_command(char* command, int screen, bool *monitors) {
    const char *exe = "F:\\Programme\\multimonitortool_1.96\\MultiMonitorTool.exe ";
    const char *on = "/TurnOn ";
    const char *off = "/disable ";
    char target[LINE_LENGTH];
    build_command_target(target, screen);
    strcpy(command, exe);
    strcat(command, monitors[screen] ? on : off);
    strcat(command, target);
}

void build_command_target(char* target, int screen) {
    switch (screen) {
        case 0:
            strcpy(target, targets.primary);
            break;
        case 1:
            strcpy(target, targets.secondary);
            break;
        case 2:
            strcpy(target, targets.tertiary);
            break;
    }
}


