# A simple makefile for CSE 100 P2

# We use this in order to feed in the correct version of g++
# (version 4.8) where it's installed under a different name in
# Gradescope. Change the CXX variable assignment at your own risk.
CXX ?= g++
CXXFLAGS=-std=c++11 -g -Wall
LDFLAGS=-g

all: compress uncompress

compress: HCTree.o

uncompress: HCTree.o

HCTree.o: HCTree.hpp

clean:
	rm -f compress uncompress *.o core* *~
