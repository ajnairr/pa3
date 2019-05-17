#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <fstream>
#include <bitset>

class BitOutputStream {
  public:
    BitOutputStream(std::ofstream* out);

    void flush();
    void writeBit(int bit);
    void writeByte(int bite);
    void writeInt(int i);

  private:
    std::bitset<8> buffer;
    int bitIndex;
    std::ofstream* out;
};

#endif /** BITOUTPUTSTREAM_HPP **/
