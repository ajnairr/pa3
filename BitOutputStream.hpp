#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <fstream>

class BitOutputStream {
  public:
    BitOutputStream(std::ofstream* out);

    void flush();
    void writeBit(int bit);
    void writeByte(int bite);
    void writeInt(int i);

  private:
    unsigned char buffer;
    unsigned int bitIndex;
    std::ofstream* out;
};

#endif /** BITOUTPUTSTREAM_HPP **/
