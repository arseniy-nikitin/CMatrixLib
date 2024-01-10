CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm

CHECK_SRC=./tests/test_*.check
TEST_SRC=./tests/test_*.c

DIR=./base_operations/ \
	./arithmetic/        \
	./another/
SRC=$(foreach dir,$(DIR),$(wildcard $(dir)*.c))
OBJ=$(patsubst %.c,%.o,$(SRC))

MSG=Minor bug fixes
BRANCH=$(shell git branch --show-current)

OS:=$(shell uname -s)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

.PHONY: test_s21_matrix.c s21_matrix.a

all:
	make test

rebuild:
	make clean
	make all

style:
	clang-format -n $(SRC) *.h

clean:
	make clean_obj
	make clean_test
	make clean_gcov
	rm -rf *.a *.dSYM ./tests/test_*.c


test_s21_matrix.c: $(CHECK_SRC)
	checkmk clean_mode=1 $(CHECK_SRC) > ./tests//$@

s21_matrix.a: $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	make clean_obj

clean_obj:
	rm -rf $(OBJ)

test: test_s21_matrix.c s21_matrix.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) ${TEST_SRC} s21_matrix.a -o unit_test -lcheck -lm
else
	$(CC) $(CFLAGS) ${TEST_SRC} s21_matrix.a -o unit_test -lcheck $(LINUX_FLAGS)
endif
	./unit_test

clean_test:
	rm -rf unit_test

# If lcov cause errors add "--filter range" after --no-external flag, works only in MAC
gcov_report: test
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o gcov_test -lcheck -lm
else
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o gcov_test -lcheck $(LINUX_FLAGS)
endif
	./gcov_test
	lcov -t "stest" -o s21_test.info --no-external -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

clean_gcov:
	rm -rf *.gcda *.gcno *.info report gcov_test

push:
ifeq ($(BRANCH), develop)
	git add $(DIR) 
else
	git add $(BRANCH)
endif
	git add Makefile tests s21_matrix.h .clang-format
	git commit -m "$(BRANCH): $(MSG)"
	git push origin $(BRANCH)

gitback:
	git stash save --keep-index
