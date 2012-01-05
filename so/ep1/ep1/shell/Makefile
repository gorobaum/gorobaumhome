

SRC_DIR = src
OBJ_DIR = .temp
OUTPUT_DIR = bin
OBJS = .temp/dirmanager.o .temp/shell.o .temp/main.o .temp/file.o .temp/aux.o\
	   .temp/command.o
OUTPUT = bin/ep1

CXX = g++
CXXFLAGS = -ansi -pedantic -Wall -lncurses -Isrc/

all: ep1

$(OBJ_DIR):
	mkdir $@

$(OUTPUT_DIR):
	mkdir $@

.temp/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

.temp/aux.o: src/aux.cpp src/aux.h
.temp/command.o: src/command.cpp src/shell.h src/dirmanager.h src/command.h \
 src/aux.h
.temp/dirmanager.o: src/dirmanager.cpp src/dirmanager.h src/file.h src/aux.h
.temp/file.o: src/file.cpp src/file.h
.temp/main.o: src/main.cpp src/shell.h src/dirmanager.h src/command.h
.temp/shell.o: src/shell.cpp src/shell.h src/dirmanager.h src/command.h \
 src/file.h src/aux.h

ep1: $(OBJ_DIR) $(OUTPUT_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(OUTPUT)

.PHONY: debug
debug: CXXFLAGS += -g
debug: ep1

.PHONY: clean
clean:
	rm -rf $(OUTPUT)
	rm -rf $(OBJ_DIR)




