CFLAGS := -Wall -Wextra

.phony: all

all: MonitorControl

MonitorControl: main.c main.h io.c io.h
	gcc $^ $(CFLAGS) -o $@

debug: main.c main.h io.c io.h
	gcc $^ $(CFLAGS) -g3 -o debug

clean:
	rm MonitorControl
	rm debug