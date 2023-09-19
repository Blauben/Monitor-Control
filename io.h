/*
 * io.h
 *
 *  Created on: 24.04.2022
 *      Author: Balthazar
 */

#ifndef IO_H_
#define IO_H_

#include <stdbool.h>

#define LINE_LENGTH 30

struct screens {
    char* primary;
    char* secondary;
    char* tertiary;
    char* lib;
};
typedef struct screens screens;
extern screens* targets;

void initScreenTargets();
void args_from_cli(bool*);
void freeTargets();

#endif /* IO_H_ */
