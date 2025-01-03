CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

BUILD_DIR = build
SRC_DIR = src
TARGET = $(BUILD_DIR)/bin
SOURCES = $(wildcard) $(SRC_DIR)/*.c

$(TARGET): $(SRC_DIR)/main.c 
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
