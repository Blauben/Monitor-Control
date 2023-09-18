/*
 * main.h
 *
 *  Created on: 23.04.2022
 *      Author: Balthazar
 */

#ifndef MAIN_H_
#define MAIN_H_

static int exec();
int* def_enum();
static char* build_command(int);
static char* build_command_target(int);

static int monitors[3] = {0,0,0};
static int values[]= def_enum();

enum screens {PRIMARY=values[0], SECONDARY=values[1], TERTIARY=values[2]};

typedef enum screens screens;
typedef struct FILE FILE;

#endif /* MAIN_H_ */
