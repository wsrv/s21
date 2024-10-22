CC=gcc
CFLAGS= -Wall -Wextra -Werror
all: clean style s21_grep test

s21_grep: 
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test:
	sh tests.sh 

clean:
	rm -rf *.out s21_grep

style:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i *.c
	rm -f .clang-format
