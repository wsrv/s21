CC=gcc
WWW = -Wall -Wextra -Werror
CFLAGS= -c $(WWW) -std=c11  
FLAGS= -g $(WWW)
ADD_MATH_LIB = $(WWW) -lm

FILES = *.c
CHECK_F = tests/calc_complements.check tests/create_matrix.check tests/determinant.check tests/eq_matrix.check tests/inverse_matrix.check tests/mult_matrix.check tests/mult_number.check tests/sub_matrix.check tests/sum_matrix.check tests/transpose.check

TEST_FLAGS=-lcheck --coverage
TEST_FUNC= tests/s21_matrix_test.c

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm 
	OPEN = echo 'report: s21_matrix/src/report/index.html'
else
	OPEN=open ./report/index.html
endif

all: clean s21_matrix.a

clean:
	rm -rf *.o *.a *.out *.gcda *.info *.gcno tests/*.out greport s21_matrix.h.gch .clang-format report gcov */*.o test tests/s21_matrix_test.c

s21_matrix.a:
	$(CC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o

	ar rcs s21_matrix.a $(FILES:.c=.o)
	ranlib s21_matrix.a

gcov_report: clean check
	mkdir -p gcov
	gcc $(FILES) $(TEST_FUNC) -o gcov/greport $(TEST_FLAGS)
	./gcov/greport;
	lcov -t "s21_matrix" -o s21_matrix.info -c -d .
	genhtml -o ./report s21_matrix.info
	$(OPEN)


check:
	checkmk clean_mode=1 tests/header.check $(CHECK_F) > tests/s21_matrix_test.c

test: s21_matrix.a check
	$(CC) $(WWW) -std=c11  tests/s21_matrix_test.c s21_matrix.a -o test $(TEST_FLAGS)

valgrind: clean check s21_matrix.a test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes ./test

