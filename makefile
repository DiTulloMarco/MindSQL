
all: run

clear:
	rm -f out/mindsql

shell: clear 
	gcc -g -o out/mindsql src/shell.c src/shell_cmds/*.c

removo:
	rm -f out/*.o

run: shell removo
	./out/mindsql
