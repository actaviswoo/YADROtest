# Compiler
CC 				= g++

# Compiler flags
CFLAGS 			= -Wextra -Wall -Werror
CPPFLAGS 		= -std=c++17
TESTFLAGS		= -lgtest -lgtest_main -fsanitize=address

# Directories
MODELDIR 		= model
BUILDDIR 		= build
TESTDIR 		= tests

# Source files
SRC_MAIN		= main.cc 
SRC_MODEL 		= $(MODELDIR)/Parcer/Parcer.cc \
				  $(MODELDIR)/Handler/Handler.cc \
				  $(MODELDIR)/Format/Format.cc
SRC_TEST 		= $(TESTDIR)/main_test.cc \
				  $(TESTDIR)/parcer_test.cc \
				  $(TESTDIR)/handler_test.cc \
				  $(TESTDIR)/format_test.cc 

# Main executable
MAIN 			= $(BUILDDIR)/task.exe

# Test executable
TEST 			= $(BUILDDIR)/test

# Targets
.PHONY: all clean run

main: 
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(MAIN) $(SRC_MAIN) $(SRC_MODEL)

test:
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(TEST) $(SRC_TEST) $(SRC_MODEL) $(TESTFLAGS)
	./$(TEST)

all: clean main

clean:
	rm -rf $(BUILDDIR)