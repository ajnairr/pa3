/*
 * Filename: BitInputStream.cpp
 * Author: Ajay Nair
 * Userid: cs100sp19bg
 * Date: May 16, 2019
 * Description: Definitions for BitInputStream member functions
 */
#include "BitInputStream.hpp"

/*
 * Function Name: BitInputStream()
 * Function Prototype: BitInputStream(std::ifstream* in);
 * Description: Constructor for BitInputStream class.
 * Parameters: in - pointer to input stream that this BitInputStream will read
 *                  from
 * Return Value: None
 */
BitInputStream::BitInputStream(std::ifstream* in) :
                                               buffer(0), bitIndex(8), in(in) {}

void BitInputStream::fillBuffer() {
  this->buffer = this->in->get();
  this->bitIndex = 0;
}

/*
 * Function Name: readBit()
 * Function Prototype: int readBit();
 * Description: Reads one bit from the input stream buffer. Clears and refills
 *              the input buffer if all bits have been read from it.
 * Parameters: None
 * Return Value: The bit read from the input stream buffer casted as an int.
 */
int BitInputStream::readBit() {
  if(this->bitIndex == 8)
    this->fillBuffer();

  return (int)(!!((this->buffer >> this->bitIndex++) & 1));
}

/*
 * Function Name: readByte()
 * Function Prototype: int readByte();
 * Description: Reads a full byte from the input stream and returns it as an
 *              int.
 * Parameters: None
 * Return Value: The byte read from the input stream casted as an int.
 */
int BitInputStream::readByte() {
  return (unsigned char)this->in->get();
}

/*
 * Function Name: readInt()
 * Function Prototype: int readInt();
 * Description: Reads enough bytes from the input stream to make up an int and
 *              then returns it all as an int.
 * Parameters: None
 * Return Value: The int read from the input stream.
 */
int BitInputStream::readInt() {
  int intRead;
  this->in->read((char*)&intRead, sizeof intRead);

  return intRead;
}
