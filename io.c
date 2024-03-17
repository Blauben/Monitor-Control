#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

#define LINE_COUNT 7

screens *targets;

void *mallocWrapper(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        fprintf(stderr, "Malloc failed!\n");
        exit(1);
    }
    return ptr;
}

const char *commands[LINE_COUNT] = {"/enable /TurnOn 1 /SetMonitors \"Name=MONITOR\\PHLC161\\{4d36e96e-e325-11ce-bfc1-08002be10318}\\0001 Primary=1 PositionX=0 PositionY=0",
                                    "/TurnOff 1", "/enable /TurnOn 2 /SetMonitors \"Name=MONITOR\\PHLC208\\{4d36e96e-e325-11ce-bfc1-08002be10318}\\0002 PositionX=4294965376 PositionY=0",
                                    "/TurnOff 2", "/enable /TurnOn 3", "/disable 3", "F:\\Programme\\multimonitortool\\MultiMonitorTool.exe"};
void initScreenTargets()
{
    targets = malloc(sizeof(screens));
    targets->primary = mallocWrapper(sizeof(command));
    targets->secondary = mallocWrapper(sizeof(command));
    targets->tertiary = mallocWrapper(sizeof(command));
    targets->primary->on = commands[0];
    targets->primary->off = commands[1];
    targets->secondary->on = commands[2];
    targets->secondary->off = commands[3];
    targets->tertiary->on = commands[4];
    targets->tertiary->off = commands[5];
    targets->lib = commands[6];
}

void freeTargets()
{
    free(targets->primary);
    free(targets->secondary);
    free(targets->tertiary);
    free(targets);
}

void extract_indices(char *buf, bool *monitors)
{
    char *num_str = strtok(buf, " ");
    while (num_str != NULL)
    {
        char **err = NULL;
        unsigned long index = strtol(num_str, err, 10);
        if (num_str != NULL && err == NULL && index > 0 && index <= 3)
        {
            monitors[index - 1] = true;
        }
        num_str = strtok(NULL, " ");
    }
}

void args_from_cli(bool *monitors)
{
    printf("Please enter the indices (primary 1, secondary 2, tertiary 3) of the monitors to be switched on, the others will be turned off!\n");
    const int buf_size = 100;
    char buf[buf_size];
    memset(buf, '\0', buf_size);
    fgets(buf, buf_size, stdin);
    extract_indices(buf, monitors);
}