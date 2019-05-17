#include "BitInputStream.hpp"

BitInputStream::BitInputStream(std::ifstream* in) :
                                               buffer(0), bitIndex(8), in(in) {}

void BitInputStream::fillBuffer() {
  this->buffer = this->in->get();
  this->bitIndex = 0;
}

int BitInputStream::readBit() {
  if(this->bitIndex == 8)
    this->fillBuffer();

  return (int)(!!((this->buffer >> this->bitIndex++) & 1));
}

int BitInputStream::readByte() {
  unsigned char byteRead = this->in->get();

  return (!this->in->eof()) ? byteRead : -1;
}

int BitInputStream::readInt() {
  int intRead;

  this->in->read((char*)&intRead, sizeof intRead);

  return (!this->in->eof()) ? intRead : -1;
}
