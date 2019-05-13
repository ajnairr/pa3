#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "HCTree.hpp"

using namespace std;

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

  ofstream out(*(argv + 2), ios::binary);
  in.open(*(argv + 1), ios::binary | ios::ate);
  if(in.tellg() == 0) {
    out.close();

    return EXIT_SUCCESS;
  }

  in.close();
  in.open(*(argv + 1), ios::binary);

  vector<int> freq = vector<int>(256, 0);
  int numBytes = 0;
  int bytesWritten = 0;

  for(unsigned int i = 0; i < freq.size(); i++) {
    in >> freq[i];
    numBytes += freq[i];
  }

  HCTree tree = HCTree();
  tree.build(freq);

  while(bytesWritten++ < numBytes)
    out << (unsigned char)tree.decode(in);

  out.close();
  in.close();
  
  return EXIT_SUCCESS;
}
