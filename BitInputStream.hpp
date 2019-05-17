#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <fstream>

class BitInputStream {
  public:
    BitInputStream(std::ifstream* in);
    void fillBuffer();
    int readBit();
    int readByte();
    int readInt();

  private:
    unsigned char buffer;
    unsigned int bitIndex;
    std::ifstream* in;
};

#endif /** BITINPUTSTREAM_HPP **/
