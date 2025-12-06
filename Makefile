# Makefile
# CCOM 4997 - Final Project: Simple Search Engine
# Author: Alfredo Frontera
# Date: December 2025

CXX = g++
CXXFLAGS = -Wall -Wextra -O2

all: search_engine

search_engine: main.o SearchEngine.o ParsedFile.o
	$(CXX) $(CXXFLAGS) main.o SearchEngine.o ParsedFile.o -o search_engine

main.o: main.cpp SearchEngine.h ParsedFile.h
	$(CXX) $(CXXFLAGS) -c main.cpp

SearchEngine.o: SearchEngine.cpp SearchEngine.h ParsedFile.h
	$(CXX) $(CXXFLAGS) -c SearchEngine.cpp

ParsedFile.o: ParsedFile.cpp ParsedFile.h
	$(CXX) $(CXXFLAGS) -c ParsedFile.cpp

clean:
	rm -f search_engine *.o

run: search_engine
	./search_engine ./moviesdb

.PHONY: all clean run
