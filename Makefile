CC := g++

CFLAGS := \
	-IInclude/ \
	-Wpedantic \
	-Werror \
	-Wformat \
	-Werror=format-security -g -O3 -Wall -std=c++17

SOURCES = $(wildcard src/*.cpp)
OBJ = ${SOURCES:.cpp=.o}

run: ${OBJ} main
	${CC} -o out main.o ${OBJ}

all: run
	./out ${ARGS}

main:
	${CC} ${CFLAGS} -c main.cpp -o main.o

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm out *.o src/*.o