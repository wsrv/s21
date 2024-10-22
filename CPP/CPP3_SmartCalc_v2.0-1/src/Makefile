CC= g++ -std=c++17   -Wall -Werror -Wextra
GTEST_FLAG = --gtest_repeat=1 --gtest_shuffle
TEST_FLAGS=-lgtest -pthread -lgtest_main -lstdc++ -lm
TEST_FUNC= test.cc ../Model/model.* ../Controller/*
PATH_TO_TEST = ./tests

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm
	GOALS = make test valgrind
else
	GOALS = make test clang
endif


all: install open

install:
	mkdir Calculator
	cp -r Controller Calculator/Controller
	cp -r Model Calculator/Model
	cd View; qmake -o ../Calculator/Makefile
	cd Calculator; make

uninstall:
	rm -rf Calculator

open:
	open Calculator/SmartCalc.app

dist:
	tar -czf SmartCalc.install.tar.gz ./* *.c *.h

dvi:
	open smartcalc.txt

valgrind: tests
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s ./$(PATH_TO_TEST)/tesst


clean:
	rm -rf tests/tesst

clang:
	clang-format -style="{BasedOnStyle: Google}" -n Controller/*.* Model/*.* View/graphwindow.* View/main*.* tests/test.*

tests: clean
	cd $(PATH_TO_TEST); $(CC) $(TEST_FUNC) -o tesst $(TEST_FLAGS); ./tesst $(GTEST_FLAG)
