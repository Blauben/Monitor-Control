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
        printf("Please specify which monitors to turn on, the others will be turned off!\n");
    }
    for (int i = 0; i < 3; i++) {
        char command[100];
        build_command(command, i, monitors);
        system(command);
    }
    return EXIT_SUCCESS;
}

void build_command(unsigned char* command, int screen, bool *monitors) {
    const unsigned char *exe = "F:\\Programme\\multimonitortool_1.96\\MultiMonitorTool.exe ";
    const unsigned char *on = "/TurnOn ";
    const unsigned char *off = "/disable ";
    unsigned char target[LINE_LENGTH];
    build_command_target(target, screen);
    strcpy(command, exe);
    strcat(command, monitors[screen] ? on : off);
    strcat(command, target);
}

void build_command_target(unsigned char* target, int screen) {
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


