CC = g++
CPPFLAGS = -lgtest -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra
TEST_FLAGS=-lcheck --coverage

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm 
	OPEN = echo 'report: s21_matrix/src/report/index.html'
else
	OPEN=open ./report/index.html
endif


all: clean s21_matrix_oop.a

test: 
	@${CC} tests.cpp s21_matrix_oop.cpp ${CHECKFLAGS} ${CPPFLAGS} -o tests
	@./tests

%.o: %.cpp
	@${CC} -std=c++17 ${CHECKFLAGS} -c $^

%.a: %.o
	@ar rcs $@ $^
	@ranlib $@

clean:
	@/bin/rm -rf *.o *.a tests *.gcno *gcda report *.info tests *.out

style:
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.cpp

leaks: test
	CK_FORK=no leaks --atExit -- ./tests