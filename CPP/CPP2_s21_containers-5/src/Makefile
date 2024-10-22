CC=g++ -std=c++17 -Wall -Werror -Wextra
FILES = s21_map
TEST_FLAGS=-lgtest -pthread -lgtest_main -lstdc++ -lm
GTEST_FLAG = --gtest_repeat=1 --gtest_shuffle
TEST_FUNC= map_tests.cc vector_tests.cc list_tests.cc queue_tests.cc stack_tests.cc array_tests.cc set_tests.cc multiset_tests.cc   
PATH_TO_TEST = ./tests

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	TEST_FLAGS += -lsubunit -lrt -lm
	GOALS = make test valgrind
else
	GOALS = make test clang
endif

all: 
	$(GOALS)

installVal:
	sudo apt-get update
	sudo apt-get upgrade -y
	sudo apt-get install valgrind -y
	sudo apt-get install libgtest-dev libgmock-dev -y
	sudo apt install g++ -y

clean:
	rm -rf *.a */*.a *.o *.info */*.o */*.out */test report gcov *.gcno *.gcda $(PATH_TO_TEST)/*.gcno $(PATH_TO_TEST)/*.gcda html gcov_report $(PATH_TO_TEST)/*.info gcov_report.dSYM .DS_Store

test: clean
	cd $(PATH_TO_TEST); $(CC) $(TEST_FUNC) -o test $(TEST_FLAGS); ./test $(GTEST_FLAG)

clang:
	clang-format -style="{BasedOnStyle: Google}" -n */*.h */*.inc */*.cc

goclang:
	clang-format -style="{BasedOnStyle: Google}" -i */*.h */*.inc */*.cc

valgrind: test
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes --track-origins=yes  -s ./$(PATH_TO_TEST)/test

push: clean goclang
	git add .
	git commit -m "$(c)"
	git push

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config */*.h tests/*.cc

gcov_report:
	cd $(PATH_TO_TEST); $(CC)  -g --coverage $(TEST_FUNC) -o ../gcov_report  $(TEST_FLAGS)
	cd ..
	./gcov_report 
	lcov -t "stest" -o s21_test.info -c -d ./ --no-external  --ignore-errors mismatch
	genhtml  --no-function-coverage -o report s21_test.info 
	open ./report/index.html
	
.PHONY: installVal clean clang goclang test valgrind check_cppcheck push gcov_report leaks
