all: Aitken.c
		gcc -Wall -o bin $^
clean:
		rm bin