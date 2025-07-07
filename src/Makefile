# Реализация Makefile @emmonsha

# text colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NO_COLOR = \033[0m

# флаги 
CC = gcc
GCC_FLAGS = -Wall -Werror -Wextra
CL_11 = -std=c11
SAN_FLAGS = -g -fsanitize=address,undefined,leak
VALGRIND_FLAGS = --tool=memcheck --leak-check=yes --show-leak-kinds=all --verbose
AR = ar rcs
CHECK_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
TEST_FLAGS = $(GCC_FLAGS) $(CL_11)
COVERAGE =

# источники
LIB_SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(LIB_SRC))
TEST_SRC = $(wildcard ./tests/*.c)
TEST_HEADER = $(wildcard tests/*.h)

LIB_NAME = s21_matrix.a

all: clean build_o s21_matrix.a

build_o:
		$(CC) -c $(TEST_FLAGS) $(COVERAGE) $(CHECK_FLAGS) $(LIB_SRC) 

s21_matrix.a: clean build_o
				
		$(AR) $@ $(OBJ)
		rm -rf $(OBJ)

clean:
	rm -rf *.gcda *.gcdo *.gcno *.a *.o \
		*.png *.css *.html *.info test gcov_report \
		tests/*.gcda tests/*.gcdo tests/*.gcno tests/*.html \
		*.txt

test: clean build_o s21_matrix.a countdown
	
	$(CC) $(TEST_FLAGS) $(TEST_SRC) $(COVERAGE) $(LIB_NAME) $(CHECK_FLAGS) -o $@ -g
	@echo "$(GREEN)=== запуск тестов ===$(NO_COLOR)"
	./test
	@echo "$(GREEN)+====================+$(NO_COLOR)"

test_sanitizer: clean asan build_o s21_matrix.a

asan: 

	$(eval TEST_FLAGS += $(SAN_FLAGS))

gcov_report: clean coverage test_sanitizer test 


# @echo "$(GREEN)=== запуск тестов ===$(NO_COLOR)"
# ./test
# @echo "$(GREEN)+====================+$(NO_COLOR)"
	mkdir -p gcov_report
	lcov  -o gcov_report/report.info -c -d .
	lcov --remove gcov_report/report.info '*/tests/*' --output-file gcov_report/report.info
	genhtml -o gcov_report gcov_report/report.info
	xdg-open gcov_report/index.html
	rm -rf *.gcda *.gcno *.gcdo *.o

	
coverage:

	$(eval COVERAGE += --coverage)
	
style:
	cp ../materials/linters/.clang-format ../src/
	clang-format -n $(LIB_SRC) $(HEADER) $(TEST_SRC) $(TEST_HEADER)
	rm -rf .clang-format

format_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -i $(LIB_SRC) $(HEADER) $(TEST_SRC) $(TEST_HEADER)
	rm -rf .clang-format


valgrind: test

	valgrind  $(VALGRIND_FLAGS) --log-file=valgrind_log.txt ./test
	@tail -n 16 valgrind_log.txt

countdown:

	@echo "$(YELLOW)До запуска тестов$(RED)"
	@for i in $$(seq 3 -1 1); do \
		echo "$$i..."; \
		sleep 1; \
	done
	@echo "$(YELLOW)Внимание$(NO_COLOR)"
	

.PHONY: all test clean gcov_report countdown valgrind