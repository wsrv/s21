CC=gcc
WWW = -Wall -Wextra -Werror
CFLAGS= -c $(WWW) -std=c11  
FLAGS= -g $(WWW)
ADD_MATH_LIB = $(WWW) -lm

FILES = support/*.c arithmetic/*.c comparison/*.c another/*.c converters/*.c

TEST_FLAGS=-lcheck --coverage
TEST_FUNC= tests/s21_decimal_test.c

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm 
	OPEN = echo 'report: C5_s21_decimal-2/src/report/index.html'
else
	OPEN=open ./report/index.html
endif

all: clean s21_decimal.a

clean:
	rm -rf *.o *.a *.out *.gcda *.info *.gcno tests/*.out greport s21_decimal.h.gch .clang-format report gcov */*.o test tests/s21_decimal_test.c

s21_decimal.a:
	$(CC) $(CFLAGS) -c arithmetic/s21_add.c -o arithmetic/s21_add.o
	$(CC) $(CFLAGS) -c arithmetic/s21_sub.c -o arithmetic/s21_sub.o
	$(CC) $(CFLAGS) -c arithmetic/s21_mul.c -o arithmetic/s21_mul.o
	$(CC) $(CFLAGS) -c arithmetic/s21_div.c -o arithmetic/s21_div.o

	$(CC) $(CFLAGS) -c comparison/s21_is_equal.c -o comparison/s21_is_equal.o
	$(CC) $(CFLAGS) -c comparison/s21_is_less.c -o comparison/s21_is_less.o
	$(CC) $(CFLAGS) -c comparison/s21_is_greater.c -o comparison/s21_is_greater.o
	
	$(CC) $(CFLAGS) -c another/s21_floor.c -o another/s21_floor.o
	$(CC) $(CFLAGS) -c another/s21_negate.c -o another/s21_negate.o
	$(CC) $(CFLAGS) -c another/s21_round.c -o another/s21_round.o
	$(CC) $(CFLAGS) -c another/s21_truncate.c -o another/s21_truncate.o

	$(CC) $(CFLAGS) -c converters/decimal_to_float.c -o converters/decimal_to_float.o
	$(CC) $(CFLAGS) -c converters/decimal_to_int.c -o converters/decimal_to_int.o
	$(CC) $(CFLAGS) -c converters/float_to_decimal.c -o converters/float_to_decimal.o
	$(CC) $(CFLAGS) -c converters/int_to_decimal.c -o converters/int_to_decimal.o

	$(CC) $(CFLAGS) -c support/support_functions.c -o support/support_functions.o
	ar rcs s21_decimal.a $(FILES:.c=.o)
	ranlib s21_decimal.a

gcov_report: clean check
	mkdir -p gcov
	gcc $(FILES) $(TEST_FUNC) -o gcov/greport $(TEST_FLAGS)
	./gcov/greport;
	lcov -t "s21_decimal" -o s21_decimal.info -c -d .
	genhtml -o ./report s21_decimal.info
	$(OPEN)

clang:
	clang-format -style="{BasedOnStyle: Google}" -n */*.c *.h

check:
	checkmk clean_mode=1 tests/headers.check tests/*/*.check > tests/s21_decimal_test.c

test: s21_decimal.a check
	$(CC) $(WWW) -std=c11  tests/s21_decimal_test.c s21_decimal.a -o test $(TEST_FLAGS)

valgrind: clean check s21_decimal.a test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes ./test