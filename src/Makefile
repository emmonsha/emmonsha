CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -fno-omit-frame-pointer
CHECK_FLAGS = $(shell pkg-config --cflags --libs check) -lm

SRC = $(wildcard s21_*.c)
TEST_SRC = $(wildcard tests/*.c)

OBJ = $(patsubst %.c, %.o, $(SRC))
TEST_OBJ = $(patsubst tests/%.c, tests/obj/%.o, $(TEST_SRC))

all: clean s21_matrix.a

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

tests/obj/%.o: tests/%.c
		@mkdir -p tests/obj
		$(CC) $(CFLAGS) -c $< -o $@

s21_matrix.a: $(OBJ)
		ar rcs $@ $(OBJ)

clean: 
		rm -f *.o *.o *.a *.gcno *.gcda *.out *.info s21_test s21_gcov_test
		rm -rf ./report tests/obj

test: s21_matrix.a
		$(CC) $(CFLAGS) $(TEST_SRC) s21_matrix.a -o s21_test $(CHECK_FLAGS)
		./s21_test

clang-format:
		clang-format -i *.c *.h tests/*.c 

gcov_report_flags:
		@$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: gcov_report_flags 
		$(CC) $(CFLAGS) $(SRC) $(TEST_SRC) -o s21_gcov_test $(CHECK_FLAGS)
		./s21_gcov_test
		mkdir -p report
		lcov -t "s21_gcov_test" -o s21_test.info -c -d .
		genhtml -o report s21_test.info
		xdg-open report/index.html

.PHONY: test clang-format gcov_report