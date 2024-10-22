CC=gcc
WWW = -Wall -Wextra -Werror
CFLAGS= -c -std=c11  
FLAGS= -g $(WWW)
ADD_MATH_LIB = $(WWW) -lm

FILES = *.c

TEST_FLAGS=-lcheck --coverage
TEST_FUNC= back/tests/my_test.c

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm
	OPEN = echo 'report: C5_calc-2/src/report/index.html'
	DOX = echo 'you must install doxygen'
else
	OPEN=open ./report/index.html
	DOX =brew install doxygen
endif

all: install gcov_report clang

install:
	mkdir -p 3D_Viewer
	cd front/Viewer; qmake -o ../../3D_Viewer/Makefile
	cd 3D_Viewer; make

installDox:
	$(DOX)

uninstall:
	rm -rf 3D_Viewer

open:
	open 3D_Viewer/Viewer.app

dist: install
	tar -czf 3D_Viewer.install.tar.gz front back 3D_Viewer

dvi: clean
	doxygen Doxyfile
	open html/index.html

clean:
	rm -rf *.a *.o report gcov test *.gcno *.gcda html $(TEST_FUNC) front/build-Viewer-Desktop_x86_darwin_generic_mach_o_64bit-Debug

transformations.a:
	$(CC) $(CFLAGS) -c back/*.c 
	ar rcs transformations.a $(FILES:.c=.o)
	ranlib transformations.a
	rm *.o

gcov_report: clean check
	mkdir -p gcov
	$(CC) back/*.c $(TEST_FUNC) -o gcov/greport $(TEST_FLAGS)
	./gcov/greport;
	lcov -t "Viewer" -o Viewer.info -c -d .
	genhtml -o ./report Viewer.info
	$(OPEN)
	rm *.gcda *.gcno *.o *.info

clang:
	clang-format -style="{BasedOnStyle: Google}" -n back/*.c back/*.h front/Viewer/*.h front/Viewer/*.cpp back/tests/*.check

goclang:
	clang-format -style="{BasedOnStyle: Google}" -i back/*.c back/*.h front/Viewer/*.h front/Viewer/*.cpp back/tests/*.check

check:
	checkmk clean_mode=1 back/tests/headers.check back/tests/*.check > $(TEST_FUNC)

test: clean transformations.a check
	$(CC) -std=c11  $(TEST_FUNC) transformations.a -o test $(TEST_FLAGS)
	./test

mytest: goclang clean uninstall install open

valgrind: clean check transformations.a test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s ./test