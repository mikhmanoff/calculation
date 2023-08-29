CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -std=c11
CORE_DIR = core
BACKEND_DIR = backend
CORE_SOURCES = $(wildcard $(CORE_DIR)/*.c)
BACKEND_SOURCES = $(wildcard $(BACKEND_DIR)/*.c)
CORE_OBJECTS = $(CORE_SOURCES:.c=.o)
BACKEND_OBJECTS = $(BACKEND_SOURCES:.c=.o)
LIB = libs21_calc_core.a
TEST_FLAGS = -lcheck $(shell pkg-config --cflags --libs check)
TEX_FILE = calc_doc
LATEX_COMPILER = latex
LATEX_FLAGS = -interaction=nonstopmode
USERNAME = $(shell whoami)

ifeq ($(shell uname), Linux)
	TST_LIBS += -lpthread -lrt -lsubunit
endif

.PHONY: all debug clean

all: clean $(LIB)

$(LIB): $(CORE_OBJECTS) $(BACKEND_OBJECTS)
	ar rc $(LIB) $(CORE_OBJECTS) $(BACKEND_OBJECTS)
	ranlib $(LIB)

$(CORE_DIR)/%.o: $(CORE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BACKEND_DIR)/%.o: $(BACKEND_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format; \
	clang-format -style=Google -n backend/*.c core/*.c SmartCalc/core/*.c SmartCalc/backend/*.c; \
	rm .clang-format

change_clang:
	cp ../materials/linters/.clang-format ../src/.clang-format; \
	clang-format -style=Google -i backend/*.c core/*.c SmartCalc/core/*.c SmartCalc/backend/*.c; \
	rm .clang-format

debug: clean $(LIB)
	$(CC) $(CFLAGS) core/s21_calculate.c $(LIB) -lm -o debug
	./debug

valgrind: 
	make test
	$(CC) $(CFLAGS) -g tests/*.c $(LIB) $(TEST_FLAGS) -o test
	valgrind --leak-check=full --show-leak-kinds=all -s ./test

build: $(LIB)
	@mkdir -p build-SmartCalc-Desktop
	@cd build-SmartCalc-Desktop/ && qmake ../SmartCalc/ && make
	@./build-SmartCalc-Desktop/SmartCalc

test: $(LIB)
	$(CC) $(CFLAGS) -g tests/*.c $(LIB) $(TEST_FLAGS) -o test
	./test

add_coverage_flag: 
	$(eval CFLAGS += --coverage)

gcov_report: add_coverage_flag test
#	rm test-*
	lcov -t “gcov_test” -o test.info --rc lcov_branch_coverage=1 --no-external -c -d .
	genhtml -o report/ test.info --rc lcov_branch_coverage=1
	open ./report/index.html

clean_gcov_report:
	rm -rf *.gcno *.gcda *.gcov *.info report \
	core/*.gcno core/*.gcda core/*.gcov core/*.info report \
	backend/*.gcno backend/*.gcda backend/*.gcov backend/*.info report

uninstall:
	@rm -rf build-SmartCalc-Desktop

clean: uninstall clean_gcov_report
	rm -f $(LIB) $(CORE_OBJECTS) $(BACKEND_OBJECTS) test debug

rebuild: clean all
