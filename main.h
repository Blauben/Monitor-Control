/*
 * main.h
 *
 *  Created on: 23.04.2022
 *      Author: Balthazar
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>
#include "io.h"

void build_command(char*, int, const bool*);
command* build_command_target(int);

#endif /* MAIN_H_ */
