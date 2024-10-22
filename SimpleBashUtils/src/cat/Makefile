CC=gcc
CFLAGS= -Wall -Wextra -Werror
all: clean style s21_cat test

s21_cat: 
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test:
	sh tests.sh 

clean:
	rm -rf *.out s21_cat

style:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i *.c
	rm -f .clang-format