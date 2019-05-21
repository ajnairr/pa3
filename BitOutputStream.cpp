/*
 * Filename: BitOutputStream.cpp
 * Author: Ajay Nair
 * Userid: cs100sp19bg
 * Date: May 16, 2019
 * Description: Definitions for BitOutputStream member functions.
 */
#include "BitOutputStream.hpp"

/*
 * Function Name: BitOutputStream()
 * Function Prototype: BitOutputStream(std::ofstream* out);
 * Description: Constructor for the BitOutputStream class
 * Parameters: out - Pointer to the output stream that this object will be
 *                   writing to.
 * Return Value: None
 */
BitOutputStream::BitOutputStream(std::ofstream* out) :
                                             buffer(0), bitIndex(0), out(out) {}

/*
 * Function Name: flush()
 * Function Prototype: void flush();
 * Description: Flushes output buffer by printing its contents to the output
 *              stream and then clearing and resetting the buffer.
 * Parameters: None
 * Return Value: None
 */
void BitOutputStream::flush() {
  this->out->put(this->buffer);
  this->out->flush();

  this->buffer = this->bitIndex = 0;
}

/*
 * Function Name: writeBit()
 * Function Prototype: void writeBit(int bit);
 * Description: Writes a single bit to the output buffer. Flushes the buffer
 *              when a full byte of data has been read into the buffer.
 * Parameters: bit - The value of the bit to write to the buffer.
 * Return Value: None
 */
void BitOutputStream::writeBit(int bit) {
  if(this->bitIndex == 8) {
    this->flush();
  }

  this->buffer |= ((unsigned int)bit) << this->bitIndex++;
}

/*
 * Function Name: writeByte()
 * Function Prototype: void writeByte(int bite);
 * Description: Writes a full byte of data to the output stream.
 * Parameters: bite - The byte to write to the output stream, provided as an
 *                    int.
 * Return Value: None
 */
void BitOutputStream::writeByte(int bite) {
  this->out->put((unsigned char)bite);
  this->out->flush();
}

/*
 * Function Name: writeInt()
 * Function Prototype: void writeInt(int i);
 * Description: Writes enough bytes to output stream to make up an int.
 * Parameters: i - the int to write to the output stream
 * Return Value: None
 */
void BitOutputStream::writeInt(int i) {
  this->out->write((char*)&i, sizeof i);
}
