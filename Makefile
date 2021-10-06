CC = clang
CFLAGS = -Wall -Wextra  -Werror  -Wpedantic

all: sorting

sorting: sorting.o 
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o stack.o queue.o set.o

sorting.o: 
	$(CC) $(CFLAGS) -c sorting.c bubble.c shell.c quick.c stack.c queue.c set.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f sorting sorting.o bubble.o shell.o quick.o stack.o queue.o set.o

scan-build: clean
	scan-build make
