/*
 * Filename: compress.cpp
 * Author: Ajay Nair
 * Userid: cs100sp19bg
 * Date: May 13, 2019
 * Description: Program that can create a compressed/encoded version of any file
 *              passed as an argument
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "HCTree.hpp"

using namespace std;

vector<int> countFreqs(string inFile, ifstream& in, int* count, int* numUniq) {
  vector<int> freqs = vector<int>(256, 0);
  int symbol = -1;

  do{
    if(symbol >= 0 && freqs[symbol]++ == 0) {
      ++*numUniq;
    }
    symbol = in.get();
    ++*count;
  } while(!in.eof());

  --*count;

  in.clear();
  in.seekg(0, ios::beg);

  return freqs;
}

void encodeFile(ifstream& in, BitOutputStream& out, HCTree* tree) {
  int symbol = -1;

  do {
    if(symbol >= 0)
      tree->encode((unsigned char)symbol, out);

    symbol = in.get();
  } while(!in.eof());

  out.flush();
}

int main(int argc, char** argv) {
  if(argc != 3) {
    cout << "Invalid number of arguments." << endl;
    cout << "Usage: " << *argv << " <infile filename> <outfile filename>"
                                                                        << endl;
    return EXIT_FAILURE;
  }

  ifstream in(*(argv + 1), ios::binary);

  if(in.fail()) {
    cout << "Invalid input file. Please try again." << endl;
    return EXIT_FAILURE;
  }

  in.clear();
  in.seekg(0, ios::end);

  // case if input file is empty: creates an empty output file
  if(in.tellg() == 0) {
    in.close();

    ofstream out(*(argv + 2), ios::binary); 
    out.close();

    return EXIT_SUCCESS;
  }
  in.clear();
  in.seekg(0, ios::beg);
  ofstream out(*(argv + 2), ios::binary);
  int fileSize = 0;
  int uniqueChars = 0;

  // store frequencies of each character in a vector
  vector<int> freqs = countFreqs(*(argv + 1), in, &fileSize, &uniqueChars);
  BitOutputStream bitOut(&out);
  HCTree* tree = new HCTree();

  // build new HCTree with read frequencies
  tree->build(freqs);

  // write file header for decoder to interpret
  bitOut.writeInt(fileSize); // save count of chars contained in input
  bitOut.writeInt(uniqueChars); // save count of unique chars contained in input
  tree->saveTree(&bitOut); // save data on tree leaf nodes

  // find and print the size of the file header written to the compressed file
  ifstream* headerRead = new ifstream(*(argv + 2), ios::binary | ios::ate);
  cout << "Header size is: " << (size_t)headerRead->tellg() << " bytes" << endl;
  headerRead->close();
  delete headerRead;

  encodeFile(in, bitOut, tree);

  delete tree;
  in.close();
  out.close();

  return EXIT_SUCCESS;
}
