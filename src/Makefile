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

debug: clean $(LIB)
	$(CC) $(CFLAGS) core/s21_calculate.c $(LIB) -lm -o debug
	./debug

valgrind: 
	make test
	$(CC) $(CFLAGS) -g tests/*.c $(LIB) $(TEST_FLAGS) -o test
	valgrind --leak-check=full --show-leak-kinds=all -s ./test

test: $(LIB)
	$(CC) $(CFLAGS) -g tests/*.c $(LIB) $(TEST_FLAGS) -o test
	./test

clean:
	rm -f $(LIB) $(CORE_OBJECTS) $(BACKEND_OBJECTS) test debug

rebuild: clean all
