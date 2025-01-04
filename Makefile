# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -fPIC

# Define the library name and files
LIB_NAME = pixel
SRC_FILES = pixel.c
HDR_FILES = pixel.h
OBJ_FILES = $(SRC_FILES:.c=.o)
STATIC_LIB = lib$(LIB_NAME).a

# Define the installation directories
PREFIX = /usr/local
INCLUDE_DIR = $(PREFIX)/include
LIB_DIR = $(PREFIX)/lib

# Default target
all: static

# Compile the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the static library
static: $(OBJ_FILES)
	ar rcs $(STATIC_LIB) $(OBJ_FILES)

# Install the library and header file
install: static
	mkdir -p $(INCLUDE_DIR)
	mkdir -p $(LIB_DIR)
	cp $(HDR_FILES) $(INCLUDE_DIR)
	cp $(STATIC_LIB) $(LIB_DIR)

# Uninstall the library and header file
uninstall:
	rm -f $(INCLUDE_DIR)/$(LIB_NAME).h
	rm -f $(LIB_DIR)/$(STATIC_LIB)

# Clean up the build files
clean:
	rm -f $(OBJ_FILES) $(STATIC_LIB)

.PHONY: all static install uninstall clean
