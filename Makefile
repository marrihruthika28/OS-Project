CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = processpulse

SRC = src/main.c \
      src/process.c \
      src/process_manager.c \
      src/monitor.c \
      src/history.c \
      src/statistics.c \
      src/ui.c \
      src/lab.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
