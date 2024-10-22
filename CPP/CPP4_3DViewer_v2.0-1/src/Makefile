# CC=g++ -Wall -Werror -Wextra -std=c++17
CC=g++ -std=c++17
TEST_FLAGS=-lgtest -pthread -lgtest_main -lstdc++ -lm
GTEST_FLAG = --gtest_repeat=10 --gtest_shuffle
TEST_FUNC= test.cc
PATH_TO_TEST = Tests

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm
	GOALS =  clang valgrind
else
	GOALS =  clang
endif

all: clean library tests check_cppcheck
	make $(GOALS)

install:
	mkdir -p Viewer
	cd View; qmake -o ../Viewer/Makefile
	cd Viewer; make
	make open

uninstall:
	rm -rf Viewer

dvi:
	doxygen Doxyfile
	open html/index.html

dist:
	tar -czf 3DViewer.install.tar.gz ./* */*.cc */*.h

clean:
	cd tests; find . -type f  ! -name "*.cc" ! -name "*.h" ! -name "*.cpp" ! -name "*.ui" ! -name "*.pro" | xargs rm -rf
	ls | grep -vxe "Makefile" -e "Controller" -e "Model" -e "View" -e "Tests" -e "ObjectFile" -e "Doxyfile" | xargs rm -rf

library:
	$(CC) -c Model/Model.cc
	ar rc libModel.a *.o
	ranlib libModel.a
	rm *.o

tests: library
	cd $(PATH_TO_TEST);rm -f test; $(CC) $(TEST_FUNC) ../libModel.a -o test $(TEST_FLAGS); ./test $(GTEST_FLAG); pwd

clang:
	find . -type f  -name "*.cc" -o -name "*.h" -o -name "*.cpp" | xargs clang-format -Werror -style="google" -n

goclang:
	find . -type f  -name "*.cc" -o -name "*.h" -o -name "*.cpp" | xargs clang-format -Werror -style="google" -i

valgrind: tests
	cd $(PATH_TO_TEST); CK_FORK=no valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s ./test

gcov_report: library
	cd $(PATH_TO_TEST); $(CC)  -g --coverage $(TEST_FUNC) ../libModel.a -o ../gcov_report  $(TEST_FLAGS); pwd
	cd $(PATH_TO_TEST); ../gcov_report
	lcov -t "report" -o s21_test.info -c -d ./ --no-external --ignore-errors mismatch
	genhtml -o report s21_test.info
	open ./report/index.html


check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config */*.h tests/*.cc

open:
	open Viewer/View.app

linux:
	sudo apt-get update
	sudo apt-get upgrade -y
	sudo apt-get install valgrind -y
	sudo apt-get install libgtest-dev libgmock-dev -y
	sudo apt install g++ -y

dox: clean
	brew install doxygen

push: clean goclang
	git add .
	git commit -m "$(c)"
	git push --set-upstream origin develop

.PHONY: linux clean clang goclang tests valgrind check_cppcheck push gcov_report library doxygen