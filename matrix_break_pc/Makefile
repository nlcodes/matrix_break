CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

BUILD_DIR = build
SRC_DIR = src
TARGET = $(BUILD_DIR)/bin

$(TARGET): $(SRC_DIR)/main.c 
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
