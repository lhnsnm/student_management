.PHONY: debug prod run clean

CPP = g++
CFLAGS = -Wall -Wextra -Wpedantic
CFLAGS_DEBUG = -g ${CFLAGS}
CFLAGS_PROD = -O2 ${CFLAGS}
APP = program
BUILD_DIR = build

debug:
	mkdir -p ${BUILD_DIR}
	${CPP} ${CFLAGS_DEBUG} src/*.cpp -o ${BUILD_DIR}/${APP}

prod:
	mkdir -p ${BUILD_DIR}
	${CPP} ${CFLAGS_PROD} src/*.cpp -o ${BUILD_DIR}/${APP}

run:
	./${BUILD_DIR}/${APP}

clean:
	rm -rf ${BUILD_DIR}
