CC      = gcc
CXX     = g++
CFLAGS  = -std=c11 -Wall -Wextra -Iinclude
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = -lm

TARGET = interpreter
SRCS   = src/main.c src/interpreter.c
OBJS   = $(SRCS:.c=.o)

TEST_TARGET = unit_tests
TEST_SRC    = tests/unit_tests.cpp
TEST_LIBS   = -lgtest -lgtest_main -lpthread

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.c include/interpreter.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Unit tests: link interpreter logic (not main.c) with Google Test
$(TEST_TARGET): $(TEST_SRC) src/interpreter.o
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRC) src/interpreter.o $(TEST_LIBS) $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(TEST_TARGET)
