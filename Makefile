# Makefile
# Build rules for EECS 280 project 3

# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

main.exe: main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump