CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = bin/my_shell

SRC = src/main.c \
      src/shell.c \
      src/parser.c \
      src/executor.c \
      src/builtin.c

OBJ = obj/main.o \
      obj/shell.o \
      obj/parser.o \
      obj/executor.o \
      obj/builtin.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
