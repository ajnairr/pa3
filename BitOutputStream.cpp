#include "BitOutputStream.hpp"

BitOutputStream::BitOutputStream(std::ofstream* out) :
                                             buffer(0), bitIndex(0), out(out) {}

void BitOutputStream::flush() {
  this->out->put(this->buffer);
  this->out->flush();

  this->buffer = this->bitIndex = 0;
}

void BitOutputStream::writeBit(int bit) {
  if(this->bitIndex == 8) {
    this->flush();
  }

  this->buffer |= ((unsigned int)bit) << this->bitIndex++;
}

void BitOutputStream::writeByte(int bite) {
  this->out->put((unsigned char)bite);
  this->out->flush();
}

void BitOutputStream::writeInt(int i) {
  this->out->write((char*)&i, sizeof i);
}
