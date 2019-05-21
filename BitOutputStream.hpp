/*
 * Filename: BitOutputStream.hpp
 * Author: Ajay Nair
 * Userid: cs100sp19bg
 * Date: May 16, 2019
 * Description: Class definition for BitOutputStream. Contains declarations for
 *              all of its members.
 */
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
