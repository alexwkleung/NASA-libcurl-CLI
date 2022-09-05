CXX = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -g -I/usr/local/Cellar/curl/7.85.0/include
LDFLAGS = -L/usr/local/Cellar/curl/7.85.0/lib -lcurl

VAR = src/main.cpp src/options.cpp src/back.cpp src/nasa.cpp
OUT = src/a.o

.PHONY: build
build:
	${CXX} ${CPPFLAGS} ${LDFLAGS} ${VAR} -o ${OUT} 

.PHONY: clean
clean:
	rm ${OUT}
