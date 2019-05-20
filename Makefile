# A simple makefile for CSE 100 PA3

# We use this in order to feed in the correct version of g++
# (version 4.8) where it's installed under a different name in
# Gradescope. Change the CXX variable assignment at your own risk.
CXX ?= g++
CXXFLAGS=-std=c++11 -g -Wall
LDFLAGS=-g

all: compress uncompress

compress: HCNode.o HCTree.o BitInputStream.o BitOutputStream.o

uncompress: HCNode.o HCTree.o BitInputStream.o BitOutputStream.o

HCTree.o: HCTree.hpp

HCNode.o: HCNode.hpp

BitInputStream.o: BitInputStream.hpp

BitOutputStream.o: BitOutputStream.hpp

clean:
	rm -f compress uncompress *.o core* *~
