.PHONY: all cmake_debug cmake_release run_cmake debug prod run clean

CPP = g++
# Use CXXFLAGS for C++ instead of CFLAGS (which is for C)
CXXFLAGS = -Wall -Wextra -Wpedantic
CXXFLAGS_DEBUG = -g $(CXXFLAGS)
CXXFLAGS_PROD = -O2 $(CXXFLAGS)

# With CMAKE
CMAKE = cmake
DCMAKE_TOOLCHAIN_FILE = -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
# Configure with Debug flags (-g)
CMAKE_DEBUG = -DCMAKE_BUILD_TYPE=Debug ${DCMAKE_TOOLCHAIN_FILE}
# Configure with Release flags (-O2)
CMAKE_RELEASE = -DCMAKE_BUILD_TYPE=Release ${DCMAKE_TOOLCHAIN_FILE}

INCLUDE = -Iinclude
APP = student_management
BUILD_DIR = build

# Find all source files dynamically
SRCS = $(wildcard src/*.cpp)

# Default target if you just type 'make'
all: run_cmake

cmake_debug:
	${CMAKE} -B ${BUILD_DIR} -S . ${CMAKE_DEBUG} && cmake --build ${BUILD_DIR}

cmake_release:
	${CMAKE} -B ${BUILD_DIR} -S . ${CMAKE_RELEASE} && cmake --build ${BUILD_DIR}

run_cmake: cmake_debug
	./${BUILD_DIR}/${APP}

# Without cmake
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
