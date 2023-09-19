CFLAGS := -Wall -Wextra

.phony: all

all: MonitorControl.exe

MonitorControl.exe: main.c main.h io.c io.h
	gcc $^ $(CFLAGS) -o $@

debug: main.c main.h io.c io.h
	gcc $^ $(CFLAGS) -g3 -o debug.exe

clean:
	rm MonitorControl.exe
	rm debug.exe