#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int main(int argc, char **argv) {

	for (int i = 1; i < argc; i++) {
		switch (**argv) {
		case "primary":
			monitors[0] = 1;
			break;
		case "secondary":
			monitors[1] = 1;
			break;
		case "tertiary":
			monitors[2] = 1;
			break;
		default: break;
		}
	}
	return exec();
}



static int exec() {
	for(int i=0; i<3; i++) {
		system(build_command(i));
	}
	return EXIT_SUCCESS;
}

static char* build_command(int screen) {
		char* exe= "F:\\Programme\\multimonitortool_1.96\\MultiMonitorTool.exe ";
		const char* on= "/TurnOn ";
		const char* off= "/disable ";
		char * target = build_command_target(screen);
		return strcat(strcat(exe, monitors[screen]==1?on:off),target);
}

static char* build_command_target(int screen) {
	screens target;
	char* dest;
	switch (screen) {
	case 0: target=PRIMARY;
	break;
	case 1: target=SECONDARY;
	break;
	case 2: target=TERTIARY;
	break;
	default: return  NULL;
	}
	sprintf(dest, "%u", target);
	return dest;
	}


