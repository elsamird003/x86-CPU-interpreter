CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Iinclude
LDFLAGS = -lm

TARGET = interpreter
SRCS   = src/main.c src/interpreter.c
OBJS   = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.c include/interpreter.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
