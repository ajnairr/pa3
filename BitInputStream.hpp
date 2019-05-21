/*
 * Filename: BitInputStream.hpp
 * Author: Ajay Nair
 * Userid: cs100sp19bg
 * Date: May 16, 2019
 * Description: Contains class definition for BitInputStream, with declarations
 *              for all of its members.
 */

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
