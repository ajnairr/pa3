#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <utility>
#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

typedef vector<pair<byte, int>> tree_data;

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
  in.close();

  in.open(*(argv + 1), ios::binary | ios::ate);
  if(in.tellg() == 0) {
    ofstream out(*(argv + 2), ios::binary);
    in.close();
    out.close();

    return EXIT_SUCCESS;
  }
  in.close();


  in.open(*(argv + 1), ios::binary);
  ofstream out(*(argv + 2), ios::binary);
  BitInputStream bitIn(&in);
  BitOutputStream bitOut(&out);

  int fileSize = bitIn.readInt();
  int numSymbols = bitIn.readInt();

  tree_data ordered(numSymbols, make_pair(0, 0));

  for(tree_data::iterator it = ordered.begin(); it != ordered.end(); it++) {
    (*it).first = bitIn.readByte();
    (*it).second = bitIn.readByte();
  }

  HCTree tree(ordered);
  for(int i = 0; i < fileSize; i++) {
    bitOut.writeByte((unsigned char)tree.decode(bitIn));
  }

  out.close();
  in.close();

  return EXIT_SUCCESS;
}
