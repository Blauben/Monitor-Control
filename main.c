#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "io.h"

int main(int argc, char **argv)
{
    initScreenTargets();
    bool monitors[] = {false, false, false};
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-1") == 0)
        {
            monitors[0] = true;
        }
        else if (strcmp(argv[i], "-2") == 0)
        {
            monitors[1] = true;
        }
        else if (strcmp(argv[i], "-3") == 0)
        {
            monitors[2] = true;
        }
        else if (strcmp(argv[i], "-off") == 0)
        {
            monitors[0] = monitors[1] = monitors[2] = false;
            break;
        }
    }
    if (argc == 1)
    {
        args_from_cli(monitors);
    }
    for (int i = 0; i < 3; i++)
    {
        char command[LINE_LENGTH];
        memset(command, '\0', LINE_LENGTH);
        build_command(command, i, monitors);
        printf("Execute:     %s\n", command);
        int code = system(command);
        printf("%s\n\n", code == 0 ? "Successful" : "Failed");
    }
    freeTargets();
    Sleep(5000);
    return EXIT_SUCCESS;
}

void build_command(char *str, int screen, const bool *monitors)
{
    command *target = build_command_target(screen);
    sprintf(str, "%s %s", targets->lib, monitors[screen] ? target->on : target->off);
}

command *build_command_target(int screen)
{
    switch (screen)
    {
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
