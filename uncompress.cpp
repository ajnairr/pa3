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
  in.clear();

  in.seekg(0, ios::end);
  if(in.tellg() == 0) {
    in.close();

    ofstream out(*(argv + 2), ios::binary);
    out.close();

    return EXIT_SUCCESS;
  }
  in.clear();

  in.seekg(0, ios::beg);
  ofstream out(*(argv + 2), ios::binary);
  BitInputStream bitIn(&in);
  BitOutputStream bitOut(&out);

  int fileSize = bitIn.readInt();
  int numSymbols = bitIn.readInt();

  tree_data treeData(numSymbols, make_pair(0, 0));

  for(tree_data::iterator it = treeData.begin(); it != treeData.end(); it++) {
    (*it).first = bitIn.readByte();
    (*it).second = bitIn.readByte();
  }

  HCTree* tree = new HCTree(treeData);
  for(int i = 0; i < fileSize; i++) {
    bitOut.writeByte((unsigned char)tree->decode(bitIn));
  }

  delete tree;
  out.close();
  in.close();

  return EXIT_SUCCESS;
}
