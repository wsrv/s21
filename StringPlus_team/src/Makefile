CC=gcc
CFLAGS= -c -Wall -Wextra -Werror -std=c11  
FLAGS= -g -Wall -Wextra -Werror
FILES = s21_string.c s21_sprintf.c
TEST_FLAGS=-lcheck --coverage
TEST_FUNC= string_tests.c


OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lm
	OPEN=echo 'report: C4_s21_math-1/src/report/index.html'
else
	OPEN=open ./report/index.html
endif

all: clean s21_string.a

clean:
	rm -rf *.o *.a *.out *.gcda *.gcno *.info s21_string rezult greport test_my_func s21_string.h.gch .clang-format index.css index.html report gcov

s21_string.a: $(FILES)
	$(CC) $(CFLAGS) $^
	ar -rcs s21_string.a $(FILES:.c=.o)

gcov_report:
	mkdir -p gcov
	gcc $(FLAGS) $(FILES) $(TEST_FUNC) -o gcov/greport $(TEST_FLAGS) 
	./gcov/greport
	lcov -t "s21_sprintf" -o s21_sprintf.info -c -d .
	genhtml -o ./report s21_sprintf.info
	$(OPEN)

test: check clean

check:
	cp -f ../materials/linters/.clang-format ./.clang-format
	clang-format -n *.c *.h
	$(CC) $(СFLAGS) $(FILES) $(TEST_FUNC) -lm -lcheck -pthread -o tests
	./tests

my: clean s21_string.a
	$(CC) $(FLAGS) test_func.c s21_string.a -o test_func
	echo
	./test_func
