# Compiler
CC 				= g++

# Compiler flags
CFLAGS 			= -Wextra -Wall -Werror
CPPFLAGS 		= -std=c++17
TESTFLAGS		= -lgtest -lgtest_main -lpthread
# TSANFLAGS		= -fsanitize=thread 

# Directories
MODELDIR 		= model
BUILDDIR 		= build
TESTDIR 		= tests

# Source files
SRC_MAIN		= main.cc 
SRC_MODEL 		= $(MODELDIR)/Model.cc \
           		  $(MODELDIR)/Parcer/Parcer.cc
SRC_TEST 		= $(TESTDIR)/main_test.cc

# Main executable
MAIN 			= $(BUILDDIR)/main

# Test executable
TEST 			= $(BUILDDIR)/test

# Targets
.PHONY: all clean run

main:
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(MAIN) $(SRC_MAIN) $(SRC_MODEL)
	./$(MAIN)

test:
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(test) $(SRC_TEST) $(SRC_MODEL)
	./$(TEST)

all: clean main

clean:
	rm -rf $(BUILDDIR)