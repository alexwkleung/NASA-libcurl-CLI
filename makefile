CXX = g++
LDFLAGS = -L/usr/local/Cellar/curl/7.85.0/lib -lcurl
CPPFLAGS = -std=c++17 -Wall -Wextra -g -I/usr/local/Cellar/curl/7.85.0/include

VAR = src/main.cpp src/options.cpp src/back.cpp src/apod.cpp
OUT = src/a.o

.PHONY: build
build:
	${CXX} ${LDFLAGS} ${CPPFLAGS} ${VAR} -o ${OUT} && ./${OUT} && rm ${OUT}