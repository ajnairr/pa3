#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "HCTree.hpp"

using namespace std;

vector<int> countFreqs(string inFile, ifstream& in) {
  vector<int> freqs = vector<int>(256, 0);
  int symbol;

  while(true) {
    symbol = in.get();
    if(in.eof()) {
      in.close();
      in.open(inFile, ios::binary);
      break;
    }
    freqs[symbol]++;
  }

  return freqs;
}

void writeHeader(ofstream& out, vector<int> freqs) {
  for(vector<int>::iterator it = freqs.begin(); it != freqs.end(); it++) {
    out << *it << endl;
  }
}

void encodeFile(ifstream& in, ofstream& out, HCTree& tree) {
  int symbol;
  while(true) {
    symbol = in.get();
    if(in.eof()) {
      in.close();
      break;
    }
    tree.encode((unsigned char)symbol, out);
  }
  out.close();
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

  vector<int> freqs = countFreqs(*(argv + 1), in);
  HCTree tree = HCTree();
  tree.build(freqs);

  ofstream out(*(argv + 2), ios::binary);

  writeHeader(out, freqs);
  encodeFile(in, out, tree);

  return EXIT_SUCCESS;
}
