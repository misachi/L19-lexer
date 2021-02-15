CC := g++

CFLAGS := \
	-IInclude/ \
	-Wpedantic \
	-Werror \
	-Wformat \
	-Werror=format-security -g -O1 -Wall -std=c++17

SOURCES = $(wildcard src/*.cpp)
OBJ = ${SOURCES:.cpp=.o}

all: run
	./a.out ${ARGS}

run: ${OBJ} main
	${CC} -o a.out main.o ${OBJ}

main:
	${CC} ${CFLAGS} -c main.cpp -o main.o

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm *.out *.o src/*.o