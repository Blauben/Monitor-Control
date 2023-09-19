/*
 * io.h
 *
 *  Created on: 24.04.2022
 *      Author: Balthazar
 */

#ifndef IO_H_
#define IO_H_

#define LINE_LENGTH 30

struct screens {
    char* primary;
    char* secondary;
    char* tertiary;
};
typedef struct screens screens;
extern screens targets;

void initScreenTargets();

#endif /* IO_H_ */
