#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <fstream>
#include <bitset>

class BitInputStream {
  public:
    BitInputStream(std::ifstream* in);
    void fillBuffer();
    int readBit();
    int readByte();
    int readInt();

  private:
    std::bitset<8> buffer;
    int bitIndex;
    std::ifstream* in;
};

#endif /** BITINPUTSTREAM_HPP **/
