#include "BitOutputStream.hpp"

BitOutputStream::BitOutputStream(std::ofstream* out) :
                                             buffer(0), bitIndex(0), out(out) {}

void BitOutputStream::flush() {
  this->out->put(static_cast<unsigned char>(this->buffer.to_ulong()));
  this->out->flush();

  this->buffer.reset();
  this->bitIndex = 0;
}

void BitOutputStream::writeBit(int bit) {
  if(this->bitIndex == 8) {
    this->flush();
  }

  this->buffer[this->bitIndex++] = bit;
}

void BitOutputStream::writeByte(int bite) {
  this->out->put((unsigned char)bite);
  this->out->flush();
}

void BitOutputStream::writeInt(int i) {
  this->out->write((char*)&i, sizeof i);
}
