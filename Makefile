.PHONY: all debug prod run clean

CPP = g++
# Use CXXFLAGS for C++ instead of CFLAGS (which is for C)
CXXFLAGS = -Wall -Wextra -Wpedantic
CXXFLAGS_DEBUG = -g $(CXXFLAGS)
CXXFLAGS_PROD = -O2 $(CXXFLAGS)
INCLUDE = -Iinclude
APP = program
BUILD_DIR = build

# Find all source files dynamically
SRCS = $(wildcard src/*.cpp)

# Default target if you just type 'make'
all: debug

debug:
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CXXFLAGS_DEBUG) $(INCLUDE) $(SRCS) -o $(BUILD_DIR)/$(APP)

prod:
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CXXFLAGS_PROD) $(INCLUDE) $(SRCS) -o $(BUILD_DIR)/$(APP)

# Added 'debug' as a dependency so it compiles automatically if missing
run: debug
	./$(BUILD_DIR)/$(APP)

clean:
	rm -rf $(BUILD_DIR)
