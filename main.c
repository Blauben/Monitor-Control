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
        const int csize = LINE_LENGTH + 500;
        char command[csize];
        memset(command,'\0', csize);
        build_command(command, i, monitors);
        printf("Execute:     %s\n",command);
        system(command);
    }
    freeTargets();
    return EXIT_SUCCESS;
}

void build_command(char* str, int screen, const bool *monitors) {
    command* target = build_command_target(screen);
    sprintf(str, "%s %s\n", targets->lib, monitors[screen]?target->on:target->off);
}

command* build_command_target(int screen) {
    switch (screen) {
        case 0:
            return targets->primary;
            break;
        case 1:
            return targets->secondary;
            break;
        default:
            return targets->tertiary;
            break;
    }
}


