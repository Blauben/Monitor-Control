/*
 * io.h
 *
 *  Created on: 24.04.2022
 *      Author: Balthazar
 */

#ifndef IO_H_
#define IO_H_

#include <stdbool.h>

#define LINE_LENGTH 1024

struct command {
    char* on;
    char* off;
};
typedef struct command command;
struct screens {
    command* primary;
    command* secondary;
    command* tertiary;
    char* lib;
};
typedef struct screens screens;
extern screens* targets;

void initScreenTargets();
void args_from_cli(bool*);
void freeTargets();

#endif /* IO_H_ */
