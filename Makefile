CC := g++

# Output of /usr/bin/python3.7-config --cflags
# -specs=/usr/share/dpkg/no-pie-compile.specs flag removed as it doesn't exist
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